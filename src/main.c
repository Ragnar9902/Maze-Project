#include "raycaster.h"

int cuadran(double dirx, double diry)
{
	if ((dirx >= 0) & (diry >= 0))
	{
		return (1);
	}
	if ((dirx > 0) & (diry < 0))
	{
		return (2);
	}
	if ((dirx <= 0) & (diry <= 0))
	{
		return (3);
	}
	if ((dirx < 0) & (diry > 0))
	{
		return (4);
	}
	return (0);
}

int init(t_sdl *sdl, t_raycaster *rc)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	rc->player_pos_x = INIT_P_POS_X;
	rc->player_pos_y = INIT_P_POS_Y;
	rc->player_dir_x = INIT_P_DIR_X;
	rc->player_dir_y = INIT_P_DIR_Y;
	rc->player_plane_x = INIT_P_PLANE_X;
	rc->player_plane_y = INIT_P_PLANE_Y;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL initialization failed (%s)\n", SDL_GetError());
		return (-1);
	}
	if (SDL_CreateWindowAndRenderer(WIN_X, WIN_Y, 0, &sdl->window, &sdl->renderer) != 0)
	{
		fprintf(stderr, "Window creation failed (%s)\n", SDL_GetError());
		return (-1);
	}
	return (0);
}

void initial_calc(t_raycaster *rc, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)(WIN_X)-1;
	rc->ray_dir_x = rc->player_dir_x + rc->player_plane_x * camera_x;
	rc->ray_dir_y = rc->player_dir_y + rc->player_plane_y * camera_x;
	rc->map_x = (int)(rc->player_pos_x);
	rc->map_y = (int)(rc->player_pos_y);
	rc->delta_dist_x = sqrt(1 + pow(rc->ray_dir_y, 2) / pow(rc->ray_dir_x, 2));
	rc->delta_dist_y = sqrt(1 + pow(rc->ray_dir_x, 2) / pow(rc->ray_dir_y, 2));
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->player_pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->player_pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->player_pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->player_pos_y) * rc->delta_dist_y;
	}
}

void perform_dda(t_raycaster *rc)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (worldMap[rc->map_x][rc->map_y] > 0)
			hit = 1;
	}
}

void calc_wall_height(t_raycaster *rc)
{
	int line_height;

	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - rc->player_pos_x + (1 - rc->step_x) / 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - rc->player_pos_y + (1 - rc->step_y) / 2) / rc->ray_dir_y;
	line_height = (int)(WIN_Y / rc->perp_wall_dist);
	rc->draw_start = -line_height / 2 + WIN_Y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = line_height / 2 + WIN_Y / 2;
	if (rc->draw_end >= WIN_Y)
		rc->draw_end = WIN_Y - 1;
}

void render_frame(t_sdl *sdl)
{
	SDL_RenderPresent(sdl->renderer);
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl->renderer);
}

int handle_events(t_raycaster *rc)
{
	SDL_Event event;
	double oldDirX;
	double oldPlaneX;
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			// Move centerpoint of rotation for one of the trees:
			if (keyboard_state_array[SDL_SCANCODE_W] && !(keyboard_state_array[SDL_SCANCODE_S]))
			{
				if (worldMap[(int)(rc->player_pos_x + rc->player_dir_x * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
					rc->player_pos_x += rc->player_dir_x * MV_SPEED;
				if (worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y + rc->player_dir_y * MV_SPEED)] == 0)
					rc->player_pos_y += rc->player_dir_y * MV_SPEED;
			}
			else if (!keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_S])
			{
				if (worldMap[(int)(rc->player_pos_x - rc->player_dir_x * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
					rc->player_pos_x -= rc->player_dir_x * MV_SPEED;
				if (worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y - rc->player_dir_y * MV_SPEED)] == 0)
					rc->player_pos_y -= rc->player_dir_y * MV_SPEED;
			}

			if (keyboard_state_array[SDL_SCANCODE_D] && !keyboard_state_array[SDL_SCANCODE_A])
			{
				double newX_dir = 0;
				double newY_dir = 0;
				newY_dir = rc->player_dir_x;
				newX_dir = -rc->player_dir_y;
				if (worldMap[(int)(rc->player_pos_x - newX_dir * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
					rc->player_pos_x -= newX_dir * MV_SPEED;
				if (worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y - newY_dir * MV_SPEED)] == 0)
					rc->player_pos_y -= newY_dir * MV_SPEED;
			}
			else if (!keyboard_state_array[SDL_SCANCODE_D] && keyboard_state_array[SDL_SCANCODE_A])
			{
				double newX_dir = 0;
				double newY_dir = 0;
				newY_dir = -rc->player_dir_x;
				newX_dir = rc->player_dir_y;
				if (worldMap[(int)(rc->player_pos_x - newX_dir * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
					rc->player_pos_x -= newX_dir * MV_SPEED;
				if (worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y - newY_dir * MV_SPEED)] == 0)
					rc->player_pos_y -= newY_dir * MV_SPEED;
			}
			if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !keyboard_state_array[SDL_SCANCODE_LEFT])
			{
				oldDirX = rc->player_dir_x;
				rc->player_dir_x = rc->player_dir_x * cos(-ROT_SPEED) - rc->player_dir_y * sin(-ROT_SPEED);
				rc->player_dir_y = oldDirX * sin(-ROT_SPEED) + rc->player_dir_y * cos(-ROT_SPEED);
				oldPlaneX = rc->player_plane_x;
				rc->player_plane_x = rc->player_plane_x * cos(-ROT_SPEED) - rc->player_plane_y * sin(-ROT_SPEED);
				rc->player_plane_y = oldPlaneX * sin(-ROT_SPEED) + rc->player_plane_y * cos(-ROT_SPEED);
			}
			else if (!keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_LEFT])
			{
				oldDirX = rc->player_dir_x;
				rc->player_dir_x = rc->player_dir_x * cos(ROT_SPEED) - rc->player_dir_y * sin(ROT_SPEED);
				rc->player_dir_y = oldDirX * sin(ROT_SPEED) + rc->player_dir_y * cos(ROT_SPEED);
				oldPlaneX = rc->player_plane_x;
				rc->player_plane_x = rc->player_plane_x * cos(ROT_SPEED) - rc->player_plane_y * sin(ROT_SPEED);
				rc->player_plane_y = oldPlaneX * sin(ROT_SPEED) + rc->player_plane_y * cos(ROT_SPEED);
			}
		}
		if (event.type == SDL_QUIT)
			return (-1);
	}
	return (0);
}

void raycaster(t_sdl *sdl, t_raycaster *rc)
{
	SDL_bool done;

	done = SDL_FALSE;
	while (!done)
	{
		for (int x = 0; x < WIN_X; x++)
		{
			initial_calc(rc, x);
			perform_dda(rc);
			calc_wall_height(rc);
			draw_vert_line(sdl, rc, x);
		}
		miniMap(sdl, MINI_MAP_X, MINI_MAP_Y, rc);
		render_frame(sdl);
		if (handle_events(rc) != 0)
			done = SDL_TRUE;
	}
}

int main()
{
	t_sdl sdl;
	t_raycaster rc;

	if (init(&sdl, &rc) != 0)
		return (-1);
	raycaster(&sdl, &rc);
	if (sdl.renderer)
		SDL_DestroyRenderer(sdl.renderer);
	if (sdl.window)
		SDL_DestroyWindow(sdl.window);
	SDL_Quit();
	return (0);
}