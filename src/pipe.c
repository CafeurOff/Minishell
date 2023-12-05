/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:35:55 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/05 18:19:18 by lduthill         ###   ########.fr       */
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
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		ft_is_builtin(cmd, data, pars, i + 1);
		if (cmd[i + 1].cmd != NULL)
			ft_exec_pipe(data, pars, cmd, i + 1);
		exit(ft_atoi(data->error));
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		waitpid(pid, &status, 0);
		data->error = ft_itoa((status >> 8));
	}
	close(fd[0]);
}

void	ft_handle_pipe(int *fd)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
}
