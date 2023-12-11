/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:02:09 by roroca            #+#    #+#             */
/*   Updated: 2023/12/11 16:08:41 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delimiter(char *s)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			printf("bash: warning:here-document at line 1 delimited"
				"by end-of-file (wanted `%s')\n", s);
			close(fd);
			free(line);
			return ;
		}
		if (ft_strncmp(line, s, ft_strlen(s) + 1) == 0)
		{
			free(line);
			close(fd);
			return ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	ft_handle_del(t_pars *cmd, int i)
{
	int	j;

	j = 0;
	while (cmd[i].del[j])
		ft_delimiter(cmd[i].del[j++]);
}

//open
//close
//unlink apres le changement de ligne de commande

void	ft_redirect_to_cmd(t_pars *cmd, t_data *data, char **pars, int i)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	if (cmd[i].del)
		ft_handle_del(cmd, i);
	if (cmd[i].flag2 != 0)
		fd_in = ft_handle_in(cmd, i);
	if (cmd[i].out)
		fd_out = ft_handle_out(cmd, i);
	ft_is_builtin(cmd, data, pars, i);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	dup2(data->fd[0], 0);
	dup2(data->fd[1], 1);
	unlink(".tmp");
}

int	ft_handle_in(t_pars *cmd, int i)
{
	int	fd;

	if (cmd[i].flag2 == 1)
		fd = open(cmd[i].in, O_RDONLY, 0644);
	else
		fd = open(".tmp", O_RDONLY, 0644);
	if (fd != -1)
		dup2(fd, 0);
	return (fd);
}


int	ft_handle_out(t_pars *cmd, int i)
{
	int	fd;
	int	j;

	j = 0;
	while (cmd[i].out[j])
	{
		if (cmd[i].flag == 1)
			fd = open(cmd[i].out[j], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(cmd[i].out[j], O_RDWR | O_CREAT | O_APPEND, 0644);
		j++;
	}
	if (fd != -1)
		dup2(fd, 1);
	return (fd);
}
