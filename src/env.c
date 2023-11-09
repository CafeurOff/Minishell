/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:30:47 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/08 17:21:46 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pre_init(t_env *env)
{
    int	i;

	i = 0;
	while (i < 4096)
	{
    	env[i].set = 0;
		env[i].id = NULL;
    	env[i].value = NULL;
		i++;
	}
}


t_env    *ft_copy_env(char **envp)
{
    t_env   *env;
    int     i;

    i = 0;
    if (!(env = malloc(sizeof(t_env) * 4096)))
        return (NULL);
    pre_init(env);
    while (envp[i])
    {
        env[i].id = ft_get_id(envp[i]);
        env[i].value = ft_get_value(envp[i]);
        i++;
    }
	// Faire nouvelle boucle pour mettre set a 1
	// Find SHLVL et faire itoa + atoi + 1 a value
    env[i].id = NULL;
    env[i].value = NULL;
    return (env);
}

char    *ft_get_id(char *str)
{
    int     i;
    char    *name;

    i = 0;
    name = NULL;
    while (str[i] != '=' && str[i])
        i++;
    if (!(name = malloc(sizeof(char) * i + 1)))
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

char    *ft_get_value(char *str)
{
    int     i;
    int     j;
    char   *value;

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
    if (!(value = malloc(sizeof(char) * j + 1)))
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
