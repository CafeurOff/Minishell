/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tab_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:46:46 by roroca            #+#    #+#             */
/*   Updated: 2023/12/11 12:48:59 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_tab(char **pars, int flag)
{
	int		i;
	int		arg;

	i = 0;
	arg = 0;
	while (pars[i])
	{
		if (arg == flag)
			return (i + 1);
		if (ft_strncmp(pars[i], "|", 2) == 0)
			arg++;
		i++;
	}
	return (-1);
}

int	ft_count_lines(char **pars)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (pars[i])
	{
		if (ft_strncmp(pars[i], "|", 2) == 0)
			len++;
		i++;
	}
	return (len + 1);
}

int	ft_count_cmd_args(char **pars, int flag)
{
	int	i;
	int	args;

	i = ft_skip_tab(pars, flag);
	args = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], "<", 2) != 0 && ft_strncmp(pars[i], ">", 2) != 0
			&& ft_strncmp(pars[i], ">>", 2)
			!= 0 && ft_strncmp(pars[i], "<<", 2) != 0)
		{
			args++;
			i++;
		}
		else
			i += 2;
	}
	return (args);
}

int	ft_count_cmd_out(char **pars, int flag)
{
	int	i;
	int	args;

	i = ft_skip_tab(pars, flag);
	args = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], ">", 2) == 0
			|| ft_strncmp(pars[i], ">>", 2) == 0)
		{
			args++;
			i++;
		}
		else
			i++;
	}
	return (args);
}

int	ft_count_cmd_del(char **pars, int flag)
{
	int	i;
	int	args;

	i = ft_skip_tab(pars, flag);
	args = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], "<<", 2) == 0)
		{
			args++;
			i++;
		}
		else
			i++;
	}
	return (args);
}
