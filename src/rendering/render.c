#include "../../includes/cub3d.h"

// Rend une frame du jeu
int render_frame(void *game_ptr)
{
    t_game *game = (t_game *)game_ptr;

    perform_raycasting(game);
#ifdef BONUS
    render_doors(game);
    render_minimap(game);
    update_sprites(game);
#endif
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

// Initialise MLX et l’image principale
void init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        exit_error("Erreur initialisation MLX");
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D");
    if (!game->win)
        exit_error("Erreur création fenêtre");
    game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    if (!game->img)
        exit_error("Erreur création image");
    game->img_data = mlx_get_data_addr(game->img, &game->img_bpp, &game->img_line_len, &game->img_endian);
    if (!game->img_data)
        exit_error("Erreur récupération données image");
    if (!load_textures(game))
        exit_error("Erreur chargement textures");
}
