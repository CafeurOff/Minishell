/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:22:33 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/08 16:38:12 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	char *bin_env;
	struct s_env	*env;
}	t_data;

typedef struct s_env
{
	int 	set; // 1 = set 0 = unset
	char	*id;
	char	*value;
}	t_env;

/* env.c */
void 	pre_init(t_env *env);
t_env	*ft_copy_env(char **envp);
char	*ft_get_id(char *str);
char    *ft_get_value(char *str);

#endif
