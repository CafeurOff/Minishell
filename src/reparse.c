/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:13:06 by roroca            #+#    #+#             */
/*   Updated: 2023/11/28 17:04:36 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	**ft_parsing(char *line, t_data *data)
{
	char	**pars;
	int		len;
	int		i;

	len = ft_count_args(line);
	pars = malloc(sizeof(char *) * (len + 1));
	if (!pars)
		return (NULL);
	pars[len] = 0;
	len = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		while ((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
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
		while ((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
			i += 2;
		if (line[i] && line[i] != 32 && (line[i] <= 9 || line[i] >= 13))
		{
			i = ft_skip_arg(line, i);
			args++;
		}
	}
	return (args);
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

char	*ft_subarg(char *line, t_data *data)
{
	int		i;
	int		j;
	char	**var;
	char	*res;

	i = 0;
	j = 0;
	line[ft_skip_arg(line, 0)] = 0;
	var = malloc(sizeof(char *) * (ft_count_env_val(line) + 1));
	if (!var)
		return (NULL);
	while(line[i])
	{
		if (line[i] == 39)
			i = ft_skip_arg_quotes(line, i);
		if (line[i] == 36 && line[i + 1] != 34)
		{
			var[j++] = ft_var(line + i, data);
			i = ft_skip_env_val(line, i);
		}
		if (line[i] && !(line[i] == 36 && line[i + 1] != 34) && line[i] != 39)	
			i++;
	}
	var[j] = 0;
	res = ft_replace_line(line, var);
	res = ft_without_quotes(res);
	return (ft_free_tab(var), free(line), res);
}

char	*ft_var(char *l, t_data *data)
{
	int	len;
	char	*tmp;
	char	*var;

	len = 0;
	if (l[1] == 63)
		return(ft_strdup(data->error));
	len = ft_skip_env_val(l, 0);
	if (len == 1 || (l[1] >= 48 && l[1] <= 57))
	{
		tmp = malloc(sizeof(char) * 1);
		tmp[0] = 0;
		return (tmp);
	}
	tmp = ft_strdup(l + 1);
	tmp[len - 1] = 0;
	var = ft_strdup(ft_getenv(tmp, data->env));
	free(tmp);
	return (var);
}

int		ft_skip_env_val(char *l, int i)
{
	i++;
	if (l[1] >= 48 && l[1]<= 57)
		return (i + 1);
	while ((l[i] >= 48 && l[i]<= 57) || (l[i] >= 65 && l[i] <= 90) || (l[i] >= 97 && l[i] <= 122) || l[i] == 95)
		i++;
	return (i);
}

char	*ft_replace_line(char *l, char **var)
{
	int	len;
	int	i;
	int	j;
	int	k;
	char	*res;
	
	len = ft_replacelen(l, var);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	len = 0;
	while (l[i])
	{
		if (l[i] == 36 && l[i + 1] != 34)
		{
			k = 0;
			while (var[j][k])
				res[len++] = var[j][k++];
			j++;
			i += ft_skip_env_val(l, i);
		}
		else
			res[len++] = l[i++];
	}
	res[len] = 0;
	return (res);
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

int		ft_count_env_val(char *line)
{
	int	args;
	int	i;

	i = 0;
	args = 0;
	while (line[i])
	{
		if (line[i] == 39)
			i = ft_skip_arg_quotes(line, i);
		while (line[i] == 36 && line[i + 1] != 34)
		{
			args++;
			i = ft_skip_env_val(line, i);
		}
		if (line[i] && line[i] != 39)
			i++;
	}
	return (args);
}

int	ft_skip_arg_quotes(char *line, int i)
{
	int	flag;

	flag = line[i++];
	while (line[i + 1] && line[i] != flag)
		i++;
	return (i + 1);
}

int	ft_white_line(char *s)
{
	int	i;

	i = 0;
	if ((s[0] == 33 || s[0] == 58) && s[1] == 0)
	while (s[i])
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != 32)
			return (0);
		i++;
	}
	return (1);
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
