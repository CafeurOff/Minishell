/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:14 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/09 17:31:49 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(int ac, char **av, char **envp)
{
    t_env   *env;
    int     i;

    i = 0;

    (void)ac;
    (void)av;
    env = ft_copy_env(envp);
    while (i < 60)
    {
       // printf("ENVP[%d] = %s\n", i, envp[i]);
        printf("env[%d].id = %s\n",i,  env[i].id);
        printf("env[%d].value = %s\n",i, env[i].value);
        printf("env[%d].set = %d\n",i, env[i].set);
        printf("\n");
        i++;
    }
    printf("AVANT SET : %s\n", ft_getenv("USER", env));
    ft_setenv("USER", "roroca", env);
    printf("APRES SET : %s\n", ft_getenv("USER", env));
    return (0);
}
