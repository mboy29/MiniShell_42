/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 22:36:16 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/11 17:12:56 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define END 0
# define LEFT 1
# define LLEFT 2
# define RIGHT 3
# define RRIGHT 4
# define TXT 5
# define PIPE 6

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <time.h>
# include "libft.h"
# include <termios.h>
# include <sys/ioctl.h>
# include <limits.h>

typedef struct s_token
{
	int		type;
	char	*str;
}			t_token;

typedef struct s_cmd
{
	int		pipefd[2];
	int		nb_redir;
	t_token	*redir_tab;
	int		ac;
	char	**av;
	char	**path;
	pid_t	pid;
	int		exit_code;
}			t_cmd;

typedef struct s_vars
{
	int			nb_cmd;
	t_cmd		*cmd;
	int			exit_status;
	int			in_cpy;
	int			out_cpy;
	char		*pwd;
	char		*home;
	int			tab_len;
	char		***tab_env;
	char		***tab_exp;
	char		**e;
	char		**word_tab;
	int			nb_tkn;
	t_token		*tkn_tab;
}				t_vars;

typedef struct s_process
{
	int		status;
	int		exit_code;
	pid_t	pid;
	int		interrupt_hd;
}		t_process;

t_process	g_sig;

void		expand(char **str, t_vars *v);
void		parser(t_vars *v);
int			tokenize(t_vars *v);
int			exec(t_vars *v);
void		sigint_handler(int code);
void		sigquit_handler(int code);
void		exit_error(char *str, int mode);
t_token		*ft_tokenize(char **tab);
char		**get_cmd_path(t_vars *v, char *cmd);
void		exec_cmds(t_vars *v);
void		test(int code);
void		test_slash(int code);
void		test2(int code);
void		ft_print(t_vars *v);
int			get_type(char *token);
void		expanser(char **tab, t_vars *v);
int			lexer(t_vars *v, char *line);
int			check_syntax(char **tab);
void		get_env(t_vars *v, char **env);
void		buitlin_init(t_vars *v, char **env);
int			builtin_env(t_vars *v, char **param);
int			builtin_echo(char **param);
int			builtin_export(t_vars *v, char **param);
char		**split_export(char *param);
int			sort_export(t_vars *v);
int			find_export(t_vars *v, char *param);
void		print_export(char **print);
int			error_export(char *param);
char		**min_export(t_vars *v, char **min);
int			builtin_unset(t_vars *v, char **param);
int			builtin_cd(t_vars *v, char **param);
int			builtin_exit(t_vars *v, char **param);
int			builtin_pwd(t_vars *v, char **param);
int			builtin(t_vars *v, int n);
void		echo_control_seq(int c);
int			redir(t_token *tkn_tab);
char		*get_tabenv(t_vars *v, char *key);
void		init_vars(t_vars *v, char **e);
char		*ft_readline(char *str);
void		ft_readline2(int fd, char *del);
void		clear(void);
int			builtin_check(char *check);
void		print_error(char *str, int mode);
int			is_sep(char c);
int			len_sep(char *str);
void		exit_error(char *str, int mode);
char		**ft_translate(t_vars *v);
void		exec_fork(t_vars *v, int cpt);
int			get_exit_code(t_vars *v);
void		exec_cmd(t_cmd c, char **e);
void		ft_replace_str(char **line, t_vars *v);
int			is_finished(char *str);
void		free_tkn(t_token *tkn_list);
void		ft_free(char **tab);

void		free_vars(t_vars *v);
void		free_matrix(char ***matrix);
void		free_cmd(t_cmd	*cmd_list, int n);
void		free_tabstr(char **tab);
void		free_tkns(t_token *tkn_list);

void		init_tabexp(t_vars *v);
int			ft_tabexp_len(char ***matrix);
char		**copy_env(char *key, char *val);
void		add_exp(t_vars *v, char *key, char *val);
int			print_exp(t_vars *v);

int			print_env(t_vars *v);
int			update_export(t_vars *v, char *param);

int			is_builtin(char *str);
void		exec_solo_built(t_vars *v);

void		fill_heredoc(t_vars *v, t_cmd c);
int			is_true_builtin(char *str);
char		**get_cmd_path(t_vars *v, char *cmd);

int			join_export(t_vars *v, char *param, int select);
t_cmd		fill_cmd(t_vars *v, int ic, int i);
char		**add_elem(char **av, char *str);
int			get_exit_code(t_vars *v);
void		atomic_exec(t_vars *v, int cpt);
void		exec_binary(t_cmd cmd, char **e);
#endif
