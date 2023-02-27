/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:27 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 14:06:14 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status;

t_data	*init_data_struct(t_cmdtab *tab, char **env)
{
	t_data	*data;
	int		i;
	
	i = 0;
	data = collect(sizeof(t_data));
	if (!data)
		return (NULL);
	data->p_count = lstsize(tab);
	data->pid = collect(sizeof(int) * data->p_count);
	if (!data->pid)
		return (NULL);
	data->fd = collect(sizeof(int *) * data->p_count);
	if (!data->fd)
		return (NULL);
	while (i < data->p_count)
	{
		data->fd[i] = collect(sizeof(int) * 2);
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
		{
			ft_putstr_fd("\n", 2);
			g_status = 130;
		}
		else if (WTERMSIG(g_status) == 3)
			ft_putstr_fd(" Quit (core dumped)\n", 2);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
        check_status(tab->opt[0]);
        close_fds(tab);
        tab = tab->next;
        i++;
    }
}

void	minishell(t_data *data, t_cmdtab *tab, int i)
{
	if (check_redir(tab))
	{
		redir(data, tab, i);
		if (is_builtin(tab))
		{
			close_pipes(data);
			launch_builtin(tab, data);
			free_gc();
			exit(0);
		}
		else
		{
			close_final_fd(tab);
			close_pipes(data);
			execve(tab->cmd, tab->opt, data->env);
		}
	}
	else
	{
		close_final_fd(tab);
		close_pipes(data);
		free_gc();
		exit(1);
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
			if (!check_access(data, tab))
				minishell(data, tab, i);
		close_final_fd(tab);
        tab = tab->next;
		i++;
	}
	close_pipes(data);
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
	prompt = NULL;
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
			tab = parser(lex);
		if (tab)
			data = init_data_struct(tab, env);
		// printer(tab);
		if (!lex || !tab || !data)
		{
			add_history(prompt);
			continue ;
		}
		if (is_builtin(tab) && data->p_count == 1 && check_redir(tab))
			launch_builtin(tab, data);
		else if (tab->opt && tab->opt[0] && data)
			exec(tab, data);
		close_final_fd(tab);
		env = ft_strdup_tab(data->env);
        add_history(prompt);
    }
    rl_clear_history();
	free_gc();
	ft_putstr_fd("exit\n", 2);
	return (g_status);
}
