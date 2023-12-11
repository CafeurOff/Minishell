/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:57:13 by roroca            #+#    #+#             */
/*   Updated: 2023/12/11 14:47:58 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_pipe(t_data *data, char **pars, t_pars *cmd, int i)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_handle_pipe_child(fd);
		ft_redirect_to_cmd(cmd, data, pars, i);
		ft_free_all(data, pars, cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		data->error = (status >> 8);
		ft_handle_pipe(data, cmd, i, fd);
		if (cmd[i + 2].cmd == NULL)
			ft_redirect_to_cmd(cmd, data, pars, i + 1);
		else
			ft_exec_pipe(data, pars, cmd, i + 1);
		dup2(data->fd[0], 0);
	}
}

void	ft_handle_pipe(t_data *data, t_pars *cmd, int i, int *fd)
{
	if (cmd[i + 2].cmd == NULL)
		dup2(data->fd[1], 1);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	ft_handle_pipe_child(int *fd)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
}

/*

	parsing
		|
		V
>	exec_pipe
|		|
|		V
|	fork	->	child	->	cmd[0]
|								|
|								V
|							parent		if cmd[1] == last		-> exec cmd[1]
|											|
|											V
|-----------------------------------------else

*/
