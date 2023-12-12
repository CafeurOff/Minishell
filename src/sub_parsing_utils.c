/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:04:44 by roroca            #+#    #+#             */
/*   Updated: 2023/12/12 15:05:58 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat_quotes(char *s, char *ref, int *i)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	s[len++] = ref[(*i)++];
	while (ref[(*i)] != 39 && ref[(*i)])
		s[len++] = ref[(*i)++];
	s[len++] = ref[(*i)++];
	return (s);
}

char	*ft_strcat_var(char *s, char *l, int *i, char *ref)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	while (s[len])
		len++;
	if (ref)
	{
		while (ref[j])
			s[len++] = ref[j++];
	}
	(*i) = ft_skip_env_val(l, (*i));
	return (s);
}

char	*ft_strcat_pars(char *s, char *ref, int *i, int *flag)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	while (ref[*i])
	{
		if (ref[(*i)] == 36 && ref[(*i) + 1] == 34 && *flag < 0)
			(*i)++;
		if (ref[(*i)] == 36 && ref[(*i) + 1] && ref[(*i) + 1] != 34)
			return (s);
		if (ref[(*i)] == 39 && *flag < 0)
			return (s);
		if (ref[(*i)] == 34)
			(*flag) = - (*flag);
		s[len++] = ref[(*i)++];
	}
	return (s);
}
