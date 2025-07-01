#include "../../includes/cub3d.h"

// Charge une texture à partir d’un chemin
static void *load_texture(t_game *game, char *path)
{
    void    *texture;
    int     width;
    int     height;

    texture = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
    if (!texture)
        return (NULL);
    game->textures.width = width;
    game->textures.height = height;
    return (texture);
}

// Charge toutes les textures
int load_textures(t_game *game)
{
    game->textures.north = load_texture(game, "./textures/north.xpm");
    game->textures.south = load_texture(game, "./textures/south.xpm");
    game->textures.west = load_texture(game, "./textures/west.xpm");
    game->textures.east = load_texture(game, "./textures/east.xpm");
    if (!game->textures.north || !game->textures.south ||
        !game->textures.west || !game->textures.east)
        return (0);
    return (1);
}
