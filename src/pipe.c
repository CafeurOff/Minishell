/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:57:13 by roroca            #+#    #+#             */
/*   Updated: 2023/12/07 12:09:08 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 LIRE
// 1 ECRIRE


void	ft_exec_pipe(t_data *data, char **pars, t_pars *cmd,  int i)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_handle_pipe(data, cmd, i, fd);
		ft_is_builtin(cmd, data, pars, i);
		if (cmd[i + 1].cmd != NULL)
			ft_exec_pipe(data, pars, cmd, i + 1);
		exit(ft_atoi(data->error));
	}
	else
	{
		dup2(0, data->fd[0]);
		waitpid(pid, &status, 0);
		data->error = ft_itoa((status >> 8));
	}
	close(fd[0]);
}

void	ft_handle_pipe(t_data *data, t_pars *cmd, int i, int *fd)
{
		if (cmd[i + 1].cmd != NULL)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else
			dup2(data->fd[1], 1);
}