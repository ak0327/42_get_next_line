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

#include "get_next_line_bonus.h"

static char	*make_newline(char *buf, t_gnl_info *info)
{
	char	*ret;
	size_t	size;

	size = 0;
	while (buf[info->buf_idx + size])
		if (buf[info->buf_idx + size++] == '\n')
			break ;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, &buf[info->buf_idx], size);
	ret[size] = '\0';
	info->buf_idx += size;
	info->nl_cnt -= 1;
	if (ft_strlen(buf) <= info->buf_idx)
		init_params(buf, info);
	return (ret);
}

char	*ret_eof_lint(t_gnl_info *info, char *buf, char *ret)
{
	info->is_eof = 1;
	init_params(buf, info);
	if (ft_strlen(ret))
		return (ret);
	free(ret);
	return (NULL);
}

char	*read_and_return(int fd, char *buf, char *ret, t_gnl_info *info)
{
	char				*line;

	while (!info->is_eof)
	{
		init_params(buf, info);
		info->reading = read(fd, buf, BUFFER_SIZE);
		if (info->reading <= 0)
			return (ret_eof_lint(info, buf, ret));
		info->nl_cnt = cnt_nl(buf);
		if (info->nl_cnt)
		{
			line = make_newline(buf, info);
			ret = ft_strjoin(ret, line);
			free(line);
			if (!ret)
				return (NULL);
			return (ret);
		}
		ret = ft_strjoin(ret, buf);
		if (!ret)
			return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char				*ret;
	static char			buf[BUFFER_SIZE + 1];
	static t_gnl_info	info;

	if (fd < 0)
		return (NULL);
	if (info.nl_cnt)
		return (make_newline(buf, &info));
	ret = make_newline(buf, &info);
	if (!ret)
		return (NULL);
	if (!info.is_eof)
		return (read_and_return(fd, buf, ret, &info));
	free(ret);
	init_params(buf, &info);
	return (NULL);
}
