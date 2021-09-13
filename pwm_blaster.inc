/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright 2021 Stefan Misik.  All rights reserved. */

#ifndef PWMBLAST_TYPE
#define PWMBLAST_TYPE char
#endif  // PWMBLAST_TYPE

static struct
{
	PWMBLAST_TYPE none_duty;
	PWMBLAST_TYPE zero_duty;
	PWMBLAST_TYPE one_duty;
} pwmblast_config = {
		.none_duty = 0,
		.zero_duty = 1,
		.one_duty = 2
};

enum pwmblast_ch_state
{
	PWMBLAST_CH_IDLE,
	PWMBLAST_CH_START,
};

struct pwmblast_channel
{
	char *buffer;
	size_t capacity;
	size_t length;

	enum pwmblast_ch_state state;
	size_t state_pos;
};

struct pwmblast
{
	struct pwmblast_channel channel[2];
};

int pwmblast_out(struct pwmblast *pwmb, PWMBLAST_TYPE *buffer, size_t capacity)
{
	return 0;
}

