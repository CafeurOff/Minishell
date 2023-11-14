/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:19:36 by roroca            #+#    #+#             */
/*   Updated: 2023/11/14 12:37:19 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_parsing()
	Mother function to pars the args of a line
*/

char	**ft_parsing(char *line, t_env *env)
{
	int		args;
	int		i;
	char	**pars;

	args = 0;
	i = 0;
	if (!line)
		return (NULL);
	if (ft_white_line(line))
		return (NULL);
	args = ft_count_args(line);
	pars = malloc(sizeof(char *) * (args + 1));
	if (!pars)
		return (NULL);
	while (i < args)
	{
		pars[i] = ft_subarg(line, i);
		pars[i] = ft_env_val(pars[i], env);
		i++;
	}
	pars[i] = '\0';
	return (pars);
}
/*	ft_count_args()
	Function to count how many args got the line,
	each args is separated by a whitespace, but "" or ''
	count only for one arg, even if it's compose with whitespace
*/

int	ft_count_args(char *line)
{
	int	args;
	int	i;

	i = 0;
	args = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	while (line[i])
	{
		if (line[i] != 32 && (line[i] <= 9 || line[i] >= 13))
		{
			i = ft_skip_arg(line, i);
			args++;
		}
		i++;
	}
	return (args);
}
/*	ft_substr_arg()
	Function that work with ft_subarg(),
	save the first arg of the line
*/

char	*ft_substr_arg(char *line)
{
	int		i;
	int		j;
	int		flag;
	char	*s;

	i = ft_skip_arg(line, 0);
	j = 0;
	if (line[0] == 39)
		flag = 1;
	else
		flag = 0;
	s = malloc(sizeof(char) * (i + 1 - flag));
	if (!s)
		return (NULL);
	while (j + flag < i)
	{
		s[j] = line[j + flag];
		j++;
	}
	s[j] = '\0';
	return (s);
}
/*	ft_subarg()
	Funtion that take a number in parameter,
	parameter that define wich argument is saved;
*/

char	*ft_subarg(char *line, int arg)
{
	int		i;
	int		flag;
	char	*s;

	i = 0;
	flag = 0;
	while (line[i])
	{
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (flag == arg)
		{
			s = ft_substr_arg(line + i);
			return (s);
		}
		else
		{
			i = ft_skip_arg(line, i);
			flag++;
		}
		i++;
	}
	return (NULL);
}
