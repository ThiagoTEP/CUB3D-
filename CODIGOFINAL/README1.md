# cub3D — My First RayCaster with miniLibX

*This project has been created as part of the 42 curriculum by thevaris.*

---

## Description

**cub3D** is a 3D maze renderer inspired by the legendary *Wolfenstein 3D* (id Software, 1992) — the game that invented the First-Person Shooter genre. The program reads a `.cub` scene file describing a 2D map, wall textures and floor/ceiling colors, then renders it in real-time from a first-person perspective using **ray-casting**.

The engine is written entirely in **C** and uses **miniLibX** for window management and pixel drawing. There is no 3D API involved; every pixel on screen is computed from scratch with trigonometry and simple 2D geometry.

Key features:
- Real-time 3D rendering via ray-casting
- Textured walls (North / South / East / West faces)
- Configurable floor and ceiling colors
- WASD movement + arrow-key / mouse rotation
- Wall-collision system
- Interactive minimap with FOV indicator

---

## Math Concepts

This section explains every math concept used in the engine, step by step.

---

### 1. The Map as a 2D Grid

The world is a 2D array of integers.
`1` = wall, `0` = empty space, `N/S/E/W` = player start.

Each cell has a fixed side length (`SQUARE = 64` pixels in world space).
A player position `(x, y)` is measured in **world-space pixels**, so the grid cell that contains the player is:

```
cell_x = (int)(player_x / SQUARE)
cell_y = (int)(player_y / SQUARE)
```

---

### 2. Angles and the Unit Circle

The player always faces a direction described by an angle **α** measured in **radians**, starting from the right (positive X-axis) and growing counter-clockwise. Note: on screen, Y grows downward, so "south" is positive Y.

| Direction | Angle (rad) | Approx. |
|-----------|-------------|---------|
| East      | 0           | 0.00    |
| South     | π/2         | 1.57    |
| West      | π           | 3.14    |
| North     | 3π/2        | 4.71    |

The angle is kept in `[0, 2π)` with this check:
```c
if (*ra < 0)      *ra += 2 * PI;
if (*ra > 2 * PI) *ra -= 2 * PI;
```

---

### 3. Sine and Cosine — Direction Vectors

Any angle gives us a direction vector with length 1:

```
dx = cos(α)   →  horizontal component
dy = sin(α)   →  vertical component
```

This is how we turn an angle into a direction we can move in.
**Why?** By the definition of the unit circle: a point at angle α and radius r is at `(r·cos α, r·sin α)`.

The player movement vector is scaled by a speed factor (7 in this project):

```c
player_delta_x = cos(player_angle) * 7;
player_delta_y = sin(player_angle) * 7;
```

Moving forward adds this vector; moving backward subtracts it.
Strafing rotates the direction 90°:

```
strafe_dx =  sin(α)   // perpendicular to forward
strafe_dy = -cos(α)
```

This works because rotating a vector 90° swaps its components and flips the sign of one.

---

### 4. Field of View (FOV)

The camera does not cast a single ray — it sends out `WIDTH` rays spread across the Field of View.

```
FOV = 60° = π/3 ≈ 1.047 radians
```

The angle added between each ray:

```
DR = FOV / WIDTH = π/3 / 1920 ≈ 0.000545 rad/pixel
```

Rays start at:

```
ra = player_angle - FOV/2
```

and each iteration increments `ra += DR`.

---

### 5. Ray-Casting — Finding Wall Intersections

For each screen column a ray is fired from the player's position at angle `ra`.
The idea behind DDA (Digital Differential Analyzer) ray-casting is that a ray going through a grid will cross **horizontal grid lines** (same Y) and **vertical grid lines** (same X) at regular, calculable steps.

We find both crossing points and use whichever is closer.

#### 5.1 Horizontal Intersections

Horizontal lines are at multiples of `SQUARE` on the Y-axis.

**Step 1 — First intersection:**

If the ray points **downward** (sin α > 0, i.e. `ra < π`):
```
ry = floor(player_y / SQUARE) * SQUARE + SQUARE   // next grid line below
```

If the ray points **upward** (sin α < 0, i.e. `ra > π`):
```
ry = floor(player_y / SQUARE) * SQUARE - 0.0001   // small offset so we don't land exactly on the line
```

The corresponding X:
```
rx = player_x + (player_y - ry) * (-1/tan(ra))
```

This comes from the ray equation `x = x₀ + t·cos(α)`, `y = y₀ + t·sin(α)` — we know ry, so we solve for the matching rx.

**Step 2 — How much to move each step** (to jump from one grid line to the next):
```
yo = ±SQUARE          (sign depends on direction)
xo = -yo / tan(ra)    (calculated from the ray angle)
```

Repeat until a wall cell is hit (`map[my][mx] == '1'`).

