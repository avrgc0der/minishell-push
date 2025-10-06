/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:00:32 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 11:56:44 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains
// *	get_input
// *	main_loop
// *	main

/// @brief Get the input string and parse it
/// @return SUCCESS or FAILURE (1 or 0)
static char	*get_input(void)
{
	char	*str;
	char	*trimmed;
	char	*temp;

	while (1)
	{
		if (isatty(0))
			str = readline(PROMPT);
		else
			str = readline("");
		if (!str)
			handle_eof(str); // this doesn't work?
		replace_whitespaces(str);
		temp = str;
		while (*temp == ' ')
			temp++;
		trimmed = ft_strdup(temp);
		free_str(str);
		if (!trimmed)
			return (NULL);
		add_history(trimmed);
		if (ft_validate(trimmed))
			return (trimmed);
		free(trimmed);
	}
}

/// @brief Main while loop Minishell
/// @param t_shell pointer
/// @return Exit status
static void	main_loop(t_shell *shell)
{
	char	*input;

	if (!isatty(0))
		rl_outstream = stdin;
	while (1)
	{
		envs_array(shell->envps, shell->envps->env);
		if (!shell->envps->envs)
		{
			ft_dprintf(2, "environ's failed\n");
			break;
		}
		input = get_input();
		if (!input)
			break;
		if (shell->ast)
			free_tree(&shell->ast);
		shell->ast = scaffold_ast(input, shell->envps);
		if (!shell->ast)
			break;
		shell->envps->e_code = execute(shell);
	}
}

/// @brief Main entry point for the Minishell
/// @param argc Argument count
/// @param argv Argument vector
/// @param envp Environment variables
/// @return Exit status
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	g_sig.exit_status = 0;
	shell = create_shell(envp);
	if (!shell)
		exit(1);
	signals_init();
	main_loop(shell);
	destroy_shell(shell);
	exit(0);
	return (0);
}
