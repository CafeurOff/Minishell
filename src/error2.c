/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:49:42 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/09 01:49:50 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_identifier_error(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i][0] >= '0' && str[i][0] <= '9')
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = 1;
		return (1);
	}
	if (str[i][0] == 61)
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = 1;
		return (1);
	}
	if (str[i][0] == 32)
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = 1;
		return (1);
	}
	return (0);
}
