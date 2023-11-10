/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:14 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/10 15:23:52 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(int ac, char **av, char **envp)
{
    t_env   *env;

    (void)ac;
    (void)av;
    env = ft_copy_env(envp);
    ft_print_env(env);
    return (0);
}
