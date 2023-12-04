/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:35:55 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/04 19:06:46 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 LIRE
// 1 ECRIRE

/*
void	ft_exec_pipe(t_data *data, char **pars, t_pars *cmd,  int i)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		waitpid(pid);
	else
	{
		if (i % 2 == 0)
			ft_handle_pipe(data->fd, data->fd2);
		ft_exec_cmd(data, pars, i + 1);
	}
}

void	ft_handle_pipe(int *in, int *out)
{
	close(in[1]);
	close(out[0]);
	dup2(out[1], STDOUT_FILENO);
}*/
