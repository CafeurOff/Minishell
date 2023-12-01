/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:09:55 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/01 15:27:01 by lduthill         ###   ########.fr       */
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
	chdir(ft_getenv("HOME", data->env));
	ft_setenv("OLDPWD", ft_getenv("PWD", data->env), data);
	ft_setenv("PWD", getcwd(NULL, 0), data);
}

/* ft_cd_path()
*  Function for change directory to a path
*  @data : struct with all the data
*  @pars : struct with all the parsed data
*/

void	ft_cd_path(t_pars *pars, t_data *data, int i)
{
	if (chdir(pars[i].args[0]) == -1)
	{
		perror(pars[i].args[0]);
		return ;
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", data->env), data);
	ft_setenv("PWD", getcwd(NULL, 0), data);
}
