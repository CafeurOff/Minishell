/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:14:46 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/14 19:10:30 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE :
* Si export avec un = alors afficher dans env sinon dans export
*/

void	ft_export(t_pars *pars, t_data *data, int i)
{
	int	j;

	j = 0;
	if (!pars->args)
		ft_print_export(data->env);
	while (pars[i].args[j])
	{
		ft_setid(data, pars[i].args[j]);
		if (ft_strchr(pars[i].args[j], 61) != NULL)
		{
			data->env[i].set = 1;
			ft_setenv(pars[i].args[j], ft_strchr(pars[i].args[j], 61) + 1,
				data->env);
		}
	}
}

void	ft_setid(t_data *data, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[j] != 61)
		j++;
	data->env[i].id = malloc(sizeof(char) * (j + 1));
	if (!data->env[i].id)
		return ;
	while (data->env[i])
		i++;
	j = 0;
	while (str[j] != 61)
	{
		data->env[i].id[j] = str[j];
		j++;
	}
	data->env[i].id[j] = '\0';
}

/*  ft_setenv()
*   Function for set a new value to an env variable
*   Exemple : ft_setenv("PATH", "/bin/ls", env);
*   Return : ft_getenv("PATH", env) == "/bin/ls"
*/

void	ft_setenv(char *find, char *str, t_env *env)
{
	int	i;

	i = 0;
	while (env[i].id)
	{
		if (ft_strncmp(find, env[i].id, ft_strlen(find)) == 0)
		{
			if (str[0] == '\0')
			{
				env[i].value = NULL;
				return ;
			}
			free(env[i].value);
			env[i].value = ft_strdup(str);
			return ;
		}
		i++;
	}
}

/*	ft_print_export()
*	Function for print all env variable
*/

void	ft_print_export(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].id)
	{
		if (env[i].set == 1)
			printf("declare -x %s\n", env[i].id);
		else
			printf("declare -x %s=\"%s\"\n", env[i].id, env[i].value);
		i++;
	}
}
