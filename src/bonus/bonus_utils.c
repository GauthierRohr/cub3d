#include "../../includes/cub3d_bonus.h"

// Libère les ressources des sprites
static void free_sprites(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->sprite_count)
    {
        j = 0;
        while (j < game->sprites[i].frame_count)
        {
            if (game->sprites[i].frames[j])
                mlx_destroy_image(game->mlx, game->sprites[i].frames[j]);
            j++;
        }
        free(game->sprites[i].frames);
        i++;
    }
    free(game->sprites);
}

// Libère les ressources audio
static void free_audio(t_game *game)
{
    if (game->audio.bg_music)
        Mix_FreeMusic((Mix_Music *)game->audio.bg_music);
    if (game->audio.footstep)
        Mix_FreeChunk((Mix_Chunk *)game->audio.footstep);
    if (game->audio.door_open)
        Mix_FreeChunk((Mix_Chunk *)game->audio.door_open);
    Mix_CloseAudio();
}

// Libère les ressources des bonus
void    free_bonus(t_game *game)
{
    int i;

    free_sprites(game);
    free_audio(game);
    if (game->doors)
    {
        i = 0;
        while (i < game->map_height)
        {
            if (game->doors[i])
                free(game->doors[i]);
            i++;
        }
        free(game->doors);
    }
}