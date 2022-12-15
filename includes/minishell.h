/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:31:31 by smessal           #+#    #+#             */
/*   Updated: 2022/12/15 21:01:01 by zel-kass         ###   ########.fr       */
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
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "../libft/libft.h"

/*-------------------------------Struct---------------------------------------*/

typedef struct s_cmd
{
	char    **brut;
	void    *next;
}               t_cmd;

typedef struct s_tks
{
	int *q;
	int *dq;
	int	*q_on;
	int	*dq_on;
	int *p;
	int	*in;
	int	*out;
	int	*ap;
	int	*d_in;
	int	*dol;
	int	*qst;
}				t_tks;

typedef struct s_file
{
	char    *file;
	char    *operator;
}       t_file;

typedef struct s_lexer
{
	struct s_file in;
	struct s_file out;
	char    del;
	char    *cmd;
	char    *opt;
	struct s_lexer *child;
	struct s_lexer *next;
}       t_lexer;

/*------------------------------------UTILS----------------*/

int 	ft_tablen(char **tab);
t_cmd   *lstnew(void);
void    lstaddback(t_cmd **list, t_cmd *new);
t_cmd	*epur_str(char **str);
void    free_tab(char **tab);
int		count_elem(char *str, char c);
int		count_d_elem(char *str, char *sub);

/*------------------------------------INIT------------------*/

t_tks	*init_tokens(char *str);
void	init_active_tokens(t_tks **tks, char *line);

/*------------------------------------GET_TOKENS------------*/

// void	get_quotes(char *line, t_tks *tks);
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
char	*fill_wrd(char *str, int i);
char	**split(char *str);
char	**split_2_ouf(char *str, t_tks *tks);

#endif