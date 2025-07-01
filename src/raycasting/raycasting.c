#include "../../includes/cub3d.h"

// Initialise les paramètres du rayon
void init_ray(t_game *game, t_ray *ray, int x)
{
    ray->camera_x = 2 * x / (double)game->win_width - 1;
    ray->dir.x = game->player.dir.x + game->player.plane.x * ray->camera_x;
    ray->dir.y = game->player.dir.y + game->player.plane.y * ray->camera_x;
    ray->map.x = (int)game->player.pos.x;
    ray->map.y = (int)game->player.pos.y;
    ray->delta_dist.x = fabs(1 / ray->dir.x);
    ray->delta_dist.y = fabs(1 / ray->dir.y);
    ray->hit = 0;
}

// Calcule les distances initiales pour DDA
void calc_step(t_game *game, t_ray *ray)
{
    if (ray->dir.x < 0)
    {
        ray->step_x = -1;
        ray->side_dist.x = (game->player.pos.x - ray->map.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step_y = -1;
        ray->side_dist.y = (game->player.pos.y - ray->map.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
    }
}

// Effectue l’algorithme DDA pour trouver le mur
static void perform_dda(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map.x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map.y += ray->step_y;
            ray->side = 1;
        }
        int map_y = (int)ray->map.y;
        int map_x = (int)ray->map.x;
        if (map_y < 0 || map_y >= game->map_height ||
            map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
        {
            ray->hit = 1;
            return;
        }
        if (game->map[map_y][map_x] == '1')
            ray->hit = 1;
    }
}

// Calcule la distance perpendiculaire au mur
void calc_perp_dist(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_dist = (ray->map.x - game->player.pos.x + (1 - ray->step_x) / 2) / ray->dir.x;
    else
        ray->perp_dist = (ray->map.y - game->player.pos.y + (1 - ray->step_y) / 2) / ray->dir.y;
    if (ray->side == 0 && ray->dir.x > 0)
        ray->wall_type = 0; // Est
    else if (ray->side == 0 && ray->dir.x < 0)
        ray->wall_type = 1; // Ouest
    else if (ray->side == 1 && ray->dir.y > 0)
        ray->wall_type = 2; // Sud
    else
        ray->wall_type = 3; // Nord
}

// Effectue le raycasting pour une frame
void perform_raycasting(t_game *game)
{
    t_ray   ray;
    int     x;

    x = 0;
    while (x < game->win_width)
    {
        init_ray(game, &ray, x);
        calc_step(game, &ray);
        perform_dda(game, &ray);
        calc_perp_dist(game, &ray);
        draw_column(game, x, &ray);
        x++;
    }
}
