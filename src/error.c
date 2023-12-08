/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:07:05 by roroca            #+#    #+#             */
/*   Updated: 2023/12/08 16:19:25 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_syntax_error(char **pars, t_data *data)
{
	int	i;

	i = 0;
	while (pars[i])
	{
		if ((ft_operator(pars[i]) && ft_operator(pars[i + 1])) || (ft_operator(pars[i]) && pars[i + 1] == NULL) || (ft_operator(pars[0]) == 1))
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
	if (s == NULL)
		return (1);
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
	int flag;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			flag = s[i];
			i = ft_skip_arg_quotes(s, i);
			if (s[i] == 0 && s[i - 1] != flag)
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

int	ft_export_error(char **str, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_identifier_error(str, data))
			return (1);
		while (str[i][j])
		{
			if (str[i][j] == 61)
				break ;
			if (ft_isalnum(str[i][j]) == 0 && str[i][j] != 95)
			{
				printf("bash: export: `%s': not a valid identifier\n", str[i]);
				data->error = "1";
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		ft_identifier_error(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i][0] >= '0' && str[i][0] <= '9')
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = "1";
		return (1);
	}
	if (str[i][0] == 61)
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = "1";
		return (1);
	}
	if (str[i][0] == 32)
	{
		printf("bash: export: `%s': not a valid identifier\n", str[i]);
		data->error = "1";
		return (1);
	}
	return (0);
}
