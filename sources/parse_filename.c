/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:20:57 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/19 10:02:47 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
char	*find_limiter(char *str)
{
    while (*str != 0)
    {   
		if (*str == '\'' || *str == '\"')
			str = skip_quotes(str, *str);
        if (*str == '<' && *(str + 1) == '<')
        {    
            str = str + 2;
            str = ft_skip_whitespace(str);
			return (str);
        }
        str++;
    }
    return (str);
}

char    *find_redir(char *str)
{
    while (*str != 0)
    {
		if (*str == '\'' || *str == '\"')
			str = skip_quotes(str, *str);
		if ((*str == '>' && *(str + 1) == '>') ||
            (*str == '<' && *(str + 1) == '<'))
        {
            str = str + 2;
            str = ft_skip_whitespace(str);
            return (str);
        }
		else if (*str == '<' || *str == '>')
        {
            str = str + 1;
            str = ft_skip_whitespace(str);
            return (str); 
        }
		str++;
    }
    return (str);
}

void	put_fd_lst(char *str, t_redir **new)
{
	while (*str != 0)
	{
		if (ft_isdigit(*str) == 1)
		{
			if (*(str - 1) == '-')
			{
				while (*str != '<' && *str != '>' && *str != 0 && *str != ' ')
					str++;
				if (*str == '<' || *str == '>')
				{
					if (*(str + 1) == '<' || *(str + 1) == '>')
						str++;
				}
			}
			else
				str = check_if_digit(str, new);
		}	
		if (*str == '<' || *str == '>')
		{
			(*new) = (*new)->next;
			if (*(str + 1) == '<' || *(str + 1) == '>')
				str++;
		}
		str++;
	}
}

char	*check_if_digit(char *str, t_redir **redir)
{
	char	*temp;
	int		i;

	i = 0;
	temp = 0;
	while (str[i] != 0 && str[i] != '<' && str[i] != '>' && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == '<' || str[i] == '>')
	{
		temp = ft_strndup(str, i);
		if (temp == 0)
			return (0);
		(*redir)->fd = ft_atoi(temp);
		(*redir)->flag = 1;
		free(temp);
		return (&str[i]);
	}
	else
		return (str);
}
