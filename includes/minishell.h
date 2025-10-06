/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:56:03 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 12:44:57 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# define PROMPT "TRASH >>"
# define TRUE 1
# define FALSE 0
# define MAX_PATH 1024

typedef struct s_sig
{
	int		exit_status;
}	t_sig;

extern t_sig	g_sig;

typedef struct s_exec
{
	int					in_fd;
	int					out_fd;
	char				*cmd;
	char				**args;
	int					error;
	struct s_exec		*next;
}	t_exec;

typedef enum e_symbol
{
	SPACES,
	WORD,
	ENV,
	PIPE,
	INPUT,
	HEREDOC,
	TRUNCATE,
	APPEND,
	INFILE,
	OUTFILE,
	END
}	t_symbol;

// ! linked list for environment variables
typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

// ! struct for all the environment data
typedef struct s_envs
{
	int		e_code;	// * exit code
	int		shlvl;	// * how many levels of shell your in
	char	*cwd;	// * current working directory
	char	*owd;	// * old working directory
	char	**path;	// * all paths in $PATH
	char	**envs;	// * our enviroment variables for execve
	t_env	*env;	// * head for envs linked list
}	t_envs;

// ! struct for actual commands in the input
typedef struct s_cmd
{
	char		*cmd; // * command to execute
	char		**args; // * arguments for the command
	t_symbol	type; // * type of symbol (refer below)
}	t_cmd;

// ! struct for ast tree
typedef struct s_ast
{
	t_cmd			value; // * value of the command
	struct s_ast	*left; // * next token in the list
	struct s_ast	*right; // * previous token in the list
}	t_ast;

// ! main struct for minishell
typedef struct s_shell
{
	t_cmd	*cmd; // * main command executable
	t_ast	*ast; // * abstract syntax tree for the input
	t_envs	*envps; // * environment variables
	t_exec	*exec; // * execution linked list
	int		exit_status; // * exit status of the last command
}	t_shell;

// ! function prototypes for enviroment variables
t_env	*split_var(char *envp);
int		env_create_var(t_env *env, char *key, char *val);
void	add_env(t_env **env, t_env *new);
t_env	*env_search(t_env *env, char *key_name);
int		envs_array(t_envs *list_envs, t_env *env);
int		modify_env(t_env *env, char *key_name, char *new_val);
int		env_size(t_env *env);
int		change_shlvl(t_env *env);

// ! function prototypes for validation
int		ft_validate(char *str);
char	*get_redirect(t_ast *node);

// ! function prototypes for cleaning
int		replace_whitespaces(char *str);
void	skip_quotes(const char *str, int *i);
void	skip_within(char *str, int *quote_count, int *final_len, int *i);
void	add_within(char *str, char *result, int *i, int *j);
char	*remove_string_quotes(char *str);

// ! function prototypes for custom functions
char	**ft_splitms(char const *s, char c);
char	*ft_strstrms(char *str, char *to_find);
char	*ft_strappend(char *str1, char *str2);
int		split_even(char *cmd, char *found, t_ast **left, t_ast **right);
int		split_in_place(char *cmd, char *found, t_ast **left, t_ast **right);

// ! function prototypes for frees
void	free_dpt(char **str);
void	free_str(char *str);
void	free_null(void **ptr);

// ! function prototypes for parsing frees
void	free_tree(t_ast **node);
void	destroy_shell(t_shell *shell);

// ! function prototypes for env frees
void	env_free_all(t_envs *envs);
void	env_free_node(t_env *env);
void	free_env(t_env *env);

// ! function prototypes for execution frees
void	free_exec(t_exec *exec);
void	free_all_exec(t_exec **exec);

// ! function prototypes for parsing errors
t_ast	*ast_error(t_ast *node, char *error_message);
void	*single_env_error(void *ptr, char *error_message);
void	*double_env_error(void *ptr1, void *ptr2, char *error_message);
int		single_tree_error(void *ptr, char *error_message);
int		double_tree_error(void *ptr1, void *ptr2, char *error_message);

// ! function prototypes for execution errors
int		one_pass_cleanup(t_shell *shell);
int		set_failure(t_exec *exec, char *error_message);
int		get_execve_error(char *cmd);

// ! function prototypes for shell
t_shell	*create_shell(char **envs);

// ! function prototypes for ast
t_ast	*scaffold_ast(char *input, t_envs *envps);
t_ast	*create_ast_node(char *value);
int		split_args(t_ast *head);
int		remove_quotes(t_ast *node);
int		remove_from_args(t_ast *node);
char	*expand_var(char *str, int i, t_envs *envps);
char	*loop_str(char *str, t_envs *envps);

// ! function prototypes for execution (traversal and handling)
t_exec	*init_exec(void);
int		execute(t_shell *shell);
int		one_pass(t_shell *shell, t_exec *exec, t_ast *node, t_env *envl);
int		two_pass(t_shell *shell, t_exec *exec, t_ast *node, t_env *envl);
int		handle_heredoc(t_shell *shell, t_exec *exec, t_ast *node, t_envs *envs);
int		handle_pipe(t_shell *shell, t_exec *exec, t_ast *node, t_env *envl);
int		handle_input(t_shell *shell, t_exec *exec, t_ast *node, t_env *env);
int		handle_append(t_shell *shell, t_exec *exec, t_ast *node, t_env *env);
int		handle_truncate(t_shell *shell, t_exec *exec, t_ast *node, t_env *env);
int		handle_word(t_exec *exec, t_ast *node, char **envar);

// ! function prototypes for execution (execve and builtins)
int		exec_external(t_shell *shell, t_exec *exec, char **envs);

// ! function prototypes for execution (multiple commands)
// Pipe execution helpers
int		count_commands(t_exec *exec);
pid_t	fork_and_exec(t_shell *shell, t_exec *exec);
void	setup_child_fds(t_exec *exec);
void	close_all_exec_fds(t_exec *exec);
int		wait_and_cleanup(pid_t *pids, int count);
int		cleanup_pids(pid_t *pids, int exit_code);

// ! function prototypes for execution helpers
int		set_path(t_envs *envs);
void	check_close(int fd);
int		find_heredoc(t_ast *node);
char	*get_path(char *command, char **env);
void	close_all_pipes(t_exec *head, t_exec *current_cmd);

// ! function prototypes for builtins
int		is_builtin(char *cmd);
int		exec_builtin(t_exec *exec, t_shell *shell);
int		ft_cd(char **args, t_envs *envs);
int		ft_echo(char **args);
int		ft_exit(char **args, t_shell *shell);
int		ft_export(t_envs *envs, char **args);
int		ft_pwd(void);
int		ft_unset(t_envs *envs, char **args);
int		ft_env(t_envs *envs);

// ! debug functions prototypes and functions i haven't for use for yet
void	debug_print_ast(t_ast *root);

// ! function prototypes for signals
void	handle_eof(t_shell *shell);
void	signals_init(void);

#endif