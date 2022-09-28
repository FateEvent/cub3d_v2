/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/09/28 13:44:46 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_hook(void* param)
{
	const mlx_t* mlx;

	mlx = param;
//	ft_printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	init_struct_child(t_program *data)
{
	data->screen->width = WIDTH;
	data->screen->height = HEIGHT;
	data->render->delay = 30;
	data->rc->precision = 64;
	data->player->fov = 60;
	data->player->x = 6;
	data->player->y = 2;
	data->player->angle = 90;
	data->screen->half_width = data->screen->width / 2;
	data->screen->half_height = data->screen->height / 2;
	data->rc->increment_angle = data->player->angle / data->screen->width;
	data->player->half_fov = data->player->fov / 2;
}

void	init_struct(t_program *data)
{
	data->screen = malloc(sizeof(*data->screen));
	data->render = malloc(sizeof(*data->render));
	data->rc = malloc(sizeof(*data->rc));
	data->player = malloc(sizeof(*data->player));
	data->map = malloc(sizeof(*data->map));
	if (!data->screen || !data->render || !data->rc || !data->player
		|| !data->map)
	{
		if (data->screen)
			free(data->screen);
		if (data->render)
			free(data->render);
		if (data->rc)
			free(data->rc);
		if (data->player)
			free(data->player);
		if (data->map)
			free(data->map);
		exit(1);
	}
	init_struct_child(data);
}

void	calculate_map_size(t_program *data)
{
	data->map->width = 0;
	data->map->height = 0;
	while (data->map->map[data->map->height])
	{
		while (data->map->map[data->map->height][data->map->width])
		{
			data->map->width++;
		}
		data->map->height++;
	}
}

int	main(int argc, char *argv[])
{
	t_program	program;
	int			i;

	i = 0;
	check_args(argc);
//	check_map_extension(argv);
//	if (!program.map->map || !ft_map_parser(program.map->map))
//		ft_puterror("Error!");
	init_struct(&program);
	program.map->map = ft_map_reader(argv[1]);
	if (!program.map->map)
		ft_puterror("Error!");
	calculate_map_size(&program);
	program.frame = 0;
	program.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	program.img.img = mlx_new_image(program.mlx, WIDTH, HEIGHT);
	if (!program.img.img) //|| (mlx_image_to_window(program.mlx,
			//	program.img.img, 0, 0) < 0))
		ft_puterror("Error!");
//	program.pixies = ft_put_sprite(&program);
//	ft_display_map(&program, program.pixies);
	mlx_image_to_window(program.mlx, program.img.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_update, &program);
//	mlx_loop_hook(program.mlx, ft_hook, program.mlx);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
