/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:05:18 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/14 12:10:27 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

typedef	struct s_expand
{
	int		start;
	int		i;
	int		j;
	int		k;
	int		l;
	char	**env;
}				t_expand;

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
int 	ft_tablen(char **tab);
void    free_tab(char **tab);
int		count_elem(char *str, char c);
int		count_d_elem(char *str, char *sub);
int		scan_2_ouf(char **sdf);
char	**split_syn(char *str);

#endif