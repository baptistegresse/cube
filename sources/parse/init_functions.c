/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:52:20 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:29:44 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	init_data(t_data *data)
{
	data->map.num_of_player = 0;
	data->map.start_line = 0;
	data->map.height = 0;
	data->map.width = 0;
	data->params.path_to_the_north_texture = NULL;
	data->params.path_to_the_south_texture = NULL;
	data->params.path_to_the_west_texture = NULL;
	data->params.path_to_the_east_texture = NULL;
	data->params.floor_rgb.red = 0;
	data->params.floor_rgb.green = 0;
	data->params.floor_rgb.blue = 0;
	data->params.celling_rgb.red = 0;
	data->params.celling_rgb.green = 0;
	data->params.celling_rgb.blue = 0;
	data->player.dir_base = 0;
	data->map.before_params = false;
	data->map.no_path_set = 0;
	data->map.we_path_set = 0;
	data->map.so_path_set = 0;
	data->map.ea_path_set = 0;
	data->map.floor_color_set = 0;
	data->map.ceiling_color_set = 0;
	data->player.dir.x = 0;
	data->player.dir.y = -1;
	data->player.pos.x = 0;
	data->player.pos.y = 0;
	data->player.plane.x = 0;
	data->player.plane.y = 0.66;
	data->keys.advance = false;
	data->keys.back = false;
	data->keys.left = false;
	data->keys.right = false;
	data->keys.rot_left = false;
	data->keys.rot_right = false;
	return (true);
}
