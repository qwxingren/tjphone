/*
linphone, gtk-glade interface.
Copyright (C) 2009  Simon MORLAT (simon.morlat@linphone.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
/*
*  C Implementation: incall_frame
*
* Description: 
*
*
* Author: Simon Morlat <simon.morlat@linphone.org>, (C) 2009
*
*
*/

#include "linphone.h"


gboolean linphone_gtk_use_in_call_view(){
	static int val=-1;
	if (val==-1) val=linphone_gtk_get_ui_config_int("use_incall_view",1);
	return val;
}

LinphoneCall *linphone_gtk_get_currently_displayed_call(gboolean *is_conf){
	LinphoneCore *lc=linphone_gtk_get_core();
	GtkWidget *main_window=linphone_gtk_get_main_window ();
	GtkNotebook *notebook=(GtkNotebook *)linphone_gtk_get_widget(main_window,"viewswitch");
	const MSList *calls=linphone_core_get_calls(lc);
	if (is_conf) *is_conf=FALSE;
	if (!linphone_gtk_use_in_call_view() || ms_list_size(calls)==1){
		if (calls) return (LinphoneCall*)calls->data;
	}else{
		int idx=gtk_notebook_get_current_page (notebook);
		GtkWidget *page=gtk_notebook_get_nth_page(notebook,idx);
		if (page!=NULL){
			LinphoneCall *call=(LinphoneCall*)g_object_get_data(G_OBJECT(page),"call");
			if (call==NULL){
				if (page==g_object_get_data(G_OBJECT(main_window),"conference_tab")){
					if (is_conf)
						*is_conf=TRUE;
					return NULL;
				}
			}
			return call;
		}
	}
	return NULL;
}

static GtkWidget *make_tab_header(int number){
	GtkWidget *w=gtk_hbox_new (FALSE,0);
	GtkWidget *i=create_pixmap ("status-green.png");
	GtkWidget *l;
	gchar *text=g_strdup_printf(_("Call #%i"),number);
	l=gtk_label_new (text);
	gtk_box_pack_start (GTK_BOX(w),i,FALSE,FALSE,0);
	gtk_box_pack_end(GTK_BOX(w),l,TRUE,TRUE,0);
	gtk_widget_show_all(w);
	return w;
}

static void linphone_gtk_in_call_set_animation_image(GtkWidget *callview, const char *image_name, gboolean is_stock){
	GtkWidget *container=linphone_gtk_get_widget(callview,"in_call_animation");
	GList *elem=gtk_container_get_children(GTK_CONTAINER(container));
	GtkWidget *image;
	
	if (!is_stock){
		if (image_name==NULL){
			gtk_widget_hide(container);
		}
		image=create_pixmap(image_name);
	}else
		image=gtk_image_new_from_stock(image_name,GTK_ICON_SIZE_DIALOG);
	if (elem)
		gtk_widget_destroy((GtkWidget*)elem->data);
	gtk_widget_show(image);
	gtk_container_add(GTK_CONTAINER(container),image);
	gtk_widget_show_all(container);
}

static void linphone_gtk_in_call_set_animation_spinner(GtkWidget *callview){
#if GTK_CHECK_VERSION(2,20,0)
	GtkWidget *container=linphone_gtk_get_widget(callview,"in_call_animation");
	GList *elem=gtk_container_get_children(GTK_CONTAINER(container));
	GtkWidget *spinner=gtk_spinner_new();
	if (elem)
		gtk_widget_destroy((GtkWidget*)elem->data);
	gtk_widget_show(spinner);
	gtk_container_add(GTK_CONTAINER(container),spinner);
	gtk_widget_set_size_request(spinner, 20,20);
	gtk_spinner_start(GTK_SPINNER(spinner));
#endif
}


static void linphone_gtk_transfer_call(LinphoneCall *dest_call){
	LinphoneCall *call=linphone_gtk_get_currently_displayed_call(NULL);
	if (call) linphone_core_transfer_call_to_another(linphone_gtk_get_core(),call,dest_call);
}

