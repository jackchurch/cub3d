#include "../inc/cub3d.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct Player {
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} player;

struct Ray {
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int wasHitVertical;
	int isRayFacingUp;
	int isRayFacingDown;
	int isRayFacingLeft;
	int isRayFacingRight;
	int wallHitContent;
} rays[NUM_RAYS];


void setup()
{
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.width = 1;
	player.height = 1;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.rotationAngle = HALF_PI;
	player.walkSpeed = 10;
	player.turnSpeed = ONE_PI / 180 * player.walkSpeed;
}

void	drawRect(t_game *game, t_rectangle *rect)
{
	int	i;
	int	j;
	
	i = rect->x;
	while (i <= (rect->x + rect->width))
	{
		j = rect->y;
		while (j <= (rect->y + rect->height))
		{
			mlx_pixel_put(game->mlx, game->win, i, j, rect->color);
			j++;
		}
		i++;
	}
	return ;
}

void drawLine(t_game *game, t_line *line) {
    
	int x0 = line->x0;
	int y0 = line->y0;
	int x1 = line->x1;
	int y1 = line->y1;
	int color = line->color;
	int deltaX = (x1 - x0);
    int deltaY = (y1 - y0);

    int longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float)longestSideLength;
    float yIncrement = deltaY / (float)longestSideLength;

    float currentX = x0;
    float currentY = y0;

    for (int i = 0; i < longestSideLength; i++) {
		mlx_pixel_put(game->mlx, game->win, round(currentX), round(currentY), color);
        currentX += xIncrement;
        currentY += yIncrement;
    }
}

void	safe_exit(t_game *game)
{
	if (game->win)
		free(game->win);
	if (game->mlx)
		free(game->mlx);
	if (game)
		free(game);
	exit(0);
}

void	renderPlayer(t_game *game)
{
	t_rectangle playerRect = {
		player.x * MINIMAP_SCALE,
		player.y * MINIMAP_SCALE,
		player.width * MINIMAP_SCALE,
		player.height * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawRect(game, &playerRect);

	t_line playerLine = {
		player.x * MINIMAP_SCALE,
		player.y * MINIMAP_SCALE,
		(player.x + cos(player.rotationAngle) * 40) * MINIMAP_SCALE,
		(player.y + sin(player.rotationAngle) * 40) * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawLine(game, &playerLine);
}

int	mapContentAt(float x, float y)
{
	int mapGridIndexX = (int)floor(x / TILE_SIZE);
	int mapGridIndexY = (int)floor(y / TILE_SIZE);
	return (map[mapGridIndexY][mapGridIndexX]);
}

// bool mapHasWallAt(float x, float y)
// {
// 	// IF out of bounds return true. 
// 	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
// 		return (true);
// 	int mapGridIndexX = floor(x / TILE_SIZE);
// 	int mapGridIndexY = floor(y / TILE_SIZE);
// 	// IF wall collision, return true
// 	if (map[mapGridIndexY][mapGridIndexX] != 0)
// 		return (true);
// 	return (false);
// }

void	movePlayer(t_game *game)
{
	if (!game)
		return ;
	player.rotationAngle += player.turnDirection * player.turnSpeed;
	float moveStep = player.walkDirection * player.walkSpeed;
	float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
	float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;


	if (mapContentAt(newPlayerX, newPlayerY) != 1)
	{
		player.x = newPlayerX;
		player.y = newPlayerY;
	}
}

float normalizeAngle(float rayAngle)
{
	rayAngle = remainder(rayAngle, TWO_PI);
	if (rayAngle < 0)
		rayAngle = TWO_PI + rayAngle;
	return (rayAngle);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) ) );
}

