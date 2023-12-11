/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:49:42 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/11 21:39:24 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_identifier_error()
**	Function for check if the string is an identifier for export
**	@str : string to check
**	@data : struct with all the data
*/

int	ft_identifier_error(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i][0] >= '0' && str[i][0] <= '9')
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = 1;
		return (1);
	}
	if (str[i][0] == 61)
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = 1;
		return (1);
	}
	if (str[i][0] == 32)
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = 1;
		return (1);
	}
	return (0);
}

/*	ft_exit()
**	Function for exit the program with code error
**	@data : struct with all the data
**	@args : arguments
**	@cmd : struct with all the parsed data
**	@i : index
*/

void	ft_exit(t_data *data, char **args, t_pars *cmd, int i)
{
	if (i != 0 || cmd[i + 1].cmd)
		return ;
	if (!cmd[i].args)
		ft_free_all(data, args, cmd);
	if (cmd[i].args[1] || ft_isdigit(cmd[i].args[0]))
	{
		if (ft_isdigit(cmd[i].args[0]))
			printf("bash: exit: %s: numeric"
				"argument required\n", cmd[i].args[0]);
		else
			printf("bash: exit: too many arguments\n");
		return ;
	}
	data->error = ft_atoi(cmd[i].args[0]) % 256;
	ft_free_all(data, args, cmd);
}

/*	ft_access_path()
**	Function for check if the path is valid for execve
**	@res : path
**	@pars : struct with all the parsed data
**	@j : index of the command
**	@data : struct with all the data
*/

int	ft_access_path(char *res, t_pars *pars, int j, t_data *data)
{
	if (access(res, F_OK) == 0)
	{
		ft_exec(pars + j, res, data);
		free(res);
		ft_free_tab(data->bin_env);
		return (1);
	}
	free(res);
	return (0);
}

/*	ft_execve_error()
**	Function for print error if execve fail
**	@pars : struct with all the parsed data
**	@data : struct with all the data
**	@j : index of the command
*/

void	ft_execve_error(t_pars *pars, t_data *data, int j)
{
	printf("%s: command not found\n", pars[j].cmd);
	data->error = 127;
	ft_free_tab(data->bin_env);
	data->bin_env = NULL;
}
