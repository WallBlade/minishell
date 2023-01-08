/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:27 by zel-kass          #+#    #+#             */
/*   Updated: 2023/01/08 16:46:09 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data_struct(t_cmdtab *tab)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->p_count = lstsize(tab);
	data->pid = malloc(sizeof(int) * data->p_count);
	if (!data->pid)
		return (NULL);
	data->wpid = 0;
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

void	redir(t_cmdtab *tab, t_data *data, int index)
{
	if (tab->in.fd > 0)
	{
		dup2(tab->in.fd, STDIN_FILENO);
		dup2(data->fd[0], tab->in.fd);
	}
	if (tab->out.fd > 0)
	{
		dup2(tab->out.fd, STDOUT_FILENO);
		dup2(data->fd[1], tab->out.fd);
	}
	else
	{
		if (index == 0 && data->p_count > 1)
			dup2(data->fd[1], STDOUT_FILENO);
		else
			dup2(data->fd[0], STDIN_FILENO);
	}
}

void	exec(t_cmdtab *tab, t_data *data)
{
	int	i;

	i = 0;
	while (tab && i < data->p_count)
	{
		if (i < data->p_count - 1 && pipe(data->fd) == -1)
			return ;
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return ;
		else if (data->pid[i] == 0)
		{
			redir(tab, data, i);
			if (tab->cmd)
			{
				close(data->fd[0]);
				close(data->fd[1]);
				execve(tab->cmd, tab->opt, NULL);
			}
		}
		tab = tab->next;
		i++;
	}
	close(data->fd[0]);
	close(data->fd[1]);
	wait_all(data);
}

int main(int argc, char **argv, char **envp)
{
	char        *prompt;
    char        **lex;
    t_cmdtab    *tab;
	t_data		*data;
	
    tab = NULL;
	(void)argc;
	(void)argv;
    while (1)
    {
        prompt = readline("minishell> ");
        lex = lexer(prompt, envp);
        tab = parser(lex);
		data = init_data_struct(tab);
        // printer(tab);
		exec(tab, data);
        add_history(prompt);
    }
    rl_clear_history();
}