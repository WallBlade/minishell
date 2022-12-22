/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:42:00 by smessal           #+#    #+#             */
/*   Updated: 2022/12/22 19:49:15 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_parser    *init_par_index(int len)
// {
//     t_parser    *par;
//     t_parser    *temp;
//     t_parser    *temp2;
//     int         i;

//     i = 0;
//     par = malloc(sizeof(t_parser));
//     if (!par)
//         return (NULL);
//     par->index = i++;
//     par->len_pip = len;
//     par->prev = NULL;
//     temp2 = par;
//     while (i < len)
//     {
//         temp = malloc(sizeof(t_parser));
//         temp->index = i++;
//         temp->len_pip = len;
//         temp2->next = temp;
//         temp2 = temp2->next;
//         temp2->prev = temp;
//     }
//     temp2->next = NULL;
//     return (par);
// }