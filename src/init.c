#include "../inc/cub3d.h"

void setup()
{
	t_player.x = WINDOW_WIDTH / 2;
	t_player.y = WINDOW_HEIGHT / 2;
	t_player.width = 1;
	t_player.height = 1;
	t_player.turnDirection = 0;
	t_player.walkDirection = 0;
	t_player.rotationAngle = M_PI / 2;
	t_player.walkSpeed = 10;
	t_player.turnSpeed = M_PI / 180 * t_player.walkSpeed;
}