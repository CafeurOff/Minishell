/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:33:32 by roroca            #+#    #+#             */
/*   Updated: 2023/11/16 18:47:59 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != 32 && (s[i + 1] == 32 || s[i + 1] == 0))
			word++;
		i++;
	}
	return (word);
}

char	**ft_split(char *s)
{
	int		i;
	int		j;
	char	**split;

	j = 0;
	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (count(s) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s == 32 && *s)
			s++;
		i = 0;
		while (s[i] != 32 && s[i])
			i++;
		if (*s && i)
			split[j++] = ft_substr(s, 0, i);
		s += i;
	}
	split[j] = 0;
	return (split);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	if (len == 0 || (int)ft_strlen(s) <= start)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	if ((int)ft_strlen(s) < len + start)
		str = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (j < len && j < (int)ft_strlen(s))
		str[j++] = s[i++];
	if (j == len)
		str[j] = '\0';
	return (str);
}
int	ft_specchar(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i][0] >= 32 && str[i][0] <= 47) ||
				(str[i][0] >= 58 && str[i][0] <= 64)
			|| (str[i][0] >= 91 && str[i][0] <= 96) ||
					(str[i][0] >= 123 && str[i][0] <= 126))
		{
			printf("minishell: export: `%s': not a valid identifier\n", str[i]);
			return (1);
		}
	}
	return (0);
}

void	ft_error_free(t_pars *pars, t_data *data)
{
	int		i;

	i = 0;
	while (pars[i].args)
	{
		free(pars[i].args);
		i++;
	}
	free(pars);
	i = 0;
	while (data->env[i].id)
	{
		free(data->env[i].id);
		free(data->env[i].value);
		i++;
	}
	free(data->env);
	free(data);
	exit(1);
}
