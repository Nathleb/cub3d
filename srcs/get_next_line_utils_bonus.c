/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:50:21 by nle-biha          #+#    #+#             */
/*   Updated: 2021/01/24 23:48:05 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t ret;

	ret = 0;
	while (s[ret])
		ret++;
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*ret;
	size_t	i;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if ((ret = (char *)malloc(lens1 + lens2 + 1)))
	{
		while (++i < lens1)
			ret[i] = s1[i];
		while (i < lens2 + lens1)
		{
			ret[i] = s2[i - lens1];
			i++;
		}
		ret[i] = '\0';
	}
	free(s1);
	free(s2);
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((ret = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		ret[0] = '\0';
		return (ret);
	}
	while (i < len && s[start + i])
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t lensrc;

	lensrc = 0;
	if (!dst && !src)
		return (lensrc);
	while (src[lensrc])
		lensrc++;
	i = 0;
	if (size == 0)
		return (lensrc);
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lensrc);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*ret;
	unsigned int	i;

	i = 0;
	if ((ret = (char *)malloc(nmemb * size)) == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		ret[i] = '\0';
		i++;
	}
	return ((void *)ret);
}
