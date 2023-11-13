/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:18:39 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/13 13:40:53 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i])
		i++;
	new = malloc(sizeof(char) * i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}
/* pre_init()
*   Function for pre-initialize the env structure with max size
*   and set all values to 0
*/

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

void	ft_free(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].id != NULL)
	{
		free(env[i].id);
		free(env[i].value);
		i++;
	}
	free(env);
}
