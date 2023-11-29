/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:07:05 by roroca            #+#    #+#             */
/*   Updated: 2023/11/29 11:55:00 by roroca           ###   ########.fr       */
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

int	ft_white_line(char *s)
{
	int	i;

	i = 0;
	if ((s[0] == 33 || s[0] == 58) && s[1] == 0)
        return (1);
	while (s[i])
	{
		if ((s[i] < 9 || s[i] > 13) && s[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	ft_unlosed_quotes(char	*s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			i = ft_skip_arg_quotes(s, i);
			if (s[i] == 0 && s[i - 1] != 34 && s[i - 1] != 39)
			{
				printf("Error not handled : quotes unclosed\n");
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}
