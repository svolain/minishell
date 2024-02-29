/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:52:38 by vsavolai          #+#    #+#             */
/*   Updated: 2024/02/29 13:59:31 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_line(char *lines)
{
	char    *temp;

    temp = lines;
    temp = ft_skip_whitespace(temp);
    if (*temp == '|' || *temp == '&')
        return (1);
    return (0);
}

int check_after_redir(char *cmd_lines)
{
    char    *temp;

    temp = cmd_lines;
    while(*temp)
    {
        if ((*temp == '<' && *(temp + 1) == '>')
            || (*temp == '>' && *(temp + 1) == '<'))
            return (1);
        if (*temp == '<' || *temp == '>')
            temp = skip_redirs(temp);
        if (*temp == '|' || *temp == '&' || *temp == 0
            || *temp == '>' || *temp == '<')
            return (1);
        temp++;
    }
    return (0);
}

int check_syntax(char **cmd_lines)
{
    int i;
    

    i = 0;
    while(cmd_lines[i])
    {
        if (check_empty_line(cmd_lines[i]) == 1)
        {
            syntax_error(cmd_lines);
            return (0);
        }
        if (check_after_redir(cmd_lines[i]) == 1)
        {
            syntax_error(cmd_lines);
            return (0);
        }
        i++;
    }
    return (i);
}