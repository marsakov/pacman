#include "Entity.hpp"
#include <cmath>
#include <ncurses.h>

Entity *player = new Entity(1, 1, 3);
Entity *enemy1 = new Entity(44, 15, 3);
Entity *enemy2 = new Entity(1, 15, 3);
int width = 17;
int height = 47;

std::string map[] = {
"||||||||||||||||||||||||||||||||||||||||||||||",
"|                                            |",
"| |||||||||| | |||||||||||||||| | |||||||||| |",
"|            |        ||        |            |",
"|||||||||||| |||||||| || |||||||| ||||||||||||",
"           | |                  | |           ",
"|||||||||||| | | |||||  ||||| | | ||||||||||||",
"|              | |          | |              |",
"|  ||||||||| | | |    **    | | | |||||||||  |",
"|            | | |||||||||||| | |            |",
"|||||||||||||| |              | ||||||||||||||",
"|                ||||||||||||                |",
"| ||||||||   |   |          |   |   |||||||| |",
"|        | | | | | |||||||| | | | | |        |",
"|||||||| | | | | |    ||    | | | | | ||||||||",
"|            |                  |            |",
"||||||||||||||||||||||||||||||||||||||||||||||",
};

void	init( void ) {

	initscr();
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);

	cbreak();
	nodelay(stdscr, true);
	keypad(stdscr, TRUE);
	curs_set(0);
	refresh();

	attron(COLOR_PAIR(1));
	mvprintw(LINES / 2, COLS / 2 - 10, "Press [ENTER] to start game");
	attroff(COLOR_PAIR(2));
	char c = 0;
	while (c != '\n')
		c = getch();
	mvprintw(LINES / 2, 0, "%*.*s", COLS, COLS - 1, " ");
	nodelay(stdscr, true);
}

void	movePlayer( void ) {
	int c;

	if ((c = getch()) != 'q')
	{
		map[player->getY()][player->getX()] = ' ';
		if (c == KEY_LEFT && player->getX() > 0 && map[player->getY()][player->getX() - 1] != '|')
			player->setX(player->getX() - 1);
		if (c == KEY_RIGHT && player->getX() < 46 && map[player->getY()][player->getX() + 1] != '|')
			player->setX(player->getX() + 1);
		if (c == KEY_UP && player->getY() > 1 && map[player->getY() - 1][player->getX()] != '|')
			player->setY(player->getY() - 1);
		if (c == KEY_DOWN && player->getY() < 17 && map[player->getY() + 1][player->getX()] != '|')
			player->setY(player->getY() + 1);
		if (map[player->getY()][player->getX()] == '*')
		{
			c = 0;
			mvprintw(LINES / 2, COLS / 2 - 10, "YOU WON [press ENTER]");
			while (c != '\n')
				c = getch();
			endwin();
			exit(0);
		}
		map[player->getY()][player->getX()] = '@';
	}
	else
	{
		endwin();
		exit(0);
	}
}

void	moveEnemies( void ) {
	
	map[enemy1->getY()][enemy1->getX()] = ' ';
	map[enemy2->getY()][enemy2->getX()] = ' ';

	if (abs(player->getX() - enemy1->getX()) > abs(player->getY() - enemy1->getY()))
	{
		if (player->getX() > enemy1->getX() && map[enemy1->getY()][enemy1->getX() + 1] == ' ')
			enemy1->setX(enemy1->getX() + 1);
		else if (player->getX() < enemy1->getX() && map[enemy1->getY()][enemy1->getX() - 1] == ' ')
			enemy1->setX(enemy1->getX() - 1);
	}
	else if (abs(player->getX() - enemy1->getX()) < abs(player->getY() - enemy1->getY()))
	{
		if (player->getY() > enemy1->getY() && map[enemy1->getY() + 1][enemy1->getX()] == ' ')
			enemy1->setY(enemy1->getY() + 1);
		else if (player->getY() < enemy1->getY() && map[enemy1->getY() - 1][enemy1->getX()] == ' ')
			enemy1->setY(enemy1->getY() - 1);
	}

	if (abs(player->getX() - enemy2->getX()) > abs(player->getY() - enemy2->getY()))
	{
		if (player->getX() > enemy2->getX() && map[enemy2->getY()][enemy2->getX() + 1] == ' ')
			enemy2->setX(enemy2->getX() + 1);
		else if (player->getX() < enemy2->getX() && map[enemy2->getY()][enemy2->getX() - 1] == ' ')
			enemy2->setX(enemy2->getX() - 1);
	}
	else if (abs(player->getX() - enemy2->getX()) < abs(player->getY() - enemy2->getY()))
	{
		if (player->getY() > enemy2->getY() && map[enemy2->getY() + 1][enemy2->getX()] == ' ')
			enemy2->setY(enemy2->getY() + 1);
		else if (player->getY() < enemy2->getY() && map[enemy2->getY() - 1][enemy2->getX()] == ' ')
			enemy2->setY(enemy2->getY() - 1);
	}

	map[enemy1->getY()][enemy1->getX()] = 'o';
	map[enemy2->getY()][enemy2->getX()] = 'o';

}

int main(int argc, char const *argv[])
{
	int	loop_counter = 0;

	init();
	map[enemy1->getY()][enemy1->getX()] = 'o';
	map[enemy2->getY()][enemy2->getX()] = 'o';
	map[player->getY()][player->getX()] = '@';
	while (player->isAlive())
	{
		// if (loop_counter % 1000 == 0)
		map[enemy1->getY()][enemy1->getX()] = 'o';
		map[enemy2->getY()][enemy2->getX()] = 'o';
			moveEnemies();
		movePlayer();
		for (int i = 0; i < 17; i++)
			mvprintw(LINES / 2 - 9 + i, COLS / 2 - 24, strdup(map[i].c_str()));
		refresh();
		loop_counter++;
	}
	// nodelay(stdscr, false);
	return (0);
}
