/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:55:57 by mhoussas          #+#    #+#             */
/*   Updated: 2024/11/30 12:37:55 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_line(char *s, size_t len)
{
	if (!s)
		return (0);
	while (*s != '\n' && len--)
		s++;
	return (*s == '\n');
}

char	*freeplus(char *s, char *s2)
{
	free(s);
	free(s2);
	return (NULL);
}

int	get_list(char *s, size_t len, char **s1, char **s2)
{
	size_t	aid;

	s = ft_strdup(s);
	if (!s)
		return (0);
	aid = 0;
	while (s[aid] != '\n' && aid < len)
		aid++;
	*s1 = ft_calloc(aid + 2, 1);
	if (!*s1)
		return ((int)freeplus(s, NULL));
	ft_memcpy(*s1, s, aid + 1);
	(*s1)[aid + 1] = '\0';
	*s2 = ft_calloc(len - aid, 1);
	if (!*s2)
		return ((int)freeplus(*s1, s));
	ft_memcpy(*s2, s + aid + 1, len - aid - 1);
	(*s2)[len - aid - 1] = '\0';
	free(s);
	return (1);
}

int	aid(int *running, char **s, char **cache, int fd)
{
	*s = ft_calloc((size_t)BUFFER_SIZE + ft_strlen(*cache) + 1, 1);
	if (!*s)
		return (0);
	if (*cache)
		ft_memcpy(*s, *cache, ft_strlen(*cache));
	if (!read(fd, *s + ft_strlen(*cache), BUFFER_SIZE))
		*running = 0;
	*cache = freeplus(*cache, NULL);
	if (find_new_line(*s, ft_strlen(*s)))
	{
		if (!get_list(*s, ft_strlen(*s), s, cache))
			return (0);
		*running = 0;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	int			running;
	char		*res;
	char		*s;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	running = 1;
	res = NULL;
	while (running)
	{
		if (cache && find_new_line(cache, ft_strlen(cache)))
		{
			if (!get_list(cache, ft_strlen(cache), &s, &cache))
				return (NULL);
			running = 0;
		}
		else
			if (!aid(&running, &s, &cache, fd))
				return (NULL);
		res = ft_strjoin(res, s);
	}
	if (!ft_strlen(res))
		return (freeplus(res, NULL));
	return (res);
}
