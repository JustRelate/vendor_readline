/* Readline.h -- the names of functions callable from within readline. */

/* Copyright (C) 1987, 1989, 1992 Free Software Foundation, Inc.

   This file is part of the GNU Readline Library, a library for
   reading lines of text with interactive input and history editing.

   The GNU Readline Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 1, or
   (at your option) any later version.

   The GNU Readline Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   The GNU General Public License is often shipped with GNU software, and
   is generally kept in a file called COPYING or LICENSE.  If you do not
   have a copy of the license, write to the Free Software Foundation,
   675 Mass Ave, Cambridge, MA 02139, USA. */

#if !defined (_READLINE_H_)
#define _READLINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined (READLINE_LIBRARY)
#  include "rlstdc.h"
#  include "keymaps.h"
#  include "tilde.h"
#else
#  include <readline/rlstdc.h>
#  include <readline/keymaps.h>
#  include <readline/tilde.h>
#endif

#include "rldynlink.h"		/* for export / import macros  */

/* Readline data structures. */

/* Maintaining the state of undo.  We remember individual deletes and inserts
   on a chain of things to do. */

/* The actions that undo knows how to undo.  Notice that UNDO_DELETE means
   to insert some text, and UNDO_INSERT means to delete some text.   I.e.,
   the code tells undo what to undo, not how to undo it. */
enum undo_code { UNDO_DELETE, UNDO_INSERT, UNDO_BEGIN, UNDO_END };

/* What an element of THE_UNDO_LIST looks like. */
typedef struct undo_list {
  struct undo_list *next;
  int start, end;		/* Where the change took place. */
  char *text;			/* The text to insert, if undoing a delete. */
  enum undo_code what;		/* Delete, Insert, Begin, End. */
} UNDO_LIST;

/* The current undo list for RL_LINE_BUFFER. */
RL_VAR(UNDO_LIST *, rl_undo_list);

/* The data structure for mapping textual names to code addresses. */
typedef struct _funmap {
  char *name;
  Function *function;
} FUNMAP;

RL_VAR(FUNMAP **, funmap);

/* **************************************************************** */
/*								    */
/*	     Functions available to bind to key sequences	    */
/*								    */
/* **************************************************************** */

/* Bindable commands for numeric arguments. */
extern int rl_digit_argument __P((int, int));
extern int rl_universal_argument __P((int, int));

/* Bindable commands for moving the cursor. */
RL_FUNC(int,  rl_forward, __P((int, int)));
RL_FUNC(int, rl_backward, __P((int, int)));
RL_FUNC(int, rl_beg_of_line, __P((int, int)));
RL_FUNC(int, rl_end_of_line, __P((int, int)));
RL_FUNC(int, rl_forward_word, __P((int, int)));
RL_FUNC(int, rl_backward_word, __P((int, int)));
RL_FUNC(int, rl_refresh_line, __P((int, int)));
RL_FUNC(int, rl_clear_screen, __P((int, int)));
RL_FUNC(int, rl_arrow_keys, __P((int, int)));

/* Bindable commands for inserting and deleting text. */
RL_FUNC(int, rl_insert, __P((int, int)));
RL_FUNC(int, rl_quoted_insert, __P((int, int)));
RL_FUNC(int, rl_tab_insert, __P((int, int)));
RL_FUNC(int, rl_newline, __P((int, int)));
RL_FUNC(int, rl_do_lowercase_version, __P((int, int)));
RL_FUNC(int, rl_rubout, __P((int, int)));
RL_FUNC(int, rl_delete, __P((int, int)));
RL_FUNC(int, rl_rubout_or_delete, __P((int, int)));
RL_FUNC(int, rl_delete_horizontal_space, __P((int, int)));
RL_FUNC(int, rl_delete_or_show_completions, __P((int, int)));
RL_FUNC(int, rl_insert_comment, __P((int, int)));

/* Bindable commands for changing case. */
RL_FUNC(int, rl_upcase_word, __P((int, int)));
RL_FUNC(int, rl_downcase_word, __P((int, int)));
RL_FUNC(int, rl_capitalize_word, __P((int, int)));

