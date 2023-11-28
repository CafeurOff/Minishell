/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:58:11 by roroca            #+#    #+#             */
/*   Updated: 2023/11/28 17:04:33 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//REFAIRE CETTE MERDE 2 FONCTIONS 1 pour allouer + donner valeurs des args autre pour avec un flag donnez les autre val

t_pars	*ft_init_cmd_line(char **pars)
{
	t_pars	*cmd;
	int		line;
	int		i;
	int		j;
	int		arg;

	i = 0;
	line = ft_count_lines(pars);
	cmd = malloc(sizeof(t_pars) * (line + 1));
	if (!cmd)
		return (NULL);
	while (i < line)
	{
		j = 0;
		cmd[i].cmd = NULL;
		arg = ft_count_args_line(pars, i);
		if (arg != 0)
		{
			cmd[i].args = malloc(sizeof(char *) * (arg + 1));
			while (j <= arg)
				cmd[i].args[j++] = NULL;
		}
		else
			cmd[i].args = NULL;
		cmd[i].in = NULL;
		cmd[i].out = NULL;
		i++;
	}
	cmd[i].cmd = NULL;
	return (ft_command_line(pars, cmd));
}

int	ft_count_args_line(char **pars, int flag)
{
	int	i;
	int	len;
	int	line;

	i = 1;
	len = 0;
	line = 0;
	while (pars[i] && line != flag)
	{
		if (ft_strncmp(pars[i], "|", 2) == 0)
		{
			i++;
			line++;
		}
		i++;
	}
	while (pars[i])
	{
		if (ft_strncmp(pars[i], "|", 2) != 0)
			len++;
		else
			return (len);
		i++;
	}
	return (len);
}

t_pars	*ft_command_line(char **pars, t_pars *cmd)
{
	int	i;
	int	j;
	int	line;

	i = 0;
	j = 0;
	line = 0;
	cmd[0].cmd = ft_strdup(pars[i++]);
	while (pars[i])
	{
		if (ft_strncmp(pars[i], "|", 2) == 0)
		{
			line++;
			i++;
			j = 0;
		}
		if (ft_strncmp(pars[i - 1], "|", 2) == 0)
			cmd[line].cmd = ft_strdup(pars[i]);
		else if (ft_strncmp(pars[i], ">", 2) == 0)
			cmd[line].out = ft_strdup(pars[++i]);
		else if (ft_strncmp(pars[i], ">>", 3) == 0)
			cmd[line].out = ft_strdup(pars[++i]);
		else if (ft_strncmp(pars[i], "<", 2) == 0)
			cmd[line].in = ft_strdup(pars[++i]);
		else
			cmd[line].args[j++] = ft_strdup(pars[i]);
		i++;
	}
	return (cmd);
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
