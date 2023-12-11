/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:02:09 by roroca            #+#    #+#             */
/*   Updated: 2023/12/11 12:26:30 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delimiter(t_pars *pars)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_RDWR | O_CREAT, 0644);
	printf("%d", fd);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			printf("bash: warning:here-document at line 1 delimited"
				"by end-of-file (wanted `%s')\n", pars[0].del);
			close(fd);
			free(line);
			return ;
		}
		if (ft_strncmp(line, pars[0].del, ft_strlen(pars[0].del)) == 0)
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

//open
//close
//unlink apres le changement de ligne de commande

void	ft_redirect_to_cmd(t_pars *cmd, t_data *data, char **pars, int i)
{
//	if (cmd[i].del)
//		ft_delimiter(cmd[i].del);
//	if (cmd[i].in)
//		ft_handle_in(cmd, i);
//	if (cmd[i].out)
//		ft_handle_out(cmd, i);
	ft_is_builtin(cmd, data, pars, i);
}
/*
void	ft_handle_in(t_pars *cmd, int i)
{

}


void	ft_handle_out(t_pars *cmd, int i)
{

}*/
