/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:09:48 by takira            #+#    #+#             */
/*   Updated: 2022/10/29 19:09:49 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_gnl_info
{
	size_t	buf_idx;
	size_t	nl_cnt;
	size_t	is_eof;
	ssize_t	reading;
}			t_gnl_info;

char	*get_next_line(int fd);
char	*strjoin_free_dst(char *dst, char *src);

size_t	ft_strlen(const char *s);
size_t	cnt_chr(char *buf, char c);

void	init_params(char *buf, t_gnl_info *info);

#endif
