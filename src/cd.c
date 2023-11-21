/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:09:55 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/21 15:48:18 by roroca           ###   ########.fr       */
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
		else
			ft_cd_path(pars);
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

/* ft_cd_path()
*  Function for change directory to a path
*  @data : struct with all the data
*  @pars : struct with all the parsed data
*/
void	ft_cd_path(t_pars *pars)
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
