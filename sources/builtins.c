/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:05 by tkartasl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/16 12:20:00 by tkartasl         ###   ########.fr       */
=======
/*   Updated: 2024/02/19 12:17:13 by vsavolai         ###   ########.fr       */
>>>>>>> 17cf0669c0e97e7a23821e103e2b59545d53968a
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo()
{


	
}

void	cd(char	*path)
{
	if (chdir(path) < 0);
		//error
}

void	pwd()
{
	char	buffer[PATH_MAX];
	char	*path;

	if (ft_strlen() > PATH_MAX)
		//error;
	if (ft_strlen() == PATH_MAX)
	{
		path = getcwd(buffer[PATH_MAX + 1], sizeof(buffer));
		if (path == NULL)
			//error;	
	}
	else
		path = getcwd(buffer[PATH_MAX], sizeof(buffer));
	if (path == NULL)
		//error;
	ft_putstr_fd(path, fd);
}

void	export()
{


	
}
