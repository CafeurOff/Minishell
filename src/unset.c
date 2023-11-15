/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:35:44 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/15 10:00:20 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  ft_unset()
* Function to unset an environment variable
* @pars : the structure with the command and args
* @data : the global structure with the env
*/

int	ft_unset(t_pars *pars, t_data *data, int i)
{
	int	j;

	j = 0;
	if (!pars->args)
		return (110);
	while (pars[i].args[j])
		ft_unsetenv(pars[i].args[j++], data);
	return (0);
}

/*  ft_unsetenv()
* Function to unset an environment variable
* Set all the values to NULL and set to 0 the set value
*/

void	ft_unsetenv(t_pars *pars, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pars[i].args[i])
	{
		while (data->env[j])
		{
			if (ft_strncmp(pars->args[i], data->env[j].id,
					ft_strlen(pars->args[i])) == 0)
			{
				free(data->env[j].id);
				free(data->env[j].value);
				data->env[j].set = 0;
				break ;
			}
			j++;
		}
		i++;
	}
}
