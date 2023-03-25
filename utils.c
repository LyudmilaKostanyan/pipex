/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:44:24 by lykostan          #+#    #+#             */
/*   Updated: 2023/03/25 15:44:25 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->ac - 1)
	{
		close(vars->pipes[i][0]);
		close(vars->pipes[i][1]);
	}
}

void	path_check(t_vars *vars, char *cmd)
{
	char	*s;
	int		i;
	int		j;

	if (access(cmd, X_OK) != -1)
	{
		vars->cmd = ft_strdup(cmd);
		return ;
	}
	j = 0;
	while (vars->paths[j])
	{
		s = ft_strjoin(vars->paths[j], "/");
		vars->cmd = ft_strjoin(s, cmd);
		free(s);
		i = access(vars->cmd, X_OK);
		if (i != -1)
			return ;
		j++;
		free(vars->cmd);
	}
	perror("Cmd");
	exit(0);
}

void	for_free(t_vars *vars)
{
	int	i;
	int	j;

	free(vars->pid);
	i = -1;
	while (++i < vars->ac - 1)
		free(vars->pipes[i]);
	free(vars->pipes);
	i = -1;
	while (++i < vars->ac)
	{
		j = -1;
		while (vars->cmds[i][++j])
			free(vars->cmds[i][j]);
		free(vars->cmds[i]);
	}
	free(vars->cmds);
}
