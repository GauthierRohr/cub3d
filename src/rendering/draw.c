#include "../../includes/cub3d.h"

// Calcule les paramètres de rendu d’un mur
static void calc_wall_params(t_game *game, t_ray *ray, int *line_height, int *draw_start, int *draw_end)
{
    *line_height = (int)(game->win_height / ray->perp_dist);
    *draw_start = -(*line_height) / 2 + game->win_height / 2;
    if (*draw_start < 0)
        *draw_start = 0;
    *draw_end = *line_height / 2 + game->win_height / 2;
    if (*draw_end >= game->win_height)
        *draw_end = game->win_height - 1;
}

// Calcule la coordonnée X de la texture
static int calc_tex_x(t_game *game, t_ray *ray)
{
    double  wall_x;
    int     tex_x;

    if (ray->side == 0)
        wall_x = game->player.pos.y + ray->perp_dist * ray->dir.y;
    else
        wall_x = game->player.pos.x + ray->perp_dist * ray->dir.x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)game->textures.width);
    if (ray->side == 0 && ray->dir.x > 0)
        tex_x = game->textures.width - tex_x - 1;
    if (ray->side == 1 && ray->dir.y < 0)
        tex_x = game->textures.width - tex_x - 1;
    return (tex_x);
}

// Dessine une colonne de mur
void draw_column(t_game *game, int x, t_ray *ray)
{
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     tex_x;
    int     y;
    int     bpp;
    int     line_len;
    int     endian;

    calc_wall_params(game, ray, &line_height, &draw_start, &draw_end);
    tex_x = calc_tex_x(game, ray);
    y = draw_start;
    while (y < draw_end)
    {
        int     tex_y = (y - game->win_height / 2 + line_height / 2) * game->textures.height / line_height;
        int     color;
        char    *tex_data;

        if (ray->wall_type == 0)
            tex_data = mlx_get_data_addr(game->textures.east, &bpp, &line_len, &endian);
        else if (ray->wall_type == 1)
            tex_data = mlx_get_data_addr(game->textures.west, &bpp, &line_len, &endian);
        else if (ray->wall_type == 2)
            tex_data = mlx_get_data_addr(game->textures.south, &bpp, &line_len, &endian);
        else
            tex_data = mlx_get_data_addr(game->textures.north, &bpp, &line_len, &endian);
        color = *(int *)(tex_data + (tex_y * line_len + tex_x * (bpp / 8)));
        *(int *)(game->img_data + (y * game->win_width + x) * (game->img_bpp / 8)) = color;
        y++;
    }
}
