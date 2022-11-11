/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:19:41 by albaur            #+#    #+#             */
/*   Updated: 2022/11/11 11:44:28 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	init_audio_allocate(t_data *data)
{
	data->audio.audio_engine = malloc(sizeof(ma_engine));
	data->audio.suspense = malloc(sizeof(ma_sound) * 14);
	data->audio.footstep = malloc(sizeof(ma_sound) * 5);
	data->audio.death = malloc(sizeof(ma_sound) * 2);
	data->audio.dead = malloc(sizeof(ma_sound) * 2);
	data->audio.smiler = malloc(sizeof(ma_sound) * 2);
	data->audio.behind_you = malloc(sizeof(ma_sound) * 4);
}

static void	init_audio_volume(t_data *data)
{
	ma_sound_set_volume(&data->audio.ambiance, 0.55);
	ma_sound_set_volume(&data->audio.creeping_down, 1.5);
	ma_sound_set_volume(&data->audio.geiger, 0.45);
	ma_sound_set_volume(&data->audio.scare, 0.75);
	ma_sound_set_volume(&data->audio.footstep[0], 0.40);
	ma_sound_set_volume(&data->audio.footstep[1], 0.40);
	ma_sound_set_volume(&data->audio.footstep[2], 0.40);
	ma_sound_set_volume(&data->audio.footstep[3], 0.40);
	ma_sound_set_volume(&data->audio.footstep[4], 0.40);
}

void	init_audio(t_data *data)
{
	ma_result			result;
	ma_engine_config	config;

	config = ma_engine_config_init();
	init_audio_allocate(data);
	if (!data->audio.audio_engine)
		throw_err_ex("Malloc error");
	result = ma_engine_init(&config, data->audio.audio_engine);
	if (result != MA_SUCCESS)
		throw_err_ex("Audio initialization error");
	init_audio_ambiance(data, &result);
	init_audio_footstep(data, &result);
	init_audio_behind_you(data, &result);
	init_audio_suspense(data, &result);
	init_audio_volume(data);
	if (result != MA_SUCCESS)
		throw_err_ex("Audio file initialization error");
	ma_sound_set_looping(&data->audio.ambiance, 1);
	data->audio.lock = 0;
	data->audio.lock2 = 0;
	ma_sound_start(&data->audio.ambiance);
	ma_sound_start(&data->audio.creeping_down);
}
