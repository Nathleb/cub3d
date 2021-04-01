/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:50:21 by nle-biha          #+#    #+#             */
/*   Updated: 2021/03/29 00:50:42 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin_free(char *s1, char *s2)
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
