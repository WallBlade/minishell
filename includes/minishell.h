/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:31:31 by smessal           #+#    #+#             */
/*   Updated: 2022/12/10 00:42:27 by smessal          ###   ########.fr       */
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

typedef struct s_tok
{
	int *q;
	int *dq;
	int *p;
	int	*in;
	int	*out;
	int	*ap;
	int	*d_in;
	int	*dol;
	int	*qst;
}				t_tok;

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
void    free_tab(char **tab);
t_cmd	*epur_str(char **str);
void    free_tab(char **tab);
int		count_elem(char *str, char c);
t_tok	*init_tokens(char *str);

#endif