static void transfer_button_clicked(GtkWidget *button, gpointer call_ref){
	GtkWidget *menu_item;
	GtkWidget *menu=gtk_menu_new();
	LinphoneCall *call=(LinphoneCall*)call_ref;
	LinphoneCore *lc=linphone_gtk_get_core();
	const MSList *elem=linphone_core_get_calls(lc);
	
	for(;elem!=NULL;elem=elem->next){
		LinphoneCall *other_call=(LinphoneCall*)elem->data;
		GtkWidget *call_view=(GtkWidget*)linphone_call_get_user_pointer(other_call);
		if (other_call!=call){
			int call_index=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(call_view),"call_index"));
			char *remote_uri=linphone_call_get_remote_address_as_string (other_call);
			char *text=g_strdup_printf(_("Transfer to call #%i with %s"),call_index,remote_uri);
			menu_item=gtk_image_menu_item_new_with_label(text);
			ms_free(remote_uri);
			g_free(text);
			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_item),create_pixmap("status-green.png"));
			gtk_widget_show(menu_item);
			gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);
			g_signal_connect_swapped(G_OBJECT(menu_item),"activate",(GCallback)linphone_gtk_transfer_call,other_call);
		}
	}
	gtk_menu_popup(GTK_MENU(menu),NULL,NULL,NULL,NULL,0,
		gtk_get_current_event_time());
	gtk_widget_show(menu);
}



void linphone_gtk_enable_transfer_button(LinphoneCore *lc, gboolean value){
	const MSList *elem=linphone_core_get_calls(lc);
	for(;elem!=NULL;elem=elem->next){
		LinphoneCall *call=(LinphoneCall*)elem->data;
		GtkWidget *call_view=(GtkWidget*)linphone_call_get_user_pointer(call);
		GtkWidget *box=linphone_gtk_get_widget (call_view,"mute_pause_buttons");
		GtkWidget *button=(GtkWidget*)g_object_get_data(G_OBJECT(box),"transfer");
		if (button && value==FALSE){
			gtk_widget_destroy(button);
			button=NULL;
		}else if (!button && value==TRUE){
			button=gtk_button_new_with_label (_("Transfer"));
			//gtk_button_set_image_position(GTK_BUTTON(button),GTK_POS_BOTTOM);
			gtk_button_set_image(GTK_BUTTON(button),gtk_image_new_from_stock (GTK_STOCK_GO_FORWARD,GTK_ICON_SIZE_BUTTON));
			g_signal_connect(G_OBJECT(button),"clicked",(GCallback)transfer_button_clicked,call);
			gtk_widget_show_all(button);
			gtk_container_add(GTK_CONTAINER(box),button);
		}
		g_object_set_data(G_OBJECT(box),"transfer",button);
	}
}

static void conference_button_clicked(GtkWidget *button, gpointer call_ref){
	linphone_core_add_all_to_conference(linphone_gtk_get_core());
	//linphone_core_add_to_conference(linphone_gtk_get_core(),(LinphoneCall*)call_ref);
	gtk_widget_set_sensitive(button,FALSE);
}

void linphone_gtk_enable_conference_button(LinphoneCore *lc, gboolean value){
	const MSList *elem=linphone_core_get_calls(lc);
	for(;elem!=NULL;elem=elem->next){
		LinphoneCall *call=(LinphoneCall*)elem->data;
		GtkWidget *call_view=(GtkWidget*)linphone_call_get_user_pointer(call);
		GtkWidget *box=linphone_gtk_get_widget (call_view,"mute_pause_buttons");
		GtkWidget *button=(GtkWidget*)g_object_get_data(G_OBJECT(box),"conference");
		if (button && value==FALSE){
			gtk_widget_destroy(button);
			button=NULL;
		}else if (!button && value==TRUE){
			button=gtk_button_new_with_label (_("Conference"));
			//gtk_button_set_image_position(GTK_BUTTON(button),GTK_POS_BOTTOM);
			gtk_button_set_image(GTK_BUTTON(button),gtk_image_new_from_stock (GTK_STOCK_ADD,GTK_ICON_SIZE_BUTTON));
			g_signal_connect(G_OBJECT(button),"clicked",(GCallback)conference_button_clicked,call);
			gtk_widget_show_all(button);
			gtk_container_add(GTK_CONTAINER(box),button);
		}
		g_object_set_data(G_OBJECT(box),"conference",button);
	}
}

