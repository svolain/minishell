/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:26:12 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/26 11:42:48 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_redirs(t_redir **redirs, char **cmd_lines)
{
    int 		i;
    int 		j;
    t_redir    *new;

    new = *redirs;
    i =    0;
    while(i < 4)
    {
        j = 0;
        while(cmd_lines[i][j] != '\0')
        {
			if (cmd_lines[i][j] == '<' && cmd_lines[i][j +1] == '<')
				j = j + 2;
            if (cmd_lines[i][j] == '<')
			{
                new->arrow = '<';
                new = new->next;
            }
            else if (cmd_lines[i][j] == '>')
            {
                if (cmd_lines[i][j + 1] == '>')
                {
                    new->arrow = '!';
                    j++;
                }
                else
                    new->arrow = '>';
                new = new->next;
            }
            j++;
        }
        i++;
    }
}

void	get_redirs(t_redir **redirs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*file;
	char	*temp;

	file = 0;
	len = 0;
	i = 0;
	while (cmd_lines[i] != 0)
	{
		temp = cmd_lines[i];
		while (*temp != 0)
		{
			temp = find_redir(temp);
			if (*temp != 0)
			{
				len = get_len(temp);
				file = ft_strndup(temp, len);
				if (file == 0)
					printf("Error\n");
				build_list(redirs, file, i);
			}	
		}
		i++;
	}
}

void	get_heredocs(t_redir **heredocs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*lim;
	char	*temp;

	lim = 0;
	len = 0;
	i = 0;
	while (cmd_lines[i] != 0)
	{
		temp = cmd_lines[i];
		while (*temp != 0)
		{
			temp = find_limiter(temp);
			if (*temp != 0)
			{
				len = get_len(temp);
				lim = ft_strndup(temp, len);
				if (lim == 0)
					printf("Error\n");
				build_list(heredocs, lim, i);
			}	
		}
		i++;
	}
}

void	parse_line(char	*line)
{
	char		**cmd_lines;
	int			pipe_count;
	t_redir		*heredocs;
	t_redir		*redirs;
	
	pipe_count = 0;
	cmd_lines = ft_split(line, '|');
	while (cmd_lines[pipe_count] != 0)
		pipe_count++;
	get_heredocs(&heredocs, cmd_lines);
	get_redirs(&redirs, cmd_lines);
	add_redirs(&redirs, cmd_lines);
	parse_command(&redirs, &heredocs, cmd_lines, pipe_count);
}
