/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:49:42 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/11 16:08:39 by roroca           ###   ########.fr       */
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

void	ft_exit(t_data *data, char **args, t_pars *cmd, int i)
{
	if (i != 0 || cmd[i + 1].cmd)
		return ;
	if (!cmd[i].args)
		ft_free_all(data, args, cmd);
	if (cmd[i].args[1] || ft_isdigit(cmd[i].args[0]))
	{
		if (ft_isdigit(cmd[i].args[0]))
			printf("bash: exit: %s: numeric argument required\n", cmd[i].args[0]);
		else
			printf("bash: exit: too many arguments\n");
		return ;
	}
	data->error = ft_atoi(cmd[i].args[0]) % 256;
	ft_free_all(data, args, cmd);
}
