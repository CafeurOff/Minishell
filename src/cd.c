/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:09:55 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/16 18:41:36 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTES :
*   cd ~ : Back to $HOME
*   cd $ENV : if the variable is a right path cd to the path.
*/


/* ft_cd()
*	Function for change directory
*	@data : struct with all the data
*	@pars : struct with all the parsed data
*/

void	ft_cd(t_data *data, t_pars *pars)
{
	int	i;

	i = 0;
	while (pars->args[i])
	{
		if (pars->args[i][0] == '~')
			ft_cd_home(data);
		else if (pars->args[i][0] == '$')
			ft_cd_env(data, pars->args[i]);
		else
			ft_cd_path(data, pars[i].args[i]);
		i++;
	}
}
/* ft_cd_home()
*  Function for change directory to $HOME
*  @data : struct with all the data
*/

void	ft_cd_home(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i].id)
	{
		if (ft_strncmp(data->env[i].id, "HOME", ft_strlen(data->env[i].id)) == 0)
		{
			chdir(data->env[i].value);
			return ;
		}
		i++;
	}
}
/*	ft_cd_env()
*	Function for change directory to a path in an env variable
*	@data : struct with all the data
*	@pars : struct with all the parsed data
*/

void	ft_cd_env(t_data *data, t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pars->args[i][j] != '$')
		j++;
	while (data->env[i].id)
	{
		if (ft_strncmp(data->env[i].id, pars->args[i] + j + 1,
				ft_strlen(data->env[i].id)) == 0)
		{
			chdir(data->env[i].value);
			return ;
		}
		i++;
	}
}

/* ft_cd_path()
*  Function for change directory to a path
*  @data : struct with all the data
*  @pars : struct with all the parsed data
*/
void	ft_cd_path(t_data *data, t_pars *pars)
{
	int	i;

	i = 0;
	while (pars->args[i])
	{
		if (chdir(pars->args[i]) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n",
				pars->args[i]);
			return ;
		}
		i++;
	}
}
