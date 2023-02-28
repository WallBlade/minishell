/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:27 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/28 15:53:50 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

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
