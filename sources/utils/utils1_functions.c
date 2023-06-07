/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:38:56 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:35:53 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(t_data *data, const char *src)
{
	char	*new_str;
	size_t	len;

	if (src == NULL)
		return (NULL);
	len = ft_strlen(src);
	new_str = (char *)ft_calloc(data, len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strcpy(new_str, src);
	return (new_str);
}

int	ft_atoi(const char *str)
{
	int		result;
	bool	negative;

	result = 0;
	negative = 0;
	if (*str == '-')
	{
		negative = true;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (negative)
		result = -result;
	return (result);
}
