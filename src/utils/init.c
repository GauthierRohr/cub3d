//init.c

#include "../../includes/cub3d.h"

// Initialise la connexion minilibX et la fenêtre
void init_game(t_game *game)
{
    ft_memset(game, 0, sizeof(t_game));
    game->win_width = 1280;
    game->win_height = 720;
    game->mlx = mlx_init();
    if (!game->mlx)
        exit_error("Erreur initialisation minilibX");
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D");
    if (!game->win)
        exit_error("Erreur création fenêtre");
    game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    if (!game->img)
        exit_error("Erreur création image");
    game->img_data = mlx_get_data_addr(game->img, &game->img_bpp, &game->img_line_len, &game->img_endian);
    game->sprite_count = 0;
    game->sprites = NULL;
    game->map = NULL;
    game->doors = NULL;
    game->map_width = 0;
    game->map_height = 0;
    game->player.move_speed = 0.1;
    game->player.rot_speed = 0.05;
    #ifdef BONUS
        init_bonus(game);
    #endif
}