/* Bindable commands for transposing characters and words. */
RL_FUNC(int, rl_transpose_words, __P((int, int)));
RL_FUNC(int, rl_transpose_chars, __P((int, int)));

/* Bindable commands for searching within a line. */
RL_FUNC(int, rl_char_search, __P((int, int)));
RL_FUNC(int, rl_backward_char_search, __P((int, int)));

/* Bindable commands for readline's interface to the command history. */
RL_FUNC(int, rl_beginning_of_history, __P((int, int)));
RL_FUNC(int, rl_end_of_history, __P((int, int)));
RL_FUNC(int, rl_get_next_history, __P((int, int)));
RL_FUNC(int, rl_get_previous_history, __P((int, int)));

/* Bindable commands for managing the mark and region. */
RL_FUNC(int, rl_set_mark, __P((int, int)));
RL_FUNC(int, rl_exchange_point_and_mark, __P((int, int)));

/* Bindable commands to set the editing mode (emacs or vi). */
RL_FUNC(int, rl_vi_editing_mode, __P((int, int)));
RL_FUNC(int, rl_emacs_editing_mode, __P((int, int)));

/* Bindable commands for managing key bindings. */
RL_FUNC(int, rl_re_read_init_file, __P((int, int)));
RL_FUNC(int, rl_dump_functions, __P((int, int)));
RL_FUNC(int, rl_dump_macros, __P((int, int)));
RL_FUNC(int, rl_dump_variables, __P((int, int)));

/* Bindable commands for word completion. */
RL_FUNC(int, rl_complete, __P((int, int)));
RL_FUNC(int, rl_possible_completions, __P((int, int)));
RL_FUNC(int, rl_insert_completions, __P((int, int)));
RL_FUNC(int, rl_menu_complete, __P((int, int)));

/* Bindable commands for killing and yanking text, and managing the kill ring. */
RL_FUNC(int, rl_kill_word, __P((int, int)));
RL_FUNC(int, rl_backward_kill_word, __P((int, int)));
RL_FUNC(int, rl_kill_line, __P((int, int)));
RL_FUNC(int, rl_backward_kill_line, __P((int, int)));
RL_FUNC(int, rl_kill_full_line, __P((int, int)));
RL_FUNC(int, rl_unix_word_rubout, __P((int, int)));
RL_FUNC(int, rl_unix_line_discard, __P((int, int)));
RL_FUNC(int, rl_copy_region_to_kill, __P((int, int)));
RL_FUNC(int, rl_kill_region, __P((int, int)));
RL_FUNC(int, rl_copy_forward_word, __P((int, int)));
RL_FUNC(int, rl_copy_backward_word, __P((int, int)));
RL_FUNC(int, rl_yank, __P((int, int)));
RL_FUNC(int, rl_yank_pop, __P((int, int)));
RL_FUNC(int, rl_yank_nth_arg, __P((int, int)));
RL_FUNC(int, rl_yank_last_arg, __P((int, int)));
/* Not available unless __CYGWIN32__ is defined. */
#if defined (__CYGWIN32__) || defined (__MINGW32__)
RL_FUNC(int, rl_paste_from_clipboard, __P((int, int)));
#endif

/* Bindable commands for incremental searching. */
RL_FUNC(int, rl_reverse_search_history, __P((int, int)));
RL_FUNC(int, rl_forward_search_history, __P((int, int)));

/* Bindable keyboard macro commands. */
RL_FUNC(int, rl_start_kbd_macro, __P((int, int)));
RL_FUNC(int, rl_end_kbd_macro, __P((int, int)));
RL_FUNC(int, rl_call_last_kbd_macro, __P((int, int)));

/* Bindable undo commands. */
RL_FUNC(int, rl_revert_line, __P((int, int)));
RL_FUNC(int, rl_undo_command, __P((int, int)));

/* Bindable tilde expansion commands. */
RL_FUNC(int, rl_tilde_expand, __P((int, int)));

/* Bindable terminal control commands. */
#if !defined (__MINGW32__)
 RL_FUNC(int, rl_restart_output, __P((int, int)));
 RL_FUNC(int, rl_stop_output, __P((int, int)));
