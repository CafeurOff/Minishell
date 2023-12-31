/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:13:06 by roroca            #+#    #+#             */
/*   Updated: 2023/12/10 15:44:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_parsing(char *line, t_data *data)
{
	char	**pars;
	int		len;
	int		i;

	pars = malloc(sizeof(char *) * (ft_count_args(line) + 1));
	if (!pars)
		return (NULL);
	pars[ft_count_args(line)] = 0;
	len = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		while ((line[i] == 34 && line[i + 1] == 34)
			|| (line[i] == 39 && line[i + 1] == 39))
			i += 2;
		if (line[i] && line[i] != 32 && (line[i] <= 9 || line[i] >= 13))
		{
			pars[len++] = ft_subarg(ft_strdup(line + i), data);
			if (line[i])
				i = ft_skip_arg(line, i);
		}
	}
	return (pars);
}

int	ft_count_args(char *line)
{
	int	args;
	int	i;

	i = 0;
	args = 0;
	while (line[i])
	{
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		while ((line[i] == 34 && line[i + 1] == 34)
			|| (line[i] == 39 && line[i + 1] == 39))
			i += 2;
		if (line[i] && line[i] != 32 && (line[i] < 9 || line[i] > 13))
		{
			i = ft_skip_arg(line, i);
			args++;
		}
	}
	return (args);
}

char	*ft_subarg(char *line, t_data *data)
{
	int		i;
	int		j;
	char	**var;

	i = 0;
	j = 0;
	line[ft_skip_arg(line, 0)] = 0;
	var = malloc(sizeof(char *) * (ft_count_env_val(line) + 1));
	if (!var)
		return (NULL);
	while (line[i])
	{
		if (line[i] == 39)
			i = ft_skip_arg_quotes(line, i);
		else if (line[i] == 36 && line[i + 1] != 34 && line[i + 1])
		{
			var[j++] = ft_var(line + i, data);
			i = ft_skip_env_val(line, i);
		}
		else if (line[i])
			i++;
	}
	var[j] = 0;
	return (ft_replace_line(line, var));
}
