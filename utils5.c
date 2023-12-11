/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:33:38 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/11 16:56:03 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_isalnum()
*  Check if the char is alphanumeric
*  @i : char to check
*  return : 1 if alphanumeric, 0 if not
*/

int	ft_isalnum(int i)
{
	if ((i >= 65 && i <= 90) || (i >= 97 && i <= 122) || (i >= 48 && i <= 57))
		return (1);
	return (0);
}

/* ft_join_env()
*  Join the env for execve
*  @data : struct with all the data
*  return : env for execve
*/

char	**ft_join_env(t_data *data)
{
	int		i;
	char	**res;
	int		set;

	set = 0;
	i = 0;
	while (data->env[i].id)
		if (data->env[i++].set == 1)
			set++;
	res = malloc(sizeof(char *) * (set + 1));
	if (!res)
		return (NULL);
	i = -1;
	set = 0;
	while (data->env[++i].id)
	{
		if (data->env[i].set == 1 && data->env[i].value != NULL)
		{
			res[set] = ft_strjoin_keep(data->env[i].id, "=");
			res[set] = ft_strjoin(res[set], data->env[i].value);
			set++;
		}
	}
	res[set] = NULL;
	return (res);
}

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 48 || s[i] > 57) && (s[i] != 45 && s[i] != 43))
			return (1);
		i++;
	}
	return (0);
}
