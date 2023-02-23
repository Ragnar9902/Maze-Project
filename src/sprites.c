#include "raycaster.h"
/**
 * init_sprite - initialize sprites
 * @sdl: SDL stuccture
 * @sp: Raycaster Structure
 * Return: 0 if success 1 if failed
 */
int init_sprite(t_sdl *sdl, t_sprite *sp)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	/** Load sprite image */
	surface = IMG_Load(url_image);
	texture = SDL_CreateTextureFromSurface(sdl->renderer, surface);

	if (!surface)
	{
		printf("Failed to load sprite image: %s\n", IMG_GetError());
		return (1);
	}

	/** Convert sprite image to texture */
	if (!texture)
	{
		printf("Failed to create texture from sprite surface: %s\n", SDL_GetError());
		return (1);
	}
	sp->surface = surface;
	sp->texture = texture;

	sp->pos_x = 20;
	sp->pos_y = 11;
	sp->id = 0;
	sp->width = 2;
	sp->height = 1;
	return (0);
}

int calculate_distance(t_sprite *sp, t_raycaster *rc)
{
	sp->rel_pos_x = rc->player_pos_x - sp->pos_x;
	sp->rel_pos_y = rc->player_pos_y - sp->pos_y;
	double dist = sqrt(pow(sp->rel_pos_x, 2) + pow(sp->rel_pos_y, 2));

	return (dist);
}
void draw_sprite(t_sdl *sdl, t_raycaster *rc, t_sprite *sp)
{
	int sprite_x = sp->pos_x;
	int sprite_y = sp->pos_y;
	int sprite_width = sp->width;
	int sprite_height = sp->height;
	int camera_x = rc->player_pos_x;
	int camera_y = rc->player_pos_y;
	int camera_angle = atan2(rc->player_pos_x, rc->player_pos_y);
	int screen_width = sdl->width;
	int screen_height = sdl->height;

	/** Calculate the distance and angle between the camera and the sprite */
	int delta_x = sprite_x - camera_x;
	int delta_y = sprite_y - camera_y;
	double distance = sqrt(delta_x * delta_x + delta_y * delta_y);
	double sprite_angle = atan2(delta_y, delta_x) - camera_angle;

	/** Calculate the size of the sprite based on its distance from camera */
	int sprite_screen_width = (int)(screen_width / distance * sprite_width);
	int sprite_screen_height = (int)(screen_height / distance * sprite_height);

	/** Calculate the position of the sprite based on its angle and size */
	int sprite_screen_x = (int)((screen_width / 2) *
									(1 + sprite_angle / (PI / 2)) -
								sprite_screen_width / 2);
	int sprite_screen_y = (int)((screen_height / 2) - sprite_screen_height / 2);

	printf(",%d,%d,%d", sprite_screen_x, sprite_screen_width, sprite_screen_y);
	/** Create a rectangle to represent the sprite on the screen */
	SDL_Rect sprite_rect = {sprite_screen_x, sprite_screen_y,
							sprite_screen_width, sprite_screen_height};

	/** Draw the sprite to the screen */
	if (fabs(sprite_angle) <= PI / 6)
	{
		if (SDL_RenderCopy(sdl->renderer, sp->texture, NULL, &sprite_rect) < 0)
		{
			printf("Failed to render sprite: %s\n", SDL_GetError());
			return;
		}
	}
}
