/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:30 by roroca            #+#    #+#             */
/*   Updated: 2023/11/21 14:51:26 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_white_line()
	Function to verif if the line is not compose from only whitespace
*/

int	ft_white_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && (line[i] >= 9 || line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}
/*	ft_skip_arg()
	Initially a function to skip charachters of a same arg
	But can also be used to count the lenght of an arg
*/

int	ft_skip_arg(char *line, int i)
{
    if ((line[i] == 60 && line[i + 1] == 60) || (line[i] == 62 && line[i + 1] == 62))
		return(i + 2);
	if (line[i] == 124 || line[i] == 60 || line[i] == 62)
		return(i + 1);
	if (line[i] == 39 || line[i] == 34)
		i = ft_skip_arg_quotes(line, i);
	else
	{
		while (line[i])
		{
			if (line[i] == 124 || line[i] == 32 || line[i] == 34 || line[i] == 39 || line[i] == 36
				|| (line[i] >= 9 && line[i] <= 13) || line[i] == 60 || line[i] == 62)
				return (i);
			i++;
		}
	}
	return (i);
}

int	ft_skip_arg_quotes(char *line, int i)
{
	int	flag;

	flag = line[i];
	i++;
	while (line[i + 1] && line[i] != flag)
		i++;
	return (i + 1);
}

int	ft_skip_env_val(char *line, int i)
{
	while (line[i] && line[i] != 36 && line[i] != 32 && (line[i] < 9 || line[i] > 13))
	{
		i++;
	}
	return (i);
}
