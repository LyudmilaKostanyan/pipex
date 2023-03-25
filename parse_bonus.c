/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:37:03 by lykostan          #+#    #+#             */
/*   Updated: 2023/03/17 19:37:04 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	path(t_vars *vars, char **env)
{
	int		i;
	char	*s;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
	s = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	vars->paths = ft_split(s, ':');
	free(s);
}

void	ft_init(t_vars *vars)
{
	int	i;

	vars->pipes = (int **)malloc(sizeof(int *) * vars->ac - 1);
	if (vars->pipes == NULL)
	{
		perror("Malloc");
		exit(0);
	}
	i = -1;
	while (++i < vars->ac - 1)
	{
		vars->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (vars->pipes[i] == NULL)
		{
			perror("Malloc");
			exit(0);
		}
	}
	vars->pid = (pid_t *)malloc(sizeof(pid_t) * vars->ac);
	if (vars->pid == NULL)
	{
		perror("Malloc");
		exit(0);
	}
}

void	ft_init_cmds(t_vars *vars, char **argv)
{
	int		i;

	vars->cmds = (char ***)malloc(sizeof(char **) * (vars->ac + 1));
	if (vars->cmds == NULL)
	{
		perror("Malloc");
		exit(0);
	}
	i = -1;
	while (++i < vars->ac)
	{
		if (vars->status)
			vars->cmds[i] = ft_split(argv[i + 2], ' ');
		else
			vars->cmds[i] = ft_split(argv[i + 3], ' ');
		if (vars->cmds[i] == NULL)
		{
			perror("Malloc");
			exit(0);
		}
	}
	vars->cmds[vars->ac] = NULL;
}

void	parse(int argc, char **argv, t_vars *vars, char **env)
{
	int	i;

	if (argc < 5)
	{
		perror("Arg");
		exit(0);
	}
	if (!vars->status && !ft_strncmp(argv[argc - 1], "tmp", 3))
	{
		perror("Please choose another file for writing");
		exit(0);
	}
	ft_init(vars);
	ft_init_cmds(vars, argv);
	i = -1;
	while (++i < vars->ac)
	{
		if (*vars->cmds[i] == NULL)
		{
			perror("Cmd");
			exit(0);
		}
	}
	path(vars, env);
}
