/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:49:30 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/11 21:42:23 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_strncmp()
**	Function for compare two strings
**	@s1 : first string
**	@s2 : second string
**	@n : number of characters to compare
*/

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

/*	ft_atoi()
**	Function for convert a string to an integer
**	@str : string to convert
*/

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	result *= sign;
	return (result);
}

/*	ft_strrev()
**	Function for reverse a string
**	@str : string to reverse
**	@a : sign
**	@n : number to convert
**	@num : number of characters
*/

char	*ft_strrev(char *str, int a, int n, int num)
{
	while (num >= 0)
	{
		str[num] = (a * (n % 10)) + 48;
		n /= 10;
		num--;
	}
	if (a == -1)
		str[0] = '-';
	return (str);
}

/*	ft_itoa()
**	Function for convert an integer to a string
**	@n : number to convert
*/

char	*ft_itoa(int n)
{
	char	*str;
	int		num;
	int		a;
	int		len;

	a = 1;
	len = 1;
	if (n < 0)
	{
		len = 2;
		a = -1;
	}
	num = n;
	while (num / 10 != 0)
	{
		num /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	str = ft_strrev(str, a, n, len - 1);
	return (str);
}

/*	ft_strlen()
**	Function for calculate the length of a string
**	@str : string to calculate
*/

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
