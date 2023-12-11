/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:47:01 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/11 16:08:41 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* sig_handler()
 *  Function for handle the signal
 *  Set errno to 2 for avoid the error message
 *  @sig : signal
 */

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT && errno != 2)
	{
		g_var = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT && errno == 2)
		g_var = 131;
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		printf("\b\b  \b\b");
	}
}

/* ft_check_signal()
 *  Function for check if signal is received and set the error message
 *  @data : struct with all the data
 */

void	ft_check_signal(t_data *data)
{
	if (g_var == 130 || g_var == 131)
	{
		data->error = g_var;
		g_var = 0;
	}
}

/* ft_setup_signal()
 *  Function for setup the signal
 */

void	ft_setup_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