#else
 extern __inline__ int rl_restart_output (int count, int key) { return 0; }
 extern __inline__ int rl_stop_output (int count, int key) { return 0; }
#endif /* __MINGW32__  */

/* Miscellaneous bindable commands. */
RL_FUNC(int, rl_abort, __P((int, int)));
RL_FUNC(int, rl_tty_status, __P((int, int)));

/* Bindable commands for incremental and non-incremental history searching. */
RL_FUNC(int, rl_history_search_forward, __P((int, int)));
RL_FUNC(int, rl_history_search_backward, __P((int, int)));
RL_FUNC(int, rl_noninc_forward_search, __P((int, int)));
RL_FUNC(int, rl_noninc_reverse_search, __P((int, int)));
RL_FUNC(int, rl_noninc_forward_search_again, __P((int, int)));
RL_FUNC(int, rl_noninc_reverse_search_again, __P((int, int)));

/* Not available unless readline is compiled -DPAREN_MATCHING. */
RL_FUNC(int, rl_insert_close, __P((int, int)));

/* Not available unless READLINE_CALLBACKS is defined. */
RL_FUNC(void, rl_callback_handler_install, __P((char *, VFunction *)));
RL_FUNC(void, rl_callback_read_char, __P((void)));
RL_FUNC(void, rl_callback_handler_remove, __P((void)));

/* Things for vi mode. Not available unless readline is compiled -DVI_MODE. */
/* VI-mode bindable commands. */
RL_FUNC(int, rl_vi_redo, __P((int, int)));
RL_FUNC(int, rl_vi_undo, __P((int, int)));
RL_FUNC(int, rl_vi_yank_arg, __P((int, int)));
RL_FUNC(int, rl_vi_fetch_history, __P((int, int)));
RL_FUNC(int, rl_vi_search_again, __P((int, int)));
RL_FUNC(int, rl_vi_search, __P((int, int)));
RL_FUNC(int, rl_vi_complete, __P((int, int)));
RL_FUNC(int, rl_vi_tilde_expand, __P((int, int)));
RL_FUNC(int, rl_vi_prev_word, __P((int, int)));
RL_FUNC(int, rl_vi_next_word, __P((int, int)));
RL_FUNC(int, rl_vi_end_word, __P((int, int)));
RL_FUNC(int, rl_vi_insert_beg, __P((int, int)));
RL_FUNC(int, rl_vi_append_mode, __P((int, int)));
RL_FUNC(int, rl_vi_append_eol, __P((int, int)));
RL_FUNC(int, rl_vi_eof_maybe, __P((int, int)));
RL_FUNC(int, rl_vi_insertion_mode, __P((int, int)));
RL_FUNC(int, rl_vi_movement_mode, __P((int, int)));
RL_FUNC(int, rl_vi_arg_digit, __P((int, int)));
RL_FUNC(int, rl_vi_change_case, __P((int, int)));
RL_FUNC(int, rl_vi_put, __P((int, int)));
RL_FUNC(int, rl_vi_column, __P((int, int)));
RL_FUNC(int, rl_vi_delete_to, __P((int, int)));
RL_FUNC(int, rl_vi_change_to, __P((int, int)));
RL_FUNC(int, rl_vi_yank_to, __P((int, int)));
RL_FUNC(int, rl_vi_delete, __P((int, int)));
RL_FUNC(int, rl_vi_back_to_indent, __P((int, int)));
RL_FUNC(int, rl_vi_first_print, __P((int, int)));
RL_FUNC(int, rl_vi_char_search, __P((int, int)));
RL_FUNC(int, rl_vi_match, __P((int, int)));
RL_FUNC(int, rl_vi_change_char, __P((int, int)));
RL_FUNC(int, rl_vi_subst, __P((int, int)));
RL_FUNC(int, rl_vi_overstrike, __P((int, int)));
RL_FUNC(int, rl_vi_overstrike_delete, __P((int, int)));
RL_FUNC(int, rl_vi_replace, __P((int, int)));
RL_FUNC(int, rl_vi_set_mark, __P((int, int)));
RL_FUNC(int, rl_vi_goto_mark, __P((int, int)));

