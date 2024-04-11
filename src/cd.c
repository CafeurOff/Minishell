/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:09:55 by lduthill          #+#    #+#             */
/*   Updated: 2024/04/11 13:51:58 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_cd()
*	Function for change directory
*	@data : struct with all the data
*	@pars : struct with all the parsed data
*/

void	ft_cd(t_data *data, t_pars *pars, int i)
{
	if (cd_error_management(data, pars, i) == 1)
		return ;
	if (pars[i].args[0][0] == '~')
		ft_cd_home(data);
	else
		ft_cd_path(pars, data, i);
}
/* ft_cd_home()
*  Function for change directory to $HOME
*  @data : struct with all the data
*/

void	ft_cd_home(t_data *data)
{
	if (chdir(ft_getenv("HOME", data->env)) == -1) // Fix a segfault issues (cd when PATH environnement is unset)
		return ;
	else
	{
		ft_setenv("OLDPWD", ft_getenv("PWD", data->env), data);
		ft_setenv("PWD", getcwd(NULL, 0), data);
	}
}

/* ft_cd_path()
*  Function for change directory to a path
*  @data : struct with all the data
*  @pars : struct with all the parsed data
*/

void	ft_cd_path(t_pars *pars, t_data *data, int i)
{
	if (getcwd(NULL, 0) == NULL)
	{
		printf("minishell: cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n");
		data->error = 1;
		return ;
	}
	if (chdir(pars[i].args[0]) == -1)
	{
		if (errno == ENOTDIR)
		{
			perror(pars[i].args[0]);
			data->error = 1;
			return ;
		}
		perror(pars[i].args[0]);
		data->error = 127;
		return ;
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", data->env), data);
	ft_setenv("PWD", getcwd(NULL, 0), data);
}

int	cd_error_management(t_data *data, t_pars *pars, int i)
{
	if (pars[i].args == NULL)
	{
		ft_cd_home(data);
		return (1);
	}
	if (pars[i].args[0][0] == '-')
	{
		printf("minishell: cd: %s: invalid option\n", pars[i].args[0]);
		data->error = 2;
		return (1);
	}
	if (pars[i].args[1] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		data->error = 1;
		return (1);
	}
	return (0);
}

/* ft_pwd()
*  Function for print the current directory
*  @data : struct with all the data
*/

void	ft_pwd(t_data *data)
{
	if (getcwd(NULL, 0) == NULL)
	{
		printf("pwd: error retrieving current directory:"
			"getcwd: cannot access parent directories:"
			"No such file or directory\n");
		return ;
	}
	printf("%s\n", ft_getenv("PWD", data->env));
}