void linphone_gtk_create_in_call_view(LinphoneCall *call){
	GtkWidget *call_view=linphone_gtk_create_widget("main","in_call_frame");
	GtkWidget *main_window=linphone_gtk_get_main_window ();
	GtkNotebook *notebook=(GtkNotebook *)linphone_gtk_get_widget(main_window,"viewswitch");
	static int call_index=1;
	int idx;

	if (ms_list_size(linphone_core_get_calls(linphone_gtk_get_core()))==1){
		/*this is the only call at this time */
		call_index=1;
	}
	g_object_set_data(G_OBJECT(call_view),"call",call);
	g_object_set_data(G_OBJECT(call_view),"call_index",GINT_TO_POINTER(call_index));

	linphone_call_set_user_pointer (call,call_view);
	linphone_call_ref(call);
	gtk_notebook_append_page (notebook,call_view,make_tab_header(call_index));
	gtk_widget_show(call_view);
	idx = gtk_notebook_page_num(notebook, call_view);
	gtk_notebook_set_current_page(notebook, idx);
	call_index++;
	linphone_gtk_enable_hold_button (call,FALSE,TRUE);
	linphone_gtk_enable_mute_button(
					GTK_BUTTON(linphone_gtk_get_widget(call_view,"incall_mute")),FALSE);
}

G_MODULE_EXPORT 
void linphone_gtk_remove_in_call_view(LinphoneCall *call){
	GtkWidget *w=(GtkWidget*)linphone_call_get_user_pointer (call);
	GtkWidget *main_window=linphone_gtk_get_main_window ();
	GtkWidget *nb=linphone_gtk_get_widget(main_window,"viewswitch");
	gboolean in_conf=linphone_call_params_local_conference_mode(linphone_call_get_current_params(call));
	int idx;
	g_return_if_fail(w!=NULL);
	idx=gtk_notebook_page_num(GTK_NOTEBOOK(nb),w);
	gtk_notebook_remove_page (GTK_NOTEBOOK(nb),idx);
	gtk_widget_destroy(w);
	if (in_conf){
		linphone_gtk_unset_from_conference(call);
	}
	linphone_call_set_user_pointer (call,NULL);
	linphone_call_unref(call);
	call=linphone_core_get_current_call(linphone_gtk_get_core());
	if (call==NULL){
		if (linphone_core_is_in_conference(linphone_gtk_get_core())){
			/*show the conference*/
			gtk_notebook_set_current_page(GTK_NOTEBOOK(nb),gtk_notebook_page_num(GTK_NOTEBOOK(nb),
		                            g_object_get_data(G_OBJECT(main_window),"conference_tab")));
		}else gtk_notebook_set_current_page(GTK_NOTEBOOK(nb), 0);
	}else{
		/*show the active call*/
		gtk_notebook_set_current_page(GTK_NOTEBOOK(nb),gtk_notebook_page_num(GTK_NOTEBOOK(nb),
		                                                                     linphone_call_get_user_pointer(call)));
	}
}

static void display_peer_name_in_label(GtkWidget *label, const LinphoneAddress *from){
	const char *displayname=NULL;
	const char *id;
	char *uri_label;
	displayname=linphone_address_get_display_name(from);
	id=linphone_address_as_string_uri_only(from);
	
	if (displayname!=NULL){
		uri_label=g_markup_printf_escaped("<span size=\"large\">%s</span>\n<i>%s</i>", 
			displayname,id);
	}else
		uri_label=g_markup_printf_escaped("<span size=\"large\"><i>%s</i></span>\n",id);
	gtk_label_set_markup(GTK_LABEL(label),uri_label);
	g_free(uri_label);
}

G_MODULE_EXPORT 
void linphone_gtk_in_call_view_set_calling(LinphoneCall *call){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *status=linphone_gtk_get_widget(callview,"in_call_status");
	GtkWidget *callee=linphone_gtk_get_widget(callview,"in_call_uri");
	GtkWidget *duration=linphone_gtk_get_widget(callview,"in_call_duration");
	
	gtk_label_set_markup(GTK_LABEL(status),_("<b>Calling...</b>"));
	display_peer_name_in_label(callee,linphone_call_get_remote_address (call));
	
	gtk_label_set_text(GTK_LABEL(duration),_("00::00::00"));
	linphone_gtk_in_call_set_animation_spinner(callview);
}

