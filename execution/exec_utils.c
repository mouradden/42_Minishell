/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:42:17 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/14 20:47:35 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_path(char *cmd, t_envp *envp)
{
	char	*path;
	char	*str;
	t_envp	*cursor;
	char	**paths;
	int		i;

	cursor = envp;
	while (cursor && cursor->title && ft_strcmp(cursor->title, "PATH"))
		cursor = cursor->next;
	if (cursor && cursor->title && !ft_strcmp(cursor->title, "PATH"))
		paths = ft_split(cursor->content, ':');
	else
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		str = ft_strjoin(path, cmd);
		free(path);
		if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
			return (str);
		i++;
	}
	return (NULL);
}
