/****************************************************************************
 *
 *  $Id: linphonec.h,v 1.3 2006/01/20 14:12:34 strk Exp $
 *
 *  Copyright (C) 2005  Sandro Santilli <strk@keybit.net>
 *
 ****************************************************************************
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 ****************************************************************************/

#ifndef LINPHONEC_H
#define LINPHONEC_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_READLINE_H
#include <readline.h>
#define HAVE_READLINE
#else
#ifdef HAVE_READLINE_READLINE_H
#include <readline/readline.h>
#define HAVE_READLINE
#endif
#endif
#ifdef HAVE_HISTORY_H
#include <history.h>
#else
#ifdef HAVE_READLINE_HISTORY_H
#include <readline/history.h>
#endif
#endif

#include <linphonecore.h>
#undef PARAMS
/**************************************************************************
 *
 * Compile-time defines
 *
 **************************************************************************/

#define HISTSIZE 500		/* how many lines of input history */
#define PROMPT_MAX_LEN 256	/* max len of prompt string */
#define LINE_MAX_LEN 256	/* really needed ? */

/*
 * Define this to have your primary contact
 * as the prompt string
 */
/* #define IDENTITY_AS_PROMPT 1 */

/*
 * Time between calls to linphonec_idle_call during main
 * input read loop in microseconds.
 */
#define LPC_READLINE_TIMEOUT 10000

/*
 * Filename of linphonec history
 */
#define LPC_HIST_FILE "~/.linphonec_history"

/*
 * Maximum number of pending authentications
 */
#define MAX_PENDING_AUTH 8

/**************************************************************************
 *
 *  Types
 *
 **************************************************************************/

/*
 * A structure which contains information on the commands this program
 * can understand.
 */
typedef int (*lpc_cmd_handler)(LinphoneCore *, char *);
typedef struct {
	char *name;		/* User printable name of the function. */
	lpc_cmd_handler func;	/* Function to call to do the job. */
	char *help;		/* Short help for this function.  */
	char *doc;		/* Long description.  */
} LPC_COMMAND;

typedef struct {
	int x,y,w,h;
	unsigned long wid;
	bool_t show;
	bool_t refresh;
} VideoParams;


extern VideoParams lpc_video_params;
extern VideoParams lpc_preview_params;

/***************************************************************************
 *
 *  Forward declarations
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

extern int linphonec_parse_command_line(LinphoneCore *lc, char *cl);
extern char *linphonec_command_generator(const char *text, int state);
void linphonec_main_loop_exit();
extern void linphonec_finish(int exit_status);
extern char *linphonec_readline(char *prompt);
void linphonec_set_autoanswer(bool_t enabled);
bool_t linphonec_get_autoanswer();
void linphonec_command_finished(void);
void linphonec_set_caller(const char *caller);
LinphoneCall *linphonec_get_call(long id);
void linphonec_call_identify(LinphoneCall* call);

extern bool_t linphonec_camera_enabled;
extern LinphoneCore *linphonec;
int linphonec_main(char *proxy, char *domain, char *password, char *identity, char *sip_route);
void show_dialog(LinphoneCall* call);
void show_dialog2(LinphoneCall* call);
void call_connected(LinphoneCall* call);
void show_dialog_callend();
void yt_answer_call();
void yt_terminate_call();
extern void registration_state_changed(struct _LinphoneCore *lc, LinphoneProxyConfig *cfg,
		LinphoneRegistrationState cstate, const char *message);
#ifdef __cplusplus
}
#endif
#endif /* def LINPHONEC_H */
