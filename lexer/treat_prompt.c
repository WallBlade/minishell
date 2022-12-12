/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:01:19 by smessal           #+#    #+#             */
/*   Updated: 2022/12/12 23:15:11 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*epur_str(char **str)
// {
// 	t_cmd	*brut;
// 	t_cmd	*temp;
// 	int		i;

// 	i = 0;
// 	brut = malloc(sizeof(t_cmd));
// 	if (!brut)
// 		return (NULL);
// 	brut = NULL;
// 	while (str && str[i])
// 	{
// 		temp = malloc(sizeof(t_cmd));
// 		if (!temp)
// 			return (NULL);
// 		temp->next = NULL;
// 		temp->brut = ft_split(str[i], ' ');
// 		lstaddback(&brut, temp);
// 		i++;
// 	}
// 	return (brut);	
// }

char    *epur_str(char *str, tks *tks)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] && betwe)
    }
}