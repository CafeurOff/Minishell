/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:18:39 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/11 21:43:05 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_strdup()
**	Function for duplicate a string
**	@str : string to duplicate
*/

char	*ft_strdup(char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
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

/*	ft_strjoin()
**	Function for join two strings
**	@s1 : first string
**	@s2 : second string
*/

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

void	pre_init(t_env *env)
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

/*	ft_free()
**	Function for free the env structure
**	@env : struct with all the env
*/

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

/*	ft_free_tab()
**	Function for free a tab
**	@s : tab to free
*/

void	ft_free_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
