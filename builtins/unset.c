/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:18:52 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/21 16:28:55 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_envp **envp, char *title)
{
	if(check_duplicate(envp, title))
	{
		remove_node(envp, title);
	}
	
}