void castRay(float rayAngle, int stripId)
{
	// "constructor methods"
	rayAngle = normalizeAngle(rayAngle);

	// Starts at 3 oclock and goes clockwise. 
	int isRayFacingDown = rayAngle > 0 && rayAngle < ONE_PI;
	int isRayFacingUp = !isRayFacingDown;
	int isRayFacingRight = rayAngle < HALF_PI || rayAngle > (ONE_PI * 1.5);
	int isRayFacingLeft = !isRayFacingRight;

	float xstep;
	float ystep;
	float xintercept;
	float yintercept;

	//////////////////////////////////////////////
	// Horizintal ray grid intersection code.
	//////////////////////////////////////////////
	int foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	// Find the y-coordinate of the closet horizontal grid intersection.  
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += (isRayFacingDown ? TILE_SIZE : 0);

	// Find the x coordinate of the closest horizontal grid intersection
	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	// Calculate the increment for xstep and ystep.
	ystep = TILE_SIZE;
	ystep *= (isRayFacingUp ? -1 : 1);

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= ((isRayFacingLeft && xstep > 0) ? -1 : 1);
	xstep *= ((isRayFacingRight && xstep < 0) ? -1 : 1);
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)
	{
		// ...We must check one beyond
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (mapContentAt(xToCheck, yToCheck) == 1)
		{
			foundHorzWallHit = true;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = mapContentAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE) );
			// horzWallContent = map[ (int)floor(yToCheck / TILE_SIZE) ][ (int)floor(xToCheck / TILE_SIZE) ];
			break ;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	//////////////////////////////////////////////
	// Vertical ray grid intersection code.
	//////////////////////////////////////////////
	int foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	// Find the x-coordinate of the closet horizontal grid intersection.  
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += (isRayFacingRight ? TILE_SIZE : 0);

	// Find the y coordinate of the closest horizontal grid intersection
	yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

	// Calculate the increment for ystep and xstep.
	xstep = TILE_SIZE;
	xstep *= (isRayFacingLeft ? -1 : 1);

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= ((isRayFacingUp && ystep > 0) ? -1 : 1);
	ystep *= ((isRayFacingDown && ystep < 0) ? -1 : 1);
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT)
	{
		// ...We must check one beyond
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapContentAt(xToCheck, yToCheck) == 1)
		{
			foundVertWallHit = true;
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = mapContentAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			// vertWallContent = map[ (int)floor(yToCheck / TILE_SIZE) ][ (int)floor(xToCheck / TILE_SIZE) ];
			break ;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}
	
	// Calculate both horizontal and vertical distances and choose the smaller.
	float horzHitDistance = (foundHorzWallHit
		? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX);

	float vertHitDistance = (foundVertWallHit
		? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
		: FLT_MAX);

	// Only store the smallest of the distances and x and y. 
	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].wallHitContent = vertWallContent;
		rays[stripId].wasHitVertical = true;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].wallHitContent = horzWallContent;
		rays[stripId].wasHitVertical = false;
	}
	rays[stripId].rayAngle = rayAngle;
	rays[stripId].isRayFacingDown = isRayFacingDown;
	rays[stripId].isRayFacingUp = isRayFacingUp;
	rays[stripId].isRayFacingLeft = isRayFacingLeft;
	rays[stripId].isRayFacingRight = isRayFacingRight;
}

void castAllRays()
{
	float rayAngle = player.rotationAngle - FOV_ANGLE / 2;
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		// printf("FOV: %f StripId: %d RayAngle: %f\n", FOV_ANGLE, stripId, rayAngle);
		castRay(rayAngle, stripId);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

void renderMap(t_game *game)
{
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE; 
			int tileY = i * TILE_SIZE;
			int _mapContent = mapContentAt(i, j);
			int tileColor = (_mapContent != 0 ? 0x000000FF : 0x00FFFFFF);
			t_rectangle mapTileRect = {
				tileX * MINIMAP_SCALE, 
				tileY * MINIMAP_SCALE, 
				TILE_SIZE * MINIMAP_SCALE, 
				TILE_SIZE * MINIMAP_SCALE, 
				tileColor
			};
			drawRect(game, &mapTileRect);
		}
	}
}

