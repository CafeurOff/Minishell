/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roroca <roroca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:22:33 by lduthill          #+#    #+#             */
/*   Updated: 2023/12/12 15:08:46 by roroca           ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>

extern int		g_var;

/* struct data
*	bin_env	=>	PATH f the shell
*	error	=>	error message
*	env		=>	list of environement variables
*/

typedef struct s_data
{
	char			**bin_env;
	char			**join_env;
	int				error;
	int				*fd;
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
*	cmd		=>	cmd of the line
*	args	=>	arguments of the cmd / option, NULL if there is none
*	in		=>	redirection in, NULL if there is none
*	out		=>	redirection out, NULL if there is none
*	flag	=>	0 = none redirection / 1 = simple redir / 2 = double redir
*	flag2	=>	0 = none redirection / 1 = redirection in / 2 = delimiteur
*	del		=>	delimiter of the function, NULL if there is none
*/

typedef struct s_pars
{
	char			*cmd;
	char			**args;
	char			*in;
	char			**out;
	int				flag;
	int				flag2;
	char			**del;
}	t_pars;

/* cd.c */
void	ft_cd(t_data *data, t_pars *pars, int i);
void	ft_cd_home(t_data *data);
void	ft_cd_path(t_pars *pars, t_data *data, int i);
int		cd_error_management(t_data *data, t_pars *pars, int i);
void	ft_pwd(t_data *data);
/* echo.c */
void	ft_echo(t_pars *pars, int i);
int		ft_print_echo(char *str);
int		ft_id_index(t_data *data, char *str);
/* env.c */
t_env	*ft_copy_env(char **envp);
char	*ft_get_id(char *str);
char	*ft_get_value(char *str);
char	*ft_getenv(char *str, t_env *env);
void	ft_print_env(t_env *env);
/* error.c */
int		ft_syntax_error(char **pars, t_data *data);
int		ft_operator(char *s);
int		ft_white_line(char *s);
int		ft_unclosed_quotes(char	*s);
int		ft_export_error(char **str, t_data *data);
/* error2.c */
int		ft_identifier_error(char *str, t_data *data);
void	ft_exit(t_data *data, char **args, t_pars *cmd, int i);
int		ft_access_path(char *res, t_pars *pars, int j, t_data *data);
void	ft_execve_error(t_pars *pars, t_data *data, int j);
/* execve.c */
void	ft_exec(t_pars *pars, char *cmd, t_data *data);
void	ft_execve(t_pars *pars, t_data *data, int j);
void	ft_exec_path(t_pars *pars, t_data *data, int j);
int		ft_is_cmd(t_pars *pars, t_data *data, int j);
char	**ft_joincmd(char *cmd, char **args);
/* export.c */
void	ft_export(t_pars *pars, t_data *data, int i);
void	ft_setid(t_data *data, char *str);
void	ft_setenv(char *find, char *str, t_data *data);
void	ft_print_export(t_env *data);
int		ft_id_exist(t_data *data, char *str);
/*main.c*/
void	ft_exec_cmd(char *line, t_data *data);
void	ft_free_all(t_data *data, char **args, t_pars *pars);
void	ft_is_builtin(t_pars *cmd, t_data *data, char **pars, int i);
void	ft_init_data(t_data *data);
/* pars_tab_utils.c */
int		ft_skip_tab(char **pars, int flag);
int		ft_count_lines(char **pars);
int		ft_count_cmd_args(char **pars, int flag);
int		ft_count_cmd_out(char **pars, int flag);
int		ft_count_cmd_del(char **pars, int flag);
/* pars_tab.c */
t_pars	*ft_init_cmd_line(char **pars);
void	ft_init_cmd_args(char **pars, t_pars *cmd, int flag);
void	ft_init_cmd_out(char **pars, t_pars *cmd, int flag);
void	ft_init_cmd_del(char **pars, t_pars *cmd, int flag);
void	ft_command_line(char **pars, t_pars *cmd);
/* parse.c */
int		ft_skip_env_val(char *l, int i);
int		ft_skip_arg(char *line, int i);
int		ft_skip_arg_quotes(char *line, int i);
char	*ft_without_quotes(char *s);
int		ft_len_without_quotes(char *s);
/* parsing.c */
char	**ft_parsing(char *line, t_data *data);
int		ft_count_args(char *line);
char	*ft_subarg(char *line, t_data *data);
/* pipe.c */
void	ft_exec_pipe(t_data *data, char **pars, t_pars *cmd, int i);
void	ft_handle_pipe(t_data *data, t_pars *cmd, int i, int *fd);
void	ft_handle_pipe_child(int *fd);
/* redirection.c */
void	ft_delimiter(char *s);
void	ft_handle_del(t_pars *cmd, int i);
void	ft_redirect_to_cmd(t_pars *cmd, t_data *data, char **pars, int i);
int		ft_handle_in(t_pars *cmd, int i);
int		ft_handle_out(t_pars *cmd, int i);
/* signal.c */
void	ft_sig_handler(int sig);
void	ft_check_signal(t_data *data);
void	ft_setup_signal(void);
/* sub_parsing.c */
char	*ft_var(char *l, t_data *data);
char	*ft_replace_line(char *l, char **var);
int		ft_replacelen(char *l, char **var);
int		ft_count_env_val(char *line);
/* sub_parsing_utils.c */
char	*ft_strcat_var(char *s, char *l, int *i, char *ref);
char	*ft_strcat_quotes(char *s, char *ref, int *i);
char	*ft_strcat_pars(char *s, char *ref, int *i, int *flag);
/* unset.c */
int		ft_unset(t_pars *pars, t_data *data, int i);
void	ft_unsetenv(char **str, t_data *data);
int		ft_unset_error(char **str, t_data *data);
int		ft_unset_identifier_error(char **str, t_data *data);
/* utils.c */
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strrev(char *str, int a, int n, int num);
char	*ft_itoa(int n);
int		ft_strlen(char *str);
/* utils2.c */
char	*ft_strdup(char *str);
char	*ft_strchr(const char *s, int c);
void	pre_init(t_env *env);
void	ft_free(t_env *env);
void	ft_free_tab(char **s);
/* utils3.c */
int		count(char *s);
char	**ft_split(char *s);
char	*ft_substr(char *s, int start, int len);
void	ft_free_t_pars(t_pars *cmd);
void	ft_error_free(t_pars *pars, t_data *data);
/* utils4.c */
char	**ft_split_env(char *s, char c);
int		count_word(char *s, char c);
char	**free_word(char **s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_keep(char *s1, char *s2);
/* utils5.c */
int		ft_isalnum(int i);
char	**ft_join_env(t_data *data);
int		ft_isdigit(char *s);
void	*ft_calloc(size_t nmb, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
