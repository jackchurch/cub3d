# Sort out. or: remove as globals
int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
Player {
Ray {

# Move functions into seperate files

## Main
main(void)
safe_exit(t_game *game)
setup() — must change

## Mlx
init_window(t_game *game)
key_hook(int keycode, t_game *game)
key_release(int keycode)

## Map
renderMap(t_game *game)
mapContentAt(float x, float y)

## Maths
normalizeAngle(float rayAngle)
istanceBetweenPoints(float x1, float y1, float x2, float y2)


## Ray
castRay(float rayAngle, int stripId)
renderRays(t_game *game) — can remove


## Player
movePlayer(t_game *game)

## Render
renderPlayer(t_game *game)
drawCeling(t_game *game)
generate3DProjection(t_game *game)
render(t_game *game)

## Render utils
drawRect(t_game *game, t_rectangle *rect)
drawLine(t_game *game, t_line *line) {