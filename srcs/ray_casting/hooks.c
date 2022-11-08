/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:53:14 by albaur            #+#    #+#             */
/*   Updated: 2022/11/08 16:13:05 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	move_doors(t_data *data, t_ray *ray) {
	t_var	var;

	ft_bzero(&var, sizeof(var));
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	while (var.i < var.height && ray->map->map[var.i])
	{
		var.j = 0;
		while (var.j < var.width && ray->map->map[var.i][var.j])
		{
			//0: Closed, 1: Opening, 2: Open, 3: Closing
			if (ray->map->map[var.i][var.j] == 3) { //Standard door
				if (ray->door.door_states[var.i][var.j] == 1){//Open doors
//					ray->door.door_offsets[var.i][var.j] += deltaTime / 100;

//				if (ray->door.door_offsets[var.i][var.j] > 1) {
//					ray->door.door_offsets[var.i][var.j] = 1;
						ray->door.door_states[var.i][var.j] = 2;//Set state to open
//						setTimeout(function(stateX, stateY){ray->door.door_states[stateX][stateY] = 3;}, 5000, x, y);//TO DO: Don't close when player is in tile
					}
//				}
				else if (ray->door.door_states[var.i][var.j] == 3)
				{//Close doors
//					ray->door.door_offsets[var.i][var.j] -= deltaTime / 100;
					
//					if (ray->door.door_offsets[var.i][var.j] < 0) {
//						ray->door.door_offsets[var.i][var.j] = 0;
						ray->door.door_states[var.i][var.j] = 0;//Set state to closed
//					}
				}
			}
			var.j++;
		}
		var.i++;
	}
}

static void	ft_mouse_input_child(t_var var, t_ray *ray, t_data *data, double x)
{
	if (x > ray->half_width)
	{
		var.old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->m.pcos - ray->dir.y * ray->m.psin;
		ray->dir.y = var.old_dir_x * ray->m.psin + ray->dir.y * ray->m.pcos;
		var.old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->m.pcos - ray->plane.y * ray->m.psin;
		ray->plane.y = var.old_plane_x * ray->m.psin + ray->plane.y
			* ray->m.pcos;
		data->player.yaw += data->player.speed.rotation / 2;
	}
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

void	ft_mouse_input(double x, double y, void *param)
{
	t_data	*data;
	t_ray	*ray;
	t_var	var;

	(void)y;
	ft_bzero(&var, sizeof(var));
	data = (t_data *)param;
	ray = &data->ray_data;
	if (ray->m.focus == 1)
		return ;
	if ((ray->half_width - x >= -5 && ray->half_width - x <= 5))
		return ;
	if (x < ray->half_width)
	{
		var.old_dir_x = ray->dir.x;
		ray->dir.x = ray->dir.x * ray->m.ncos - ray->dir.y * ray->m.nsin;
		ray->dir.y = var.old_dir_x * ray->m.nsin + ray->dir.y * ray->m.ncos;
		var.old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * ray->m.ncos - ray->plane.y * ray->m.nsin;
		ray->plane.y = var.old_plane_x * ray->m.nsin + ray->plane.y
			* ray->m.ncos;
		data->player.yaw -= data->player.speed.rotation / 2;
	}
	ft_mouse_input_child(var, ray, data, x);
}

void	ft_update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->enemy.alive)
	{
		ft_key_input(data);
		return ;
	}
	if (data->enemy.kill_countdown <= 0 && data->enemy.disable_ai == 0 && data->enemy.alive == 1)
		draw_death(data);
	get_delay(1, 16666);
	while (data->delay > 16666)
	{
		ft_key_input(data);
		++data->time;
		data->delay -= 16666;
	}
	ft_key_input(data);
	ray_casting(data);
	move_doors(data, &data->ray_data);
	draw_minimap(data);
	mlx_image_to_window(data->mlx, data->map->minimap->img, 0, 0);
	data->delay += get_delay(0, 16666);
	++data->time;
	if (data->enemy.alive == 0)
		show_death(data);
}
