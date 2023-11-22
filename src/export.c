/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:14:46 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/22 23:22:13 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  ft_export()
*   Function for set a new env variable
*   @pars : struct with all the parsed data
*   @data : struct with all the data
*   @i : index of the first arg
*/

void	ft_export(t_pars *pars, t_data *data, int i)
{
	int	j;
	int	k;

	j = 0;
	if (!pars->args)
	{
		ft_print_export(data->env);
		return ;
	}
	while (pars[i].args[j])
	{
		k = ft_id_index(data, pars[i].args[j]);
		if (ft_id_exist(data, pars[i].args[j]) == 0)
			ft_setid(data, pars[i].args[j]);
		if (ft_strchr(pars[i].args[j], 61) != NULL)
		{
			if (data->env[k].value)
				free(data->env[k].value);
			data->env[k].value = ft_strdup(ft_strchr(pars[i].args[j], 61) + 1);
		}
		data->env[k].set = 1;
		j++;
	}
}

/*  ft_setid()
*   Function for set a new id to an env variable
*   @data : struct with all the data
*   @str : arg of export
*/

void	ft_setid(t_data *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != 61)
		j++;
	while (data->env[i].id)
		i++;
	data->env[i].id = malloc(sizeof(char) * (j + 1));
	if (!data->env[i].id)
		return ;
	j = 0;
	while (str[j] != 61 && str[j])
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

void	ft_setenv(char *find, char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i].id)
	{
		if (ft_strncmp(find, data->env[i].id, ft_strlen(find)) == 0)
		{
			if (str[0] == '\0')
			{
				data->env[i].value = NULL;
				return ;
			}
			free(data->env[i].value);
			data->env[i].value = ft_strdup(str);
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
		{
			if (env[i].value == NULL)
				printf("declare -x %s\n", env[i].id);
			else
				printf("declare -x %s=\"%s\"\n", env[i].id, env[i].value);
		}
		i++;
	}
}

/*  ft_id_exist()
*   Function for check if the id exist
*   @data : struct with all the data
*   @str : arg of export
*/

int		ft_id_exist(t_data *data, char *str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] != 61 && str[i])
		i++;
	while (data->env[j].id)
	{
		if (ft_strncmp(data->env[j].id, str, i) == 0)
			return (1);
		j++;
	}
	return (0);
}