/* VI-mode utility functions. */
RL_FUNC(int, rl_vi_check, __P((void)));
RL_FUNC(int, rl_vi_domove, __P((int, int *)));
RL_FUNC(int, rl_vi_bracktype, __P((int)));

/* VI-mode pseudo-bindable commands, used as utility functions. */
RL_FUNC(int, rl_vi_fWord, __P((int, int)));
RL_FUNC(int, rl_vi_bWord, __P((int, int)));
RL_FUNC(int, rl_vi_eWord, __P((int, int)));
RL_FUNC(int, rl_vi_fword, __P((int, int)));
RL_FUNC(int, rl_vi_bword, __P((int, int)));
RL_FUNC(int, rl_vi_eword, __P((int, int)));

/* **************************************************************** */
/*								    */
/*			Well Published Functions		    */
/*								    */
/* **************************************************************** */

/* Readline functions. */
/* Read a line of input.  Prompt with PROMPT.  A NULL PROMPT means none. */
RL_FUNC(char *, readline, __P((char *)));

RL_FUNC(int, rl_initialize, __P((void)));

RL_FUNC(int, rl_discard_argument, __P((void)));

/* Utility functions to bind keys to readline commands. */
RL_FUNC(int, rl_add_defun, __P((char *, Function *, int)));
RL_FUNC(int, rl_bind_key, __P((int, Function *)));
RL_FUNC(int, rl_bind_key_in_map, __P((int, Function *, Keymap)));
RL_FUNC(int, rl_unbind_key, __P((int)));
RL_FUNC(int, rl_unbind_key_in_map, __P((int, Keymap)));
RL_FUNC(int, rl_unbind_function_in_map, __P((Function *, Keymap)));
RL_FUNC(int, rl_unbind_command_in_map, __P((char *, Keymap)));
RL_FUNC(int, rl_set_key, __P((char *, Function *, Keymap)));
RL_FUNC(int, rl_generic_bind, __P((int, char *, char *, Keymap)));
RL_FUNC(int, rl_variable_bind, __P((char *, char *)));

/* Backwards compatibility, use rl_generic_bind instead. */
RL_FUNC(int, rl_macro_bind, __P((char *, char *, Keymap)));

/* Undocumented in the texinfo manual; not really useful to programs. */
RL_FUNC(int, rl_translate_keyseq, __P((char *, char *, int *)));
RL_FUNC(char *, rl_untranslate_keyseq, __P((int)));

RL_FUNC(Function *, rl_named_function, __P((char *)));
RL_FUNC(Function *, rl_function_of_keyseq, __P((char *, Keymap, int *)));

RL_FUNC(void, rl_list_funmap_names, __P((void)));
RL_FUNC(char **, rl_invoking_keyseqs_in_map, __P((Function *, Keymap)));
RL_FUNC(char **, rl_invoking_keyseqs, __P((Function *)));
 
RL_FUNC(void, rl_function_dumper, __P((int)));
RL_FUNC(void, rl_macro_dumper, __P((int)));
RL_FUNC(void, rl_variable_dumper, __P((int)));

RL_FUNC(int, rl_read_init_file, __P((char *)));
RL_FUNC(int, rl_parse_and_bind, __P((char *)));

/* Functions for manipulating keymaps. Most of them
   have been already fincluded from keymaps.h */
RL_FUNC(void, rl_set_keymap_from_edit_mode, __P((void)));
RL_FUNC(char *, rl_get_keymap_name_from_edit_mode, __P((void)));

/* Functions for manipulating the funmap, which maps command names to functions. */
RL_FUNC(int, rl_add_funmap_entry, __P((char *, Function *)));
RL_FUNC(void, rl_initialize_funmap, __P((void)));
RL_FUNC(char **, rl_funmap_names, __P((void)));

/* Utility functions for managing keyboard macros. */
RL_FUNC(void, rl_push_macro_input, __P((char *)));

