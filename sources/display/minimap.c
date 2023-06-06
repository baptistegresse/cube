/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:39:57 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/06 11:21:34 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_SIZE 10

bool	load_textures(t_data *data)
{
    char	*texture_paths[4];

    texture_paths[0] = data->params.path_to_the_north_texture;
    texture_paths[1] = data->params.path_to_the_south_texture;
    texture_paths[2] = data->params.path_to_the_west_texture;
    texture_paths[3] = data->params.path_to_the_east_texture;

	for (int i = 0; i < 4; i++)
	{
		data->text[i].width = 64;
		data->text[i].height = 64;
	}
    for (int i = 0; i < 4; i++)
    {
        data->text[i].img = mlx_xpm_file_to_image(data->win.mlx, texture_paths[i], &data->text[i].width, &data->text[i].height);
        if (!data->text[i].img)
        {
            fprintf(stderr, "Failed to load texture: %s\n", texture_paths[i]);
			exit(1);
        }
        data->text[i].data = mlx_get_data_addr(data->text[i].img, &data->text[i].bpp, &data->text[i].size_line, &data->text[i].endian);
    }
	return (true);
}

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
	load_textures(data);
    data->win.mlx_win = mlx_new_window(data->win.mlx, WIN_W, WIN_H, "cube");
    data->win.img = mlx_new_image(data->win.mlx, WIN_W, WIN_H);
    data->win.addr = mlx_get_data_addr(data->win.img, &(data->win.bits_per_pixel), &(data->win.line_length), &(data->win.endian));
    mlx_hook(data->win.mlx_win, 2, (1L << 0), handle_keypress, data);
    mlx_hook(data->win.mlx_win, 3, (1L << 1), handle_keyrelease, data);
    mlx_loop_hook(data->win.mlx, loop_hook, data);
    mlx_loop(data->win.mlx);
}
