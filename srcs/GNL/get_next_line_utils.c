/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:01:30 by jbaringo          #+#    #+#             */
/*   Updated: 2021/10/19 17:53:41 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t		str_size;

	str_size = 0;
	while (s[str_size])
		str_size++;
	return (str_size);
}

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		i;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i] = '\0';
	j = ft_strlen(joined);
	i = 0;
	while (s2[i] != '\0')
	{
		joined[i + j] = s2[i];
		i++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*ft_strchr(char *s, int c)
{
	char	*str;

	str = (char *)s;
	if (c == '\0')
	{
		while (*str)
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		count;
	size_t		size;
	char		*tab;

	count = -1;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	while (++count < len)
		tab[count] = s[start + count];
	tab[count] = '\0';
	return (tab);
}
