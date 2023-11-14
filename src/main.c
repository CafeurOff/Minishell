/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:14 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/14 17:53:20 by lduthill         ###   ########.fr       */
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
			add_history(line);
			ft_exec_cmd(line, data);
		}
		free(line);
	}
//	ft_print_env(data->env);
//	ft_print_export(data->env);
//	ft_free(data->env);
}

void	ft_exec_cmd(char *line, t_data *data)
{
	int		i;
	char	**pars;

	i = 0;
	pars = ft_parsing(line, data->env);
	while (pars[i])
	{
		printf("Parsing line [%d] : %s\n", i, pars[i]);
		i++;
	}
	free(line);
	ft_free_tab(pars);
	rl_clear_history();
	ft_free(data->env);
	free(data);
	exit(0);
}
