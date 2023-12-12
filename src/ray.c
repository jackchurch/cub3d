
#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

ray_t	rays[NUM_RAYS];

int	isRayFacingDown(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}

int	isRayFacingRight(float angle)
{
	return (angle < (M_PI / 2) || angle > (M_PI * 1.5));
}

int	isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}

void cast_one_ray(float rayAngle, int stripId)
{
	// "constructor methods"
	normalizeAngle(&rayAngle);

	// Starts at 3 oclock and goes clockwise. 
	// int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	// int isRayFacingUp = !isRayFacingDown;
	// int isRayFacingRight = rayAngle < (M_PI / 2) || rayAngle > (M_PI * 1.5);
	// int isRayFacingLeft = !isRayFacingRight;

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
	yintercept = floor(t_player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += (isRayFacingDown(rayAngle) ? TILE_SIZE : 0);

	// Find the x coordinate of the closest horizontal grid intersection
	xintercept = t_player.x + (yintercept - t_player.y) / tan(rayAngle);

	// Calculate the increment for xstep and ystep.
	ystep = TILE_SIZE;
	ystep *= (isRayFacingUp(rayAngle) ? -1 : 1);

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= ((isRayFacingLeft(rayAngle) && xstep > 0) ? -1 : 1);
	xstep *= ((isRayFacingRight(rayAngle) && xstep < 0) ? -1 : 1);
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		// ...We must check one beyond
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp(rayAngle) ? -1 : 0);

		if (mapContentAt(xToCheck, yToCheck) == 1)
		{
			foundHorzWallHit = true;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = mapContentAt((yToCheck / TILE_SIZE), (xToCheck / TILE_SIZE) );
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
	xintercept = floor(t_player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += (isRayFacingRight(rayAngle) ? TILE_SIZE : 0);

	// Find the y coordinate of the closest horizontal grid intersection
	yintercept = t_player.y + (xintercept - t_player.x) * tan(rayAngle);

	// Calculate the increment for ystep and xstep.
	xstep = TILE_SIZE;
	xstep *= (isRayFacingLeft(rayAngle) ? -1 : 1);

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= ((isRayFacingUp(rayAngle) && ystep > 0) ? -1 : 1);
	ystep *= ((isRayFacingDown(rayAngle) && ystep < 0) ? -1 : 1);
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		// ...We must check one beyond
		float xToCheck = nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapContentAt(xToCheck, yToCheck) == 1)
		{
			foundVertWallHit = true;
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = mapContentAt((yToCheck / TILE_SIZE), (xToCheck / TILE_SIZE));
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
		? distanceBetweenPoints(t_player.x, t_player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX);

	float vertHitDistance = (foundVertWallHit
		? distanceBetweenPoints(t_player.x, t_player.y, vertWallHitX, vertWallHitY)
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
	rays[stripId].isRayFacingDown = isRayFacingDown(rayAngle);
	rays[stripId].isRayFacingUp = isRayFacingUp(rayAngle);
	rays[stripId].isRayFacingLeft = isRayFacingLeft(rayAngle);
	rays[stripId].isRayFacingRight = isRayFacingRight(rayAngle);
}

void castAllRays(void)
{
	float rayAngle = t_player.rotationAngle - FOV_ANGLE / 2;
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		// printf("FOV: %f StripId: %d RayAngle: %f\n", FOV_ANGLE, stripId, rayAngle);
		cast_one_ray(rayAngle, stripId);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}


void	renderRays(t_game *game)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		t_line line = {
			t_player.x * MINIMAP_SCALE,
			t_player.y * MINIMAP_SCALE,
			rays[i].wallHitX * MINIMAP_SCALE,
			rays[i].wallHitY * MINIMAP_SCALE,
			0x00FFC8D7
		};
		drawLine(game, &line);
	}
}