
#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

t_ray	g_rays[NUM_RAYS];

int	is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	is_ray_facing_up(float angle)
{
	return (!is_ray_facing_down(angle));
}
+2
int	is_ray_facing_right(float angle)
{
	return (angle < (M_PI / 2) || angle > (M_PI * 1.5));
}

int	is_ray_facing_left(float angle)
{
	return (!is_ray_facing_right(angle));
}

void	calculate_steps(float ray_angle, float *xstep, float *ystep, char axis)
{
	if (axis == 'x')
	{
		*ystep = TILE_SIZE;
		if (is_ray_facing_up(ray_angle))
			*ystep *= -1;
		*xstep = TILE_SIZE / tan(ray_angle);
		if (is_ray_facing_left(ray_angle) && *xstep > 0)
			*xstep *= -1;
		if (is_ray_facing_right(ray_angle) && *xstep < 0)
			*xstep *= -1;
	}
	if (axis == 'y')
	{
		*xstep = TILE_SIZE;
		if (is_ray_facing_left(ray_angle))
			*xstep *= -1;
		*ystep = TILE_SIZE / tan(ray_angle);
		if (is_ray_facing_up(ray_angle) && *ystep > 0)
			*ystep *= -1;
		if (is_ray_facing_down(ray_angle) && *ystep < 0)
			*ystep *= -1;
	}
}

void	wall_hit_params(t_wall_hit *params)
{
	params->xstep = 0.0;
	params->ystep = 0.0;
	params->found_wall_hit = 0;
	params->wall_hit_x = 0.0;
	params->wall_hit_y = 0.0;
	params->wall_content = 0;
	params->next_touch_x = 0.0;
	params->next_touch_y = 0.0;
	params->is_vertical = 0;
}

void	cast_one_ray(float ray_angle, int stripId)
{
	// "constructor methods"
	normalizeAngle(&ray_angle);

	// Starts at 3 oclock and goes clockwise. 
	// int is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	// int is_ray_facing_up = !is_ray_facing_down;
	// int is_ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > (M_PI * 1.5);
	// int is_ray_facing_left = !is_ray_facing_right;

	float xstep;
	float ystep;
	float xintercept;
	float yintercept;
	t_wall_hit	params;

	wall_hit_params(&params);

	//////////////////////////////////////////////
	// Horizintal ray grid intersection code.
	//////////////////////////////////////////////

	int foundHorzWallHit = false;
	float horzwall_hit_x = 0;
	float horzwall_hit_y = 0;
	int horz_wall_content = 0;

	// Find the y-coordinate of the closet horizontal grid intersection.  
	yintercept = floor(t_player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += (is_ray_facing_down(ray_angle) ? TILE_SIZE : 0);

	// Find the x coordinate of the closest horizontal grid intersection
	xintercept = t_player.x + (yintercept - t_player.y) / tan(ray_angle);

	// Calculate the increment for xstep and ystep.
	calculate_steps(ray_angle, &xstep, &ystep, 'x');
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (is_inside_map(nextHorzTouchX, nextHorzTouchY))
	{
		// ...We must check one beyond
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (is_ray_facing_up(ray_angle) ? -1 : 0);

		if (map_content_at(xToCheck, yToCheck) == 1)
		{
			foundHorzWallHit = true;
			horzwall_hit_x = nextHorzTouchX;
			horzwall_hit_y = nextHorzTouchY;
			horz_wall_content = map_content_at((yToCheck / TILE_SIZE), (xToCheck / TILE_SIZE) );
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
	xintercept += (is_ray_facing_right(ray_angle) ? TILE_SIZE : 0);

	// Find the y coordinate of the closest horizontal grid intersection
	yintercept = t_player.y + (xintercept - t_player.x) * tan(ray_angle);

	// Calculate the increment for ystep and xstep.
	calculate_steps(ray_angle, &xstep, &ystep, 'y');
	// Ask is that a wall for each ystep and xstep, if yes, get the distance, but therei s a catch....
	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	//Inc xstep and ystep until wall is found
	while (is_inside_map(nextVertTouchX, nextVertTouchY))
	{
		// ...We must check one beyond
		float xToCheck = nextVertTouchX + (is_ray_facing_left(ray_angle) ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (map_content_at(xToCheck, yToCheck) == 1)
		{
			foundVertWallHit = true;
			vertwall_hit_x = nextVertTouchX;
			vertwall_hit_y = nextVertTouchY;
			vertwall_content = map_content_at((yToCheck / TILE_SIZE), (xToCheck / TILE_SIZE));
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
		g_rays[stripId].distance = vertHitDistance;
		g_rays[stripId].wall_hit_x = vertwall_hit_x;
		g_rays[stripId].wall_hit_y = vertwall_hit_y;
		g_rays[stripId].wall_hit_content = vertwall_content;
		g_rays[stripId].was_hit_vertical = true;
	}
	else
	{
		g_rays[stripId].distance = horzHitDistance;
		g_rays[stripId].wall_hit_x = horzwall_hit_x;
		g_rays[stripId].wall_hit_y = horzwall_hit_y;
		g_rays[stripId].wall_hit_content = horz_wall_content;
		g_rays[stripId].was_hit_vertical = false;
	}
	g_rays[stripId].ray_angle = ray_angle;
	g_rays[stripId].is_ray_facing_down = is_ray_facing_down(ray_angle);
	g_rays[stripId].is_ray_facing_up = is_ray_facing_up(ray_angle);
	g_rays[stripId].is_ray_facing_left = is_ray_facing_left(ray_angle);
	g_rays[stripId].is_ray_facing_right = is_ray_facing_right(ray_angle);
}

void cast_all_rays(void)
{
	float ray_angle = t_player.rotation_angle - FOV_ANGLE / 2;
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		// printf("FOV: %f StripId: %d ray_angle: %f\n", FOV_ANGLE, stripId, ray_angle);
		cast_one_ray(ray_angle, stripId);
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}

void	render_rays(t_game *game)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		t_line line = {
			t_player.x * MINIMAP_SCALE,
			t_player.y * MINIMAP_SCALE,
			g_rays[i].wall_hit_x * MINIMAP_SCALE,
			g_rays[i].wall_hit_y * MINIMAP_SCALE,
			0x00FFC8D7
		};
		drawLine(game, &line);
	}
}