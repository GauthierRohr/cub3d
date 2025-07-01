#include "../../../includes/cub3d_bonus.h"

// Joue un son selon l’événement
void play_sound(t_game *game, char *event)
{
    if (ft_strcmp(event, "footstep") == 0)
        Mix_PlayChannel(-1, (Mix_Chunk *)game->audio.footstep, 0);
    else if (ft_strcmp(event, "door_open") == 0)
        Mix_PlayChannel(-1, (Mix_Chunk *)game->audio.door_open, 0);
}
