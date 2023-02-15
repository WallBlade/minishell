/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:49:27 by zel-kass          #+#    #+#             */
/*   Updated: 2023/02/15 20:26:53 by zel-kass         ###   ########.fr       */
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
	while (i < data->p_count)
	{
		waitpid(data->pid[i], &g_status, 0);
		if (WIFSIGNALED(g_status) == 1)
		{
			printf("test\n");
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
		}
		else
		{
			printf("test\n");
			signal(SIGINT, child_signal);
			signal(SIGQUIT, child_signal);
		}
		g_status = WEXITSTATUS(g_status);
		if (!get_paths(data->env) && !tab->cmd && tab->opt[0])
			tab->in.file = ft_strdup(tab->opt[0]);
        check_status(tab->opt[0], tab->in.file);
        tab = tab->next;
        i++;
    }
}

void	open_files(t_cmdtab *tab)
{
	if (tab->in.file)
	{
		if (!ft_strcmp(tab->in.operator, "<"))
		{
			tab->in.fd = open(tab->in.file, O_RDONLY);
			if (tab->in.fd < 0)
				file_error(tab->in.file);
		}
	}
	if (tab->out.file)
	{
		if (!strcmp(tab->out.operator, ">"))
		{
			tab->out.fd = open(tab->out.file, O_RDWR | O_CREAT | O_TRUNC, 0664);
			if (tab->out.fd < 0)
				file_error(tab->in.file);
		}
		else if (!strcmp(tab->out.operator, ">>"))
		{
			tab->out.fd = open(tab->out.file, O_RDWR | O_APPEND | O_CREAT);
			if (tab->out.fd < 0)
				file_error(tab->in.file);
		}
	}
}

void	minishell(t_data *data, t_cmdtab *tab, int i)
{
	open_files(tab);
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
		/*Appeler fonction free all au cas ou execve ne marche pas*/
	}
}

void	exec(t_cmdtab *tab, t_data *data)
{
	int	i;
    t_cmdtab *tmp;

	i = 0;
    tmp = tab;
	init_pipes(data);
	while (tab && i < data->p_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return ;
		if (data->pid[i] == 0)
		{
			if (!check_access(data, tab))
				minishell(data, tab, i);
		}
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
	env = ft_strdup_tab(envp);
	(void)argc;
	(void)argv;
    while (1)
    {
		signal(SIGINT, signal_nl);
		signal(SIGQUIT, SIG_IGN);
        prompt = readline("minishell> ");
		if (!prompt)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
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
		else if (is_builtin(tab) && data->p_count >= 1)
			launch_builtin(tab, data);
		else
			exec(tab, data);
		if (env)
			free_tab(env);
		env = ft_strdup_tab(data->env);
		free_tab(lex);
		free_cmdtab(tab);
        add_history(prompt);
    }
    rl_clear_history();
	free_tab(env);
	return (g_status);
}
