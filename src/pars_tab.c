/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:58:11 by roroca            #+#    #+#             */
/*   Updated: 2023/12/11 12:48:13 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*ft_init_cmd_line(char **pars)
{
	t_pars	*cmd;
	int		i;
	int		j;

	cmd = malloc(sizeof(t_pars) * (ft_count_lines(pars) + 1));
	if (!cmd)
		return (NULL);
	cmd[0].cmd = ft_strdup(pars[0]);
	i = 1;
	j = 0;
	cmd[j].in = NULL;
	while (pars[i])
	{
		if (ft_strncmp(pars[i], "|", 2) == 0)
			cmd[++j].in = NULL;
		else if (ft_strncmp(pars[i - 1], "|", 2) == 0)
			cmd[j].cmd = ft_strdup(pars[i]);
		i++;
	}
	cmd[++j].cmd = NULL;
	ft_command_line(pars, cmd);
	return (cmd);
}

void	ft_init_cmd_args(char **pars, t_pars *cmd, int flag)
{
	int		i;
	int		j;
	int		args;

	args = ft_count_cmd_args(pars, flag);
	if (args == 0)
		return ;
	cmd[flag].args = malloc(sizeof(char *) * (args + 1));
	i = ft_skip_tab(pars, flag);
	j = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], "<", 2) != 0 && ft_strncmp(pars[i], ">", 2) != 0
			&& ft_strncmp(pars[i], ">>", 2) != 0
			&& ft_strncmp(pars[i], "<<", 2) != 0)
			cmd[flag].args[j++] = ft_strdup(pars[i++]);
		else
			i += 2;
	}
	cmd[flag].args[j] = NULL;
}

void	ft_init_cmd_out(char **pars, t_pars *cmd, int flag)
{
	int		i;
	int		j;
	int		args;

	args = ft_count_cmd_out(pars, flag);
	if (args == 0)
		return ;
	cmd[flag].out = malloc(sizeof(char *) * (args + 1));
	i = ft_skip_tab(pars, flag);
	j = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], ">", 2) == 0
			|| ft_strncmp(pars[i], ">>", 2) == 0)
		{
			if (ft_strncmp(pars[i], ">", 2) == 0)
				cmd[flag].flag = 1;
			else
				cmd[flag].flag = 2;
			cmd[flag].out[j++] = ft_strdup(pars[++i]);
		}
		else
			i++;
	}
	cmd[flag].out[j] = NULL;
}

void	ft_init_cmd_del(char **pars, t_pars *cmd, int flag)
{
	int		i;
	int		j;
	int		args;

	args = ft_count_cmd_del(pars, flag);
	if (args != 0)
		cmd[flag].del = malloc(sizeof(char *) * (args + 1));
	i = ft_skip_tab(pars, flag);
	j = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], "<<", 2) == 0)
		{
			cmd[flag].flag2 = 2;
			cmd[flag].del[j++] = ft_strdup(pars[++i]);
		}
		else if (ft_strncmp(pars[i++], "<", 2) == 0)
		{
			cmd[flag].flag2 = 1;
			if (cmd[flag].in)
				free(cmd[flag].in);
			cmd[flag].in = ft_strdup(pars[i]);
		}
	}
	cmd[flag].del[j] = NULL;
}

void	ft_command_line(char **pars, t_pars *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		cmd[i].flag = 0;
		cmd[i].flag2 = 0;
		cmd[i].del = NULL;
		cmd[i].args = NULL;
		cmd[i].out = NULL;
		cmd[i].del = NULL;
		ft_init_cmd_args(pars, cmd, i);
		ft_init_cmd_out(pars, cmd, i);
		ft_init_cmd_del(pars, cmd, i);
		i++;
	}
}
