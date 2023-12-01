/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:07:05 by roroca            #+#    #+#             */
/*   Updated: 2023/12/01 16:41:20 by lduthill         ###   ########.fr       */
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
			printf("bash: syntax error near unexpected token `%s'\n", pars[i]);
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

int	ft_export_error(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == 61)
		{
			printf("bash: export: `%s': not a valid identifier\n", str[i]);
			return (1);
		}
		if (str[i][0] == 22)
		{
			printf("bash: export: `%s': not a valid identifier\n", str[i]);
			return (1);
		}
		while (str[i][j])
		{
			if (str[i][j] == 61)
				break ;
			if (ft_isalnum(str[i][j]) == 0)
			{
				printf("bash: export: `%s': not a valid identifier\n", str[i]);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
