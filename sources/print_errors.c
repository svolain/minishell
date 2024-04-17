/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:02:18 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/16 15:09:52 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_filename(char *s, int *flag)
{
	int	i;

	i = 1;
	if (*flag == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": can't open file", 2);
	}
	else
	{
		while (s[i] != 0 && s[i] != '$' && s[i] != '=' && s[i] != '"'
			&& s[i] != '\'' && s[i] != ' ' && s[i] != '?' && s[i] != '/')
			i++;
		if (s[i] == '$' || s[i] == '=' || s[i] == '"'
			|| s[i] == '\'' || s[i] == '/')
			return ;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		*flag = 1;
	}
}

void	print_error(t_cmd_args **arr, int flag)
{
	if (flag == -1)
		ft_putendl_fd("minishell: error allocating memory", 2);
	if (flag == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((*arr)->args[0], 2);
		ft_putendl_fd(": File name too long", 2);
	}
	if (flag == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((*arr)->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

void	export_error(char *str, t_env **env_table)
{
	change_cmd_status(env_table, 256);
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

int	check_flag(int flag, char **cmd)
{
	if (flag == 3 || flag == 4)
	{
		pipe_error(flag, NULL, cmd);
		return (-1);
	}
	if (cmd == NULL)
		return (-1);
	return (1);
}
