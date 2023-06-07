/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:22:44 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:34:20 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	paths_rgb_are_filled(t_data *data)
{
	if (data->params.path_to_the_north_texture == NULL)
		return (false);
	if (data->params.path_to_the_south_texture == NULL)
		return (false);
	if (data->params.path_to_the_west_texture == NULL)
		return (false);
	if (data->params.path_to_the_east_texture == NULL)
		return (false);
	if (!data->map.floor_color_set)
		return (false);
	if (!data->map.ceiling_color_set)
		return (false);
	return (true);
}

bool	map_unclosed(t_data *data, int x, int y, bool **visited)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (x < 0 || x >= data->map.width || y < 0 || \
	y >= data->map.height || data->map.array[y][x] == '3')
		return (false);
	if (visited[y][x] || data->map.array[y][x] == '1')
		return (true);
	visited[y][x] = true;
	up = map_unclosed(data, x, y + 1, visited);
	down = map_unclosed(data, x, y - 1, visited);
	left = map_unclosed(data, x - 1, y, visited);
	right = map_unclosed(data, x + 1, y, visited);
	return (up && down && left && right);
}

bool	cube_parser(t_data *data, char *argv)
{
	if (!get_file_paths_rgb(data, argv))
		return (false);
	if (!check_validity_of_map(data, argv))
		return (false);
	if (!get_size_of_map(data, argv))
		return (false);
	if (!data->map.width || !data->map.height)
		return (printf("ERR_MAP_EMPTY"), false);
	if (data->map.num_of_player > 1 || !data->map.num_of_player)
		return (printf("ERR_MAP_MULTI"), false);
	if (!malloc_map_visited(data))
		return (false);
	if (!fill_map_array(data, argv))
		return (false);
	if (!map_unclosed(data, (int)data->player.pos.x, \
	(int)data->player.pos.y, data->map.visited))
		return (printf("ERR_MAP_UNCLOSED"), false);
	return (true);
}
