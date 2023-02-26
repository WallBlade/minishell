/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:05:45 by smessal           #+#    #+#             */
/*   Updated: 2023/02/26 17:58:55 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)s;
	while (i < n)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int main()
{
	int i = 0;
	char *s = (char *)collect(sizeof(char) * 40);
	s = ft_memset(s, 'b', 30);
	while (i < 40)
	{
		printf("%c", s[i]);
		i++;
	}
    return (0);
}
*/
