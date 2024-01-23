
#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

t_ray	rays[NUM_RAYS];

int	isRayFacingDown(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}
+2
int	isRayFacingRight(float angle)
{
	return (angle < (M_PI / 2) || angle > (M_PI * 1.5));
}

int	isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}

void	calculateSteps(float ray_angle, float *xstep, float *ystep, char axis)
{
	if (axis == 'x')
	{
		*ystep = TILE_SIZE;
		if (isRayFacingUp(ray_angle))
			*ystep *= -1;
		*xstep = TILE_SIZE / tan(ray_angle);
		if (isRayFacingLeft(ray_angle) && *xstep > 0)
			*xstep *= -1;
		if (isRayFacingRight(ray_angle) && *xstep < 0)
			*xstep *= -1;
	}
	if (axis == 'y')
	{
		*xstep = TILE_SIZE;
		if (isRayFacingLeft(ray_angle))
			*xstep *= -1;
		*ystep = TILE_SIZE / tan(ray_angle);
		if (isRayFacingUp(ray_angle) && *ystep > 0)
			*ystep *= -1;
		if (isRayFacingDown(ray_angle) && *ystep < 0)
			*ystep *= -1;
	}
}

void	wallHitParams(t_wall_hit *params)
{
	params->xstep = 0;
	params->ystep = 0;

}

void	cast_one_ray(float ray_angle, int stripId)
{
	// "constructor methods"
	normalizeAngle(&ray_angle);

	// Starts at 3 oclock and goes clockwise. 
	// int isRayFacingDown = ray_angle > 0 && ray_angle < M_PI;
	// int isRayFacingUp = !isRayFacingDown;
	// int isRayFacingRight = ray_angle < (M_PI / 2) || ray_angle > (M_PI * 1.5);
	// int isRayFacingLeft = !isRayFacingRight;

	float xstep;
	float ystep;
	float xintercept;
	float yintercept;
	t_wall_hit	params;

	wallHitParams(&params);

	//////////////////////////////////////////////
	// Horizintal ray grid intersection code.
	//////////////////////////////////////////////

	int foundHorzWallHit = false;
	float horzwall_hit_x = 0;
	float horzwall_hit_y = 0;
	int horz_wall_content = 0;

	// Find the y-coordinate of the closet horizontal grid intersection.  
	yintercept = floor(t_player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += (isRayFacingDown(ray_angle) ? TILE_SIZE : 0);

	// Find the x coordinate of the closest horizontal grid intersection
	xintercept = t_player.x + (yintercept - t_player.y) / tan(ray_angle);

	// Calculate the increment for xstep and ystep.
	calculateSteps(ray_angle, &xstep, &ystep, 'x');
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		// ...We must check one beyond
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp(ray_angle) ? -1 : 0);

		if (mapContentAt(xToCheck, yToCheck) == 1)
		{
			foundHorzWallHit = true;
			horzwall_hit_x = nextHorzTouchX;
			horzwall_hit_y = nextHorzTouchY;
			horz_wall_content = mapContentAt((yToCheck / TILE_SIZE), (xToCheck / TILE_SIZE) );
			// horz_wall_content = map[ (int)floor(yToCheck / TILE_SIZE) ][ (int)floor(xToCheck / TILE_SIZE) ];
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
	float vertwall_hit_x = 0;
	float vertwall_hit_y = 0;
	int vertwall_content = 0;

	// Find the x-coordinate of the closet horizontal grid intersection.  
	xintercept = floor(t_player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += (isRayFacingRight(ray_angle) ? TILE_SIZE : 0);

	// Find the y coordinate of the closest horizontal grid intersection
	yintercept = t_player.y + (xintercept - t_player.x) * tan(ray_angle);

	// Calculate the increment for ystep and xstep.
	calculateSteps(ray_angle, &xstep, &ystep, 'y');
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		// ...We must check one beyond
		float xToCheck = nextVertTouchX + (isRayFacingLeft(ray_angle) ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapContentAt(xToCheck, yToCheck) == 1)
		{
			foundVertWallHit = true;
			vertwall_hit_x = nextVertTouchX;
			vertwall_hit_y = nextVertTouchY;
			vertwall_content = mapContentAt((yToCheck / TILE_SIZE), (xToCheck / TILE_SIZE));
			// vertwall_content = map[ (int)floor(yToCheck / TILE_SIZE) ][ (int)floor(xToCheck / TILE_SIZE) ];
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
		? distanceBetweenPoints(t_player.x, t_player.y, horzwall_hit_x, horzwall_hit_y)
		: FLT_MAX);

	float vertHitDistance = (foundVertWallHit
		? distanceBetweenPoints(t_player.x, t_player.y, vertwall_hit_x, vertwall_hit_y)
		: FLT_MAX);

	// Only store the smallest of the distances and x and y. 
	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wall_hit_x = vertwall_hit_x;
		rays[stripId].wall_hit_y = vertwall_hit_y;
		rays[stripId].wall_hit_content = vertwall_content;
		rays[stripId].was_hit_vertical = true;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wall_hit_x = horzwall_hit_x;
		rays[stripId].wall_hit_y = horzwall_hit_y;
		rays[stripId].wall_hit_content = horz_wall_content;
		rays[stripId].was_hit_vertical = false;
	}
	rays[stripId].ray_angle = ray_angle;
	rays[stripId].is_ray_facing_down = isRayFacingDown(ray_angle);
	rays[stripId].is_ray_facing_up = isRayFacingUp(ray_angle);
	rays[stripId].is_ray_facing_left = isRayFacingLeft(ray_angle);
	rays[stripId].is_ray_facing_right = isRayFacingRight(ray_angle);
}

void castAllRays(void)
{
	float ray_angle = t_player.rotation_angle - FOV_ANGLE / 2;
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		// printf("FOV: %f StripId: %d ray_angle: %f\n", FOV_ANGLE, stripId, ray_angle);
		cast_one_ray(ray_angle, stripId);
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}


void	renderRays(t_game *game)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		t_line line = {
			t_player.x * MINIMAP_SCALE,
			t_player.y * MINIMAP_SCALE,
			rays[i].wall_hit_x * MINIMAP_SCALE,
			rays[i].wall_hit_y * MINIMAP_SCALE,
			0x00FFC8D7
		};
		drawLine(game, &line);
	}
}