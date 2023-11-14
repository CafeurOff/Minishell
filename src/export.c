/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:14:46 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/14 12:25:57 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE :
* Si export avec un = alors afficher dans env sinon dans export
*/

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
			free(env[i].value);
			env[i].value = ft_strdup(str);
			return ;
		}
		i++;
	}
}

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
