/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:58:11 by roroca            #+#    #+#             */
/*   Updated: 2023/12/11 11:47:05 by roroca           ###   ########.fr       */
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
	{
		cmd[flag].args = NULL;
		return ;
	}
	cmd[flag].args = malloc(sizeof(char *) * (args + 1));
	i = ft_skip_tab(pars, flag);
	j = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], "<", 2) != 0 && ft_strncmp(pars[i], ">", 2) != 0
			&& ft_strncmp(pars[i], ">>", 2) != 0 && ft_strncmp(pars[i], "<<", 2) != 0)
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
	{
		cmd[flag].out = NULL;
		return ;
	}
	cmd[flag].out = malloc(sizeof(char *) * (args + 1));
	i = ft_skip_tab(pars, flag);
	j = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], ">", 2) == 0 || ft_strncmp(pars[i], ">>", 2) == 0)
			cmd[flag].out[j++] = ft_strdup(pars[++i]);
		if (ft_strncmp(pars[i], ">", 2) == 0)
			cmd[flag].flag = 1;
		else if (ft_strncmp(pars[i], ">>", 2) == 0)
			cmd[flag].flag = 2;
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
	if (args == 0)
	{
		cmd[flag].del = NULL;
		return ;
	}
	cmd[flag].del = malloc(sizeof(char *) * (args + 1));
	i = ft_skip_tab(pars, flag);
	j = 0;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], "<<", 2) == 0)
			cmd[flag].del[j++] = ft_strdup(pars[++i]);
		else
			i++;
	}
	cmd[flag].del[j] = NULL;
}

void	ft_init_cmd_in(char **pars, t_pars *cmd, int flag)
{
	int	i;

	i = ft_skip_tab(pars, flag);
	cmd[flag].in = NULL;
	while (pars[i] && ft_strncmp(pars[i], "|", 2) != 0)
	{
		if (ft_strncmp(pars[i], "<", 2) == 0)
			cmd[flag].in = ft_strdup(pars[++i]);
		i++;
	}
}

void	ft_command_line(char **pars, t_pars *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		cmd[i].flag = 0;
//		printf("cmd[%d].cmd= %s\n", i, cmd[i].cmd);
		ft_init_cmd_args(pars, cmd, i);
//		if (cmd[i].args)
//			printf("cmd[%d].args[0]= %s\n", i, cmd[i].args[0]);
		ft_init_cmd_out(pars, cmd, i);
//		if (cmd[i].out)
//			printf("cmd[%d].out[0]= %s\n", i, cmd[i].out[0]);
		ft_init_cmd_del(pars, cmd, i);
//		if (cmd[i].del)
//			printf("cmd[%d].del[0]= %s\n", i, cmd[i].del[0]);
		ft_init_cmd_in(pars, cmd, i);
//		printf("cmd[%d].in= %s\n", i, cmd[i].in);
//		printf("\n");
		i++;
	}
}

int		ft_skip_tab(char **pars, int flag)
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
			&& ft_strncmp(pars[i], ">>", 2) != 0 && ft_strncmp(pars[i], "<<", 2) != 0)
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
		if (ft_strncmp(pars[i], ">", 2) == 0 || ft_strncmp(pars[i], ">>", 2) == 0)
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
