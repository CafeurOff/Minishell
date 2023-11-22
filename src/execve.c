/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:18:03 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/22 23:19:49 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_exec()
* Function for execute a command if not a builtin
* @pars : struct with all the parsed data
* @cmd : command to execute
* @envp : environnement
*/

void	ft_exec(t_pars *pars, char *cmd, char **envp)
{
	pid_t	pid;
	int	status;
	char	**args;

	args = ft_joincmd(cmd, pars->args);
    pid = fork();
    if (pid == 0)
        execve(cmd , args, envp);
	else if (pid < 0)
		printf("error pid");
	waitpid(pid, &status, 0);
	ft_free_tab(args);
}

/* ft_execve()
* Function for execute a command if not a builtin
* Parse the PATH for find the command in bin
* @pars : struct with all the parsed data
* @data : struct with all the data
* @envp : environnement
*/

void	ft_execve(t_pars *pars, t_data *data, char **envp)
{
	char	*res;
	char	*path;
	int		i;

	i = 0;
	data->bin_env = ft_split_env(ft_getenv("PATH", data->env), ':');
	if (!data->bin_env)
	{
		printf("%s: connard not found\n", pars->cmd);
		return ;
	}
	while (data->bin_env[i])
	{
		path = ft_strjoin_keep(data->bin_env[i], "/");
		res = ft_strjoin(path, pars->cmd);
		if (access(res, F_OK) == 0)
		{
			ft_exec(pars, res, envp);
			free(res);
			ft_free_tab(data->bin_env);
			return ;
		}
		free(res);
		i++;
	}
	printf("%s: connard not found\n", pars->cmd);
	ft_free_tab(data->bin_env);
	data->bin_env = NULL;
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
