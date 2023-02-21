#ifndef RAYCASTER_H_
#define RAYCASTER_H_

/**
 * raycaster.h
 */

/** System includes */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

/** Map */
#define mapWidth 24
#define mapHeight 24

extern int worldMap[mapWidth][mapHeight];

/** Initial values */
#define WIN_X 1280
#define WIN_Y 720
#define INIT_P_POS_X 23
#define INIT_P_POS_Y 10
#define INIT_P_DIR_X -1
#define INIT_P_DIR_Y 0
#define INIT_P_PLANE_X 0
#define INIT_P_PLANE_Y 0.66
#define MV_SPEED 0.199
#define ROT_SPEED 0.1745
#define AMB_LIGHT 7
#define MINI_MAP_CELL 10
#define MINI_MAP_X WIN_X - 280
#define MINI_MAP_Y WIN_Y - 50
#define PI 3.14159265358979323846

/** Colors */
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000

/** Structures */
typedef struct s_sdl
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} t_sdl;

typedef struct s_sprite
{
	/* Data */
	double sprite_pos_x;
	double sprite_pos_y;
	int id;
	double sprite_dir_x;
	double sprite_dir_y;

} t_sprite;

typedef struct s_raycaster
{
	double player_pos_x;
	double player_pos_y;
	double player_dir_x;
	double player_dir_y;
	double player_plane_x;
	double player_plane_y;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	int step_x;
	int step_y;
	int side;
	int draw_start;
	int draw_end;
	double perp_wall_dist;
	int player_color;
} t_raycaster;

/** Proto */
SDL_Color convert_color(int hexa_value);
SDL_Color select_wall_color(int map_x, int map_y);
SDL_Color apply_night_effect(SDL_Color color, double distance);
void draw_incli_line(t_sdl *sdl, int x, int y, int h, double dir,
int hexa_code);
void draw_square(t_sdl *sdl, int x, int y, size_t l, int hexa_code);
void draw_vert_line(t_sdl *sdl, t_raycaster *rc, int x);
void miniMap(t_sdl *sdl, int x, int y, t_raycaster *rc);
int hexa_wall_color(int map);
void draw_triangle(t_sdl *sdl, int x, int y, size_t h, int w, double dir,
int hexa_code);

#endif /* !RAYCASTER_H_ */
