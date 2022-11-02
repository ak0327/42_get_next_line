/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:09:17 by takira            #+#    #+#             */
/*   Updated: 2022/11/02 21:37:33 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line_frm_buf(t_gnl_info *info)
{
	char	*ret;
	size_t	size;
	size_t	i;
	size_t	j;

	size = 0;
	while (info->buf[info->buf_idx + size])
		if (info->buf[info->buf_idx + size++] == '\n')
			break ;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
		ret[i++] = info->buf[info->buf_idx + j++];
	ret[size] = '\0';
	info->buf_idx += size;
	info->nl_cnt--;
	if (ft_strlen(info->buf) <= info->buf_idx)
		init_params(info);
	return (ret);
}

static char	*get_eof_line_frm_buf(t_gnl_info *info, char *ret)
{
	info->is_eof = 1;
	if (ft_strlen(ret))
		return (ret);
	init_params(info);
	free(ret);
	return (NULL);
}

static char	*read_and_return(int fd, char *ret, t_gnl_info *info)
{
	char				*line;

	while (!info->is_eof)
	{
		info->reading = read(fd, info->buf, BUFFER_SIZE);
		if (info->reading <= 0)
			return (get_eof_line_frm_buf(info, ret));
		info->nl_cnt = cnt_chr(info->buf, '\n');
		if (info->nl_cnt > 0)
		{
			line = get_line_frm_buf(info);
			ret = strjoin_free_dst(ret, line);
			free(line);
			if (!ret)
				return (NULL);
			return (ret);
		}
		ret = strjoin_free_dst(ret, info->buf);
		if (!ret)
			return (NULL);
		init_params(info);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char				*ret;
	static t_gnl_info	info[256];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 255)
		return (NULL);
	if (info[fd].nl_cnt > 0)
		return (get_line_frm_buf(&info[fd]));
	ret = get_line_frm_buf(&info[fd]);
	if (!ret)
		return (NULL);
	if (!info[fd].is_eof)
		return (read_and_return(fd, ret, &info[fd]));
	free(ret);
	init_params(&info[fd]);
	return (NULL);
}
