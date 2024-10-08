/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:14:19 by vsavolai          #+#    #+#             */
/*   Updated: 2024/09/15 20:35:59 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>

# define PATHH_MAX 1024
# define TABLE_SIZE 64
# define DELETED_NODE 0xFFFFFFFFFFFFFFFFUL

typedef struct s_redir
{
	char			arrow;
	char			*filename;
	int				index;
	int				fd;
	int				flag;
	int				original_input;
	int				original_output;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd_args
{
	t_redir		**head_redir;
	t_redir		**head_hdocs;
	char		*cmd;
	char		**args;
	int			pipe_count;
	int			cmd_count;
}				t_cmd_args;

typedef struct s_env
{
	char	*name;
	char	*value;
	int		status;
}			t_env;

char		*find_redir(char *str);
int			get_len(char *str);
char		*find_limiter(char *str);
int			build_list(t_redir **head, char *lim, int index);
t_cmd_args	**get_array(t_redir **redr, t_redir **hdoc, char **line, int pipe);
char		**parse_arguments(char *line, char *line2);
char		*skip_redirs(char *cmd_line);
void		syntax_error(char **cmd_line, t_env **env, char token);
int			check_syntax(char **cmd_lines, int pipe_count, t_env **env);
void		list_free(t_redir **hdoc, t_redir **redir, char **cmd, int flag);
void		redir_lstclear(t_redir **lst, void (*del)(void *));
void		free_struct_array(t_cmd_args **arr);
int			get_pipe_count(char **cmd_lines);
void		run_pipes(t_cmd_args **cmd_args, int pc, char **envp, t_env **et);
int			get_cmd_len(char *str, char quote);
char		*skip_quotes(char *str, char quote);
char		**ft_split_remix(char *s, char c);
int			check_pipe_repetition(char *line, t_env **env);
void		run_commands(t_cmd_args **cmd_args, int pipe_count, t_env **env_t);
char		*skip_arg(char *str);
int			get_arg_len(char *str);
int			check_in_redir(t_redir **head_redir, int i, int fd1);
int			check_out_redir(t_redir **head_redir, int i, int fd2, int *fl);
char		*check_if_digit(char *str, t_redir **redir);
void		put_fd_lst(char *line, t_redir **new);
int			get_envs(t_cmd_args **cmd_arg, t_env **env_table, int *flag);
char		*cpy_expanded(char *str, char *expanded_str, int *i, t_env **env);
char		*cpy_line(char *str, char *expanded_str, int *i, int *flag);
char		*cpy_quote_to_quote(char *str, char *expanded_str, int *i);
char		*cpy_double_quote(char **str, char *expanded_str);
int			split_cmd(t_cmd_args **cmd_arg, int i, int len);
int			word_count(char *str);
int			count_env_variables(char *str);
int			create_envs(char **envp, t_env **env_table);
int			hash(char *name);
int			table_insert(t_env *env, t_env **env_tabl);
t_env		*search_table(char *name, t_env **env_t);
int			table_delete(char *name, t_env **et);
int			get_value(t_env *env, char *envp, t_env **env_table);
char		**get_env_list(t_env **env_tabl);
char		*ft_get_env(char *name, t_env **env_table);
void		check_cmds(t_cmd_args **cmd_args, t_env **env_table);
int			remove_arg_quotes(t_cmd_args **cmd_args);
int			remove_cmd_quotes(t_cmd_args **cmd_args);
int			remove_file_quotes(t_redir **redirs);
char		*clean_arg(char *arg);
int			check_h_docs(t_redir *head_redir, int i, char **filename);
void		free_env_table(t_env **env_table);
void		ft_exit(t_env **env_table, t_cmd_args **cmd_args, int flag);
void		export(t_cmd_args *cmd_args, t_env **env_table, int *flag, int i);
void		pwd(int *flag, t_env **env_table);
void		echo(char **args, int fd, int *flag, t_env **env_table);
void		unset(t_cmd_args *c_a, t_env **env_table, int *flag);
void		cd(t_cmd_args *cmd_args, t_env **env_table, int *flag);
void		env(t_env **env_table, int *flag);
void		export_env(t_env **env_table, int *flag);
void		pipe_error(int error_nbr, char *cmd, char **cmds);
int			check_builtins(t_cmd_args *ca, t_env **et, int call, int flag);
void		signals_before_rl(int flag);
void		signals_after_rl(void);
int			termios_before_rl(void);
void		file_error(int error_nbr, char *cmd);
char		*check_null_cmd(char **line, int i, t_env **env);
int			create_file(char *filename);
void		pipe_error_cmd(char *cmd, char **cmds);
void		print_error(t_cmd_args **arr, int flag, t_env **env_table);
void		print_error_filename(char *s, int *flag, int error);
char		*expand_all_env(char *old, char *expanded_str, int i, t_env **env);
char		*count_expand_cmd(char *cmd, int i, t_env **env, int *flag);
void		change_cmd_status(t_env **env_t, int status);
int			find_correct_index(t_env **env);
int			check_flag(int flag, char **cmd);
void		export_error(char *str, t_env **env_table, t_env *env);
int			check_newline(char **cmd_line, t_env **env, int i);
int			check_redir_syntax(char **line);
int			variable_word_count(char *str);
char		**split_line(char *s, t_env **env, t_redir **hdoc, t_redir **rdir);
char		**get_cmd(t_cmd_args *cmd_args);
int			update_table(t_env **env_table);
int			check_ambiguos_redirect_after(char *file);
int			init_pipe_vars(int *i, int *fd1, int **process_ids, int pc);
void		wait_children(int *process_ids, int fd2, t_env **et);
void		null_cmd_hdoc(t_cmd_args *ca, int *flag);
int			redir_fail(void);
char		*skip_digit(char *str);

#endif