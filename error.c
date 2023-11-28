/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:07:05 by roroca            #+#    #+#             */
/*   Updated: 2023/11/28 17:26:53 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_syntax_error(char **pars, t_data *data)
{
	int	i;

	i = 1;
	if (ft_operator(pars[0]))
		return (1);
	while (pars[i])
	{
		if ((ft_operator(pars[i]) && ft_operator(pars[i + 1])) || (ft_operator(pars[i]) && pars[i + 1] == NULL))
		{
			data->error = "2";
			printf("bash: syntax error near unexpected token `%s'", pars[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_operator(char *s)
{
	if (ft_strncmp(s, ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "|", 2) == 0)
		return (1);
	else
		return (0);
}
