/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:31:31 by smessal           #+#    #+#             */
/*   Updated: 2023/02/18 15:39:57 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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

extern int g_status;

/*-------------------------------Struct---------------------------------------*/

typedef struct s_file
{
	char    *file;
	char    *operator;
	int		fd;
}       t_file;

typedef	struct s_data
{
	int		**fd;
	int		is_abs;
	int		p_count;
	pid_t	*pid;
	char	**env;
}		t_data;

typedef struct s_cmdtab
{
	struct s_file in;
	struct s_file out;
	char    *cmd;
	char    **opt;
	struct s_cmdtab *next;
}				t_cmdtab;

/*------------------------------------INIT------------------*/

t_tks	*init_tokens(char *str);
void	init_active_tokens(t_tks **tks, char *line);

/*----------------------EXPAND---------------------*/

char	*get_varname(char *prompt, int start, int end);
int		find_varname_env(char *var, char *env_var);
char	*get_var(char *prompt, char **env, int start, int end);
int		len_expand(char *prompt, t_tks *tks, char **env);
char	*expand(char *prompt, char **env, t_tks *tks);
char 	*expand_err_code(char *prompt, int start, int end);

/*----------------------PARSER---------------------*/

t_cmdtab    *lstnew_par(char *pipe);
void    	lst_addback_par(t_cmdtab **tab, t_cmdtab *new);
void		here_doc(char *split, int i);
void    	fill_in(t_cmdtab **par, char **split);
void    	fill_out(t_cmdtab **par, char **split);
int 		is_redir(char *arg);
char		**get_paths(char **env);
int 		len_cmd(char **split);
char    	**get_opt(char **split);
char    	*get_abs_path(char **paths, char **opt);
t_cmdtab    *parser(char **lexer);
void    	printer(t_cmdtab *tab);
int			lstsize(t_cmdtab *lst);

/*---------------------EXEC-------------------------*/

void		init_pipes(t_data *data);
void		close_pipes(t_data *data);
void		make_dup(int in, int out);
void		redir(t_data *data, t_cmdtab *tab, int index);
void		exec(t_cmdtab *tab, t_data *data);
void    	redir_file(t_data *data, t_cmdtab *tab, int index);
int			launch_builtin(t_cmdtab *tab, t_data *data);
void		minishell(t_data *data, t_cmdtab *tab, int i);
void		open_files(t_cmdtab *tab);

/*-----------------------BUILT-INS------------------*/

int 		len_tab(char **tab);
char    	**export(char **env, char **var_exp);
char    	**multi_export(char **env, char *var_exp);
int 		is_inv_identif(char c);
int    		existing_var(char **env, char *var_exp);
void    	print_export(t_cmdtab *tab, char **env);
char    	**converted_env(char **env);
char		*ft_strdup_quote(char *env);
int			is_builtin(t_cmdtab *tab);
char    	**unset(char **env, char *varname);
void    	env_print(char **env, int fd);
void		pwd(int fd);
int			change_dir(char *path);
void    	env_print(char **env, int fd);
int			is_there_n(char **cmd);
void		echo(char **cmd, int fd);
char		**ft_strdup_tab(char **tab);
int 		is_numeric(char *str);
void    	exit_bin(t_cmdtab *tab, t_data *data);

/*-------------------UTILS------------------*/

char	*allocate_str(char *str);
int 	len_tab(char **tab);


/*-------------------ERROR------------------*/

void	check_status(char *cmd, char *file);
void	cmd_error(char *cmd);
void	file_error(char *file);
int		check_access(t_data *data, t_cmdtab *tab);
int 	is_inv_identif(char c);
int 	error_export(char *var_exp);
void    error_export_print(char *var_exp);

/*-------------------FREE---------------------*/

/*Lexer*/
void	free_tks(t_tks *tks);
void	free_tks2(t_tks *tks);

/*Parser*/
void	free_cmdtab(t_cmdtab *tab);
void	free_data_struct(t_data *data);

/*-------------------SIGNALS ---------------------*/

void	signal_nl(int num);
void	child_signal(int num);
void	here_doc_signal();

#endif