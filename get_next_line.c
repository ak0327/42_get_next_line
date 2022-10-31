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

static char	*make_ret(char *buf, t_gnl_info info)
{
	char	*ret;

	ret = (char *)ft_calloc(sizeof(char), 1);
	if (!ret)
		return (NULL);
	if (info.res_byte)
	{
		ret = ft_strjoin(ret, &buf[info.buf_idx], info.res_byte);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

static char	*get_one_line_frm_idx(char *buf, t_gnl_info *info)
{
	char	*ret;
	size_t	i;

	i = 0;
	while (buf[info->buf_idx + i] != '\n' && buf[info->buf_idx + i] != '\0')
		i++;
	if (buf[info->buf_idx + i] == '\n')
		i++;
	ret = (char *)ft_calloc(sizeof(char), i + 1);
	if (!ret)
		return (NULL);
	ret = ft_strjoin(ret, &buf[info->buf_idx], i);
	if (!ret)
		return (NULL);
	info->buf_idx += i;
	info->gnl_cnt -= 1;
	info->res_byte -= i;
	return (ret);
}

static char	*ret_next_line(char *ret, char *buf, t_gnl_info *info)
{
	char	*one_line;

	info->buf_idx = 0;
	info->res_byte = info->buf_size;
	one_line = get_one_line_frm_idx(buf, info);
	if (!one_line)
		return (NULL);
	ret = ft_strjoin(ret, one_line, ft_strlen(one_line));
	free(one_line);
	if (!ret)
		return (NULL);
	if (ft_strlen(ret) == 0)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

static bool	read_get_params(int fd, char *ret, char *buf, t_gnl_info *info)
{
	ssize_t	reading;

	info->init_i = 0;
	while (info->init_i < BUFFER_SIZE + 1)
		buf[info->init_i++] = '\0';
	reading = read(fd, buf, BUFFER_SIZE);
	if (reading < 0 || (reading == 0 && ft_strlen(ret) == 0))
	{
		free(ret);
		return (false);
	}
	if (reading == 0 || reading < BUFFER_SIZE)
		info->is_eof = 1;
	info->buf_size = 0;
	while (buf[info->buf_size])
		if (buf[info->buf_size++] == '\n')
			info->gnl_cnt++;
	if (info->buf_size < BUFFER_SIZE)
		info->gnl_cnt++;
	return (true);
}

char	*get_next_line(int fd)
{
	char				*ret;
	static char			buf[BUFFER_SIZE + 1];
	static t_gnl_info	info;

	if (fd < 0)
		return (NULL);
	if (info.gnl_cnt && info.res_byte)
		return (get_one_line_frm_idx(buf, &info));
	ret = make_ret(buf, info);
	if (!ret)
		return (NULL);
	while (!info.is_eof)
	{
		if (!read_get_params(fd, ret, buf, &info))
			return (NULL);
		if (info.gnl_cnt)
			return (ret_next_line(ret, buf, &info));
		ret = ft_strjoin(ret, buf, info.buf_size);
		if (!ret)
			return (NULL);
	}
	free(ret);
	return (NULL);
}
