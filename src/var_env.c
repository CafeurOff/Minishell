/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:10:45 by roroca            #+#    #+#             */
/*   Updated: 2023/11/14 17:57:07 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_env_val()
*	Is a function for check args,
*	to find/transform environement variable,
*	in the correct value
*/

//	NEED TO BE REVIEW FOR ENV VAR WHO ARE NOT FIND/DOESN'T EXIST

char	*ft_env_val(char *pars, t_env *env)
{
	char	*tmp;

	if (pars[0] == 36) //36 == $
	{
		tmp = ft_strdup(pars + 1);
		free(pars);
		pars = ft_strdup(ft_getenv(tmp, env));
		free(tmp);
	}
	else if (pars[0] == 34) //34 == "
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

	var = ft_env_var(ft_split(s), env);
	i = 0;
	j = 1;
	k = 0;
	res = malloc(sizeof(char) * (ft_strenv_len(var) + 1));
	if (!res)
		return (NULL);
	while (var[i])
	{
		while (var[i][j])
			res[k++] = var[i][j++];
		j = 0;
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
			tmp = ft_strdup(var[i]);
			free(var[i]);
			var[i] = ft_strdup(ft_getenv(tmp + 1, env));
			free(tmp);
		}
		i++;
	}
	return (var);
}
