/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:10:17 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/05 20:08:36 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void  dda_algo(t_data *data);
void  calc_wall(t_data *data, int x);

void    raycasting(t_data *data)
{
  printf("%f %f\n", data->player.pos.x, data->player.pos.y);
    for(int x = 0; x < WIN_W; x++)
    {
      //calculate ray position and direction
      data->ray.camera.x = 2 * x / (double)WIN_W - 1; //x-coordinate in camera space
      data->ray.dir.x = data->player.dir.x + data->player.plane.x * data->ray.camera.x;
      data->ray.dir.y = data->player.dir.y + data->player.plane.y * data->ray.camera.x;
      dda_algo(data);
      calc_wall(data, x);
    }
}

void  dda_algo(t_data *data)
{
  data->ray.map.x = (int)data->player.pos.x;
  data->ray.map.y = (int)data->player.pos.y;

  if (data->ray.dir.x == 0)
    data->ray.delta_dist.x = 1e30;
  else
    data->ray.delta_dist.x = fabs(1 / data->ray.dir.x);
  
  if (data->ray.dir.y == 0)
    data->ray.delta_dist.y = 1e30;
  else
    data->ray.delta_dist.y = fabs(1 / data->ray.dir.y);
    
    if (data->ray.dir.x < 0)
    {
      data->ray.step.x = -1;
      data->ray.side_dist.x = (data->player.pos.x - data->ray.map.x) * data->ray.delta_dist.x;
    }
    else
    {
      data->ray.step.x = 1;
      data->ray.side_dist.x = (data->ray.map.x + 1.0 - data->player.pos.x) * data->ray.delta_dist.x;
    }
    
    if (data->ray.dir.y < 0)
    {
      data->ray.step.y = -1;
      data->ray.side_dist.y = (data->player.pos.y - data->ray.map.y) * data->ray.delta_dist.y;
    }
    else
    {
      data->ray.step.y = 1;
      data->ray.side_dist.y = (data->ray.map.y + 1.0 - data->player.pos.y) * data->ray.delta_dist.y;
    }
    
    data->ray.hit = 0;
    data->ray.side = 0;
    while (data->ray.hit == 0)
    {
        if (data->ray.side_dist.x < data->ray.side_dist.y)
        {
          data->ray.side_dist.x += data->ray.delta_dist.x;
          data->ray.map.x += data->ray.step.x;
          data->ray.side = 0;
        }
        else
        {
          data->ray.side_dist.y += data->ray.delta_dist.y;
          data->ray.map.y += data->ray.step.y;
          data->ray.side = 1;
        }
        if (data->map.array[data->ray.map.y][data->ray.map.x] == '1')
          data->ray.hit = 1;
    }

    if(data->ray.side == 0) 
      data->ray.perp_wall_dist = (data->ray.side_dist.x - data->ray.delta_dist.x);
    else
      data->ray.perp_wall_dist = (data->ray.side_dist.y - data->ray.delta_dist.y);        
}

void  calc_wall(t_data *data, int x)
{

      //Calculate height of line to draw on screen
      int lineHeight = (int)(WIN_H / data->ray.perp_wall_dist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + WIN_H / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + WIN_H / 2;
      if(drawEnd >= WIN_H)drawEnd = WIN_H - 1;
  
      for (int y = 0; y < WIN_H; y++)
      {
        if (y < drawStart)
          my_mlx_pixel_put(data, x, y, data->params.celling_color);
        else if (y < drawEnd)
          my_mlx_pixel_put(data, x, y, 0x44444);
        else if (y < WIN_H)
          my_mlx_pixel_put(data, x, y, data->params.floor_color);
      }
}
