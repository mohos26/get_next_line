/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:51:45 by mhoussas          #+#    #+#             */
/*   Updated: 2024/11/27 12:43:46 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*aid;
	void			*ptr;

	if (count != 0 && size > ((size_t)-1) / count)
		return (NULL);
	size *= count;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	aid = ptr;
	while (size--)
		*aid++ = 0;
	return (ptr);
}

size_t	ft_strlen(char const *s)
{
	size_t	len;

	len = 0;
	while (s && *s++)
		len++;
	return (len);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	char	*head;
	int		i;

	ptr = ft_calloc(ft_strlen(s1) * sizeof(char) + 1, 1);
	if (!ptr)
		return (NULL);
	i = 0;
	head = ptr;
	while (s1[i])
		*ptr++ = s1[i++];
	*ptr = '\0';
	free(s1);
	return (head);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	char	*head;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (!res)
		return (NULL);
	head = res;
	i = 0;
	while (s1[i])
		*res++ = s1[i++];
	i = 0;
	while (s2[i])
		*res++ = s2[i++];
	*res = '\0';
	free(s1);
	free(s2);
	return (head);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*aid;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	ptr = (unsigned char *)dst;
	aid = (const unsigned char *)src;
	while (n--)
		*ptr++ = *aid++;
	return (dst);
}
