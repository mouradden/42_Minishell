/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:34:11 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/24 16:37:19 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_check(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		signal(sig, sig_check);
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	sig_check_herdoc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}