G_MODULE_EXPORT 
void linphone_gtk_in_call_view_set_incoming(LinphoneCall *call){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *status=linphone_gtk_get_widget(callview,"in_call_status");
	GtkWidget *callee=linphone_gtk_get_widget(callview,"in_call_uri");
	GtkWidget *answer_button;
	GtkWidget *image;

	gtk_label_set_markup(GTK_LABEL(status),_("<b>Incoming call</b>"));
	gtk_widget_show_all(linphone_gtk_get_widget(callview,"answer_decline_panel"));
	gtk_widget_hide(linphone_gtk_get_widget(callview,"mute_pause_buttons"));
	display_peer_name_in_label(callee,linphone_call_get_remote_address (call));

	answer_button=linphone_gtk_get_widget(callview,"accept_call");
	image=create_pixmap (linphone_gtk_get_ui_config("start_call_icon","startcall-green.png"));
	gtk_button_set_label(GTK_BUTTON(answer_button),_("Answer"));
	gtk_button_set_image(GTK_BUTTON(answer_button),image);
	gtk_widget_show(image);
	
	image=create_pixmap (linphone_gtk_get_ui_config("stop_call_icon","stopcall-red.png"));
	gtk_button_set_image(GTK_BUTTON(linphone_gtk_get_widget(callview,"decline_call")),image);
	gtk_widget_show(image);
	
	linphone_gtk_in_call_set_animation_image(callview,GTK_STOCK_DIALOG_INFO,TRUE);
}

static void rating_to_color(float rating, GdkColor *color){
	const char *colorname="grey";
	if (rating>=4.0)
		colorname="green";
	else if (rating>=3.0)
		colorname="white";
	else if (rating>=2.0)
		colorname="yellow";
	else if (rating>=1.0)
		colorname="orange";
	else if (rating>=0)
		colorname="red";
	if (!gdk_color_parse(colorname,color)){
		g_warning("Fail to parse color %s",colorname);
	}
}

static const char *rating_to_text(float rating){
	if (rating>=4.0)
		return _("good");
	if (rating>=3.0)
		return _("average");
	if (rating>=2.0)
		return _("poor");
	if (rating>=1.0)
		return _("very poor");
	if (rating>=0)
		return _("too bad");
	return _("unavailable");
}

static gboolean linphone_gtk_in_call_view_refresh(LinphoneCall *call){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *qi=linphone_gtk_get_widget(callview,"quality_indicator");
	float rating=linphone_call_get_current_quality(call);
	GdkColor color;
	gchar tmp[50];
	linphone_gtk_in_call_view_update_duration(call);
	if (rating>=0){
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(qi),rating/5.0);
		snprintf(tmp,sizeof(tmp),"%.1f (%s)",rating,rating_to_text(rating));
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(qi),tmp);
	}else{
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(qi),0);
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(qi),_("unavailable"));
	}
	rating_to_color(rating,&color);
	gtk_widget_modify_bg(qi,GTK_STATE_NORMAL,&color);
	return TRUE;
}



typedef struct _volume_ctx{
	GtkWidget *widget;
	get_volume_t get_volume;
	void *data;
	float last_value;
}volume_ctx_t;

#define UNSIGNIFICANT_VOLUME (-26)
#define SMOOTH 0.15

static gboolean update_audio_meter(volume_ctx_t *ctx){
	float volume_db=ctx->get_volume(ctx->data);
	float frac=(volume_db-UNSIGNIFICANT_VOLUME)/(float)(-UNSIGNIFICANT_VOLUME+3.0);
	if (frac<0) frac=0;
	if (frac>1.0) frac=1.0;
	if (frac<ctx->last_value){
		frac=(frac*SMOOTH)+(ctx->last_value*(1-SMOOTH));
	}
	ctx->last_value=frac;
	//g_message("volume_db=%f, frac=%f",volume_db,frac);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ctx->widget),frac);
	return TRUE;
}