/* Functions for undoing, from undo.c */
RL_FUNC(void, rl_add_undo, __P((enum undo_code, int, int, char *)));
RL_FUNC(void, free_undo_list, __P((void)));
RL_FUNC(int, rl_do_undo, __P((void)));
RL_FUNC(int, rl_begin_undo_group, __P((void)));
RL_FUNC(int, rl_end_undo_group, __P((void)));
RL_FUNC(int, rl_modifying, __P((int, int)));

/* Functions for redisplay. */
RL_FUNC(void, rl_redisplay, __P((void)));
RL_FUNC(int, rl_on_new_line, __P((void)));
RL_FUNC(int, rl_forced_update_display, __P((void)));
RL_FUNC(int, rl_clear_message, __P((void)));
RL_FUNC(int, rl_reset_line_state, __P((void)));

#if defined (__STDC__) && defined (USE_VARARGS) && defined (PREFER_STDARG)
RL_FUNC(int, rl_message, (const char *, ...));
#else
RL_FUNC(int, rl_message, (void));
#endif

/* Undocumented in texinfo manual. */
RL_FUNC(int, rl_show_char, __P((int)));
RL_FUNC(int, rl_character_len, __P((int, int)));
RL_FUNC(int, crlf, __P((void)));

/* Save and restore internal prompt redisplay information. */
RL_FUNC(void, rl_save_prompt, __P((void)));
RL_FUNC(void, rl_restore_prompt, __P((void)));

/* Modifying text. */
RL_FUNC(int, rl_insert_text, __P((char *)));
RL_FUNC(int, rl_delete_text, __P((int, int)));
RL_FUNC(int, rl_kill_text, __P((int, int)));
RL_FUNC(char, *rl_copy_text, __P((int, int)));

/* Terminal and tty mode management. */
RL_FUNC(void, rl_prep_terminal, __P((int)));
RL_FUNC(void, rl_deprep_terminal, __P((void)));
RL_FUNC(void, rltty_set_default_bindings, __P((Keymap)));

RL_FUNC(int, rl_reset_terminal, __P((char *)));
RL_FUNC(void, rl_resize_terminal, __P((void)));

/* `Public' utility functions . */
RL_FUNC(void, rl_extend_line_buffer, __P((int)));
RL_FUNC(int, ding, __P((void)));

/* Functions for character input. */
RL_FUNC(int, rl_stuff_char, __P((int)));
RL_FUNC(int, rl_execute_next, __P((int)));
RL_FUNC(int, rl_read_key, __P((void)));
RL_FUNC(int, rl_getc, __P((FILE *)));
#if defined (HANDLE_SIGNALS)
/* Readline signal handling, from signals.c */
RL_FUNC(int, rl_set_signals, __P((void)));
RL_FUNC(int, rl_clear_signals, __P((void)));
RL_FUNC(void, rl_cleanup_after_signal, __P((void)));
RL_FUNC(void, rl_reset_after_signal, __P((void)));
RL_FUNC(void, rl_free_line_state, __P((void)));
#endif	/* HANDLE_SIGNALS  */

/* Undocumented. */
RL_FUNC(int, rl_expand_prompt, __P((char *)));

RL_FUNC(int, maybe_save_line, __P((void)));
RL_FUNC(int, maybe_unsave_line, __P((void)));
RL_FUNC(int, maybe_replace_line, __P((void)));

/* Completion functions. */
RL_FUNC(int, rl_complete_internal, __P((int)));
RL_FUNC(void, rl_display_match_list, __P((char **, int, int)));

RL_FUNC(char **, completion_matches, __P((char *, CPFunction *)));
RL_FUNC(char *, username_completion_function, __P((char *, int)));
RL_FUNC(char *, filename_completion_function, __P((char *, int)));

/* **************************************************************** */
/*								    */
/*			Well Published Variables		    */
/*								    */
/* **************************************************************** */

/* The version of this incarnation of the readline library. */
RL_VAR(char *, rl_library_version);

/* The name of the calling program.  You should initialize this to
   whatever was in argv[0].  It is used when parsing conditionals. */
RL_VAR(char *, rl_readline_name);

/* The prompt readline uses.  This is set from the argument to
   readline (), and should not be assigned to directly. */
RL_VAR(char *, rl_prompt);