void	renderRays(t_game *game)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		t_line line = {
			player.x * MINIMAP_SCALE,
			player.y * MINIMAP_SCALE,
			rays[i].wallHitX * MINIMAP_SCALE,
			rays[i].wallHitY * MINIMAP_SCALE,
			0x00FFC8D7
		};
		drawLine(game, &line);
	}
}

// 320 pixls window width
// 60 deg FOV -> must convert to rads
//
// while (column < 320width)
// {
// 	cast a ray
// 	trace the ray until it intersects with a wall (map[i][j] == 1)
// 	record the intersection x,y and ray distance
// 	add angle increment to go to the next ray (rayangle += 60/320) -> convert 60 deg into rads
// }

int	key_release(int keycode)
{
	if (keycode == LEFT)
		player.turnDirection = 0;
	else if (keycode == RIGHT)
		player.turnDirection = 0;
	else if (keycode == UP)
		player.walkDirection = 0;
	else if (keycode == DOWN)
		player.walkDirection = 0;
	return (0);
}


void drawCeling(t_game *game)
{
	t_rectangle celing = {
		.x = 0,
		.y = 0,
		.width = WINDOW_WIDTH,
		.height = WINDOW_HEIGHT / 2,
		.color = 0x00FAF0E6
	};
	drawRect(game, &celing);

	t_rectangle floor = {
		.x = 0,
		.y = WINDOW_HEIGHT / 2,
		.width = WINDOW_WIDTH,
		.height = WINDOW_HEIGHT / 2,
		.color = 0x008B9E8A
	};
	drawRect(game, &floor);

}

void	generate3DProjection(t_game *game)
{
	drawCeling(game);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		float correctedDistance = rays[i].distance * cos(rays[i].rayAngle - player.rotationAngle);
		float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWallHeight = (TILE_SIZE / correctedDistance) * distanceProjPlane;
		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;


		int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallTopPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

		int _color;
		if (rays[i].isRayFacingDown && !rays[i].wasHitVertical)
			_color = 0x0000FFFF;
		if (rays[i].isRayFacingUp && !rays[i].wasHitVertical)
			_color = 0x00FFFF00;
		if (rays[i].isRayFacingLeft && rays[i].wasHitVertical)
			_color = 0x00FF00FF;
		if (rays[i].isRayFacingRight && rays[i].wasHitVertical)
			_color = 0x0000FF00;
		t_rectangle rect = {
			.x = i,
			.y = WINDOW_HEIGHT / 2 - wallStripHeight / 2, 
			.width = 1,
			.height = wallStripHeight,
			.color = _color
		};
		drawRect(game, &rect);
	}
}

void	render(t_game *game)
{
	movePlayer(game);
	renderMap(game);
	renderPlayer(game);
	castAllRays();
	// renderRays(game);
	generate3DProjection(game);

}
int	key_hook(int keycode, t_game *game)
{
	if (keycode == LEFT)
		player.turnDirection = -1;
	else if (keycode == RIGHT)
		player.turnDirection = 1;
	else if (keycode == UP)
		player.walkDirection = 1;
	else if (keycode == DOWN)
		player.walkDirection = -1;
	else if (keycode == ESC)
		safe_exit(game);
	// renderPlayer(game);
	// movePlayer(game);
	// renderMap(game);
	// renderPlayer(game);
	render(game);
	return (0);
}

bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		safe_exit(game);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Legally Distinct Slï'mę Game");
	if (!game->win)
		safe_exit(game);
	mlx_hook(game->win, 2, 0, key_hook, game);
	mlx_hook(game->win, 3, 0, key_release, game);

	return (true);
}

int	main(void)
{
	t_game *game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	init_window(game);
	setup();

	// process_input(); // See keyhooks
	// update(game); // Add FPS if have time. 
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
