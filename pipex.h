/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:36:42 by lykostan          #+#    #+#             */
/*   Updated: 2023/03/17 19:36:45 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_vars
{
	char	*cmd;
	char	**paths;
	int		**pipes;
	pid_t	*pid;
	char	***cmds;
	int		ac;
	int		status;
}	t_vars;

void	parse(int argc, char **argv, t_vars *vars, char **env);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *s, int start, int j);
int		ft_strchr_gnl(char *str, int c);
void	close_pipes(t_vars *vars);
void	here_doc(char *end);
void	path_check(t_vars *vars, char *cmd);
void	for_free(t_vars *vars);

#endif
