/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:10:24 by lduthill          #+#    #+#             */
/*   Updated: 2023/02/21 11:10:25 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	setcmp(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] != '\0')
	{
		if (setcmp(set, s1[start]) == 0)
			return (start);
		start++;
	}
	return (start);
}

static size_t	ft_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	len;

	len = ft_strlen(s1) - 1;
	end = 0;
	while (len - end > 0)
	{
		if (setcmp(set, s1[len - end]) == 0)
			return (end);
		end++;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*s2;

	if (!s1 || !set)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	if (start + end >= ft_strlen(s1))
		return (ft_strdup(""));
	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) - (end + start) + 1));
	if (!s2)
		return (NULL);
	s2 = ft_substr(s1, start, (ft_strlen(s1) - (end + start)));
	return (s2);
}
