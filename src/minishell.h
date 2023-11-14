/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:22:33 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/14 19:05:07 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	char			*bin_env;
	struct s_env	*env;
}	t_data;

/*	struct env
*	set		=>	1 = set	//	0 = unset
*	id		=>	name of environement variable
*	value	=>	value of environement variable
*/

typedef struct s_env
{
	int				set;
	char			*id;
	char			*value;
}	t_env;

typedef struct s_pars
{
	char			*cmd;
	char			**args;
	char			*in;
	char			*out;
}	t_pars;

/* env.c */
t_env	*ft_copy_env(char **envp);
char	*ft_get_id(char *str);
char	*ft_get_value(char *str);
char	*ft_getenv(char *str, t_env *env);
void	ft_print_env(t_env *env);
/* export.c */
void	ft_export(t_pars *pars, t_data *data, int i);
void	ft_setenv(char *find, char *str, t_env *env);
void	ft_print_export(t_env *data);
void	ft_setid(t_data *data, char *str);
/* utils.c */
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strrev(char *str, int a, int n, int num);
char	*ft_itoa(int n);
int		ft_strlen(char *str);
/* utils2.c */
void	pre_init(t_env *env);
char	*ft_strdup(char *str);
char	*ft_strchr(char *s, int c);
void	ft_free(t_env *env);
/* utils3.c */
int		count(char *s);
char	**ft_split(char *s);
char	*ft_substr(char *s, int start, int len);
/*parse.c*/
char	*ft_substr_arg(char *line);
char	*ft_subarg(char *line, int arg);
int		ft_white_line(char *line);
int		ft_skip_arg(char *line, int i);
/*parsing.c*/
char	**ft_parsing(char *line, t_env *env);
int		ft_count_args(char *line);
char	*ft_env_val(char *pars, t_env *env);
char	*ft_env_in_string(char *s, t_env *env);
int		ft_strenv_len(char **var);
char	**ft_env_var(char **var, t_env *env);
void	ft_free_tab(char **s);
/*main.c*/
void	ft_exec_cmd(char *line, t_data *data);
/* signa.c */
void   ft_sigint(int sig);
void   ft_sigquit(int sig);

#endif
