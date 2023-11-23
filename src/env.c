/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:30:47 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/23 16:05:05 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  ft_copy_env()
*   Function for copy the envp in a structure
*   Set SHLVL to 1
*/

t_env	*ft_copy_env(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = malloc(sizeof(t_env) * 4096);
	if (!env)
		return (NULL);
	pre_init(env);
	while (envp[i])
	{
		env[i].id = ft_get_id(envp[i]);
		if (ft_strncmp("SHLVL=", envp[i], 6) == 0)
			env[i].value = ft_itoa(ft_atoi(envp[i] + 6) + 1);
		else
			env[i].value = ft_get_value(envp[i]);
		i++;
	}
	i = 0;
	while (env[i].id != NULL)
		env[i++].set = 1;
	env[i].id = NULL;
	env[i].value = NULL;
	return (env);
}

/*  ft_get_id()
*   Function for get the id of the env variable
*   Exemple : PATH=/bin/ls
*   Return : PATH
*/

char	*ft_get_id(char *str)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (str[i] != '=' && str[i])
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/* ft_get_value()
*  Function for get the value of the env variable
*  Exemple : PATH=/bin/ls
*  Return : /bin/ls
*/

char	*ft_get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	j = 0;
	i = 0;
	value = NULL;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	if (str[i] == '\0')
		return (NULL);
	while (str[j + i])
		j++;
	value = malloc(sizeof(char) * j + 1);
	if (!value)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		value[j] = str[i + j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

/*  ft_getenv()
*   Function for get the value of the env variable
*   Exemple : ft_getenv("PATH", env)
*   Return : /bin/ls
*/

char	*ft_getenv(char *str, t_env *env)
{
	int	i;

	i = 0;
	if (str[0] == 0)
		return (NULL);
	while (env[i].id)
	{
		if (ft_strncmp(str, env[i].id, ft_strlen(str)) == 0)
			return (env[i].value);
		i++;
	}
	return (NULL);
}

/*  ft_print_env()
*   Function for print the env variable
*   If set == 1 then print with a '='
*/

void	ft_print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].id)
	{
		if (env[i].set == 1)
			printf("%s=%s\n", env[i].id, env[i].value);
		i++;
	}
}