static void on_audio_meter_destroy(guint task_id){
	g_source_remove(task_id);
}

void linphone_gtk_init_audio_meter(GtkWidget *w, get_volume_t get_volume, void *data){
	guint task_id=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(w),"task_id"));
	if (task_id==0){
		volume_ctx_t *ctx=g_new(volume_ctx_t,1);
		ctx->widget=w;
		ctx->get_volume=get_volume;
		ctx->data=data;
		ctx->last_value=0;
		g_object_set_data_full(G_OBJECT(w),"ctx",ctx,g_free);
		task_id=g_timeout_add(50,(GSourceFunc)update_audio_meter,ctx);
		g_object_set_data_full(G_OBJECT(w),"task_id",GINT_TO_POINTER(task_id),(GDestroyNotify)on_audio_meter_destroy);
	}
}

void linphone_gtk_uninit_audio_meter(GtkWidget *w){
	guint task_id=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(w),"task_id"));
	if (task_id!=0){
		g_object_set_data(G_OBJECT(w),"ctx",NULL);
		g_object_set_data(G_OBJECT(w),"task_id",NULL);
	}
}

void linphone_gtk_in_call_view_enable_audio_view(LinphoneCall *call, gboolean val){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *audio_view=linphone_gtk_get_widget(callview,"incall_audioview");
	//GtkWidget *mic=linphone_gtk_get_widget(callview,"incall_mic_icon");
	GtkWidget *spk=linphone_gtk_get_widget(callview,"incall_spk_icon");
	GtkWidget *mic_level=linphone_gtk_get_widget(callview,"mic_audiolevel");
	GtkWidget *spk_level=linphone_gtk_get_widget(callview,"spk_audiolevel");
	GdkPixbuf *pbuf;
	//gtk_image_set_from_pixbuf(GTK_IMAGE(mic),(pbuf=create_pixbuf("mic_active.png")));
	//g_object_unref(pbuf);
	if (val){
		gtk_image_set_from_pixbuf(GTK_IMAGE(spk),(pbuf=create_pixbuf("speaker.png")));
		g_object_unref(pbuf);
		linphone_gtk_init_audio_meter(mic_level,(get_volume_t)linphone_call_get_record_volume,call);
		linphone_gtk_init_audio_meter(spk_level,(get_volume_t)linphone_call_get_play_volume,call);
		gtk_widget_show_all(audio_view);
	}else{
		linphone_gtk_uninit_audio_meter(mic_level);
		linphone_gtk_uninit_audio_meter(spk_level);
		gtk_widget_hide(audio_view);
	}
}

G_MODULE_EXPORT 
void linphone_gtk_auth_token_verified_clicked(GtkButton *button){
	LinphoneCall *call=linphone_gtk_get_currently_displayed_call(NULL);
	if (call){
		linphone_call_set_authentication_token_verified(call,!linphone_call_get_authentication_token_verified(call));
	}
}

void linphone_gtk_in_call_view_show_encryption(LinphoneCall *call){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *encryption_box=linphone_gtk_get_widget(callview,"encryption_box");
	GtkWidget *label=linphone_gtk_get_widget(callview,"encryption_label");
	GtkWidget *status_icon=linphone_gtk_get_widget(callview,"encryption_status_icon");
	GtkWidget *verify_button=linphone_gtk_get_widget(callview,"encryption_verify_button");
	LinphoneMediaEncryption me=linphone_call_params_get_media_encryption(linphone_call_get_current_params(call));
	bool_t verified=linphone_call_get_authentication_token_verified(call);
	switch(me){
		case LinphoneMediaEncryptionSRTP:
			gtk_widget_show_all(encryption_box);
			gtk_label_set_markup(GTK_LABEL(label),_("Secured by SRTP"));
			gtk_widget_hide(status_icon);
			gtk_widget_hide(verify_button);
		break;
		case LinphoneMediaEncryptionZRTP:
		{
			gchar *text=g_strdup_printf(_("Secured by ZRTP - [auth token: %s]"),linphone_call_get_authentication_token(call));
			gtk_label_set_markup(GTK_LABEL(label),text);
			g_free(text);
			gtk_image_set_from_stock(GTK_IMAGE(status_icon),
			                          verified ? GTK_STOCK_APPLY : GTK_STOCK_DIALOG_WARNING,GTK_ICON_SIZE_MENU);
			gtk_button_set_label(GTK_BUTTON(verify_button),
			                     verified ? _("Set unverified") : _("Set verified"));
			gtk_widget_show_all(encryption_box);
		}	
		break;
		default:
			gtk_widget_hide_all(encryption_box);
	}
}

