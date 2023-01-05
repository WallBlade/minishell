/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:31:31 by smessal           #+#    #+#             */
/*   Updated: 2023/01/05 23:26:49 by smessal          ###   ########.fr       */
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
# include "../libft/libft.h"

/*-------------------------------Struct---------------------------------------*/

typedef struct s_tks
{
	int		*q;
	int		*dq;
	int		*q_on;
	int		*dq_on;
	int		*p;
	int		*in;
	int		*out;
	int		*ap;
	int		*d_in;
	int		*dol;
	int		*qst;
	char	*prompt;
}				t_tks;

typedef struct s_file
{
	char    *file;
	char    *operator;
	int		fd;
}       t_file;

typedef struct s_cmdtab
{
	struct s_file in;
	struct s_file out;
	char    *cmd;
	char    **opt;
	struct s_cmdtab	*prev;
	struct s_cmdtab *next;
}				t_cmdtab;

/*------------------------------------UTILS----------------*/

int 	ft_tablen(char **tab);
void    free_tab(char **tab);
int		count_elem(char *str, char c);
int		count_d_elem(char *str, char *sub);

/*------------------------------------INIT------------------*/

t_tks	*init_tokens(char *str);
void	init_active_tokens(t_tks **tks, char *line);

/*------------------------------------LEXER------------*/

void	get_squotes(char *line, int *q);
void	get_dquotes(char *line, int *dq);
int		not_quotes(t_tks *tks,int i, char c);
void	fill_tks(t_tks **tks, char c, int active, int j);
void	conditions_quotes(int *dominant, int *tab, int index);
void	conditions_dquotes(int *dominant, int *tab, int index);
void	active_quotes(char *line, t_tks *tks);
void	active_s_tokens(char *line, t_tks *tks, char c);
void	active_d_tokens(char *line, t_tks *tks, char *dc);
void	active_dol_token(char *line, t_tks *tks);
int		count_pipes(char *str, t_tks *tks);
int		*pipe_strlen(char *str, t_tks *tks);
char	**split_2_ouf(char *str, t_tks *tks);
char	**split(char *str);
int		between_squotes(int *q, int i);
int		between_dquotes(int *dq, int i);
int		in_quotes(int *q, int *dq, int i);
int		count_pipes(char *str, t_tks *tks);
int		*pipe_strlen(char *str, t_tks *tks);
int		cwords(char *str);
int		wdlen(char *str, int i);
char	*fill_wrd(char *str, int *i);
char	**split(char *str);
char	**split_2_ouf(char *str, t_tks *tks);
char	*clean_2_ouf(char *prompt, t_tks *tks);
int		is_token(char c);
char	**lexer(char *prompt, char **env);

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

/*-----------------------BUILT-INS------------------*/
int 		len_tab(char **tab);
char    	**export(char **env, char *var_exp);

#endif