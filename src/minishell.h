/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:22:33 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/13 13:41:10 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
t_env	*ft_copy_env(char **envp);
char	*ft_get_id(char *str);
char    *ft_get_value(char *str);
char   *ft_getenv(char *str, t_env *env);
void    ft_print_env(t_env *env);
/* export.c */
void    ft_setenv(char *find, char *str, t_env *env);
void    ft_print_export(t_env *data);
/* utils.c */
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strrev(char *str, int a, int n, int num);
char	*ft_itoa(int n);
int		ft_strlen(char *str);
/* utils2.c */
void 	pre_init(t_env *env);
char	*ft_strdup(char *str);
char	*ft_strchr(const char *s, int c);
void	ft_free(t_env *env);
#endif
