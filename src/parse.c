/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:56:56 by roroca            #+#    #+#             */
/*   Updated: 2023/12/12 15:22:50 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_env_val(char *l, int i)
{
	i++;
	if ((l[1] >= 48 && l[1] <= 57) || l[i] == 63)
		return (i + 1);
	while ((l[i] >= 48 && l[i] <= 57) || (l[i] >= 65 && l[i] <= 90)
		|| (l[i] >= 97 && l[i] <= 122) || l[i] == 95)
		i++;
	return (i);
}

int	ft_skip_arg(char *line, int i)
{
	if ((line[i] == 60 && line[i + 1] == 60)
		|| (line[i] == 62 && line[i + 1] == 62))
		return (i + 2);
	else if (line[i] == 60 || line[i] == 62 || line[i] == 124)
		return (i + 1);
	while (line[i] && line[i] != 32 && line[i] != 60 && line[i] != 62
		&& (line[i] <= 9 || line[i] >= 13) && line[i] != 124)
	{
		if (line[i] == 34 || line[i] == 39)
			i = ft_skip_arg_quotes(line, i) - 1;
		if (line[i])
			i++;
	}
	return (i);
}

int	ft_skip_arg_quotes(char *line, int i)
{
	int	flag;

	flag = line[i++];
	while (line[i + 1] && line[i] != flag)
		i++;
	return (i + 1);
}

char	*ft_without_quotes(char *s)
{
	int		i;
	int		len;
	int		flag;
	char	*res;

	res = malloc(sizeof(char) * (ft_len_without_quotes(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	flag = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
		{
			flag = s[i++];
			while (s[i] != flag && s[i])
				res[len++] = s[i++];
			i++;
		}
		else
			res[len++] = s[i++];
	}
	res[len] = 0;
	return (free(s), res);
}

int	ft_len_without_quotes(char *s)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
		{
			i = ft_skip_arg_quotes(s, i);
			flag++;
		}
		else
			i++;
	}
	i -= (flag * 2);
	return (i);
}
