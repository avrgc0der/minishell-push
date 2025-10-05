/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:00:32 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/05 18:28:58 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * get_input
// * main_loop
// * main

/// @brief Get the input string and parse it
/// @return SUCCESS or FAILURE (1 or 0)
static char	*get_input(void)
{
	char	*str;

	while (1)
	{
		if (isatty(0))
			str = readline(PROMPT);
		else
			str = readline("");
		if (!str)
		{
			ft_dprintf(2, "input failed\n"); // * signal here
			return (NULL);
		}
		replace_whitespaces(str);
		while (*str == ' ')
			str++;
		str = ft_strdup(str);
		if (!str)
			return (NULL);
		if ((add_history(str), 1) && ft_validate(str))
			return (str);
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
			break ;
		}
		input = get_input();
		if (!input)
			break ;
		if (shell->ast)
			free_tree(&shell->ast);
		shell->ast = scaffold_ast(input, shell->envps);
		if (!shell->ast)
			break ;
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

	(void) argc;
	(void) argv;
	shell = create_shell(envp);
	if (!shell)
		exit(1);
	main_loop(shell);
	destroy_shell(shell);
	exit(0);
	return (0);
}
