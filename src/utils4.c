/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:51:21 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/22 18:39:39 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_env(char *s, char c)
{
	int		i;
	int		j;
	char	**split;

	j = 0;
	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		i = 0;
		while (s[i] != c && s[i])
			i++;
		if (*s && i)
			split[j++] = ft_substr(s, 0, i);
		s += i;
	}
	split[j] = 0;
	return (split);
}

int	count_word(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			word++;
		i++;
	}
	return (word);
}

char	**free_word(char **s)
{
	while (*s)
		free(*s++);
	free(s);
	return (NULL);
}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	if (!s1)
		return (s2);
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[a] != '\0')
	{
		str[i + a] = s2[a];
		a++;
	}
	str[i + a] = '\0';
	return (str);
}

char	*ft_strjoin_keep(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	if (!s1)
		return (s2);
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[a] != '\0')
	{
		str[i + a] = s2[a];
		a++;
	}
	str[i + a] = '\0';
	return (str);
}
