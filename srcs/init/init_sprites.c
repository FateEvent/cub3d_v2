/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:34:31 by faventur          #+#    #+#             */
/*   Updated: 2022/11/07 15:56:01 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_enemy(t_data *data)
{
	t_vec	tmp;

	data->enemy.disable_ai = 0;
	data->enemy.alive = 1;
	pathfinding_dist_check(data, 10);
	pathfinding_list_pos(data);
	tmp = pathfinding_get_pos(data);
	data->enemy.pos = pathfinding_pos_dist(data, (t_vec2){tmp.x + 0.5, tmp.y + 0.5},
		data->ray_data.pos, 10);
	if (data->enemy.pos.x == 0 && data->enemy.pos.y == 0)
		data->enemy.disable_ai = 1;
	data->enemy.kill_countdown = KILLCOUNTDOWN;
	data->enemy.move_countdown = MOVECOUNTDOWN;
	if (data->enemy.disable_ai == 1)
		printf("Map too small ! Disabling AI...\n");
	data->enemy.warning_text = malloc(sizeof(t_image));
}

void	init_sprites_pos(t_data *data, t_ray *ray)
{
	size_t		i;
	t_s_caster	*sprite;

	i = 0;
	sprite = &data->ray_data.sprite;
	while (i < NUMSPRITES)
	{
		sprite->sprite_order[i] = i;
		sprite->sprite_dist[i] = ((ray->pos.x - sprite->sprites[i].x)
				* (ray->pos.x - sprite->sprites[i].x)
				+ (ray->pos.y - sprite->sprites[i].y)
				* (ray->pos.y - sprite->sprites[i].y));
		i++;
	}
	sort_sprites(sprite->sprite_order, sprite->sprite_dist, NUMSPRITES);
}

void	init_sprites(t_data *data, t_ray *ray)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->sprites = malloc(sizeof(t_sprite) * NUMSPRITES);
	sprite->sprite_order = malloc(sizeof(int) * NUMSPRITES);
	sprite->sprite_dist = malloc(sizeof(double) * NUMSPRITES);
	sprite->z_buffer = malloc(sizeof(double) * ray->resolution.x);
	if (!sprite->sprites || !sprite->z_buffer || !sprite->sprite_order
		|| !sprite->sprite_dist)
		return ;
	sprite->sprites[0].x = data->enemy.pos.x;
	sprite->sprites[0].y = data->enemy.pos.y;
	sprite->sprites[0].texture = 6;
	sprite->sprites[1].x = 0;
	sprite->sprites[1].y = 0;
	sprite->sprites[1].texture = 7;
	sprite->sprites[2].x = 0;
	sprite->sprites[2].y = 0;
	sprite->sprites[2].texture = 8;
	init_sprites_pos(data, ray);
}