#### 5.2 Vertical Intersections

Vertical lines are at multiples of `SQUARE` on the X-axis — same logic, but flipped:

```
rx = floor(player_x / SQUARE) * SQUARE + SQUARE  // or -0.001 for left-facing
ry = player_x - rx) * (-tan(ra)) + player_y
xo = ±SQUARE
yo = -xo * tan(ra)
```

---

### 6. Euclidean Distance

After finding both intersection points `(hx, hy)` for horizontal and `(vx, vy)` for vertical, we compute the **Euclidean distance** from the player to each:

```
d = √( (x₂ - x₁)² + (y₂ - y₁)² )
```

This is the straight-line distance in 2D — the length of the diagonal of the right triangle formed by the X and Y differences.

```c
float line_length(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
```

The **shorter** distance wins: that is the actual wall hit. It also tells us whether the ray hit the top/bottom or left/right side of the wall, which matters for choosing the right texture.

---

### 7. Fisheye Correction

If you use the raw distance directly, walls look curved — rays at the edges of the FOV travel a longer path than the center ray, even when hitting the same flat wall.

**Fix:** Multiply the distance by the cosine of the angle between the current ray and the camera's forward direction:

```
corrected_distance = raw_distance * cos(player_angle - ra)
```

**Why does this work?**
`player_angle - ra` is the angle between the current ray and the center ray. Multiplying by `cos` of that angle gives the **straight distance** from the player to the wall — as if you dropped a perpendicular line to the wall. That's the distance a real camera would see, so walls look straight and flat.

This is called dot-product projection: the length of a vector projected onto another direction is `|v| · cos(θ)` where θ is the angle between them.

---

### 8. 3D Wall Height Projection

Once we have the corrected distance, we calculate how tall the wall strip should appear on screen:

```
line_h = (SQUARE * HEIGHT) / corrected_distance
```

**How this formula works:** It comes from similar triangles — the same way a camera lens works:

```
apparent_height / screen_distance = real_height / real_distance
```

`screen_distance` is 1 (built into the formula) and `real_height = SQUARE`. So:

```
line_h = SQUARE * HEIGHT / corrected_distance
```

The wall strip is then centred vertically:

```
line_start = (HEIGHT / 2) - (line_h / 2)
```

If `line_h > HEIGHT` (player is very close to a wall), it is cut to `HEIGHT` and a `ty_offset` is calculated so we only draw the part of the texture that is actually visible on screen.

---

### 9. Texture Mapping

#### 9.1 Which Texture Face?

The texture is chosen based on **which side of a wall was hit** and in **which direction** the ray was travelling:

| Hit type    | Ray direction        | Face    | Texture |
|-------------|----------------------|---------|---------|
| Horizontal  | downward (sin > 0)   | North   | north   |
| Horizontal  | upward   (sin < 0)   | South   | south   |
| Vertical    | rightward (cos > 0)  | West    | west    |
| Vertical    | leftward  (cos < 0)  | East    | east    |

(In this engine Y grows downward on screen, which flips North and South compared to a map.)

#### 9.2 Horizontal Texture Coordinate (tx)

The X position inside the texture (which column of the 64×64 image to use) is the remainder of the hit position divided by `SQUARE`:

```c
tx = (int)(hit_position) % SQUARE;
```

For some faces the texture is flipped so it faces the right way:

```c
tx = 63 - tx;   // flip for North and East
```

#### 9.3 Vertical Texture Coordinate (ty)

We move through the texture top-to-bottom as we draw each pixel of the wall strip:

```
ty_step   = SQUARE / line_h          // how much texture Y advances per screen pixel
ty_offset = (line_h - HEIGHT) / 2    // skip invisible top portion when wall fills screen
ty        = ty_offset * ty_step      // starting texture Y
```

Each rendered pixel:

```
color = texture[tx][ty]
ty += ty_step
```

---

### 10. The Minimap

The minimap is a small top-down view of the grid drawn in the corner of the screen.

**Scale factor:**
```
MM_TILE = 8    // each world SQUARE → 8×8 pixel tile on minimap
```

**Player position on minimap:**
```
px_mm = MM_MARGIN + (player_x / SQUARE) * MM_TILE
py_mm = MM_MARGIN + (player_y / SQUARE) * MM_TILE
```

The FOV cone is drawn by casting 30 rays spread from `angle - FOV/2` to `angle + FOV/2`, stepping one pixel at a time along each ray using `cos`/`sin` until hitting a wall.

---

### 11. Collision Detection

Instead of a single point, the player has a small box around them defined by a margin:

```c
// Check both sides in the movement direction
mx = (int)((x - margin) / SQUARE);
my = (int)((y - margin) / SQUARE);
// and
mx = (int)((x + margin) / SQUARE);
my = (int)((y + margin) / SQUARE);
```

