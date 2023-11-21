/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:19:36 by roroca            #+#    #+#             */
/*   Updated: 2023/11/21 15:17:03 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_parsing()
*	Mother function to pars the args of a line
*/

/*	A GERER !!!!!
*	les acollades ouvrantes/fermantes ex: '''"''hello"' => '"hello"'
*	Insererez tous les elements du parsing dans le tableau t_pars
*/

char	**ft_parsing(char *line, t_env *env)
{
	int		args;
	int		i;
	char	**pars;

	args = 0;
	i = 0;
	args = ft_count_args(line);
	//printf("Args :%d\n", args);
	pars = malloc(sizeof(char *) * (args + 1));
	if (!pars)
		return (NULL);
	while (i < args)
	{
		pars[i] = ft_subarg(line, i, env);
//		printf("pars[%d] = %s\n", i, pars[i]);
		i++;
	}
	pars[i] = '\0';
	(void)env;
	free(line);
	return (pars);
}
/*	ft_count_args()
*	Function to count how many args got the line,
*	each args is separated by a whitespace, but "" or ''
*	count only for one arg, even if it's compose with whitespace
*/

int	ft_count_args(char *line)
{
	int	args;
	int	i;

	i = 0;
	args = 0;
	while (line[i])
	{
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		while ((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
			i += 2;
		if (line[i] && line[i] != 32 && (line[i] <= 9 || line[i] >= 13))
		{
			i = ft_skip_arg(line, i);
			args++;
		}
	}
	return (args);
}
/*	ft_substr_arg()
*	Function that work with ft_subarg(),
*	save the first arg of the line
*/

char	*ft_substr_arg(char *line, t_env *env)
{
	int		i;
	int		j;
	int		k;
	char	*s;

	i = ft_skip_arg(line, 0);
	j = 0;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	k = 0;
	while (j < i)
		s[k++] = line[j++];
	s[k] = '\0';
	s = ft_env_val(s, env);     
	return (s);
}
/*	ft_subarg()
*	Funtion that take a number in parameter,
*	parameter that define wich argument is saved;
*/

char	*ft_subarg(char *line, int arg, t_env *env)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
			i++;
		while ((line[i] == 34 && line[i + 1] == 34) || (line[i] == 39 && line[i + 1] == 39))
			i += 2;
		if (flag == arg && line[i] != 34 && line[i] != 39)
			return (ft_substr_arg(line + i, env));
		else if (flag == arg)
			return(ft_subarg_quotes(line + i, env));
		else
		{
			i = ft_skip_arg(line, i);
			flag++;
		}
	}
	return (NULL);
}

char	*ft_subarg_quotes(char *line, t_env *env)
{
	int i;
	int j;
	int len;
	int flag;
	char    *s;

	len = ft_skip_arg_quotes(line, 0);
	i = 1;
	j = 0;
	flag = line[0];
	s = malloc(sizeof(char) * (len - 1));
	if (!s)
		return (NULL);
	while (line[i] && line[i] != flag)
		s[j++] = line[i++];
	s[j] = '\0';
	if (flag == 34)
		s = ft_env_in_string(s, env);
	return (s);
}
