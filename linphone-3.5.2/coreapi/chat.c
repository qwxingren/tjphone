/***************************************************************************
 *            chat.c
 *
 *  Sun Jun  5 19:34:18 2005
 *  Copyright  2005  Simon Morlat
 *  Email simon dot morlat at linphone dot org
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
 #include "linphonecore.h"
 #include "private.h"
 
 LinphoneChatRoom * linphone_core_create_chat_room(LinphoneCore *lc, const char *to){
	LinphoneAddress *parsed_url=NULL;

	if ((parsed_url=linphone_core_interpret_url(lc,to))!=NULL){
		LinphoneChatRoom *cr=ms_new0(LinphoneChatRoom,1);
		cr->lc=lc;
		cr->op=NULL;
		cr->tobedestroy=FALSE;
		cr->peer=linphone_address_as_string(parsed_url);
		cr->peer_url=parsed_url;
		lc->chatrooms=ms_list_append(lc->chatrooms,(void *)cr);
		return cr;
	}
	return NULL;
 }
 
 void linphone_chat_room_set_tobedestroy(LinphoneChatRoom *cr, bool_t tobedestroy){
	cr->tobedestroy = tobedestroy;
 }

void linphone_chat_room_destroy(LinphoneChatRoom *cr){
	SalOp *op;
	MSList *elem;
	linphone_address_destroy(cr->peer_url);
	ms_free(cr->peer);
	if (cr->op){
		for(elem=cr->op;elem!=NULL;elem=ms_list_next(elem)){
			op=(SalOp *)elem->data;
			if (op){
				 sal_op_release(op);
			}
		}
	}
	ms_list_free(cr->op);
	ms_free(cr);
 }
 
 void linphone_chat_room_remove(LinphoneChatRoom *cr){
	LinphoneCore *lc=cr->lc;
	lc->chatrooms=ms_list_remove(lc->chatrooms,(void *) cr);
	linphone_chat_room_destroy(cr);
 }
 
const char* linphone_chat_room_send_message(LinphoneChatRoom *cr, const char *msg){
	const char *route=NULL;
	const char *message_id=NULL;
	const char *identity=linphone_core_find_best_identity(cr->lc,cr->peer_url,&route);
	SalOp *op=NULL;
#if 0
	LinphoneCall *call;
	if((call = linphone_core_get_call_by_remote_address(cr->lc,cr->peer))!=NULL){
		if (call->state==LinphoneCallConnected ||
		    call->state==LinphoneCallStreamsRunning ||
		    call->state==LinphoneCallPaused ||
		    call->state==LinphoneCallPausing ||
		    call->state==LinphoneCallPausedByRemote){
			ms_message("send SIP message through the existing call.");
			op = call->op;
		}
	}
#endif
	if (op==NULL){
		/*sending out of calls*/
		op = sal_op_new(cr->lc->sal);
		sal_op_set_route(op,route);
		ms_list_append(cr->op, op);
	}
	sal_text_send(op,identity,cr->peer,msg);
	sal_op_get_callid(op, &message_id);
	return message_id;
}

bool_t linphone_chat_room_matches(LinphoneChatRoom *cr, const LinphoneAddress *from){
	if (linphone_address_get_username(cr->peer_url) && linphone_address_get_username(from) && 
		strcmp(linphone_address_get_username(cr->peer_url),linphone_address_get_username(from))==0) return TRUE;
	return FALSE;
}

void linphone_chat_room_text_received(LinphoneChatRoom *cr, LinphoneCore *lc, const LinphoneAddress *from, const char *msg){
	if (lc->vtable.text_received!=NULL) lc->vtable.text_received(lc, cr, from, msg);
}

void linphone_core_text_status(SalOp *op,const char *from, const char *callid,bool_t status)
{
	MSList *elem;
	LinphoneChatRoom *cr=NULL;
	LinphoneAddress *addr;
	char *cleanfrom;
	LinphoneCore *lc=NULL;
	SalOp *chroomop=NULL;
	if(op){
		lc=(LinphoneCore *)sal_get_user_pointer(sal_op_get_sal(op));
	}

	addr=linphone_address_new(from);
	linphone_address_clean(addr);
	if(!lc) return;
	for(elem=lc->chatrooms;elem!=NULL;elem=ms_list_next(elem)){
		cr=(LinphoneChatRoom*)elem->data;
		if (linphone_chat_room_matches(cr,addr)){
			break;
		}
		cr=NULL;
	}
	cleanfrom=linphone_address_as_string(addr);
	if(cr && cr->op){
			ms_list_remove(cr->op, op);
			sal_op_release(op);
			if(cr->tobedestroy && ms_list_size(cr->op)==0){
				linphone_chat_room_remove(cr);				
			}
	} else {
		/* create a new chat room */
		cr=linphone_core_create_chat_room(lc,cleanfrom);
	}
	linphone_address_destroy(addr);

	if (lc->vtable.text_status!=NULL) lc->vtable.text_status(lc, cr, cr->peer_url, callid, status);
}

void linphone_core_text_received(LinphoneCore *lc, const char *from, const char *msg){
	MSList *elem;
	LinphoneChatRoom *cr=NULL;
	LinphoneAddress *addr;
	char *cleanfrom;

	addr=linphone_address_new(from);
	linphone_address_clean(addr);
	for(elem=lc->chatrooms;elem!=NULL;elem=ms_list_next(elem)){
		cr=(LinphoneChatRoom*)elem->data;
		if (linphone_chat_room_matches(cr,addr)){
			break;
		}
		cr=NULL;
	}
	cleanfrom=linphone_address_as_string(addr);
	if (cr==NULL){
		/* create a new chat room */
		cr=linphone_core_create_chat_room(lc,cleanfrom);
	}

	linphone_address_destroy(addr);
	linphone_chat_room_text_received(cr,lc,cr->peer_url,msg);
	ms_free(cleanfrom);
}


void linphone_chat_room_set_user_data(LinphoneChatRoom *cr, void * ud){
	cr->user_data=ud;
}
void * linphone_chat_room_get_user_data(LinphoneChatRoom *cr){
	return cr->user_data;
}
const LinphoneAddress* linphone_chat_room_get_peer_address(LinphoneChatRoom *cr) {
	return cr->peer_url;
}
