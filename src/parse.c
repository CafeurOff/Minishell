/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:30 by roroca            #+#    #+#             */
/*   Updated: 2023/11/17 16:14:57 by roroca           ###   ########.fr       */
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
		i = ft_skip_arg_quotes(line, i);
	else if (line[i] == 34)
		i = ft_skip_arg_quotes(line, i);
	else
	{
		while (line[i])
		{
			if (line[i] == 32 || line[i] == 34 || line[i] == 39
				|| (line[i] >= 9 && line[i] <= 13))
				break ;
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
	{
		i++;
	}
	return (i + 1);
}

//A REVOIR

//""''echo hola""'''' que""'' tal""''

char	*ft_parse_pipe(char *line)
{
	int	i;
	int len;
	int	flag;
	int	flag2;
	char	*res;

	line = ft_parse_quotes(line);
	i = 0;
	len = 0;
	flag = 1;
	flag2 = 1;
	while (line[i])
	{
		if (line[i] == 34)
			flag = -flag;
		if (line[i] == 39)
			flag2 = -flag2;
		if (flag && flag2 && line[i] == '|' && line[i + 1] != 32)
			len++;
		if (flag && flag2 && line[i] == '|' && line[i - 1] != 32)
			len++;
		i++;
	}
	res = malloc(sizeof(char) * (len + i + 1));
	if (!res)
		return (NULL);
	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
			flag = -flag;
		if (line[i] == 39)
			flag2 = -flag2;
		if (flag && flag2 && line[i] == '|' && line[i - 1] != 32)
			res[len++] = ' ';
		res[len++] = line[i++];
		if (flag && flag2 && line[i - 1] == '|' && line[i] != 32)
			res[len++] = ' ';
	}
	res[len] = '\0';
	free(line);
	return (res);
}

char	*ft_parse_quotes(char *line)
{
	int	i;
	int	len;
	char	*res;

	i = 0;
	len = 0;
	while(line[i])
	{
		if((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
			i++;
		else
			len++;
		i++;
	}
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	while (line[i])
	{
		while ((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
			i += 2;
		if (line[i])
			res[len++] = line[i++];
	}
	res[len] = '\0';
	free(line);
	return (res);
}
