/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:27 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/27 19:09:31 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

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
	int	i;

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

void	minishell_exec(t_data *data, t_cmdtab *tab)
{
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

void	minishell(t_data *data, t_cmdtab *tab, int i)
{
	if (check_redir(tab))
	{
		redir(data, tab, i);
		minishell_exec(data, tab);
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

void	init_par_data(char **lex, t_cmdtab **tab, t_data **data, char **env)
{
	if (lex)
		*tab = parser(lex);
	if (tab)
		*data = init_data_struct(*tab, env);
}

void	exec_final(t_cmdtab *tab, t_data *data)
{
	if (is_builtin(tab) && data->p_count == 1 && check_redir(tab))
		launch_builtin(tab, data);
	else if (tab->opt && tab->opt[0] && data)
		exec(tab, data);
	close_final_fd(tab);
}

void	printer(t_cmdtab *tab)
{
	t_cmdtab	*temp;

	temp = tab;
	while (temp)
	{
		if (temp->cmd)
			printf("abs_path: %s\n", temp->cmd);
		if (temp->opt)
		{
			for (int i = 0; temp->opt[i]; i++)
				printf("option_%d %s\n", i, temp->opt[i]);
		}
		temp = temp->next;
	}
}

void	mini_loop(char **env)
{
	char		*prompt;
	char		**lex;
	t_cmdtab	*tab;
	t_data		*data;

	tab = NULL;
	while (1)
	{
		signal(SIGINT, signal_nl);
		signal(SIGQUIT, SIG_IGN);
		prompt = readline("minishell> ");
		if (!prompt)
			break ;
		if (prompt[0])
			add_history(prompt);
		lex = lexer(prompt, env);
		init_par_data(lex, &tab, &data, env);
		if (!lex || !tab || !data)
			continue ;
		printer(tab);
		exec_final(tab, data);
		env = ft_strdup_tab(data->env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		**env;

	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Fuck off !\n", 2);
		exit(2);
	}
	env = ft_strdup_tab(envp);
	(void)argc;
	(void)argv;
	mini_loop(env);
	rl_clear_history();
	free_gc();
	ft_putstr_fd("exit\n", 2);
	return (g_status);
}
