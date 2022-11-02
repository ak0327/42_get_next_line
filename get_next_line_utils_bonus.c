/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:09:28 by takira            #+#    #+#             */
/*   Updated: 2022/10/29 19:09:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*strjoin_free_dst(char *dst, char *src)
{
	char			*ret;
	const size_t	size = ft_strlen(dst) + ft_strlen(src);
	size_t			i;
	size_t			j;

	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
	{
		free(dst);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (dst[i])
		ret[i++] = dst[j++];
	j = 0;
	while (src[j])
		ret[i++] = src[j++];
	ret[i] = '\0';
	free(dst);
	return (ret);
}

void	init_params(t_gnl_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)BUFFER_SIZE + 1)
		info->buf[i++] = '\0';
	info->buf_idx = 0;
	info->nl_cnt = 0;
	info->is_eof = 0;
	info->reading = 0;
}

size_t	cnt_chr(char *buf, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (buf[i])
		if (buf[i++] == c)
			cnt++;
	return (cnt);
}