G_MODULE_EXPORT 
void linphone_gtk_in_call_view_set_in_call(LinphoneCall *call){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *status=linphone_gtk_get_widget(callview,"in_call_status");
	GtkWidget *callee=linphone_gtk_get_widget(callview,"in_call_uri");
	GtkWidget *duration=linphone_gtk_get_widget(callview,"in_call_duration");
	guint taskid=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(callview),"taskid"));
	gboolean in_conf=linphone_call_params_local_conference_mode(linphone_call_get_current_params(call));
	
	display_peer_name_in_label(callee,linphone_call_get_remote_address (call));

	gtk_widget_set_visible(linphone_gtk_get_widget(callview,"mute_pause_buttons"),!in_conf);
	gtk_widget_hide(linphone_gtk_get_widget(callview,"answer_decline_panel"));
	gtk_label_set_markup(GTK_LABEL(status),in_conf ? _("In conference") : _("<b>In call</b>"));

	gtk_label_set_text(GTK_LABEL(duration),_("00::00::00"));
	linphone_gtk_in_call_set_animation_image(callview,GTK_STOCK_MEDIA_PLAY,TRUE);
	linphone_gtk_enable_mute_button(
					GTK_BUTTON(linphone_gtk_get_widget(callview,"incall_mute")),!in_conf);
	if (taskid==0){
		taskid=g_timeout_add(250,(GSourceFunc)linphone_gtk_in_call_view_refresh,call);
		g_object_set_data(G_OBJECT(callview),"taskid",GINT_TO_POINTER(taskid));
	}
	linphone_gtk_in_call_view_enable_audio_view(call, !in_conf);
	linphone_gtk_in_call_view_show_encryption(call);
	if (in_conf) linphone_gtk_set_in_conference(call);
}

G_MODULE_EXPORT 
void linphone_gtk_in_call_view_set_paused(LinphoneCall *call){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *status=linphone_gtk_get_widget(callview,"in_call_status");
	gtk_widget_hide(linphone_gtk_get_widget(callview,"answer_decline_panel"));
	gtk_label_set_markup(GTK_LABEL(status),_("<b>Paused call</b>"));
	linphone_gtk_in_call_set_animation_image(callview,GTK_STOCK_MEDIA_PAUSE,TRUE);
}

G_MODULE_EXPORT 
void linphone_gtk_in_call_view_update_duration(LinphoneCall *call){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *duration_label=linphone_gtk_get_widget(callview,"in_call_duration");
	int duration=linphone_call_get_duration(call);
	char tmp[256]={0};
	int seconds=duration%60;
	int minutes=(duration/60)%60;
	int hours=duration/3600;
	snprintf(tmp,sizeof(tmp)-1,_("%02i::%02i::%02i"),hours,minutes,seconds);
	gtk_label_set_text(GTK_LABEL(duration_label),tmp);
}

static gboolean in_call_view_terminated(LinphoneCall *call){
	linphone_gtk_remove_in_call_view(call);
	return FALSE;
}

