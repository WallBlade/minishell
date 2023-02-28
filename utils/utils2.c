/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:38:07 by smessal           #+#    #+#             */
/*   Updated: 2023/02/28 16:22:05 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	numlen(int num)
{
	int	i;

	i = 0;
	if (num < 0)
	{
		i++;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int	is_numeric(char *str)
{
	if (numlen(ft_atoi(str)) == ft_strlen(str))
		return (1);
	return (0);
}

int	is_char_num(char c)
{
	char	*nums;
	int		i;

	i = 0;
	printf("test\n");
	nums = allocate_str("0123456789");
	if (!nums)
		return (0);
	while (nums && nums[i])
	{
		if (c == nums[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_hd(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*dest;

	if (!s1)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)collect(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i++] = s2[j];
	dest[i] = '\0';
	return (dest);
}