/* The line buffer that is in use. */
RL_VAR(char *, rl_line_buffer);

/* The location of point, and end. */
RL_VAR(int, rl_point);
RL_VAR(int, rl_end);

/* The mark, or saved cursor position. */
RL_VAR(int, rl_mark);

/* Flag to indicate that readline has finished with the current input
   line and should return it. */
RL_VAR(int, rl_done);

/* If set to a character value, that will be the next keystroke read. */
RL_VAR(int, rl_pending_input);

/* Non-zero if we called this function from _rl_dispatch().  It's present
   so functions can find out whether they were called from a key binding
   or directly from an application. */
RL_VAR(int, rl_dispatching);

/* The name of the terminal to use. */
RL_VAR(char *, rl_terminal_name);

/* The input and output streams. */
RL_VAR(FILE *, rl_instream);
RL_VAR(FILE *, rl_outstream);

/* If non-zero, then this is the address of a function to call just
   before readline_internal () prints the first prompt. */
RL_VAR(Function *, rl_startup_hook);

/* If non-zero, this is the address of a function to call just before
   readline_internal_setup () returns and readline_internal starts
   reading input characters. */
RL_VAR(Function *, rl_pre_input_hook);
      
/* The address of a function to call periodically while Readline is
   awaiting character input, or NULL, for no event handling. */
RL_VAR(Function *, rl_event_hook);

RL_VAR(Function *, rl_getc_function);
RL_VAR(VFunction *, rl_redisplay_function);
RL_VAR(VFunction *, rl_prep_term_function);
RL_VAR(VFunction *, rl_deprep_term_function);

/* Dispatch variables. */
RL_VAR(Keymap, rl_executing_keymap);
RL_VAR(Keymap, rl_binding_keymap);

/* Display variables. */
/* If non-zero, readline will erase the entire line, including any prompt,
   if the only thing typed on an otherwise-blank line is something bound to
   rl_newline. */
RL_VAR(int, rl_erase_empty_line);

#if defined (HANDLE_SIGNALS)
/* Variables to control readline signal handling. */
/* If non-zero, readline will install its own signal handlers for
   SIGINT, SIGTERM, SIGQUIT, SIGALRM, SIGTSTP, SIGTTIN, and SIGTTOU. */
RL_VAR(int, rl_catch_signals);

#if  defined (SIGWINCH)
/* If non-zero, readline will install a signal handler for SIGWINCH
   that also attempts to call any calling application's SIGWINCH signal
   handler.  Note that the terminal is not cleaned up before the
   application's signal handler is called; use rl_cleanup_after_signal()
   to do that. */
RL_VAR(int, rl_catch_sigwinch);
#endif	/* SIGWINCH  */
#endif	/* HANDLE_SIGNALS  */

/* Completion variables. */
/* Pointer to the generator function for completion_matches ().
   NULL means to use filename_entry_function (), the default filename
   completer. */
RL_VAR(Function *, rl_completion_entry_function);

/* If rl_ignore_some_completions_function is non-NULL it is the address
   of a function to call after all of the possible matches have been
   generated, but before the actual completion is done to the input line.
   The function is called with one argument; a NULL terminated array
   of (char *).  If your function removes any of the elements, they
   must be free()'ed. */
RL_VAR(Function *, rl_ignore_some_completions_function);

/* Pointer to alternative function to create matches.
   Function is called with TEXT, START, and END.
   START and END are indices in RL_LINE_BUFFER saying what the boundaries
   of TEXT are.
   If this function exists and returns NULL then call the value of
   rl_completion_entry_function to try to match, otherwise use the
   array of strings returned. */
RL_VAR(CPPFunction *, rl_attempted_completion_function);

/* The basic list of characters that signal a break between words for the
   completer routine.  The initial contents of this variable is what
   breaks words in the shell, i.e. "n\"\\'`@$>". */
RL_VAR(char *, rl_basic_word_break_characters);

/* The list of characters that signal a break between words for
   rl_complete_internal.  The default list is the contents of
   rl_basic_word_break_characters.  */
RL_VAR(char *, rl_completer_word_break_characters);

