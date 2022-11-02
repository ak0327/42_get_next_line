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

static char	*get_line_frm_buf(char *buf, t_gnl_info *info)
{
	char	*ret;
	size_t	size;
	size_t	i;
	size_t	j;

	size = 0;
	while (buf[info->buf_idx + size])
		if (buf[info->buf_idx + size++] == '\n')
			break ;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
		ret[i++] = buf[info->buf_idx + j++];
	ret[size] = '\0';
	info->buf_idx += size;
	info->nl_cnt--;
	if (ft_strlen(buf) <= info->buf_idx)
		init_params(buf, info);
	return (ret);
}

static char	*get_eof_line_frm_buf(t_gnl_info *info, char *buf, char *ret)
{
	info->is_eof = 1;
	if (ft_strlen(ret))
		return (ret);
	init_params(buf, info);
	free(ret);
	return (NULL);
}

static char	*read_and_return(int fd, char *buf, char *ret, t_gnl_info *info)
{
	char				*line;

	while (!info->is_eof)
	{
		info->reading = read(fd, buf, BUFFER_SIZE);
		if (info->reading <= 0)
			return (get_eof_line_frm_buf(info, buf, ret));
		info->nl_cnt = cnt_chr(buf, '\n');
		if (info->nl_cnt > 0)
		{
			line = get_line_frm_buf(buf, info);
			ret = strjoin_free_dst(ret, line);
			free(line);
			if (!ret)
				return (NULL);
			return (ret);
		}
		ret = strjoin_free_dst(ret, buf);
		if (!ret)
			return (NULL);
		init_params(buf, info);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char				*ret;
	static char			buf[BUFFER_SIZE + 1];
	static t_gnl_info	info;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (info.nl_cnt > 0)
		return (get_line_frm_buf(buf, &info));
	ret = get_line_frm_buf(buf, &info);
	if (!ret)
		return (NULL);
	if (!info.is_eof)
		return (read_and_return(fd, buf, ret, &info));
	free(ret);
	init_params(buf, &info);
	return (NULL);
}
