/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:27 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/22 17:48:28 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status;

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
		data->env = ft_strdup_tab(env);
	return (data);
}

void	wait_all(t_data *data, t_cmdtab *tab)
{
	int     i;

	i = 0;
	while (tab && waitpid(data->pid[i], &g_status, 0) > 0)
	{
		if (WTERMSIG(g_status) == 2)
			ft_putstr_fd("\n", 2);
		else if (WTERMSIG(g_status) == 3)
			ft_putstr_fd(" Quit (core dumped)\n", 2);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		// if (!get_paths(data->env) && !tab->cmd && tab->opt[0])
		// 	tab->in->file = ft_strdup(tab->opt[0]);
        check_status(tab->opt[0]);
        tab = tab->next;
        i++;
    }
}

void	minishell(t_data *data, t_cmdtab *tab, int i)
{
	redir(data, tab, i);
	if (is_builtin(tab))
	{
		close_pipes(data);
		launch_builtin(tab, data);
		exit(0);
	}
	else
	{
		close_pipes(data);
		execve(tab->cmd, tab->opt, data->env);
	}
}

void	exec(t_cmdtab *tab, t_data *data)
{
	int			i;
    t_cmdtab	*tmp;

	i = 0;
    tmp = tab;
	init_pipes(data);
	while (tab && i < data->p_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return ;
		signal(SIGINT, child_signal);
		signal(SIGQUIT, child_signal);
		if (data->pid[i] == 0)
		{
			if (!check_access(data, tab))
				minishell(data, tab, i);
		}
		tab = tab->next;
		i++;
	}
	close_pipes(data);
	unlink("temp");
	wait_all(data, tmp);
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
		signal(SIGINT, signal_nl);
		signal(SIGQUIT, SIG_IGN);
        prompt = readline("minishell> ");
		if (!prompt)
			break ;
		lex = lexer(prompt, env);
		if (lex)
        {
			tab = parser(lex);
			data = init_data_struct(tab, env);
		}
		// printer(tab);
		if (!lex)
		{
			add_history(prompt);
			continue ;
		}
		else if (is_builtin(tab) && data->p_count == 1 && !check_access(data, tab))
			launch_builtin(tab, data);
		else if (g_status != 1)
			exec(tab, data);
		if (env)
			free_tab(env);
		env = ft_strdup_tab(data->env);
		// free_tab(lex);
		// free_cmdtab(tab);
        add_history(prompt);
    }
    rl_clear_history();
	free_tab(env);
	ft_putstr_fd("exit\n", 2);
	return (g_status);
}
