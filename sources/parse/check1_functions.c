/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:25:26 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/01 21:39:58 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	textures_are_valid(t_data *data)
{
	int		file_descriptor;

	file_descriptor = open(data->params.path_to_the_north_texture, O_RDONLY);
	if (file_descriptor < 0)
		return (perror("open file descriptor"), false);
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	file_descriptor = open(data->params.path_to_the_south_texture, O_RDONLY);
	if (file_descriptor < 0)
		return (perror("open file descriptor"), false);
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	file_descriptor = open(data->params.path_to_the_west_texture, O_RDONLY);
	if (file_descriptor < 0)
		return (perror("open file descriptor"), false);
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	file_descriptor = open(data->params.path_to_the_east_texture, O_RDONLY);
	if (file_descriptor < 0)
		return (perror("open file descriptor"), false);
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	return (true);
}

bool	is_map_line(char *line)
{
	if (!line)
		return (false);
	if (line[0] == '\0')
		return (false);
	if (line[0] == '\n')
		return (false);
	return (true);
}

static bool	process_map_line(t_data *data, char *line)
{
	int		index;

	index = -1;
	while (line[++index])
	{
		if (line[index] == '1' || line[index] == '0' || line[index] == ' ' \
		|| line[index] == '\n')
			;
		else if (line[index] == 'N' || line[index] == 'S' \
			|| line[index] == 'E' || line[index] == 'W')
			data->map.num_of_player++;
		else
			return (printf("ERR_MAP_CHAR"), false);
	}
	return (true);
}

bool	check_value_of_map(t_data *data, char *line, int file_descriptor)
{
	while (line != NULL)
	{
		if (line[0] == '\n')
			break ;
		if (!process_map_line(data, line))
			return (false);
		line = get_next_line(data, file_descriptor);
	}
	line = get_next_line(data, file_descriptor);
	while (line != NULL)
	{
		if (line[0] != '\n')
			return (printf("ERR_MAP_SPLIT"), false);
		line = get_next_line(data, file_descriptor);
	}
	return (true);
}

bool	check_validity_of_map(t_data *data, char *argv)
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
		line = get_next_line(data, file_descriptor);
	if (!check_value_of_map(data, line, file_descriptor))
		return (false);
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	return (true);
}
