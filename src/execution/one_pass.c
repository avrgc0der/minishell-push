/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_pass.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:35:33 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/08 11:51:47 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains
// *	heredoc_child
// *	handle_heredoc
// *	handle_pipe

void	heredoc_child(int fds[2], char *end, t_shell *shell, t_envs *envs)
{
	char	*line;

	close(fds[0]);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, end) == 0)
			break ;
		line = loop_str(line, envs);
		if (!line)
		{
			ft_dprintf(2, "An unknown error has occurred\n");
			break ;
		}
		ft_dprintf(fds[1], "%s\n", line);
		free_str(line);
	}
	close(fds[1]);
	destroy_shell(shell);
	exit(0);
}

int	handle_heredoc(t_shell *shell, t_exec *exec, t_ast *node, t_envs *envs)
{
	int		fds[2];
	int		status;
	int		pid;

	if (pipe(fds) == -1)
		return (set_failure(exec, "An unknown error has occurred\n"));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc_child(fds, node->right->value.args[0], shell, envs);
	}
	waitpid(pid, &status, 0);
	check_close(exec->in_fd);
	exec->in_fd = fds[0];
	close(fds[1]);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		exec->error = 1;
		return (FALSE);
	}
	return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
}

int	handle_pipe(t_shell *shell, t_exec *exec, t_ast *node, t_env *envl)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (set_failure(exec, "An unknown error has occurred\n"));
	exec->next = init_exec();
	if (!exec->next)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exec->error = 1;
		return (FALSE);
	}
	exec->out_fd = pipe_fds[1];
	exec->next->in_fd = pipe_fds[0];
	return (one_pass(shell, exec->next, node->right, envl));
}
