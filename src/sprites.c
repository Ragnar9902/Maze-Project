#include "raycaster.h"

void init_sprite(t_sdl *sdl,t_sprite * sp)
{
  // Load sprite image
    if (!sp->texture) {
        sp->surface = IMG_Load("/home/jesus/Maze-Project/src/sprite.png");
        sp->texture = SDL_CreateTextureFromSurface(sdl->renderer, sp->surface);
    }
    if (!sp->surface) {
        printf("Failed to load sprite image: %s\n", IMG_GetError());
        return;
    }

    // Convert sprite image to texture
    if (!sp->texture) {
        printf("Failed to create texture from sprite surface: %s\n", SDL_GetError());
        return;
    }

    // Set destination rectangle for sprite
    //SDL_Rect destRect = { sp->pos_x, sp->pos_y, 100, 100 };

    // Render sprite to screen
    //if (SDL_RenderCopy(sdl->renderer, sp->texture, NULL, &destRect) < 0) {
    //    printf("Failed to render sprite: %s\n", SDL_GetError());
    //    SDL_DestroyTexture(sp->texture);
    //    SDL_FreeSurface(sp->surface);
    //    return;
    //}

    // Update screen
    //SDL_RenderPresent(sdl->renderer);
    sp->pos_x = 7;
	sp->pos_y = 9;
	sp->dir_x = 0;
	sp->dir_y = 1;
	sp->id    = 0;
    sp->width = 50;
    sp->height = 50;
}

int calculate_distance(t_sprite *sp, t_raycaster *rc)
{
    sp->rel_pos_x = rc->player_pos_x - sp->pos_x;
    sp->rel_pos_y = rc->player_pos_y - sp->pos_y;
    double dist = sqrt(pow(sp->rel_pos_x,2) + pow(sp->rel_pos_y, 2));
    return (dist);
}
void draw_sprite(t_sdl *sdl, t_raycaster *rc, t_sprite *sp)
{
    int spriteDistance = (int)sqrt(pow(sp->pos_x, 2) + pow(sp->pos_y, 2));
    double transformZ = (rc->player_plane_x * (sp->pos_y - rc->player_pos_y) - rc->player_plane_y * (sp->pos_x - rc->player_pos_x)) / spriteDistance;
    transformZ *= cos(atan2(rc->player_dir_x , rc->player_dir_y) - atan2(sp->pos_y - rc->player_pos_y, sp->pos_x - rc->player_pos_x));
    double spriteX = sp->pos_x - rc->player_pos_x;
    double spriteY = sp->pos_y - rc->player_pos_y;
    double invDet = 1.0 / (rc->player_plane_x * rc->player_dir_y - rc->player_dir_x * rc->player_plane_y);
    double transformX = invDet * (rc->player_dir_y * spriteX - rc->player_dir_x * spriteY);
    //double transformY = invDet * (-rc->player_plane_y * spriteX + rc->player_plane_x * spriteY);
    double spriteScreenX = (sdl->width / 2) * (1 + transformX / transformZ);

    // Calculate width of the sprite in the world
    //int spriteWidth = sp->width;

    // Calculate width of the sprite on the screen
    //int screenWidth = sdl->width;
    int spriteScreenHeight = abs((int)(sdl->height / (transformZ))) / 50;
    int spriteScreenWidth = abs((int)(sdl->height / (transformZ))) / 50;
    int spriteScreenStartX = (int)(-spriteScreenWidth / 2 + spriteScreenX);
    //int spriteScreenEndX = (int)(spriteScreenWidth / 2 + spriteScreenX);
    int spriteScreenStartY = (int)(-spriteScreenHeight / 2 + sdl->height / 2);
    //int spriteScreenEndY = (int)(spriteScreenHeight / 2 + sdl->height / 2);
    //double distance_to_object = spriteDistance * cos(atan2(rc->player_dir_x , rc->player_dir_y) - atan2(sp->pos_y - rc->player_pos_y, sp->pos_x - rc->player_pos_x));
    //double vertical_angle = atan2(0, sqrt(rc->player_dir_x * rc->player_dir_x + rc->player_dir_y * rc->player_dir_y));
    //double depth = distance_to_object * cos(vertical_angle) * 5;
    // Draw the sprite to the screen
    // Set destination rectangle for sprite
    SDL_Rect destRect = { spriteScreenStartX, spriteScreenStartY, 100, 100 };

    // Render sprite to screen
    if (SDL_RenderCopy(sdl->renderer, sp->texture, NULL, &destRect) < 0) {
        printf("Failed to render sprite: %s\n", SDL_GetError());
        SDL_DestroyTexture(sp->texture);
        SDL_FreeSurface(sp->surface);
        return;
    }

    // Update screen
    SDL_RenderPresent(sdl->renderer);
    
}
