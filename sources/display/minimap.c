/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:39:57 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/05 21:37:59 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_SIZE 10

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (y == (int)data->player.pos.y && x == (int)data->player.pos.x)
				color = 0xFF0000;
			else if (data->map.array[y][x] == '0')
				color = 0xFFFFFF;
			else if (data->map.array[y][x] == '1')
				color = 0x000000;
			for (int dy = 0; dy < MINIMAP_SIZE; dy++)
			{
				for (int dx = 0; dx < MINIMAP_SIZE; dx++)
				{
					my_mlx_pixel_put(data, x * MINIMAP_SIZE + dx, y * MINIMAP_SIZE + dy, color);
				}
			}
			x++;
		}
		y++;
	}
}


int     loop_hook(t_data *data)
{
    update_player(data);
    mlx_destroy_image(data->win.mlx, data->win.img);
    data->win.img = mlx_new_image(data->win.mlx, WIN_W, WIN_H);
    data->win.addr = mlx_get_data_addr(data->win.img, &(data->win.bits_per_pixel), &(data->win.line_length), &(data->win.endian));
    raycasting(data);
    draw_minimap(data);
    mlx_put_image_to_window(data->win.mlx, data->win.mlx_win, data->win.img, 0, 0);
    return (0);
}

void display_game(t_data *data)
{
    data->win.mlx = mlx_init();
    data->win.mlx_win = mlx_new_window(data->win.mlx, WIN_W, WIN_H, "cube");
    data->win.img = mlx_new_image(data->win.mlx, WIN_W, WIN_H);
    data->win.addr = mlx_get_data_addr(data->win.img, &(data->win.bits_per_pixel), &(data->win.line_length), &(data->win.endian));
    mlx_hook(data->win.mlx_win, 2, (1L << 0), handle_keypress, data);
    mlx_hook(data->win.mlx_win, 3, (1L << 1), handle_keyrelease, data);
    mlx_loop_hook(data->win.mlx, loop_hook, data);
    mlx_loop(data->win.mlx);
}
