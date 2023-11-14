/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:30 by roroca            #+#    #+#             */
/*   Updated: 2023/11/14 12:32:56 by roroca           ###   ########.fr       */
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
	if (line[i] == 39)
	{
		i++;
		while (line[i + 1] && line[i] != 39)
			i++;
	}
	else if (line[i] == 34)
	{
		i++;
		while (line[i + 1] && line[i] != 34)
			i++;
	}
	else
	{
		while ((line[i] > 0 && line[i] < 9) || (line[i] > 13 && line[i] < 32)
			|| line[i] > 32)
			i++;
	}
	return (i);
}
