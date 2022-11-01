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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char *dst, char *src)
{
	char			*ret;
	const size_t	dstlen = ft_strlen(dst);
	const size_t	srclen = ft_strlen(src);

	ret = (char *)malloc(sizeof(char) * (dstlen + srclen + 1));
	if (!ret)
	{
		free(dst);
		return (NULL);
	}
	ft_memcpy(ret, dst, dstlen);
	ft_memcpy(&ret[dstlen], src, srclen);
	ret[dstlen + srclen] = '\0';
	free(dst);
	return (ret);
}

void	init_params(char *buf, t_gnl_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)BUFFER_SIZE + 1)
		buf[i++] = '\0';
	info->buf_idx = 0;
	info->nl_cnt = 0;
	info->is_eof = 0;
	info->reading = 0;
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
