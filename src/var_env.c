/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:10:45 by roroca            #+#    #+#             */
/*   Updated: 2023/11/22 23:49:08 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_env_val()
*	Is a function for check args,
*	to find/transform environement variable,
*	in the correct value
*/

char	*ft_env_val(char *pars, t_env *env)
{
	char	*tmp;
	char	*tmp2;

	if (pars[0] == 36 && pars[1])
	{
		tmp = ft_strdup(pars + 1);
		tmp2 = ft_strdup(ft_getenv(tmp, env));
		if (tmp2)
		{
			free(pars);
			free(tmp);
			return (tmp2);
		}
		free(tmp);
	}
	else if (pars[0] == 34)
		pars = ft_env_in_string(pars, env);
	return (pars);
}

/*	ft_env_in_string()
*	Is a specific function to find and transform string in ""
*	who contains env var (ex: $USER)
*/

//	NEED TO BE REVIEW FOR SEPARATOR BETWEEN EACH ARG, SHOULD BE THE SAME

char	*ft_env_in_string(char *s, t_env *env)
{
	int		k;
	int		i;
	int		j;
	char	**var;
	char	*res;

	var = ft_env_var(ft_split_string(s), env);
	i = 0;
	k = 0;
	res = malloc(sizeof(char) * (ft_strenv_len(var) + 1));
	if (!res)
		return (NULL);
	while (var[i])
	{
		j = 0;
		while (var[i][j])
			res[k++] = var[i][j++];
		i++;
		if (var[i])
			res[k++] = ' ';
	}
	res[k] = '\0';
	return (ft_free_tab(var), free(s), res);
}

/*	ft_strenv_len()
*	It's an ft_strlen modify for count the length of a **char
*/

int	ft_strenv_len(char **var)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (var[i])
	{
		j = 0;
		while (var[i][j])
		{
			j++;
			len++;
		}
		i++;
		len++;
	}
	return (len);
}

/*	ft_env_var()
*	transform every line with an env var
*	in the apropriate value
*/

char	**ft_env_var(char **var, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (var[i])
	{
		if (var[i][0] == 36)
		{
			tmp = ft_strdup(ft_getenv(var[i] + 1, env));
			if (tmp)
			{
				free(var[i]);
				var[i] = tmp;
			}
		}
		i++;
	}
	return (var);
}

char	**ft_split_string(char *s)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * (ft_count_split(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		res[j++] = ft_substr_quotes(s + i);
		i = ft_len_arg(s, i);
	}
	res[j] = 0;
	return (res);
}

int	ft_len_arg(char	*s, int i)
{
	if (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
	{
		while (s[i] && (s[i] == 32 || (s[i] >= 9 && s[i] <= 13)))
			i++;
	}
	else
	{
		while (s[i] && s[i] != 32 && (s[i] < 9 || s[i] > 13))
			i++;
	}
	return (i);
}

char	*ft_substr_quotes(char	*s)
{
	int	i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (ft_len_arg(s, 0) + 1));
	if (!res)
		return (NULL);
	if (s[0] == 32 || (s[0] >= 9 && s[0] <= 13))
	{
		while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		{
			res[i] = s[i];
			i++;
		}
	}
	else
	{
		while (s[i] && s[i] != 32 && (s[i] < 9 || s[i] > 13))
		{
			res[i] = s[i];
			i++;
		}
	}
	res[i] = 0;
	return (res);
}

int	ft_count_split(char *s)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (s[i])
	{
		if (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		{
			args++;
			while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
				i++;
		}
		else
		{
			args++;
			while (s[i] && s[i] != 32 && (s[i] < 9 || s[i] > 13))
				i++;
		}
	}
	return (args);
}
