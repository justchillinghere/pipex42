/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luchitel <luchitel@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:06:52 by luchitel          #+#    #+#             */
/*   Updated: 2023/12/03 18:08:52 by luchitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int print_msg(char *msg) {
	write(1, msg, ft_strlen(msg));
	return (1);
}

int	print_error(char *msg) {
	perror(msg);
	exit(1);
}
