/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:31:31 by smessal           #+#    #+#             */
/*   Updated: 2023/03/06 20:06:41 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer.h"
# include "../libft/libft.h"
# include <limits.h>

extern int	g_status;

# define REDIR_IN 1
# define REDIR_OUT 2
# define APPEND 3
# define HERE_DOC 4

/*-------------------------------Struct---------------------------------------*/

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}		t_garbage;

typedef struct s_file
{
	char			*file;
	int				op;
	int				fd;
	struct s_file	*next;
}		t_file;

typedef struct s_data
{
	int		**fd;
	int		is_abs;
	int		p_count;
	pid_t	*pid;
	char	**env;
}		t_data;

typedef struct s_cmdtab
{
	struct s_file	*in;
	struct s_file	*out;
	char			*cmd;
	char			**opt;
	int				fd;
	int				index;
	struct s_cmdtab	*next;
	struct s_cmdtab	*prev;
}		t_cmdtab;

/*------------------------------------INIT------------------*/

t_tks			*init_tokens(char *str);
void			init_active_tokens(t_tks **tks, char *line);

/*----------------------EXPAND---------------------*/

char			*get_varname(char *prompt, int start, int end);
int				find_varname_env(char *var, char *env_var);
char			*get_var(char *prompt, char **env, int start, int end);
int				len_expand(char *prompt, t_tks *tks, char **env);
char			*expand(char *prompt, char **env, t_tks *tks);
char			*expand_err_code(char *prompt, int start, int end);
t_expand		*init_expand(char **env);
int				no_expand_hd(char *prompt, int dol, t_tks *tks);

/*----------------------LEXER---------------------*/

char			*fill_2_ouf(char *str, int len, int *k);
void			fill_tks(t_tks **tks, char c, int active, int j);

/*----------------------PARSER---------------------*/

t_cmdtab		*lstnew_cmd(char **spl, int index);
void			lst_addback_cmd(t_cmdtab **tab, t_cmdtab *new);
void			lst_addback_red(t_file **red, t_file *new);
t_file			*fill_in(int op, char *file);
t_file			*fill_out(int op, char *file);
int				is_redir(char *arg);
char			**get_paths(char **env);
int				len_cmd(char **split);
char			**get_opt(char **split);
char			*get_abs_path(char **paths, char **opt);
t_cmdtab		*parser(char **lexer);
void			init_files(t_cmdtab *tab, char **spl);
int				lstsize(t_cmdtab *lst);
void			throw_error(t_file *f);
t_cmdtab		*lstlast(t_cmdtab *lst);

/*---------------------HERE_DOC-------------------*/

t_file			*fill_hd(int op, char *eof, t_cmdtab *tab, int count);
char			*ft_strjoin_hd(char *s1, char *s2);
void			here_doc(char *split, int fd);
int				detect_hd(char **spl, t_cmdtab *tab);
int				detect_hd_loop(char **spl, t_cmdtab *tab, int *count);

/*---------------------EXEC-------------------------*/

void			init_pipes(t_data *data);
void			close_pipes(t_data *data);
void			make_dup(int in, int out);
void			redir(t_data *data, t_cmdtab *tab, int index);
void			exec(t_cmdtab *tab, t_data *data);
void			redir_file(t_data *data, t_cmdtab *tab, int index);
int				launch_builtin(t_cmdtab *tab, t_data *data);
void			minishell(t_data *data, t_cmdtab *tab, int i);
void			open_files(t_cmdtab *tab);
void			close_fds(t_cmdtab *tab);
void			close_final_fd(t_cmdtab *tab);
void			close_fds_hd(t_cmdtab *tab);
t_data			*init_data_struct(t_cmdtab *tab, char **env);
void			init_par_data(char **lex, t_cmdtab **tab,
					t_data **data, char **env);
void			exec_final(t_cmdtab *tab, t_data *data);
void			wait_all(t_data *data, t_cmdtab *tab);

/*-------------------BUILT-INS------------------*/

int				len_tab(char **tab);
char			**export(char **env, char **var_exp);
char			**multi_export(char **env, char *var_exp);
int				is_inv_identif(char c);
int				existing_var(char **env, char *var_exp);
void			print_export(t_cmdtab *tab, char **env);
char			**converted_env(char **env);
char			*ft_strdup_quote(char *env);
int				is_builtin(t_cmdtab *tab);
char			**init_unseted(char **env, char *varname);
char			**unset(char **env, char *varname);
void			env_print(char **env, int fd);
void			pwd(int fd);
int				change_dir(char *path);
void			env_print(char **env, int fd);
int				is_there_n(char **cmd);
void			echo(char **cmd, int fd);
char			**ft_strdup_tab(char **tab);
int				is_numeric(char *str);
void			exit_bin(t_cmdtab *tab, t_data *data);
void			launch_cd(t_cmdtab *tab, t_data *data);
void			getcwd_error(char *error);

/*-------------------UTILS------------------*/

char			*allocate_str(char *str);
int				len_tab(char **tab);
int				is_char_num(char c);
long long int	ft_atol(const char *nptr);

/*-------------------ERROR------------------*/

void			check_status(char *cmd);
int				check_redir(t_cmdtab *tab);
void			cmd_error(char *cmd);
void			file_error(char *file);
int				check_access(t_data *data, t_cmdtab *tab);
int				is_inv_identif(char c);
int				error_export(char *var_exp);
void			error_export_print(char *var_exp);
int				consecutive_redir(char *prompt, t_tks *tks);

/*-------------------FREE---------------------*/

t_garbage		**singleton(void);
void			*collect(size_t size);
void			free_gc(void);
void			add_front(t_garbage **lst, void *ptr);
char			**ft_tabdup_env(char **tab);
char			*ft_strdup_env(char *src);

/*-------------------SIGNALS ---------------------*/

void			signal_nl(int num);
void			child_signal(int num);
void			hd_sig_child(int num);
void			hd_sig_parent(int num);
void			sig_unexpected_eof(char *del, int line);

#endif