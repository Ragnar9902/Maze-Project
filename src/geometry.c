#include "raycaster.h"

void draw_vert_line(t_sdl *sdl, t_raycaster *rc, int x)
{
	SDL_Color color;

	color = apply_night_effect(select_wall_color(rc->map_x, rc->map_y),
							   rc->perp_wall_dist);

	if (rc->side == 1)
	{
		color.r /= 2;
		color.g /= 2;
		color.b /= 2;
	}
	SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g,
						   color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(sdl->renderer, x, rc->draw_start, x, rc->draw_end);
}

void draw_incli_line(t_sdl *sdl, int x, int y, int d,
					 double dir, int hexa_code)
{
	SDL_Color color;

	color = convert_color(hexa_code);

	SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g,
						   color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(sdl->renderer, x - (d / 2) * cos(dir * 2 * PI / 360),
					   y + (d / 2) * sin(dir * 2 * PI / 360),
					   x + (d / 2) * cos(dir * 2 * PI / 360),
					   y - (d / 2) * sin(dir * 2 * PI / 360));
}

void draw_square(t_sdl *sdl, int x, int y, size_t l, int hexa_code)
{
	for (size_t i = 0; i < l; i++)
	{
		draw_incli_line(sdl, x, y + i, l, 180, hexa_code);
	}
}
void draw_triangle(t_sdl *sdl, int x, int y, size_t h, int w,
				   double dir, int hexa_code)
{
	SDL_Color color;

	color = convert_color(hexa_code);

	SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g,
						   color.b, SDL_ALPHA_OPAQUE);

	for (size_t i = 0; i < h; i++)
	{
		draw_incli_line(sdl, x + i * cos((dir * 2 * PI / 360)),
						y - i * sin((dir * 2 * PI / 360)), w - i * (w / h),
						dir - 90, hexa_code);
	}
}
void miniMap(t_sdl *sdl, int x, int y, t_raycaster *rc)
{
	size_t wall_side = 10;

	for (size_t i = 0; i < mapWidth; i++)
	{
		for (size_t j = 0; j < mapHeight; j++)
		{
			draw_square(sdl, x + wall_side * i, y - wall_side * j, wall_side,
						hexa_wall_color(worldMap[i][j]));
		}
	}
	int miniCx = (9.1 * rc->player_pos_x) + x + 16;
	int miniCy = (-9.1 * rc->player_pos_y) + y - 4;
	double miniDir = atan(rc->player_dir_y / rc->player_dir_x) *
						 (360 / (2 * PI)) + 180;
	draw_triangle(sdl, miniCx, miniCy, 15, 15, miniDir, RED);
}
