/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:14 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/01 16:30:52 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* main()
*  Main function of the minishell
*  @ac : number of args
*  @av : args
*  @envp : environnement
*/

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
	data->join_env = NULL;
	data->error = "0";
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		line = readline("minishit>");
		if (!line)
			return (ft_free(data->env), free(data), rl_clear_history(), 0);
		add_history(line);
		if (ft_white_line(line) != 1 && ft_unlosed_quotes(line) != 1)
			ft_exec_cmd(line, data);
		else
			free(line);
	}
	return (0);
}

/* ft_exec_cmd()
*  Function for execute a command
*  @line : line of the command
*  @data : struct with all the data
*  @envp : environnement
*/

void	ft_exec_cmd(char *line, t_data *data)
{
	char	**pars;
	t_pars	*cmd;

	pars = ft_parsing(line, data);
	free(line);
	if (ft_syntax_error(pars, data))
	{
		ft_free_tab(pars);
		return ;
	}
	cmd = ft_init_cmd_line(pars);
	ft_is_builtin(cmd, data, pars, 0);
	ft_free_tab(pars);
	ft_free_t_pars(cmd);
}

/* ft_free_all()
*  Function for free all the malloc
*  @data : struct with all the data
*  @args : args of the command
*  @pars : struct with all the parsed data
*/

void	ft_free_all(t_data *data, char **args, t_pars *pars)
{
	rl_clear_history();
	ft_free_tab(args);
	ft_free_t_pars(pars);
	ft_free(data->env);
	free(data);
	exit(0);
}

/* ft_is_builtin()
*  Function for execute a builtin command
*  @cmd : struct with all the parsed data
*  @data : struct with all the data
*  @pars : struct with all the parsed data
*  @envp : environnement
*/

void	ft_is_builtin(t_pars *cmd, t_data *data, char **pars, int i)
{
	if (cmd[i].del != NULL)
		ft_delimiter(cmd);
	if (ft_strncmp(cmd[i].cmd, "cd", 3) == 0)
		ft_cd(data, cmd, i);
	else if (ft_strncmp(cmd[i].cmd, "export", 7) == 0)
		ft_export(cmd, data, i);
	else if (ft_strncmp(cmd[i].cmd, "unset", 6) == 0)
		ft_unset(cmd, data, i);
	else if (ft_strncmp(cmd[i].cmd, "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(cmd[i].cmd, "env", 4) == 0)
		ft_print_env(data->env);
	else if (ft_strncmp(cmd[i].cmd, "echo", 5) == 0)
		ft_echo(cmd, i);
	else if (ft_strncmp(cmd[i].cmd, "exit", 5) == 0)
		ft_free_all(data, pars, cmd);
	else
		ft_execve(cmd, data);
}

void	ft_pwd(t_data *data)
{
	if (getcwd(NULL, 0) == NULL)
	{
		printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return ;
	}
	printf("%s\n", ft_getenv("PWD", data->env));
}
