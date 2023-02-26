/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:55:30 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/26 18:41:47 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_garbage	**singleton(void)
{
	static t_garbage	*collect;

	return (&collect);
}

void	*collect(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	add_front(singleton(), ptr);
	return (ptr);
}

int	lstsize_garb(t_garbage *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	add_front(t_garbage **lst, void *ptr)
{
	t_garbage	*collect;
	
	collect = malloc(sizeof(t_garbage));
	if (!collect)
		return ;
	collect->ptr = ptr;
	collect->next = *lst;
	*lst = collect;
	return ;
}

void	free_gc()
{
	//int			len;
	t_garbage	*collect;
	t_garbage	*tmp;

	collect = (*singleton());
	printf("test %p\n", collect);
	while (collect)
	{
		free(collect->ptr);
		collect->ptr = NULL;
		tmp = collect;
 		collect = collect->next;
		free(tmp);
	}
	/*
	len = lstsize_garb(collect);
	while (len > 0)
	{
		tmp = collect->next;
		free(collect->ptr);
		free(collect);
		collect = tmp;
		len--;
	}
	*/
}