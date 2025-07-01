#include "../../includes/cub3d.h"
#ifdef BONUS
# include "../../includes/cub3d_bonus.h"
#endif

// Libère les ressources de la carte
static void free_map(t_game *game)
{
    int i;

    if (game->map)
    {
        i = 0;
        while (i < game->map_height)
        {
            if (game->map[i])
                free(game->map[i]);
            i++;
        }
        free(game->map);
    }
}

// Libère les ressources des textures
static void free_textures(t_game *game)
{
    if (game->textures.north)
        mlx_destroy_image(game->mlx, game->textures.north);
    if (game->textures.south)
        mlx_destroy_image(game->mlx, game->textures.south);
    if (game->textures.west)
        mlx_destroy_image(game->mlx, game->textures.west);
    if (game->textures.east)
        mlx_destroy_image(game->mlx, game->textures.east);
}

// Libère toutes les ressources du jeu
void    free_game(t_game *game)
{
    free_map(game);
    free_textures(game);
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
#ifdef BONUS
    free_bonus(game);
#endif
    if (game->mlx)
        free(game->mlx); // Pas besoin de mlx_destroy_display sur macOS
}
