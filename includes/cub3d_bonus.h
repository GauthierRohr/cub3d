#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"
# include "/opt/homebrew/include/SDL2/SDL_mixer.h"

// Bonus: Wall collision
int     check_collision(t_game *game, double new_x, double new_y);

// Bonus: Minimap
void    render_minimap(t_game *game);
void    draw_minimap(t_game *game, int x, int y);

// Bonus: Doors
void    render_doors(t_game *game);
void    toggle_door(t_game *game, int x, int y);
void	init_doors(t_game *game);

// Bonus: Animations
void    update_sprites(t_game *game);
void    load_sprites(t_game *game);

// Bonus: Mouse rotation
void    rotate_with_mouse(t_game *game, int x);

// Bonus: Map generator
void    generate_map(t_game *game, int width, int height);
void    save_map_to_file(t_game *game, char *filename);

// Bonus: Audio
void    init_audio(t_game *game);
void    play_sound(t_game *game, char *event);

// Bonus: Initialization and utils
void    init_bonus(t_game *game);
void    free_bonus(t_game *game);

#endif