/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:15:04 by smessal           #+#    #+#             */
/*   Updated: 2023/02/27 13:25:50 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_inv_identif(char c)
{
	char	*invalid;
	int		i;

	i = 0;
	invalid = allocate_str(".?+/<>");
	while (invalid && invalid[i])
	{
		if (c == invalid[i])
			return (1);
		i++;
	}
	return (0);
}

int	error_export(char *var_exp)
{
	int	i;

	i = 0;
	while (var_exp && var_exp[i] && var_exp[i] != '=')
	{
		if (is_inv_identif(var_exp[i]))
			return (1);
		i++;
	}
	return (0);
}

void	error_export_print(char *var_exp)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var_exp, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
}