G_MODULE_EXPORT 
void linphone_gtk_in_call_view_terminate(LinphoneCall *call, const char *error_msg){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer(call);
	GtkWidget *status=linphone_gtk_get_widget(callview,"in_call_status");
	guint taskid=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(callview),"taskid"));
	gboolean in_conf=linphone_call_params_local_conference_mode(linphone_call_get_current_params(call));	

	if (error_msg==NULL)
		gtk_label_set_markup(GTK_LABEL(status),_("<b>Call ended.</b>"));
	else{
		char *msg=g_markup_printf_escaped("<span color=\"red\"><b>%s</b></span>",error_msg);
		gtk_label_set_markup(GTK_LABEL(status),msg);
		g_free(msg);
	}
	linphone_gtk_in_call_set_animation_image(callview,
	           linphone_gtk_get_ui_config("stop_call_icon","stopcall-red.png"),FALSE);
	
	gtk_widget_hide(linphone_gtk_get_widget(callview,"answer_decline_panel"));
	gtk_widget_hide(linphone_gtk_get_widget(callview,"incall_audioview"));
	linphone_gtk_enable_mute_button(
		GTK_BUTTON(linphone_gtk_get_widget(callview,"incall_mute")),FALSE);
	linphone_gtk_enable_hold_button(call,FALSE,TRUE);
	
	if (taskid!=0) g_source_remove(taskid);
	g_timeout_add_seconds(2,(GSourceFunc)in_call_view_terminated,call);
	if (in_conf)
		linphone_gtk_terminate_conference_participant(call);
}

G_MODULE_EXPORT 
void linphone_gtk_draw_mute_button(GtkButton *button, gboolean active){
	g_object_set_data(G_OBJECT(button),"active",GINT_TO_POINTER(active));
	if (active){
		GtkWidget *image=create_pixmap("mic_muted.png");
		/*gtk_button_set_label(GTK_BUTTON(button),_("Unmute"));*/
		if (image!=NULL) {
			gtk_button_set_image(GTK_BUTTON(button),image);
			gtk_widget_show(image);
		}
	}else{
		GtkWidget *image=create_pixmap("mic_active.png");
		/*gtk_button_set_label(GTK_BUTTON(button),_("Mute"));*/
		if (image!=NULL) {
			gtk_button_set_image(GTK_BUTTON(button),image);
			gtk_widget_show(image);
		}
	}
}

G_MODULE_EXPORT 
void linphone_gtk_mute_clicked(GtkButton *button){
	int active=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button),"active"));
	linphone_core_mute_mic(linphone_gtk_get_core(),!active);
	linphone_gtk_draw_mute_button(button,!active);
}

G_MODULE_EXPORT 
void linphone_gtk_enable_mute_button(GtkButton *button, gboolean sensitive)
{
	/*gtk_widget_set_sensitive(GTK_WIDGET(button),sensitive);*/
	gtk_widget_set_visible(GTK_WIDGET(button),sensitive);
	linphone_gtk_draw_mute_button(button,FALSE);
}

G_MODULE_EXPORT 
void linphone_gtk_draw_hold_button(GtkButton *button, gboolean active){
	g_object_set_data(G_OBJECT(button),"active",GINT_TO_POINTER(active));
	if (active){
		GtkWidget *image=create_pixmap("hold_off.png");
		gtk_button_set_label(GTK_BUTTON(button),_("Resume"));
		if (image!=NULL) {
			gtk_button_set_image(GTK_BUTTON(button),image);
			gtk_widget_show(image);
		}
	}else{
		GtkWidget *image=create_pixmap("hold_on.png");
		gtk_button_set_label(GTK_BUTTON(button),_("Pause"));
		if (image!=NULL) {
			gtk_button_set_image(GTK_BUTTON(button),image);
			gtk_widget_show(image);
		}
	}
}

G_MODULE_EXPORT 
void linphone_gtk_hold_clicked(GtkButton *button){
	int active=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button),"active"));
	LinphoneCall *call=linphone_gtk_get_currently_displayed_call(NULL);
	if (!call) return;
	if(!active)
	{
		linphone_core_pause_call(linphone_gtk_get_core(),call);
	}
	else
	{
		linphone_core_resume_call(linphone_gtk_get_core(),call);
	}
}

void linphone_gtk_enable_hold_button(LinphoneCall *call, gboolean sensitive, gboolean holdon){
	GtkWidget *callview=(GtkWidget*)linphone_call_get_user_pointer (call);
	GtkWidget *button;
	g_return_if_fail(callview!=NULL);
	button=linphone_gtk_get_widget(callview,"hold_call");
	gtk_widget_set_sensitive(GTK_WIDGET(button),sensitive);
	gtk_widget_set_visible(GTK_WIDGET(button),sensitive);
	linphone_gtk_draw_hold_button(GTK_BUTTON(button),!holdon);
}
