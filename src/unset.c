/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:35:44 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/16 15:29:53 by lduthill         ###   ########.fr       */
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
		return (110); // Make error functions for free and display error message.
	if (ft_specchar(pars[i].args) == 1)
		return (110); // Error message and free
	while (pars[i].args[j])
		ft_unsetenv(pars[i++].args, data);
	return (0);
}

/*  ft_unsetenv()
* Function to unset an environment variable
* Set all the values to NULL and set to 0 the set value
*/

void	ft_unsetenv(char **str, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (data->env[j].id) // .id ?
		{
			if (ft_strncmp(str[i], data->env[j].id,
					ft_strlen(str[i])) == 0)
			{
				data->env[j].set = 0;
				break ;
			}
			j++;
		}
		i++;
	}
}
