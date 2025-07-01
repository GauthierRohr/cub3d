#include "../../includes/cub3d_bonus.h"

void init_bonus(t_game *game)
{
    ft_putstr_fd("Début init_bonus\n", 1);
    init_audio(game);
    init_doors(game);
    load_sprites(game);
}
