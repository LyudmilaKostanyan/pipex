/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:36:52 by lykostan          #+#    #+#             */
/*   Updated: 2023/03/17 19:36:54 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->ac - 1)
	{
		if (pipe(vars->pipes[i]) == -1)
		{
			while (--i >= 0)
			{
				close(vars->pipes[i][0]);
				close(vars->pipes[i][1]);
			}
			perror("Pipe");
			exit(0);
		}
		i++;
	}
}

void	child_elif(int i, int argc, char **argv, t_vars *vars)
{
	if (!vars->status)
	{
		if (dup2(open(argv[argc - 1], O_CREAT
					| O_APPEND | O_WRONLY, 0644), 1) == -1)
		{
			perror("Output file");
			exit(0);
		}
	}
	else
	{
		if (dup2(open(argv[argc - 1], O_CREAT
					| O_TRUNC | O_WRONLY, 0644), 1) == -1)
		{
			perror("Output file");
			exit(0);
		}
	}
	dup2(vars->pipes[i - 1][0], 0);
}

void	child(int i, int argc, char **argv, t_vars *vars)
{
	if (i == 0)
	{
		if (!vars->status)
			dup2(open("tmp", O_RDONLY), 0);
		else
		{
			if (dup2(open(argv[1], O_RDONLY), 0) == -1)
			{
				perror("Input file");
				exit(0);
			}
		}
		dup2(vars->pipes[0][1], 1);
	}
	else if (i == vars->ac - 1)
		child_elif(i, argc, argv, vars);
	else
	{
		dup2(vars->pipes[i - 1][0], 0);
		dup2(vars->pipes[i][1], 1);
	}
}

void	proc(int argc, char **argv, char **env, t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->ac)
	{
		vars->pid[i] = fork();
		if (vars->pid[i] == -1)
		{
			perror("Fork");
			exit(0);
		}
		if (!vars->pid[i])
		{
			child(i, argc, argv, vars);
			close_pipes(vars);
			path_check(vars, *vars->cmds[i]);
			exit(execve(vars->cmd, vars->cmds[i], env));
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	vars.status = (ft_strncmp(argv[1], "here_doc", 8)
			|| ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])));
	if (!vars.status)
		vars.ac = argc - 4;
	else
		vars.ac = argc - 3;
	parse(argc, argv, &vars, env);
	if (!vars.status)
		here_doc(argv[2]);
	pipes(&vars);
	proc(argc, argv, env, &vars);
	close_pipes(&vars);
	for_free(&vars);
	return (0);
}
