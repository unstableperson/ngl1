/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:11:01 by kfalia-f          #+#    #+#             */
/*   Updated: 2018/12/10 19:46:18 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	ft_zap(char *buf, char **line, char **list)
{
	int		i;
	char	*s;
	int		flag;

	flag = 0;
	s = ft_strnew(0);
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
	{
		buf[i++] = '\0';
		flag = 1;
	}
	*line = ft_strjoinre(*line, buf);
	if (flag == 1)
		*list = ft_strjoinre(s, buf + i);
	if (!line || !list)
		return (-1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*list = NULL;
	int			ret;
	char		buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!list)
		list = ft_strnew(0);
	*line = ft_strnew(0);
	if (ft_strexist(list) == 1)
		if (ft_zap(list, line, &list) == -1)
			return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n') != NULL)
		{
			if (ft_zap(buf, line, &list) == -1)
				return (-1);
			break ;
		}
		*line = ft_strjoinre(*line, buf);
	}
	if (ret == 0 && !ft_strexist(*line))
		return (0);
	return (1);
}
