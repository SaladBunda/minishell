/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:33:02 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 18:24:25 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "./readline/history.h"
# include "./readline/readline.h"

# define ED _edit

# ifndef ARG_MAX
#  define ARG_MAX (256 * 1024)
# endif

# define CMD_ROW 100
# define AND_ROW 200
# define OR_ROW 300
# define LEFT_ROW 400
# define RIGHT_ROW 500
# define PIPE_ROW 600

/* Commands codes */
# define FILE_NAME 101
# define COMMAND 102
# define PARAM 103
# define OP 104

/* String tokens divisible by 2 */
# define STR 2
# define VAR 4
# define WILD 8

/* Redirection tokens divisible by 3 */
# define GREAT 3
# define LESS 9
# define APPEND 15
# define HEREDOC 21

/* Command Tokens None divisible by 2/3 */
# define ENV 0
# define S_CMD 1
# define E_CMD 5
# define SPC 7
# define PIPE 11
# define SQUOTE 13
# define DQUOTE 17
# define OR 19
# define AND 23
# define LEFT_PAR 25
# define RIGHT_PAR 29

/* Token DS */

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_family		t_family;
typedef struct s_tree		t_tree;
typedef struct s_utils		t_utils;

typedef struct s_utils
{
	int						fds[2];
	int						saved;
	int						i;
	int						pipes;
}							t_utils;

typedef struct s_command
{
	int						in;
	int						out;
	char					**data;
	int						type;
	t_command				*prev;
	t_command				*next;
}							t_command;

typedef struct s_group
{
	t_command				*head;
	t_command				*tail;
}							t_group;

typedef struct s_files
{
	char					*path;
	int						type;
	int						fd;
	int						is_var;
	char					*lim;
}							t_files;

typedef struct s_family
{
	t_family				*next;
	t_family				*prev;
	t_token					*start;
	t_token					*end;
	t_files					*files;
	int						in;
	int						out;
	int						prev_fd;
	int						type;
	int						level;
	int						index;
	char					**args;
	char					*cmd_path;
	char					*last_in;
	char					*last_out;
}							t_family;

typedef struct s_token
{
	int						type;
	int						index;
	char					*value;
	int						group;
	int						level;
	int						hidden;
	t_family				*family;
	t_token					*next;
	t_token					*prev;
}							t_token;

typedef struct s_list
{
	char					*content;
	struct s_list			*next;
}							t_list;

void						execution(t_family *family_head, t_token *env);
t_family					*parsing(char *cmd, t_token *env);

/* Data structures*/
t_token						*new_token(char *value, int type);
t_token						*create_list(void);
t_token						*list_tail(t_token *node);
void						append_token(t_token *tail, t_token *token);
void						print_tokens(t_token *head);
int							delete_token(t_token *env_head, char *unset_var);

/* Lexer Handlers */
t_token						*angle_bracket(int state, char *cmd, int *index);
t_token						*q_handler(char *cmd, int *index, char q_type);
t_token						*words_handler(char *cmd, int *index, int state);
t_token						*single_handlers(char *cmd, int *index, int state,
								char c);
t_token						*wide_handlers(char *cmd, int *index, char c);
int							is_whitespace(int c);
int							is_special_var(char c);
int							brackets(char *cmd);
int							quotes(char *cmd);
int							is_special(char c, int flag);
void						bracket_util(char *str, int i, int j, int *opened);

/* Free Functions */
// void						free_token(t_token *token);
// void						free_darr(char **arr);
// void						free_all_family(t_family *head);
// void						free_list2(t_token *head);
// void						free_list(t_token *head, int flag);

/* env functions */
int							append_var(t_token *env_head, t_token *env_tail,
								char *export_var);
int							delete_var(t_token *env_head, char *unset_var);
t_token						*env_process(char **env, int flag);
void						joiner(t_token *head, t_token *env);
char						*get_var_value(char *str);
char						**env_decompose(t_token *env_head);
t_token						*env_process(char **env, int flag);
int							env_size(t_token *env_head);

// substitution functions
char						*search_replace(char *str, int start, int end,
								t_token *env);
char						*substitution(int *i, int *j, char *var,
								t_token *token);
char						*substitution2(int *i, int *j, char *var,
								char *string);
void						var_name(char *cmd, int *index, int state);

// family functions
t_family					*create_family_ll(t_token *ll_head);
void						print_family(t_family *head);
t_family					*new_family(int type);

// and/or functions parsing parantheses

void						level_checker(t_family *head);
// void						free_list(t_token *head, int flag);

/* Tree */
t_family					*smallest_level(t_family *family_ll);

/*Built-In*/
void						echo_builtin(t_family *cmd_row);
void						pwd_builtin(void);
char						*get_var_name(char *str);
void						exit_builtin(t_family *family);
void						cd_builtin(t_family *token, t_token *env);
int							variables_handler(t_token *cmd, t_token *env_list,
								t_family *cmd_family);
char						*pwd_extract(void);

// executionner function
int							fake_ex(t_family *family, t_token *env);
int							handle_fds(t_family *head);
int							handle_pipes(t_family *cmd_row, t_token *env,
								int status, t_utils v);

void						print_env(t_token *env_head);

void						handle_errors(t_family *cmd);

// Syntatic Functions
int							syntactic_tester(t_token *head);
void						organizer(t_family *tmp, t_token *tmp2, int flag);
void						omit_spaces(t_token *head);

// bunda test
int							count_files(t_family *head);

/* Parsing struct of execution */
// t_token *space_free(t_token *list);
void						extract_files(t_family *family_ll);
void						print_2d(char **strs);
void						extract_paths(t_family *head, t_token *env);
t_token						*space_free(t_token *list);

void						signal_handler(void);

void						sigquit_reset(int sig);
void						signals_init(int flag);
void						here_sig(int sig);

/* norme function*/
void						edit_global(int status);
void						_edit(int *var, int value);
int							nof_pipes(t_family *head);
void						close_fds(int *fds);
void						save_pipe(int *prev_fd, int *fds);
int							handle_heredocs(t_family *head, t_token *env);
void						get_io_single(t_family *cmd_row);
void						heredoc_sigg(int sig);

/* Paths */
void						extract_paths(t_family *head, t_token *env);
char						*ft_strjoin_cmd(char const *s1, char const *s2);
int							count_args(t_token *start, t_token *end);
int							is_empty(t_token *token);

/* Joiner */
void						token_merger(t_token *head);

/* Frees */
void						free_all_family(t_family *head);
void						free_list(t_token *head, int flag);
void						free_list2(t_token *head);
void						free_token(t_token *token);
void						free_token2(t_token *token);
void						free_family_node(t_family *node);
void						free_files(t_family *node);
void						free_darr(char **arr);

/*Redirs*/
int							count_files(t_family *head);

/* Organizer Utils */
int							is_op(t_token *t);
int							is_str(t_token *t);

/* exit utils */
int							is_numeric(char *str);
int							all_numeric(char **args);
int							in_range(char *str, unsigned long number, int sign,
								int i);

// wildcards
void						wildcard_sub(t_token *head, t_token *env);
int							is_string(t_token *t);
t_token *basic_env(t_token *tail, t_token *head, t_token *token);

#endif
