/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths_rgb_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:47:39 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/01 21:39:16 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	parse_rgb_values(char *line, uint8_t rgb_values[3])
{
	char		*start;
	char		*end;
	int			index;

	index = 0;
	start = line;
	while (index < 3)
	{
		end = strchr(start, ',');
		if (end)
			*end = '\0';
		else if (index < 2)
			return ;
		if (atoi(start) > 255)
			printf("Warning\nsomething wrong whith rgb value\n");
		rgb_values[index] = (uint8_t)atoi(start);
		start = end + 1;
		index++;
	}
}

void	get_color_value(t_data *data, t_rgb *rgb, char *line)
{
	uint8_t		rgb_values[3];

	if (line == NULL)
		return ;
	while (*line == ' ' || *line == 'F' || *line == 'C')
	{
		if (*line == 'F')
			data->map.floor_color_set += 1;
		else if (*line == 'C')
			data->map.ceiling_color_set += 1;
		line++;
	}
	parse_rgb_values(line, rgb_values);
	rgb->red = rgb_values[0];
	rgb->green = rgb_values[1];
	rgb->blue = rgb_values[2];
}

void	get_path_value(t_data *data, char **path, char *line)
{
	int		index;
	int		length;
	char	*end;

	if (strstr(line, "NO"))
		data->map.no_path_set += 1;
	else if (strstr(line, "SO"))
		data->map.so_path_set += 1;
	else if (strstr(line, "WE"))
		data->map.we_path_set += 1;
	else if (strstr(line, "EA"))
		data->map.ea_path_set += 1;
	index = 0;
	while (line[index] && line[index] == ' ')
		index++;
	while (line[index] && line[index] != ' ')
		index++;
	while (line[index] && line[index] == ' ')
		index++;
	end = &line[index];
	while (*end && *end != ' ' && *end != '\n')
		end++;
	length = end - &line[index];
	*path = ft_strndup(data, &line[index], length);
}

void	fill_paths_rgb(t_data *data, char *line)
{
	if (strstr(line, "NO"))
		get_path_value(data, &data->params.path_to_the_north_texture, line);
	else if (strstr(line, "SO"))
		get_path_value(data, &data->params.path_to_the_south_texture, line);
	else if (strstr(line, "WE"))
		get_path_value(data, &data->params.path_to_the_west_texture, line);
	else if (strstr(line, "EA"))
		get_path_value(data, &data->params.path_to_the_east_texture, line);
	else if (strstr(line, "F"))
		get_color_value(data, &data->params.floor_rgb, line);
	else if (strstr(line, "C"))
		get_color_value(data, &data->params.celling_rgb, line);
	else if (paths_rgb_are_filled(data))
		return ;
	else if (is_map_line(line))
		data->map.before_params = true;
	data->map.start_line++;
}

bool	paths_rgb_duplicate(t_data *data)
{
	if (data->map.no_path_set > 1)
		return (true);
	if (data->map.so_path_set > 1)
		return (true);
	if (data->map.we_path_set > 1)
		return (true);
	if (data->map.ea_path_set > 1)
		return (true);
	if (data->map.floor_color_set > 1)
		return (true);
	if (data->map.ceiling_color_set > 1)
		return (true);
	return (false);
}

bool	get_file_paths_rgb(t_data *data, char *argv)
{
	int		file_descriptor;
	char	*line;

	file_descriptor = open(argv, O_RDONLY);
	if (file_descriptor < 0)
		return (perror("open file descriptor"), false);
	line = get_next_line(data, file_descriptor);
	while (line != NULL)
	{
		fill_paths_rgb(data, line);
		line = get_next_line(data, file_descriptor);
	}
	if (close(file_descriptor) < 0)
		return (perror("close file descriptor"), false);
	if (!paths_rgb_are_filled(data))
		return (printf("ERR_PATH_RGB_FILE"), false);
	if (paths_rgb_duplicate(data))
		return (printf("ERR_PATH_RGB_DUP"), false);
	if (!textures_are_valid(data))
		return (printf("ERR_TEXT_FILE"), false);
	if (data->map.before_params)
		return (printf("ERR_MAP_BEFORE_PARAMS"), false);
	data->params.celling_color = rgb_to_int(data->params.celling_rgb);
	data->params.floor_color = rgb_to_int(data->params.floor_rgb);
	return (true);
}
