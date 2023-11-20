/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:14 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/18 16:41:37 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	*data;

	(void)ac;
	(void)av;
	line = NULL;
	data = malloc(sizeof(t_data));
	data->env = ft_copy_env(envp);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		line = readline("minishit>");
		if (!line)
			return (ft_free(data->env), free(data), 0);
		if (line[0] != '\0')
		{
			if (ft_white_line(line) != 1)
			{
				add_history(line);
				ft_exec_cmd(line, data);
			}
		}
		free(line);
	}
	return (0);
}

void	ft_exec_cmd(char *line, t_data *data)
{
	int		i;
	//int		j;
	char	**pars;
	t_pars	*cmd;

	i = 0;
	//j = 0;
	pars = ft_parsing(line, data->env);
	while (pars[i])
	{
		printf("Parsing line [%d] : %s\n", i, pars[i]);
		i++;
	}
	//printf("\n\n\n");
	cmd = ft_init_cmd_line(pars);
	/*while (i < 5)
	{
		printf("CMD Line [%d] :\n	cmd :%s\n", i, cmd[i].cmd);
		while (cmd[i].args[j])
		{
			printf("	args[%d] :%s\n", j, cmd[i].args[j]);
			j++;
		}
		printf("	in :%s\n", cmd[i].in);
		printf("	out :%s\n", cmd[i].out);
		i++;
		j = 0;
	}*/
	/*printf("cmd de merde : %s\n", cmd[1].cmd);
	printf("args de merde : %s\n", cmd[1].args[1]);
	printf("in de merde : %s\n", cmd[1].in);
	printf("out de merde : %s\n", cmd[1].out);*/
	(void)cmd;
	ft_free_tab(pars);
	ft_free_t_pars(cmd);
	rl_clear_history();
	ft_free(data->env);
	free(data);
	exit(0);
}
