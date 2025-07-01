#include "../../../includes/cub3d_bonus.h"

// Dessine un pixel de la minicarte
static void draw_minimap_pixel(t_game *game, int x, int y, int color)
{
    int i;
    int j;
    int scale;

    scale = 8; // Taille d’un bloc en pixels
    i = y * scale;
    while (i < (y + 1) * scale && i < game->win_height)
    {
        j = x * scale;
        while (j < (x + 1) * scale && j < game->win_width)
        {
            *(int *)(game->img_data + (i * game->win_width + j) * (game->img_bpp / 8)) = color;
            j++;
        }
        i++;
    }
}

// Dessine un élément de la minicarte
void    draw_minimap(t_game *game, int x, int y)
{
    if (game->map[y][x] == '1')
        draw_minimap_pixel(game, x, y, 0xFFFFFF); // Mur : blanc
    else if (game->map[y][x] == '0')
        draw_minimap_pixel(game, x, y, 0x000000); // Sol : noir
    else if ((int)game->player.pos.x == x && (int)game->player.pos.y == y)
        draw_minimap_pixel(game, x, y, 0xFF0000); // Joueur : rouge
    else if (game->doors[y][x] == 'D')
        draw_minimap_pixel(game, x, y, 0x00FF00); // Porte : vert
}
