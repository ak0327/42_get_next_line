/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:09:17 by takira            #+#    #+#             */
/*   Updated: 2022/10/29 19:09:19 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_params(t_gnl_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)BUFFER_SIZE + 1)
		info->buf[i++] = '\0';
	info->buf_idx = 0;
	info->nl_cnt = 0;
	info->is_eof = 0;
}

size_t	cnt_nl(char *buf)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;

	while (buf[i])
		if (buf[i++] == '\n')
			cnt++;
	return (cnt);
}

char	*get_nl_cnt(t_gnl_info *info)
{
	char	*ret;
	size_t	size;

	size = 0;
	while (info->buf[info->buf_idx + size])
		if (info->buf[info->buf_idx + size++] == '\n')
			break ;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, &info->buf[info->buf_idx], size);
	ret[size] = '\0';
	info->buf_idx += size;
	info->nl_cnt -= 1;
	if (ft_strlen(info->buf) <= info->buf_idx)
		init_params(info);
	return (ret);
}

char	*no_nl_line(t_gnl_info *info)
{
	char			*dst;
	const size_t	buflen = ft_strlen(info->buf) - info->buf_idx;

	dst = (char *)malloc(sizeof(char) * (buflen + 1));
	ft_memcpy(dst, &info->buf[info->buf_idx], buflen);
	dst[buflen] = '\0';
	info->buf_idx = 0;
	return (dst);
}



char	*get_next_line(int fd)
{
	char				*ret;
	char				*line;
	static t_gnl_info	info;
	ssize_t				reading;

	if (fd < 0)
		return (NULL);
	if (info.nl_cnt)
		return (get_nl_cnt(&info));
	ret = no_nl_line(&info);
	if (!ret)
		return (NULL);
	while (!info.is_eof)
	{
		init_params(&info);
		reading = read(fd, info.buf, BUFFER_SIZE);
		if (reading <= 0)
		{
			info.is_eof = 1;
			init_params(&info);
			if (ft_strlen(ret))
				return (ret);
			free(ret);
			return (NULL);
		}
		info.nl_cnt = cnt_nl(info.buf);
		if (info.nl_cnt == 0)
		{
			info.buf_idx = 0;
			ret = ft_strjoin(ret, info.buf);
			if (!ret)
				return (NULL);
			continue ;
		}
		line = get_nl_cnt(&info);
		ret = ft_strjoin(ret, line);
		free(line);
		if (!ret)
			return (NULL);
		return (ret);
	}
	free(ret);
	init_params(&info);
	return (NULL);
}
