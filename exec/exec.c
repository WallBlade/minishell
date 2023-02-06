/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:27 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/06 18:42:57 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data_struct(t_cmdtab *tab, char **env)
{
	t_data	*data;
	int		i;
	
	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->p_count = lstsize(tab);
	data->pid = malloc(sizeof(int) * data->p_count);
	if (!data->pid)
		return (NULL);
	data->wpid = 0;
	data->fd = malloc(sizeof(int *) * data->p_count);
	if (!data->fd)
		return (NULL);
	while (i < data->p_count)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (!data->fd[i])
			return (NULL);
		i++;
	}
	if (env)
		data->env = env;
	return (data);
}

void	wait_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_count)
	{
		waitpid(data->pid[i], &data->wpid, 0);
		i++;
	}
}

void	exec(t_cmdtab *tab, t_data *data)
{
	int	i;

	i = 0;
	init_pipes(data);
	while (tab && i < data->p_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return ;
		if (data->pid[i] == 0)
		{
			redir(data, tab, i);
			if (is_builtin(tab))
			{
				close_pipes(data);
				launch_builtin(tab, data);
				exit(0);
			}
			else if (tab->cmd)
			{
				close_pipes(data);
				execve(tab->cmd, tab->opt, NULL);
			}
		}
		tab = tab->next;
		i++;
	}
	close_pipes(data);
	wait_all(data);
}

int main(int argc, char **argv, char **envp)
{
	char        *prompt;
    char        **lex;
    t_cmdtab    *tab;
	t_data		*data;
	char		**env;
	
    tab = NULL;
	env = ft_strdup_tab(envp);
	(void)argc;
	(void)argv;
    while (1)
    {
        prompt = readline("minishell> ");
        lex = lexer(prompt, env);
        tab = parser(lex);
		data = init_data_struct(tab, env);
        // printer(tab);
		if (is_builtin(tab) && data->p_count == 1)
			launch_builtin(tab, data);
		else
			exec(tab, data);
		env = ft_strdup_tab(data->env);
        add_history(prompt);
    }
    rl_clear_history();
}
