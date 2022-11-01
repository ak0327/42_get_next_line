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
# include <unistd.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

//typedef struct s_gnl_info
//{
//	size_t	buf_size;
//	size_t	buf_idx;
//	size_t	res_byte;
//	size_t	init_i;
//	int		gnl_cnt;
//	int		is_eof;
//
//	int 	cnt;
//}			t_gnl_info;



char	*get_next_line(int fd);

char	*ft_strjoin(char *dst, char *src);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