X and Y collisions are checked **separately** — this lets the player slide along walls instead of stopping completely on contact.

---

### 12. Mouse Rotation

Mouse movement in X produces a rotation delta:

```c
delta_angle = delta_x * sensitivity;   // sensitivity = 0.0025 rad/pixel
player_angle += delta_angle;
```

After updating the angle, the movement vector is recomputed:

```c
player_delta_x = cos(player_angle) * 7;
player_delta_y = sin(player_angle) * 7;
```

The cursor is moved back to the center of the screen every frame (`mlx_mouse_move`) so it never reaches the edge.

---

### 13. Color Encoding

RGB colors are packed into a single 32-bit integer:

```c
int rgb_to_int(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}
```

Bits 23–16 hold Red, bits 15–8 hold Green, bits 7–0 hold Blue.
This is the format miniLibX expects when writing pixels to the image buffer.

---

### 14. Flood-Fill Map Validation

The parser checks that the map is fully surrounded by walls using a recursive **flood fill** starting from the player's position:

1. Start at `(player_x, player_y)`.
2. Mark the cell as visited (`F`).
3. Do the same for the 4 neighbors: up, down, left, right.
4. Stop when hitting a wall (`1`) or an already-visited cell.

If any visited cell ends up on the edge of the map array, the map has an opening → error.

This works the same way as the "paint bucket" tool in image editors.

---

## Instructions

### Dependencies

- GCC / cc
- GNU Make
- miniLibX (included in `minilibx-linux/`)
- libft (included in `libraries/libft/`)
- X11 development libraries: `libX11`, `libXext`
- `libm` (math), `libbsd`

On Ubuntu/Debian:
```bash
sudo apt-get install gcc make libx11-dev libxext-dev libbsd-dev
```

### Compilation

```bash
make        # compile the project
make re     # clean + recompile
make clean  # remove object files
make fclean # remove objects and binary
```

### Execution

```bash
./cub3D map_files/valid/map3.cub
```

The argument must be a `.cub` file with the following format:

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F 220,100,0
C 225,30,0

111111
100N01
100001
111111
```

Map rules:
- Characters: `1` (wall), `0` (floor), `N/S/E/W` (player spawn + orientation)
- Map must be fully enclosed by walls
- Map must be the **last** element in the file
- Exactly **one** player spawn point

### Controls

| Key            | Action              |
|----------------|---------------------|
| `W`            | Move forward        |
| `S`            | Move backward       |
| `A`            | Strafe left         |
| `D`            | Strafe right        |
| `←` / `→`     | Rotate camera       |
| Mouse X        | Rotate camera       |
| `ESC`          | Quit                |
| Window `✕`    | Quit                |

---

## Project Structure

```
cub3D/
├── Includes/
│   └── cub3d.h              # All structs, defines, prototypes
├── src/
│   ├── 01_Process/          # Main loop, setup, cleanup, error handling
│   ├── 02_Parse/            # .cub file parsing and validation
│   ├── 03_Grafic/           # Raycaster, renderer, textures, minimap
│   └── 04_Moves/            # Player movement, rotation, collision
├── Textures/                # XPM wall textures
├── map_files/               # Example .cub scene files
├── libraries/libft/         # Custom C library
├── minilibx-linux/          # miniLibX graphics library
└── Makefile
```

---

## Resources

### Ray-Casting & 3D Graphics

- **Lode's Computer Graphics Tutorial — Ray-Casting**
  https://lodev.org/cgtutor/raycasting.html
  The best beginner-friendly guide for DDA ray-casting, fisheye correction, and texture mapping.

- **3DSage — Make Your Own Raycaster** (YouTube)
  https://www.youtube.com/watch?v=gYRrGTC7GtA
  Video walkthrough that follows an approach very close to this project.

- **OneLoneCoder — Code-It-Yourself: First Person Shooter** (YouTube)
  https://www.youtube.com/watch?v=xW8skO7MFYw

### miniLibX

- **42Docs — MiniLibX**
  https://harm-smits.github.io/42docs/libs/minilibx

- **miniLibX Linux sources**
  https://github.com/42Paris/minilibx-linux

### Mathematics

- **Wikipedia — Unit Circle**
  https://en.wikipedia.org/wiki/Unit_circle

- **Wikipedia — Euclidean Distance**
  https://en.wikipedia.org/wiki/Euclidean_distance

- **Wolfenstein 3D (play in browser)**
  http://users.atw.hu/wolf3d/

### Use of AI

Claude (Anthropic) was used as an assistant during this project for:

- **Math explanations** — understanding the trigonometry behind fisheye correction.
- **Documentation** — Style with colors and formatting, text correction this README.

AI was **not** used to write the core game logic or algorithms — all raycasting, parsing, and rendering code was written by the authors.
