/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:10:17 by bgresse           #+#    #+#             */
/*   Updated: 2023/06/07 12:46:17 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void raycasting(t_data *data)
{
	int column_pix;

	column_pix = -1;
	while (++column_pix < WIN_W)
	{
		// Calcul de la position de la caméra sur le plan de projection
		data->ray.camera.x = 2 * column_pix / (double)WIN_W - 1;

		// Calcul de la direction du rayon en fonction de la position de la caméra
		data->ray.dir.x = data->player.dir.x + data->player.plane.x * data->ray.camera.x;
		data->ray.dir.y = data->player.dir.y + data->player.plane.y * data->ray.camera.x;

		// Appel de la fonction dda_algo pour effectuer l'algorithme DDA
		dda_algo(data);

		// Appel de la fonction calc_wall pour calculer la hauteur du mur et les coordonnées de texture
		calc_wall(data, column_pix);
	}
}


void 	dda_algo(t_data *data)
{
	// Déterminer la case de la carte dans laquelle le rayon se trouve
	data->ray.map.x = (int)data->player.pos.x;
	data->ray.map.y = (int)data->player.pos.y;

	// Calculer les distances delta (deltas horizontale et verticale) pour le déplacement du rayon
	if (data->ray.dir.x == 0)
		data->ray.delta_dist.x = 1e30; // Utilisation d'une valeur très grande pour représenter l'infini
	else
		data->ray.delta_dist.x = fabs(1 / data->ray.dir.x);

	if (data->ray.dir.y == 0)
		data->ray.delta_dist.y = 1e30;
	else
		data->ray.delta_dist.y = fabs(1 / data->ray.dir.y);

	// Déterminer la direction du déplacement du rayon sur l'axe X et les distances de côté
	if (data->ray.dir.x < 0)
	{
		data->ray.step.x = -1; // Déplacement vers la gauche sur l'axe X
		data->ray.side_dist.x = (data->player.pos.x - data->ray.map.x) * data->ray.delta_dist.x;
	}
	else
	{
		data->ray.step.x = 1; // Déplacement vers la droite sur l'axe X
		data->ray.side_dist.x = (data->ray.map.x + 1.0 - data->player.pos.x) * data->ray.delta_dist.x;
	}

	// Déterminer la direction du déplacement du rayon sur l'axe Y et les distances de côté
	if (data->ray.dir.y < 0)
	{
		data->ray.step.y = -1; // Déplacement vers le haut sur l'axe Y
		data->ray.side_dist.y = (data->player.pos.y - data->ray.map.y) * data->ray.delta_dist.y;
	}
	else
	{
		data->ray.step.y = 1; // Déplacement vers le bas sur l'axe Y
		data->ray.side_dist.y = (data->ray.map.y + 1.0 - data->player.pos.y) * data->ray.delta_dist.y;
	}

	// Initialisation des indicateurs de collision et de côté du mur
	data->ray.hit = 0;
	data->ray.side = 0;

	// Algorithme DDA pour trouver le mur intersecté par le rayon
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist.x < data->ray.side_dist.y)
		{
			data->ray.side_dist.x += data->ray.delta_dist.x;
			data->ray.map.x += data->ray.step.x;
			data->ray.side = 0; // Le rayon a intersecté un mur vertical
		}
		else
		{
			data->ray.side_dist.y += data->ray.delta_dist.y;
			data->ray.map.y += data->ray.step.y;
			data->ray.side = 1; // Le rayon a intersecté un mur horizontal
		}

		// Vérifier si la case de la carte actuelle est un mur (représenté par '1')
		if (data->map.array[data->ray.map.y][data->ray.map.x] == '1')
			data->ray.hit = 1; // Le rayon a intersecté un mur
	}

	// Calcul de la distance perpendiculaire du mur par rapport à la caméra
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = (data->ray.side_dist.x - data->ray.delta_dist.x);
	else
		data->ray.perp_wall_dist = (data->ray.side_dist.y - data->ray.delta_dist.y);
}


void calc_wall(t_data *data, int x)
{
	// Calcul de la hauteur de la ligne à dessiner à l'écran
	int lineHeight = (int)(WIN_H / data->ray.perp_wall_dist);

	// Calcul du pixel le plus bas et le plus haut à remplir dans la bande actuelle
	int texNum;

	if (data->ray.side == 0)
	{
		if (data->ray.dir.x > 0)
			texNum = 1; // Sud
		else
			texNum = 0; // Nord
	}
	else
	{
		if (data->ray.dir.y > 0)
			texNum = 3; // Est
		else
			texNum = 2; // Ouest
	}

	int drawStart = -lineHeight / 2 + WIN_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_H / 2;
	if (drawEnd >= WIN_H)
		drawEnd = WIN_H - 1;

	double wallX;
	if (data->ray.side == 0)
		wallX = data->player.pos.y + data->ray.perp_wall_dist * data->ray.dir.y;
	else
		wallX = data->player.pos.x + data->ray.perp_wall_dist * data->ray.dir.x;
	wallX -= floor(wallX);

	// Calcul de la coordonnée X sur la texture
	int texX = (int)(wallX * (double)(data->text[texNum].width));

	// Modification de texX en fonction de la direction du rayon
	if ((data->ray.side == 0 && data->ray.dir.x < 0) || (data->ray.side == 1 && data->ray.dir.y > 0))
		texX = data->text[texNum].width - texX - 1;

	for (int y = 0; y < WIN_H; y++)
	{
		if (y < drawStart)
			my_mlx_pixel_put(data, x, y, data->params.celling_color);
		else if (y >= drawStart && y < drawEnd)
		{
			int d = y * 256 - WIN_H * 128 + lineHeight * 128; // Facteurs 256 et 128 pour éviter les calculs en virgule flottante
			int texY = ((d * data->text[texNum].height) / lineHeight) / 256;

			// Obtention de la couleur à partir des données de l'image de texture
			int color = *(int *)(data->text[texNum].data + ((texY * data->text[texNum].size_line) + texX * (data->text[texNum].bpp / 8)));
			my_mlx_pixel_put(data, x, y, color);
		}
		else if (y >= drawEnd)
			my_mlx_pixel_put(data, x, y, data->params.floor_color);
	}
}




