/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:35:47 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/16 13:30:05 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	(void)ac;
	(void)av;
	env.envp = copy_env(envp);
	env.in = dup(STDIN_FILENO);
	env.out = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	minishell(env, envp);
	clear_history();
	free_envp(&env);
	return (0);
}
