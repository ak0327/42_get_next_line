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

void	init_params(char *buf, size_t *buf_idx, size_t *nl_cnt, size_t *is_eof)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
		buf[i++] = '\0';
	*buf_idx = 0;
	*nl_cnt = 0;
	*is_eof = 0;
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

char	*get_nl_cnt(char *buf, size_t *nl_cnt, size_t *buf_idx, size_t *is_eof)
{
	char	*ret;
	size_t	size;

	size = 0;
	while (buf[*buf_idx + size])
		if (buf[*buf_idx + size++] == '\n') // ~\n, ~\0
			break ;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, &buf[*buf_idx], size);
	ret[size] = '\0';
	*buf_idx += size;
	*nl_cnt -= 1;
	if (ft_strlen(buf) <= *buf_idx)
		init_params(buf, buf_idx, nl_cnt, is_eof);
	return (ret);
}

char	*get_no_nl_cnt(char *buf, size_t *buf_idx)
{
	char			*dst;
	const size_t	buflen = ft_strlen(buf) - *buf_idx;

	dst = (char *)malloc(sizeof(char) * (buflen + 1));
	ft_memcpy(dst, &buf[*buf_idx], buflen);
	dst[buflen] = '\0';
	*buf_idx = 0;
	return (dst);
}


char	*get_next_line(int fd)
{
	char			*ret;
	char			*line;
	static char		buf[BUFFER_SIZE + 1];
	static size_t	buf_idx;
	static size_t	nl_cnt;
	static size_t	is_eof;
	ssize_t			reading;

	if (nl_cnt)
		return (get_nl_cnt(buf, &nl_cnt, &buf_idx, &is_eof));
	ret = get_no_nl_cnt(buf, &buf_idx);
	if (!ret)
		return (NULL);
	while (!is_eof)
	{
		init_params(buf, &buf_idx, &nl_cnt, &is_eof);
		reading = read(fd, buf, BUFFER_SIZE);
		if (reading <= 0)
		{
			is_eof = 1;
			init_params(buf, &buf_idx, &nl_cnt, &is_eof);
			if (ft_strlen(ret))
				return (ret);
			free(ret);
			return (NULL);
		}
		nl_cnt = cnt_nl(buf);
		if (nl_cnt == 0)
		{
			buf_idx = 0;
			ret = ft_strjoin(ret, buf);
			if (!ret)
				return (NULL);
			continue ;
		}
		line = get_nl_cnt(buf, &nl_cnt, &buf_idx, &is_eof);
		ret = ft_strjoin(ret, line);
		free(line);
		if (!ret)
			return (NULL);
		return (ret);
	}
	free(ret);
	init_params(buf, &buf_idx, &nl_cnt, &is_eof);
	return (NULL);
}
