/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:31:31 by smessal           #+#    #+#             */
/*   Updated: 2023/01/13 16:09:53 by smessal          ###   ########.fr       */
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
	int		wpid;
	int		p_count;
	pid_t	*pid;
}		t_data;

typedef struct s_cmdtab
{
	struct s_file in;
	struct s_file out;
	char    *cmd;
	char    **opt;
	struct s_cmdtab	*prev;
	struct s_cmdtab *next;
}				t_cmdtab;

/*------------------------------------INIT------------------*/

t_tks	*init_tokens(char *str);
void	init_active_tokens(t_tks **tks, char *line);

/*----------------------EXPAND---------------------*/

char	*get_varname(char *prompt, int start, int end);
char	*get_var(char *prompt, char **env, int start, int end);
int		len_expand(char *prompt, t_tks *tks, char **env);
char	*expand(char *prompt, char **env, t_tks *tks);

/*----------------------PARSER---------------------*/

t_cmdtab    *lstnew_par(char *pipe);
void    	lst_addback_par(t_cmdtab **tab, t_cmdtab *new);
char    	*here_doc(char **split, int i);
void    	fill_in(t_cmdtab **par, char **split);
void    	fill_out(t_cmdtab **par, char **split);
int 		is_redir(char *arg);
char		**get_paths(void);
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
void		redir(t_data *data, int	index);
void		exec(t_cmdtab *tab, t_data *data);

/*-----------------------BUILT-INS------------------*/

int 		len_tab(char **tab);
char    	**export(char **env, char *var_exp);
char    	**unset(char **env, char *varname);
void    	env_print(char **env, int fd);
void		pwd();

#endif