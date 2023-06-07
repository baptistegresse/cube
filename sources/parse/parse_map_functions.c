/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:50:25 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:33:21 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	get_size_of_map(t_data *data, char *argv)
{
	int		file_descriptor;
	char	*line;
	int		index;

	index = -1;
	file_descriptor = open(argv, O_RDONLY);
	if (file_descriptor < 0)
		return (perror("open file descriptor"), false);
	line = get_next_line(data, file_descriptor);
	while (line != NULL && (++index < data->map.start_line || line[0] == '\n'))
	{
		line = get_next_line(data, file_descriptor);
	}
	while (line != NULL)
	{
		if (line[0] == '\n')
			break ;
		data->map.height++;
		if ((int)strlen(line) - 1 > data->map.width)
			data->map.width = strlen(line) - 1;
		line = get_next_line(data, file_descriptor);
	}
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	return (true);
}

bool	malloc_map_visited(t_data *data)
{
	int		index;

	index = -1;
	data->map.array = ft_calloc(data, data->map.height + 1, sizeof(char *));
	if (!data->map.array)
		return (false);
	while (++index < data->map.height)
	{
		data->map.array[index] = ft_calloc(data, data->map.width + 1 \
		, sizeof(char));
		if (!data->map.array[index])
			return (false);
	}
	index = -1;
	data->map.visited = ft_calloc(data, data->map.height + 1, sizeof(bool *));
	if (!data->map.visited)
		return (false);
	while (++index < data->map.height)
	{
		data->map.visited[index] = ft_calloc(data, data->map.width + 1 \
		, sizeof(bool));
		if (!data->map.visited[index])
			return (false);
	}
	return (true);
}

void	get_position_player(t_data *data, float x, float y, char dir_base)
{
	if (data->player.pos.x != 0.0f || data->player.pos.y != 0.0f)
		return ;
	data->player.pos.x = x + 0.5f;
	data->player.pos.y = y + 0.5f;
	data->player.plane.x = 0;
	data->player.plane.y = 0;
	data->player.dir_base = dir_base;
	if (dir_base == 'N')
	{
		data->player.angle = (float)(3 * M_PI / 2);
		data->player.plane.x = 0.66f;
	}
	else if (dir_base == 'S')
	{
		data->player.angle = M_PI / 2;
		data->player.plane.x = -0.66f;
	}
	else if (dir_base == 'E')
	{
		data->player.angle = 0;
		data->player.plane.y = 0.66f;
	}
	else if (dir_base == 'W')
	{
		data->player.angle = M_PI;
		data->player.plane.y = -0.66f;
	}
	data->player.dir.x = cosf(data->player.angle);
	data->player.dir.y = sinf(data->player.angle);
}

void	fill_map_array_line(t_data *data, char *line, int index)
{
	int		index_j;
	int		len;

	index_j = -1;
	while (++index_j < (int)ft_strlen(line))
	{
		if (line[index_j] == ' ')
			line[index_j] = '3';
		else if (line[index_j] == 'N' || line[index_j] == 'S' || \
			line[index_j] == 'E' || line[index_j] == 'W')
		{
			get_position_player(data, (float)index_j, \
			(float)index, line[index_j]);
			line[index_j] = '0';
		}
		else if (line[index_j] == '\n')
			line[index_j] = '\0';
	}
	strcpy(data->map.array[index], line);
	len = ft_strlen(line);
	if (len < data->map.width)
		while (len < data->map.width)
			data->map.array[index][len++] = '3';
}

bool	fill_map_array(t_data *data, char *argv)
{
	int		file_descriptor;
	char	*line;
	int		index;

	index = -1;
	file_descriptor = open(argv, O_RDONLY);
	if (file_descriptor < 0)
		return (perror("open file descriptor"), false);
	line = get_next_line(data, file_descriptor);
	while (line != NULL && (++index < data->map.start_line || line[0] == '\n'))
	{
		line = get_next_line(data, file_descriptor);
	}
	index = 0;
	while (line != NULL)
	{
		if (line[0] == '\n')
			break ;
		fill_map_array_line(data, line, index);
		line = get_next_line(data, file_descriptor);
		index++;
	}
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	return (true);
}
