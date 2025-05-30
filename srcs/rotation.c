#include "../include/tetris.h"

void rotate_tetromino(t_tetris *tetris)
{
	float pivot_x = (float)tetris->current->coord[0].x;
	float pivot_y = (float)tetris->current->coord[0].y;
	float	x_rel;
	float y_rel;
	float	new_x;
	float new_y;
	int	i = 0;
	int	rot;
	t_coord *temp;

	if (tetris->current->type == O_PIECE)
	{
		tetris->current->times_moved++;
		return ;
	}
	if (tetris->current->type == I_PIECE)
	{
 		switch (tetris->current->orientation)
		{
			case LEFT:
			{
				pivot_x = (float)(tetris->current->coord[0].x + tetris->current->coord[3].x) / 2;
				pivot_y = (float)(tetris->current->coord[0].y + tetris->current->coord[0].y + 1) / 2;
				rot = UP;
				break;
			}

			case UP:
			{
				pivot_x = (float)(tetris->current->coord[0].x + tetris->current->coord[0].x - 1) / 2;
				pivot_y = (float)(tetris->current->coord[0].y + tetris->current->coord[3].y) / 2;
				rot = RIGHT;
				break;
			}
			case RIGHT:
			{
				pivot_x = (float)(tetris->current->coord[0].x + tetris->current->coord[3].x) / 2;
				pivot_y = (float)(tetris->current->coord[0].y + tetris->current->coord[0].y - 1) / 2;
				rot = DOWN;
				break;
			}	
			case DOWN:
			{
				pivot_x = (float)(tetris->current->coord[0].x + tetris->current->coord[0].x + 1) / 2;
				pivot_y = (float)(tetris->current->coord[0].y + tetris->current->coord[3].y) / 2;
				rot = LEFT;
				break;
			}
		}
		i = -1;
	}
	else
	{
		pivot_x = (float)tetris->current->coord[0].x;
		pivot_y = (float)tetris->current->coord[0].y;
	}
	temp = malloc(4 * sizeof(t_coord));
	if (!temp)
		close_game(tetris, 1, true);
	while (++i < 4)
	{
		x_rel = (float)tetris->current->coord[i].x - pivot_x;
		y_rel = (float)tetris->current->coord[i].y - pivot_y;
		
		new_x = -y_rel;
		new_y = x_rel;

		temp[i].x = (int)round(new_x + pivot_x);
		temp[i].y = (int)round(new_y + pivot_y);
	}
	if (tetris->current->type != I_PIECE)
	{
		temp[0].x = tetris->current->coord[0].x;
		temp[0].y = tetris->current->coord[0].y;
	}
	else
		tetris->current->orientation = rot;
	if (manage_collision(tetris, temp))
	{
		free(temp);
		return ;
	}
	i = -1;
	while (++i < 4)
		tetris->map[tetris->current->coord[i].y][tetris->current->coord[i].x] = EMPTY;
	free(tetris->current->coord);
	tetris->current->coord = temp;
	load_current_tetromino(tetris);
	tetris->time_since_last = 0.0f;
	if (++tetris->current->times_moved)
		check_lock(tetris);
}
