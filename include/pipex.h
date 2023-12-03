/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luchitel <luchitel@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:27:41 by luchitel          #+#    #+#             */
/*   Updated: 2023/12/03 18:12:23 by luchitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include "libft.h"
# include "limits.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> 
# include <stdio.h>
# include <errno.h>


int 	print_msg(char *);
int 	print_error(char *);
char 	*find_path(char **);
char 	*get_cmd_path(char *, char **);
void	execute_cmd(char *, char **);
void	clean_pipes(int *);

#endif