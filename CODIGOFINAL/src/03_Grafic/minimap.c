
#include "../../Includes/cub3d.h"

static void draw_mm_tile(t_img *img, int sx, int sy, int color)
{
    int y;
    int x;

    y = 0;
    while (y < MM_TILE)
    {
        x = 0;
        while (x < MM_TILE)
        {
            my_pixel_put(img, x + sx, y + sy, color);
            x++;
        }
        y++;
    }
}

static void draw_mm_player(t_mlx *win)
{
    int py;
    int px;

    px = MM_MARGIN + ((win->player->x / SQUARE) * MM_TILE);
    py = MM_MARGIN + ((win->player->y / SQUARE) * MM_TILE);
    draw_mm_tile(&win->img, px, py, 0xFF0000);
}

void    ft_draw_minimap(t_mlx *win)
{
    int x;
    int y;
    int screen_x;
    int screen_y;

    y = 0;
    while (y < win->map->height)
    {
        x = 0;
        while (x < win->map->width)
        {
            screen_x = (MM_TILE * x) + MM_MARGIN;
            screen_y = (MM_TILE * y) + MM_MARGIN;
            if (win->map->coord[y][x] == '1')
                draw_mm_tile(&win->img, screen_x, screen_y, 0x333333);
            else
                draw_mm_tile(&win->img, screen_x, screen_y, 0xAAAAAA);
            x++;
        }
        y++;
    }
    draw_mm_player(win);
}
