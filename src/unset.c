/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:35:44 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/07 15:58:48 by lduthill         ###   ########.fr       */
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
	if (ft_unset_error(pars[i].args, data) == 1)
		return (0);
	ft_unsetenv(pars[i].args, data);
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
	while (str[i])
	{
		j = 0;
		while (data->env[j].id)
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
/* ft_unset_error()
* Check if there is an error in the command
* @str : string to check
* @data : struct with all the data
* return : 1 if error, 0 if not
*/

int	ft_unset_error(char **str, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		ft_unset_identifier_error(str, data);
		while (str[i][j])
		{
			if (str[i][j] == 61)
				break ;
			if (ft_is_special(i, j, str, data) == 0)
				return (1);
			if (ft_isalnum(str[i][j]) == 0 && str[i][j] != 95)
			{
				printf("bash: unset: `%s': not a valid identifier\n", str[i]);
				data->error = "1";
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/* ft_unset_identifier_error()
* Check if the identifier is valid
* @str : string to check
* @data : struct with all the data
* return : 1 if error, 0 if not
*/

int		ft_unset_identifier_error(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i][0] >= '0' && str[i][0] <= '9')
	{
		printf("bash: unset: `%s': not a valid identifier\n", str[i]);
		data->error = "1";
		return (1);
	}
	if (str[i][0] == 61)
	{
		printf("bash: unset: `%s': not a valid identifier\n", str[i]);
		data->error = "1";
		return (1);
	}
	if (str[i][0] == 32)
	{
		printf("bash: unset: `%s': not a valid identifier\n", str[i]);
		data->error = "1";
		return (1);
	}
	return (0);
}

/* ft_is_special()
* Check if the char is special
* @i : index of the string
* @j : index of the char
* @str : string to check
* @data : struct with all the data
* return : 1 if special, 0 if not
*/

int	ft_is_special(int i, int j, char **str, t_data *data)
{
	if (str[i][j] == '=' && str[i][j + 1] == 61)
	{
		printf("bash: unset: `%s': not a valid identifier\n", str[i]);
		data->error = "1";
		return (0);
	}
	return (1);
}


