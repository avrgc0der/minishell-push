/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:15:27 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 17:25:51 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Get a string representation of a token type
 * @param type The token type
 * @return String representation of the token type
 */
static char *token_type_to_str(t_symbol type)
{
    if (type == WORD)
        return "WORD";
    else if (type == PIPE)
        return "PIPE";
    else if (type == INPUT)
        return "INPUT";
    else if (type == HEREDOC)
        return "HEREDOC";
    else if (type == TRUNCATE)
        return "TRUNCATE";
    else if (type == APPEND)
        return "APPEND";
    else if (type == SPACES)
        return "SPACES";
    else if (type == ENV)
        return "ENV";
    else if (type == INFILE)
        return "INFILE";
    else if (type == OUTFILE)
        return "OUTFILE";
    else if (type == END)
        return "END";
    else
        return "UNKNOWN";
}

/**
 * @brief Print a tree branch connector with appropriate indentation
 * @param depth Current depth in the tree
 * @param is_last Whether this is the last child at this level
 * @param is_right Whether this is a right child
 */
static void print_branch(int depth, int is_last, int is_right)
{
    int i;

    for (i = 0; i < depth - 1; i++)
        printf("│   ");

    if (depth > 0)
    {
        if (is_last)
            printf("└── ");
        else
            printf("├── ");

        if (is_right)
            printf("\033[1;36m[R]\033[0m ");
        else
            printf("\033[1;35m[L]\033[0m ");
    }
}

/**
 * @brief Print arguments array with formatting
 * @param args Array of argument strings
 */
static void print_args(char **args)
{
    int i = 0;

    if (!args || !args[0])
        return;

    printf("\033[3mArgs:\033[0m ");
    while (args[i])
    {
        printf("\033[1;33m\"%s\"\033[0m", args[i]);
        if (args[i + 1])
            printf(", ");
        i++;
    }
}

/**
 * @brief Recursively print the AST with beautiful formatting
 * @param node Current node to print
 * @param depth Current depth in the tree for indentation
 * @param is_last Whether this node is the last child of its parent
 * @param is_right Whether this node is a right child (1) or left child (0)
 */
static void print_ast_recursive(t_ast *node, int depth, int is_last, int is_right)
{
    if (!node)
        return;

    print_branch(depth, is_last, is_right);

    // Print node type
    printf("\033[1m%s\033[0m", token_type_to_str(node->value.type));

    // Print command if exists
    if (node->value.cmd && *node->value.cmd)
        printf(": \033[3;32m\"%s\"\033[0m", node->value.cmd);

    // Print arguments if they exist
    if (node->value.args)
    {
        printf(" ");
        print_args(node->value.args);
    }

    printf("\n");

    // Print children
    if (node->left || node->right)
    {
        if (node->left)
            print_ast_recursive(node->left, depth + 1, !node->right, 0);
        if (node->right)
            print_ast_recursive(node->right, depth + 1, 1, 1);
    }
}

/**
 * @brief Print a decorative header for the AST
 */
static void print_header(void)
{
    printf("\n\033[1;36m╔════════════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║          ABSTRACT SYNTAX TREE (AST)             ║\033[0m\n");
    printf("\033[1;36m╚════════════════════════════════════════════════╝\033[0m\n\n");
}

/**
 * @brief Print a decorative footer for the AST
 */
static void print_footer(void)
{
    printf("\n\033[1;36m╔════════════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║                  END OF AST                     ║\033[0m\n");
    printf("\033[1;36m╚════════════════════════════════════════════════╝\033[0m\n\n");
}

/**
 * @brief Debug function to print the entire AST in a beautiful tree format
 * @param root Root node of the AST
 */
void	debug_print_ast(t_ast *root)
{
    print_header();

    if (!root)
        printf("\033[1;31m[EMPTY TREE]\033[0m\n");
    else
        print_ast_recursive(root, 0, 1, 0);

    print_footer();
}