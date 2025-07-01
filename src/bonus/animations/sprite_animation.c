#include "../../../includes/cub3d_bonus.h"

// Met à jour les animations des sprites (alternative si séparé)
void update_sprites(t_game *game)
{
    static double time = 0.0;
    int i;

    time += 0.016; // Supposons 60 FPS
    i = 0;
    while (i < game->sprite_count)
    {
        if (time >= game->sprites[i].anim_speed)
        {
            game->sprites[i].frame = (game->sprites[i].frame + 1) % game->sprites[i].frame_count;
            time = 0.0;
        }
        i++;
    }
}
