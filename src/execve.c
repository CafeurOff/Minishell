/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:18:03 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/09 02:21:39 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_exec()
* Function for execute a command if not a builtin
* @pars : struct with all the parsed data
* @cmd : command to execute
* @envp : environnement
*/

void	ft_exec(t_pars *pars, char *cmd, t_data *data)
{
	pid_t	pid;
	int		status;
	char	**args;

	data->join_env = ft_join_env(data);
	args = ft_joincmd(cmd, pars->args);
	pid = fork();
	if (pid == 0)
	{
		ft_setup_signal();
		execve(cmd, args, data->join_env);
	}
	else if (pid < 0)
		printf("error pid");
	else
		waitpid(pid, &status, 0);
	ft_free_tab(data->join_env);
	ft_free_tab(args);
}

/* ft_execve()
* Function for execute a command if not a builtin
* Parse the PATH for find the command in bin
* @pars : struct with all the parsed data
* @data : struct with all the data
* @envp : environnement
*/

void	ft_execve(t_pars *pars, t_data *data, int j)
{
	char	*res;
	char	*path;
	int		i;

	i = 0;
	if (pars[j].cmd[0] == '.' || pars[j].cmd[0] == '/')
	{
		ft_exec_path(pars, data, j);
		return ;
	}
	data->bin_env = ft_split_env(ft_getenv("PATH", data->env), ':');
	if (!data->bin_env)
	{
		printf("%s: command not found\n", pars[j].cmd);
		return ;
	}
	while (data->bin_env[i])
	{
		path = ft_strjoin_keep(data->bin_env[i], "/");
		res = ft_strjoin(path, pars[j].cmd);
		if (access(res, F_OK) == 0)
		{
			ft_exec(pars + j, res, data);
			free(res);
			ft_free_tab(data->bin_env);
			return ;
		}
		free(res);
		i++;
	}
	printf("%s: command not found\n", pars[j].cmd);
	data->error = errno;
	ft_free_tab(data->bin_env);
	data->bin_env = NULL;
}

/* ft_exec_path()
* Function for execute a command with a path
* Parse the PATH for find the command in bin
* @pars : struct with all the parsed data
* @data : struct with all the data
* @j : index of the command
*/

void	ft_exec_path(t_pars *pars, t_data *data, int j)
{
	if (ft_is_cmd(pars, data, j) == 1)
		return ;
	if (access(pars[j].cmd, X_OK) == 0)
	{
		ft_exec(pars + j, pars[j].cmd, data);
		return ;
	}
	printf("%s: command not found\n", pars[j].cmd);
	data->error = 127;
	return ;
}

/* ft_is_cmd()
* Function for check if the command is a valid command
* @pars : struct with all the parsed data
* @data : struct with all the data
*/

int	ft_is_cmd(t_pars *pars, t_data *data, int j)
{
	int	i;

	i = 0;
	while (pars[j].cmd[i])
	{
		if (pars[j].cmd[i] == '.' || pars[j].cmd[i] == '/')
		{
			if (strncmp(pars[j].cmd + i, "../", 3) == 0
				|| strcmp(pars[j].cmd + i, "./") == 0)
			{
				printf("%s: Is a directory\n", pars[j].cmd);
				data->error = errno;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

/* ft_joincmd()
* Function for join cmd and args in one tab
* @cmd : command
* @args : args of the command
*/

char	**ft_joincmd(char *cmd, char **args)
{
	int		i;
	char	**res;

	i = 0;
	if (!args)
	{
		res = malloc(sizeof(char *) * 2);
		res[0] = ft_strdup(cmd);
		res[1] = NULL;
		return (res);
	}
	while (args[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	res[i] = ft_strdup(cmd);
	while (args[i])
	{
		res[i + 1] = ft_strdup(args[i]);
		i++;
	}
	res[i + 1] = '\0';
	return (res);
}
