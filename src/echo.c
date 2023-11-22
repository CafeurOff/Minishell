/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:10:49 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/22 14:02:13 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(t_pars *pars, int i)
{
	int		flag;

	flag = 1;
	if (pars->args[i])
	{
		while (pars->args[i])
		{
			if (ft_print_echo(pars->args[i]) == 0)
				flag = 0;
			else
				break ;
			i++;
		}
		while (pars->args[i])
    	{
			printf("%s", pars->args[i]);
			if (pars->args[++i])
				printf(" ");
    	}
	}
	if (flag == 1)
		printf("\n");
}

/* ft_print_echo()
*	If echo have option "-n" return 1 else return 0
*/
int		ft_print_echo(char *str)
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
