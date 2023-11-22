/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:14 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/22 19:07:48 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	*data;

	(void)ac;
	(void)av;
	line = NULL;
	data = malloc(sizeof(t_data));
	data->env = ft_copy_env(envp);
	data->bin_env = NULL;
	data->error = NULL;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		line = readline("minishit>");
		if (!line)
			return (ft_free(data->env), free(data), 0);
		add_history(line);
		if (ft_white_line(line) != 1)
			ft_exec_cmd(line, data, envp);
		else
			free(line);
	}
	return (0);
}

void	ft_exec_cmd(char *line, t_data *data, char **envp)
{
	char	**pars;
	t_pars	*cmd;

	pars = ft_parsing(line, data->env);
	cmd = ft_init_cmd_line(pars);
	ft_is_builtin(cmd, data, pars, envp);
	ft_free_tab(pars);
	ft_free_t_pars(cmd);
}

void	ft_free_all(t_data *data, char **args, t_pars *pars)
{
	rl_clear_history();
	ft_free_tab(args);
	ft_free_t_pars(pars);
	ft_free(data->env);
	if (data->error)
		free(data->error);
	free(data);
	exit(0);
}

void	ft_is_builtin(t_pars *cmd, t_data *data, char **pars, char **envp)
{
	if (ft_strncmp(cmd[0].cmd, "cd", 3) == 0)
		ft_cd(data, cmd);
	else if (ft_strncmp(cmd[0].cmd, "export", 7) == 0)
		ft_export(cmd, data, 0);
	else if (ft_strncmp(cmd[0].cmd, "unset", 6) == 0)
		ft_unset(cmd, data, 0);
	else if (ft_strncmp(cmd[0].cmd, "pwd", 4) == 0)
		printf("%s\n", ft_getenv("PWD", data->env));
	else if (ft_strncmp(cmd[0].cmd, "env", 4) == 0)
		ft_print_env(data->env);
	else if (ft_strncmp(cmd[0].cmd, "echo", 5) == 0)
		ft_echo(cmd, 0);
	else if (ft_strncmp(cmd[0].cmd, "exit", 5) == 0)
		ft_free_all(data, pars, cmd);
	else
		ft_execve(cmd, data, envp);
}
