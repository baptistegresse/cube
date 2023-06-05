/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:01:52 by bgresse           #+#    #+#             */
/*   Updated: 2023/05/15 15:49:39 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*get_next_line(t_data *data, int fd)
{
	int		i;
	int		rd;
	char	character;
	char	*buffer;	

	buffer = ft_calloc(data, 1000, 1);
	i = 0;
	rd = 0;
	while (1)
	{
		rd = read(fd, &character, 1);
		if (rd <= 0)
			break ;
		buffer[i++] = character;
		if (character == '\n')
			break ;
	}
	buffer[i] = '\0';
	if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
		return (free_remove(data->garbage, buffer), NULL);
	return (buffer);
}

void	*ft_calloc(t_data *data, size_t num, size_t size)
{
	size_t			total_size;
	void			*allocated_memory;
	unsigned char	*ptr;
	size_t			i;

	if (num == 0 || size == 0)
		return (NULL);
	total_size = num * size;
	allocated_memory = free_malloc(data->garbage, total_size);
	if (allocated_memory == NULL)
		return (NULL);
	ptr = (unsigned char *)allocated_memory;
	i = 0;
	while (i < total_size)
		ptr[i++] = 0;
	return (allocated_memory);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_ptr;
	const char	*src_ptr;
	size_t		i;

	i = 0;
	src_ptr = (const char *)src;
	dst_ptr = (char *)dst;
	if (dst == NULL || src == NULL)
		return (NULL);
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}

char	*ft_strndup(t_data *data, const char *src, size_t n)
{
	char	*dst;
	size_t	len;

	if (src == NULL)
		return (NULL);
	len = strlen(src);
	if (n < len)
		len = n;
	dst = (char *)ft_calloc(data, len + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}
