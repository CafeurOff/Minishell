/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:33:32 by roroca            #+#    #+#             */
/*   Updated: 2023/11/22 14:51:46 by lduthill         ###   ########.fr       */
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
void	ft_free_t_pars(t_pars *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i].cmd)
	{
		free(cmd[i].cmd);
        if (cmd[i].args)
		{
            while (cmd[i].args[j])
			    free(cmd[i].args[j++]);
		    free(cmd[i].args);
        }
		free(cmd[i].in);
		free(cmd[i].out);
		j = 0;
		i++;
	}
	free (cmd);
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
