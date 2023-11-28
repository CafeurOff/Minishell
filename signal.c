/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:47:01 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/22 23:26:15 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_sigint()
 * Function for handle the signal SIGINT
 * @sig : signal
 */

void	ft_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* ft_sigquit()
 * Function for handle the signal SIGQUIT
 * @sig : signal
 */

void	ft_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
	printf("\b\b  \b\b");
}