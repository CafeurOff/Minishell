/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:14 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/21 15:25:43 by roroca           ###   ########.fr       */
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
	data->bin_env = NULL;
	data->error = NULL;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		line = readline("minishit>");
		if (!line)
			return (ft_free(data->env), free(data), 0);
		add_history(line);
		if (ft_white_line(line) != 1)
			ft_exec_cmd(line, data);
		else
			free(line);
	}
	return (0);
}

void	ft_exec_cmd(char *line, t_data *data)
{
//	int		i;
	//int		j;
	char	**pars;
	t_pars	*cmd;

//	i = 0;
	//j = 0;
	pars = ft_parsing(line, data->env);
/*	while (pars[i])
	{
		printf("Parsing line [%d] : %s\n", i, pars[i]);
		i++;
	}
	printf("\n\n\n");*/
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
	if (ft_strncmp(cmd[0].cmd, "exit", 5) == 0)
		ft_free_all(data, pars, cmd);
	/*printf("cmd de merde : %s\n", cmd[1].cmd);
	printf("args de merde : %s\n", cmd[1].args[1]);
	printf("in de merde : %s\n", cmd[1].in);
	printf("out de merde : %s\n", cmd[1].out);*/
	(void)cmd;
	ft_free_tab(pars);
	ft_free_t_pars(cmd);
}

void	ft_free_all(t_data *data, char **args, t_pars *pars)
{
	rl_clear_history();
	ft_free_tab(args);
	ft_free_t_pars(pars);
	ft_free(data->env);
	if (data->error)
		free(data->error);
	if (data->bin_env)
		free(data->bin_env);
	free(data);	
	exit(0);	
}
