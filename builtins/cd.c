/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:47:26 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/12 15:37:33 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_env __unused *env, char *path)
{
	if (path == NULL)
		chdir("/Users/mdenguir");
	else if (chdir(path) != 0)
	{
		printf("cd : %s : No such file or directory\n", path);
		gl_exit_status = 1;
	}
}
