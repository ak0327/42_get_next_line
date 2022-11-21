/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:09:17 by takira            #+#    #+#             */
/*   Updated: 2022/11/21 17:03:00 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	minval(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

static char	*create_line_frm_save(char *save)
{
	char	*new_line;
	size_t	i;

	if (!save || save[0] == '\0')
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, save, i + 1);
	return (new_line);
}

static char	*update_save(char *save)
{
	char	*new_save;
	size_t	i;
	size_t	j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
		return (ft_free(save, NULL));
	new_save = (char *)malloc(sizeof(char) * (ft_strlen_gnl(save) - i + 1));
	if (!new_save)
		return (ft_free(save, NULL));
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	ft_free(save, NULL);
	return (new_save);
}

static char	*read_file_and_save(int fd, char *save)
{
	char	*buf;
	ssize_t	read_bytes;
	size_t	nl_cnt;

	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	nl_cnt = 0;
	while (nl_cnt == 0 && read_bytes != 0)
	{
		read_bytes = read(fd, buf, minval(BUFFER_SIZE, INT_MAX));
		if (read_bytes == -1)
			return (ft_free(buf, NULL));
		buf[read_bytes] = '\0';
		nl_cnt = cnt_chr(buf, '\n');
		save = ft_strjoin_gnl(save, buf);
	}
	ft_free(buf, NULL);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*gnl_line;
	static char	*save_buf[OPEN_MAX];

	errno = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 | UINT_MAX < BUFFER_SIZE)
		return (NULL);
	save_buf[fd] = read_file_and_save(fd, save_buf[fd]);
	if (!save_buf[fd])
		return (NULL);
	gnl_line = create_line_frm_save(save_buf[fd]);
	save_buf[fd] = update_save(save_buf[fd]);
	if (errno != 0)
		return (ft_free(save_buf[fd], gnl_line));
	return (gnl_line);
}
