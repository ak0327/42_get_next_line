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

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_gnl_info
{
	size_t	buf_idx;
	size_t	nl_cnt;
	size_t	is_eof;
	ssize_t	reading;
}			t_gnl_info;

char	*get_next_line(int fd);
char	*ft_strjoin(char *dst, char *src);

size_t	ft_strlen(const char *s);
size_t	cnt_nl(char *buf);

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	init_params(char *buf, t_gnl_info *info);

#endif
