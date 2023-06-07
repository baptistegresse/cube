/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:40:42 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:42:21 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ADVANCE)
		data->keys.advance = true;
	if (keycode == BACK)
		data->keys.back = true;
	if (keycode == RIGHT)
		data->keys.right = true;
	if (keycode == LEFT)
		data->keys.left = true;
	if (keycode == ROT_LEFT)
		data->keys.rot_left = true;
	if (keycode == ROT_RIGHT)
		data->keys.rot_right = true;
	if (keycode == ESC)
	{
		ft_free(data->garbage);
		exit(0);
	}
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == ADVANCE)
		data->keys.advance = false;
	if (keycode == BACK)
		data->keys.back = false;
	if (keycode == RIGHT)
		data->keys.right = false;
	if (keycode == LEFT)
		data->keys.left = false;
	if (keycode == ROT_LEFT)
		data->keys.rot_left = false;
	if (keycode == ROT_RIGHT)
		data->keys.rot_right = false;
	return (0);
}

void	handle_direction(t_data *data, double *new_x, double *new_y)
{
	if (data->keys.advance)
	{
		*new_x = data->player.pos.x + SPEED * data->player.dir.x;
		*new_y = data->player.pos.y + SPEED * data->player.dir.y;
	}
	if (data->keys.back)
	{
		*new_x = data->player.pos.x - SPEED * data->player.dir.x;
		*new_y = data->player.pos.y - SPEED * data->player.dir.y;
	}
	if (data->keys.right)
	{
		*new_x = data->player.pos.x + SPEED * data->player.plane.x;
		*new_y = data->player.pos.y + SPEED * data->player.plane.y;
	}
	if (data->keys.left)
	{
		*new_x = data->player.pos.x - SPEED * data->player.plane.x;
		*new_y = data->player.pos.y - SPEED * data->player.plane.y;
	}
}

void	handle_rotation(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = 0;
	old_plane_x = 0;
	if (data->keys.rot_right)
	{
		old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(ROT_SPEED) - data->player.dir.y * sin(ROT_SPEED);
		data->player.dir.y = old_dir_x * sin(ROT_SPEED) + data->player.dir.y * cos(ROT_SPEED);
		old_plane_x = data->player.plane.x;
		data->player.plane.x = data->player.plane.x * cos(ROT_SPEED) - data->player.plane.y * sin(ROT_SPEED);
		data->player.plane.y = old_plane_x * sin(ROT_SPEED) + data->player.plane.y * cos(ROT_SPEED);
	}
	if (data->keys.rot_left)
	{
		old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(-ROT_SPEED) - data->player.dir.y * sin(-ROT_SPEED);
		data->player.dir.y = old_dir_x * sin(-ROT_SPEED) + data->player.dir.y * cos(-ROT_SPEED);
		old_plane_x = data->player.plane.x;
		data->player.plane.x = data->player.plane.x * cos(-ROT_SPEED) - data->player.plane.y * sin(-ROT_SPEED);
		data->player.plane.y = old_plane_x * sin(-ROT_SPEED) + data->player.plane.y * cos(-ROT_SPEED);
	}
}

void	update_player(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	if (data->keys.advance || data->keys.back || data->keys.right || data->keys.left)
		handle_direction(data, &new_x, &new_y);
	if (data->keys.rot_right || data->keys.rot_left)
		handle_rotation(data);
	if (new_x >= 0 && new_x < data->map.width && new_y >= 0 && new_y < data->map.height && data->map.array[(int)new_y][(int)new_x] != '1')
	{
			data->player.pos.x = new_x;
			data->player.pos.y = new_y;
	}
}
