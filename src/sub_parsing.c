/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:00:11 by roroca            #+#    #+#             */
/*   Updated: 2023/12/11 12:40:21 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_var(char *l, t_data *data)
{
	int		len;
	char	*tmp;
	char	*var;

	len = 0;
	if (l[1] == 63)
		return (ft_itoa(data->error));
	len = ft_skip_env_val(l, 0);
	if (len == 1 && !(l[1] >= 48 && l[1] <= 57))
	{
		tmp = malloc(sizeof(char) * 2);
		tmp[0] = 36;
		tmp[1] = 0;
		return (tmp);
	}
	tmp = ft_strdup(l + 1);
	tmp[len - 1] = 0;
	var = ft_strdup(ft_getenv(tmp, data->env));
	if (var == NULL || (l[1] >= 48 && l[1] <= 57))
	{
		var = malloc(sizeof(char));
		var[0] = 0;
	}
	free(tmp);
	return (var);
}

char	*ft_replace_line(char *l, char **var)
{
	int		len;
	int		i;
	int		j;
	int		k;
	char	*res;

	res = malloc(sizeof(char) * (ft_replacelen(l, var) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	len = 0;
	while (l[i])
	{
		if (l[i] == 39)
		{
			i++;
			while (l[i] != 39)
				res[len++] = l[i++];
			i++;
		}
		else if (l[i] == 36 && l[i + 1] == 34)
			i++;
		else if (l[i] == 36 && l[i + 1])
		{
			k = 0;
			while (var[j][k])
				res[len++] = var[j][k++];
			j++;
			i = ft_skip_env_val(l, i);
		}
		else
			res[len++] = l[i++];
	}
	res[len] = 0;
	return (ft_free_tab(var), free(l), ft_without_quotes(res));
}

int	ft_replacelen(char *l, char **var)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (l[i])
	{
		if (l[i] == 36 && l[i + 1] != 34)
			i += ft_skip_env_val(l, i);
		else
		{
			len++;
			i++;
		}
	}
	i = 0;
	while (var[i])
		len += ft_strlen(var[i++]);
	return (len);
}

int	ft_count_env_val(char *line)
{
	int	args;
	int	i;

	i = 0;
	args = 0;
	while (line[i])
	{
		if (line[i] == 39)
			i = ft_skip_arg_quotes(line, i);
		while (line[i] == 36 && line[i + 1] != 34 && line[i + 1])
		{
			args++;
			i = ft_skip_env_val(line, i);
		}
		if (line[i] && line[i] != 39)
			i++;
	}
	return (args);
}
