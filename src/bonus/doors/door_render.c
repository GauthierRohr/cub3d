#include "../../../includes/cub3d_bonus.h"

// Rend les portes dans le raycasting
void render_doors(t_game *game)
{
    t_ray ray;
    int x;

    x = 0;
    while (x < game->win_width)
    {
        init_ray(game, &ray, x);
        calc_step(game, &ray);
        while (ray.hit == 0)
        {
            if (ray.side_dist.x < ray.side_dist.y)
            {
                ray.side_dist.x += ray.delta_dist.x;
                ray.map.x += ray.step_x;
                ray.side = 0;
            }
            else
            {
                ray.side_dist.y += ray.delta_dist.y;
                ray.map.y += ray.step_y;
                ray.side = 1;
            }
            if (ray.map.x >= 0 && ray.map.x < game->map_width &&
                ray.map.y >= 0 && ray.map.y < game->map_height)
            {
                if (game->map[(int)ray.map.y][(int)ray.map.x] == '1')
                    ray.hit = 1;
                else if (game->doors[(int)ray.map.y][(int)ray.map.x] == 'D')
                {
                    ray.hit = 1;
                    calc_perp_dist(game, &ray);
                    draw_column(game, x, &ray);
                }
            }
        }
        x++;
    }
}
