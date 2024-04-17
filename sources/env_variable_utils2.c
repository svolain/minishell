/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:29:54 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/16 09:07:13 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	variable_word_count(char *str)
{
	int		count;
	char	*temp;

	count = 0;
	if (str == 0)
		return (count);
	temp = str;
	while (*temp != 0 && *temp != '=')
	{
		if (*temp != ' ' && *temp != 0)
			count++;
		while (*temp != ' ' && *temp != 0 && *temp != '=')
			temp++;
		if (*temp != 0 && *temp != '=')
			temp++;
	}
	return (count);
}

int	word_count(char *str)
{
	int		count;
	char	*temp;

	count = 0;
	if (str == 0)
		return (count);
	temp = str;
	while (*temp != 0)
	{
		if (*temp != ' ' && *temp != 0)
			count++;
		while (*temp != ' ' && *temp != 0)
			temp++;
		if (*temp != 0)
			temp++;
	}
	return (count);
}

char	*count_expand_cmd(char *cmd, int i, t_env **env)
{
	char	*str;

	str = 0;
	if (count_env_variables(cmd) > 0)
	{
		str = ft_strdup("");
		if (str == 0)
			return (0);
		cmd = expand_all_env(cmd, str, i, env);
	}
	if (cmd == 0)
	{
		free(str);
		return (0);
	}
	return (cmd);
}

void	change_cmd_status(t_env **env_t, int status)
{
	int	i;

	i = 0;
	if (status > 0)
		status = status / 256;
	while (i < TABLE_SIZE)
	{
		if (env_t[i] != (t_env *)DELETED_NODE && env_t[i] != NULL)
			env_t[i]->status = status;
		i++;
	}
}