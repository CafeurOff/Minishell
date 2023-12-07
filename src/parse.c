/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:56:56 by roroca            #+#    #+#             */
/*   Updated: 2023/11/29 11:54:59 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_skip_env_val(char *l, int i)
{
	i++;
	if ((l[1] >= 48 && l[1]<= 57) || l[i] == 63)
	
		return (i + 1);
	while ((l[i] >= 48 && l[i]<= 57) || (l[i] >= 65 && l[i] <= 90) || (l[i] >= 97 && l[i] <= 122) || l[i] == 95)
		i++;
	return (i);
}

int	ft_skip_arg(char *line, int i)
{
	if ((line[i] == 60 && line[i + 1] == 60) || (line[i] == 62 && line[i + 1] == 62))
		return(i + 2);
	else if (line[i] == 60 || line[i] == 62 || line[i] == 124)
		return (i + 1);
	while (line[i] && line[i] != 32 && line[i] != 60 && line[i] != 62 && (line[i] <= 9 || line[i] >= 13) && line[i] != 124)
		i++;
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
	int	i;
	int	len;
	char	*res;

	i =-1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != 39 && s[i] != 34)
			len++;
	}
	res = malloc(sizeof(char)  * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == 39 || s[i] == 34)
			i++;
		if (s[i])
			res[len++] = s[i++];
	}
	res[len] = 0;
	return (free(s), res);
}
