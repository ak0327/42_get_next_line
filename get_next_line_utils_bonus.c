/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:09:28 by takira            #+#    #+#             */
/*   Updated: 2022/11/19 16:37:11 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	cnt_chr(const char *buf, char c)
{
	size_t	i;
	size_t	cnt;

	if (!buf)
		return (0);
	i = 0;
	cnt = 0;
	while (buf[i])
		if (buf[i++] == c)
			cnt++;
	return (cnt);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dstsize)
	{
		while (src[i] && i + 1 < dstsize)
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (ft_strlen_gnl(src));
}

void	*ft_free(char *str1, char *str2)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *dst, char *src)
{
	size_t	dstlen;
	size_t	srclen;
	char	*joined_str;

	if (!dst)
	{
		dst = (char *)malloc(sizeof(char) * 1);
		if (!dst)
			return (NULL);
		dst[0] = '\0';
	}
	dstlen = ft_strlen_gnl(dst);
	srclen = ft_strlen_gnl(src);
	joined_str = (char *)malloc(sizeof(char) * (dstlen + srclen + 1));
	if (!joined_str)
		return (NULL);
	ft_strlcpy(joined_str, dst, dstlen + 1);
	ft_strlcpy(&joined_str[dstlen], src, dstlen + srclen + 1);
	ft_free(dst, NULL);
	return (joined_str);
}
