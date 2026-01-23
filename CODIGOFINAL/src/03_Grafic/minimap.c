
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

static int mm_hit_check(t_mlx *win, float x, float y)
{
    int map_x;
    int map_y;

    map_x = (int)((x - MM_MARGIN) / MM_TILE); 
    map_y = (int)((y - MM_MARGIN) / MM_TILE);
    if (map_x < 0 || map_x >= win->map->width || map_y < 0 || map_y >= win->map->height)
        return (1);
    return (win->map->coord[map_y][map_x] == '1');
}

static void draw_mm_dir_ray(t_mlx *win, float ra)
{
    int     i;
    int     mm_lim;
    float   x;
    float   y;
    float   dx;
    float   dy;

    i = 0;
    mm_lim = win->map->width * SQUARE;
    x = (MM_MARGIN + (win->player->x / SQUARE) * MM_TILE) + MM_P_MARGIN;
    y = (MM_MARGIN + (win->player->y / SQUARE) * MM_TILE) + MM_P_MARGIN;
    dx = cos(ra);
    dy = sin(ra);
    while (i < mm_lim)
    {
        if (mm_hit_check(win, x, y))
                break;
        my_pixel_put(&win->img, (int)x, (int)y, 0xAA00FF);
        x += dx;
        y += dy;
        i++;
    }
}

static void draw_mm_dir(t_mlx *win)
{
    int     i;
    float   start;
    float   step;
    float   ra;

    start = win->player->player_angle - (FOV / 2);
    step = FOV / 30;
    i = 0;
    while (i < 30)
    {
        ra = start + i * step;
        draw_mm_dir_ray(win, ra);
        i++;
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
    draw_mm_dir(win);
}
