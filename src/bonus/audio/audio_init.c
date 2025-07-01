#include "../../../includes/cub3d_bonus.h"

// Initialise le système audio
void init_audio(t_game *game)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        exit_error("Erreur initialisation SDL2_mixer");
    game->audio.bg_music = Mix_LoadMUS("./audio/spinning-head.mp3");
    if (!game->audio.bg_music)
        exit_error("Erreur chargement audio/spinning-head.mp3");
    game->audio.footstep = Mix_LoadWAV("./audio/footsteps.wav");
    if (!game->audio.footstep)
        exit_error("Erreur chargement audio/footsteps.wav");
    game->audio.door_open = Mix_LoadWAV("./audio/door_open.wav");
    if (!game->audio.door_open)
        exit_error("Erreur chargement audio/door_open.wav");
    Mix_PlayMusic(game->audio.bg_music, -1);
}
