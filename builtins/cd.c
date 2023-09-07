/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:47:26 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/07 17:25:38 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char *path)
{
	if (path == NULL)
		chdir("/Users/mdenguir");
	else if (chdir(path) != 0)
		printf("cd : %s : No such file or directory\n", path);
}
