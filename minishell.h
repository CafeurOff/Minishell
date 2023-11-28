/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:22:33 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/28 17:26:56 by roroca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
/* struct data
*	bin_env	=>	PATH f the shell
*	error	=>	error message
*	env		=>	list of environement variables
*/

typedef struct s_data
{
	char			**bin_env;
	char			**join_env;
	char			*error;
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

/*	struct pars
*	cmd			=>	cmd of the line
*	args		=>	arguments of the cmd / option, NULL if there is none
*	in			=>	redirection in, NULL if there is none
*	out			=>	redirection out, NULL if there is none
*	flag		=>	0 = none redirection / 1 = simple redirection / 2 = double redirection
*	del			=>	delimiter of the function, NULL if there is none
*/

typedef struct s_pars
{
	char			*cmd;
	char			**args;
	char			*in;
	char			*out;
	int				flag;
	char			*del;
}	t_pars;

/* env.c */
t_env	*ft_copy_env(char **envp);
char	*ft_get_id(char *str);
char	*ft_get_value(char *str);
char	*ft_getenv(char *str, t_env *env);
void	ft_print_env(t_env *env);
/* export.c */
void	ft_export(t_pars *pars, t_data *data, int i);
void	ft_setenv(char *find, char *str, t_data *data);
void	ft_print_export(t_env *data);
void	ft_setid(t_data *data, char *str);
int		ft_id_exist(t_data *data, char *str);
/* unset.c */
int		ft_unset(t_pars *pars, t_data *data, int i);
void	ft_unsetenv(char **str, t_data *data);
/* cd.c */
void	ft_cd(t_data *data, t_pars *pars);
void	ft_cd_home(t_data *data);
void	ft_cd_path(t_pars *pars, t_data *data);
/* echo.c */
void	ft_echo(t_pars *pars, int i);
int		ft_print_echo(char *str);
int		ft_id_index(t_data *data, char *str);
/* utils.c */
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strrev(char *str, int a, int n, int num);
char	*ft_itoa(int n);
int		ft_strlen(char *str);
/* utils2.c */
void	pre_init(t_env *env);
char	*ft_strdup(char *str);
char	*ft_strchr(const char *s, int c);
void	ft_free(t_env *env);
void	ft_free_tab(char **s);
/* utils3.c */
int		count(char *s);
char	**ft_split(char *s);
char	*ft_substr(char *s, int start, int len);
void	ft_free_t_pars(t_pars *cmd);
void	ft_error_free(t_pars *pars, t_data *data);
/* utils4.c */
char	**free_word(char **s);
int		count_word(char *s, char c);
char	**ft_split_env(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_keep(char *s1, char *s2);
/*main.c*/
void	ft_exec_cmd(char *line, t_data *data);
void	ft_free_all(t_data *data, char **args, t_pars *pars);
void	ft_is_builtin(t_pars *cmd, t_data *data, char **pars);
/* signal.c */
void	ft_sigint(int sig);
void	ft_sigquit(int sig);
/* execve.c */
void	ft_exec(t_pars *pars, char *cmd, t_data *data);
void	ft_execve(t_pars *pars, t_data *data);
char	**ft_joincmd(char *cmd, char **args);
char	**ft_join_env(t_data *data);
/* pars_tab.c */
t_pars	*ft_init_cmd_line(char **pars);
int		ft_count_args_line(char **pars, int flag);
t_pars	*ft_command_line(char **pars, t_pars *cmd);
int		ft_count_lines(char **pars);



/* reparse.c */
char	**ft_parsing(char *line, t_data *data);
int	ft_count_args(char *line);
int	ft_skip_arg(char *line, int i);
char	*ft_subarg(char *line, t_data *data);
char	*ft_var(char *l, t_data *data);
int		ft_skip_env_val(char *l, int i);
char	*ft_replace_line(char *l, char **var);
int	ft_replacelen(char *l, char **var);
int		ft_count_env_val(char *line);
int	ft_skip_arg_quotes(char *line, int i);
int	ft_white_line(char *s);
char	*ft_without_quotes(char *s);

/* error.c */
int		ft_syntax_error(char **pars, t_data *data);
int		ft_operator(char *s);

#endif