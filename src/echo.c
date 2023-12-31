/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:10:49 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/12 13:58:41 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_echo()
* Function for print args passed in echo command
* @pars : struct with all the parsed data
* @i : index of the first arg
*/

void	ft_echo(t_pars *pars, int i)
{
	int		flag;
	int		j;

	j = 0;
	flag = 1;
	if (pars[i].args == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_print_echo(pars[i].args[j]) == 0)
	{
		flag = 0;
		j++;
	}
	while (pars[i].args[j])
	{
		printf("%s", pars[i].args[j]);
		if (pars[i].args[++j])
			printf(" ");
	}
	if (flag == 1)
		printf("\n");
}

/* ft_print_echo()
*	If echo have option "-n" return 1 else return 0
*	@str : arg of echo
*/

int	ft_print_echo(char *str)
{
	int		i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

/* ft_id_index()
*	Return the index of the env variable
*	@data : struct with all the data
*	@str : arg of export
*/

int	ft_id_index(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_strdup(str);
	j = 0;
	i = 0;
	while (str[i] != 61 && str[i])
		i++;
	tmp[i] = '\0';
	while (data->env[j].id)
	{
		if (ft_strncmp(data->env[j].id, tmp, i + 1) == 0)
		{
			free(tmp);
			return (j);
		}
		j++;
	}
	free(tmp);
	return (j);
}
