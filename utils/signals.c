/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi <enoshahi@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:41:36 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/06 12:23:57 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

static void	sigint_handler(int sig)
{
	(void)sig;
	g_sig.exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
}

void	signals_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	handle_eof(char *line, t_shell *shell)
{
	if (!line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		destroy_shell(shell);
		exit(g_sig.exit_status);
	}
}