/* List of characters which can be used to quote a substring of the line.
   Completion occurs on the entire substring, and within the substring   
   rl_completer_word_break_characters are treated as any other character,
   unless they also appear within this list. */
RL_VAR(char *, rl_completer_quote_characters);

/* List of quote characters which cause a word break. */
RL_VAR(char *, rl_basic_quote_characters);

/* List of characters that need to be quoted in filenames by the completer. */
RL_VAR(char *, rl_filename_quote_characters);

/* List of characters that are word break characters, but should be left
   in TEXT when it is passed to the completion function.  The shell uses
   this to help determine what kind of completing to do. */
RL_VAR(char *, rl_special_prefixes);

/* If non-zero, then this is the address of a function to call when
   completing on a directory name.  The function is called with
   the address of a string (the current directory name) as an arg. */
RL_VAR(Function *, rl_directory_completion_hook);

/* Backwards compatibility with previous versions of readline. */
#define rl_symbolic_link_hook rl_directory_completion_hook

/* If non-zero, then this is the address of a function to call when
   completing a word would normally display the list of possible matches.
   This function is called instead of actually doing the display.
   It takes three arguments: (char **matches, int num_matches, int max_length)
   where MATCHES is the array of strings that matched, NUM_MATCHES is the
   number of strings in that array, and MAX_LENGTH is the length of the
   longest string in that array. */
RL_VAR(VFunction *, rl_completion_display_matches_hook);

/* Non-zero means that the results of the matches are to be treated
   as filenames.  This is ALWAYS zero on entry, and can only be changed
   within a completion entry finder function. */
RL_VAR(int, rl_filename_completion_desired);

/* Non-zero means that the results of the matches are to be quoted using
   double quotes (or an application-specific quoting mechanism) if the
   filename contains any characters in rl_word_break_chars.  This is
   ALWAYS non-zero on entry, and can only be changed within a completion
   entry finder function. */
RL_VAR(int, rl_filename_quoting_desired);

/* Set to a function to quote a filename in an application-specific fashion.
   Called with the text to quote, the type of match found (single or multiple)
   and a pointer to the quoting character to be used, which the function can
   reset if desired. */
RL_VAR(CPFunction *, rl_filename_quoting_function);

/* Function to call to remove quoting characters from a filename.  Called
   before completion is attempted, so the embedded quotes do not interfere
   with matching names in the file system. */
RL_VAR(CPFunction *, rl_filename_dequoting_function);

/* Function to call to decide whether or not a word break character is
   quoted.  If a character is quoted, it does not break words for the
   completer. */
RL_VAR(Function *, rl_char_is_quoted_p);

/* Non-zero means to suppress normal filename completion after the
   user-specified completion function has been called. */
RL_VAR(int, rl_attempted_completion_over);

/* Set to a character describing the type of completion being attempted by
   rl_complete_internal; available for use by application completion
   functions. */
RL_VAR(int, rl_completion_type);

/* Character appended to completed words when at the end of the line.  The
   default is a space.  Nothing is added if this is '\0'. */
RL_VAR(int, rl_completion_append_character);

/* Up to this many items will be displayed in response to a
   possible-completions call.  After that, we ask the user if she
   is sure she wants to see them all.  The default value is 100. */
RL_VAR(int, rl_completion_query_items);

/* If non-zero, then disallow duplicates in the matches. */
RL_VAR(int, rl_ignore_completion_duplicates);

/* If this is non-zero, completion is (temporarily) inhibited, and the
   completion character will be inserted as any other. */
RL_VAR(int, rl_inhibit_completion);
   
/* Definitions available for use by readline clients. */
#define RL_PROMPT_START_IGNORE	'\001'
#define RL_PROMPT_END_IGNORE	'\002'

/* Possible values for do_replace argument to rl_filename_quoting_function,
   called by rl_complete_internal. */
#define NO_MATCH        0
#define SINGLE_MATCH    1
#define MULT_MATCH      2

#if !defined (savestring)
extern char *savestring ();	/* XXX backwards compatibility */
#endif

#ifdef __cplusplus
}
#endif

#endif /* _READLINE_H_ */

