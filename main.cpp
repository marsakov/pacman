#include "Entity.hpp"
#include <ncurses.h>

Entity *player = new Entity(25, 1);
Entity *enemies[4] = {new Entity(44, 15), new Entity(1, 15), new Entity(1, 7), new Entity(44, 7)};
int amountEnemies = 4;
int width = 47;
int height = 17;
int stars = 0;

std::string map[] = {
"||||||||||||||||||||||||||||||||||||||||||||||",
"| *    *    *    *          *    *    *    * |",
"| |||||||||| | |||||||||||||||| | |||||||||| |",
"| *    *    *    *    ||    *    *    *    * |",
"|||||||||||| |||||||| || |||||||| ||||||||||||",
"           |*    *   *  *   *    *|           ",
"|||||||||||| | | |||||  ||||| | | ||||||||||||",
"| *    *    *  | | *      * | |  *    *    * |",
"|  ||||||||| | | |   [__]   | | | |||||||||  |",
"| *    *    *  | |||||||||||| |  *    *    * |",
"|||||||||||||| | *   *  *   * | ||||||||||||||",
"| *    *         ||||||||||||         *    * |",
"| ||||||||   |*    *      *    *|   |||||||| |",
"| *    *   | | |   ||||||||   | | |   *    * |",
"|||||||| | | | | |    ||    | | | | | ||||||||",
"| *    *    *|  *   *    *   *  |*    *    * |",
"||||||||||||||||||||||||||||||||||||||||||||||",
};

void	init( void ) {

	initscr();
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		curs_set(1);
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

void	exitFunc(int wonOrLose) {
	int c = 0;

	if (wonOrLose == 1)
	{
		attron(COLOR_PAIR(1));
		mvprintw(LINES / 2, COLS / 2 - 10, "YOU WON [press ENTER]");
		attroff(COLOR_PAIR(1));
	}
	else
	{
		attron(COLOR_PAIR(4));
		mvprintw(LINES / 2, COLS / 2 - 10, "YOU LOSE [press ENTER]", stars);
		attron(COLOR_PAIR(4));
	}
	while (c != '\n')
		c = getch();
	curs_set(1);
	endwin();
	exit(0);
}

void	movePlayer( void ) {
	int c;

	if ((c = getch()) != 'q' && c != 'Q')
	{
		map[player->getY()][player->getX()] = ' ';
		if (c == KEY_LEFT)
			player->moveLeft(map, '|');
		if (c == KEY_RIGHT)
			player->moveRight(map, '|', width);
		if (c == KEY_UP)
			player->moveUp(map, '|');
		if (c == KEY_DOWN)
			player->moveDown(map, '|', height);
		if (map[player->getY()][player->getX()] == '_' || map[player->getY()][player->getX()] == 'o')
		{
			if (map[player->getY()][player->getX()] == '_')
				exitFunc(1);
			else
				exitFunc(0);
		}
		if (map[player->getY()][player->getX()] == '*')
			stars++;
		map[player->getY()][player->getX()] = '@';
	}
	else
	{
		curs_set(1);
		endwin();
		exit(0);
	}
}

void	moveEnemies( void ) {

	for (int i = 0; i < amountEnemies; i++) {
		map[enemies[i]->getY()][enemies[i]->getX()] = ' ';
		switch (enemies[i]->getDirection()) {
			case 'E':
				if (!enemies[i]->moveRight(map, '|', width))
					enemies[i]->chooseDirection(player, map, '|', width, height);
				break;
			case 'W':
				if (!enemies[i]->moveLeft(map, '|'))
					enemies[i]->chooseDirection(player, map, '|', width, height);
				break;
			case 'N':
				if (!enemies[i]->moveUp(map, '|'))
					enemies[i]->chooseDirection(player, map, '|', width, height);
				break;
			case 'S':
				if (!enemies[i]->moveDown(map, '|', height))
					enemies[i]->chooseDirection(player, map, '|', width, height);
		}

		if (map[enemies[i]->getY()][enemies[i]->getX()] == '@')
		{
			--player->lives;
			if (player->lives <= 0) {
				exitFunc(0);
			}
		}
		map[enemies[i]->getY()][enemies[i]->getX()] = 'o';
	}

}

int main(int argc, char const *argv[])
{
	int	loop_counter = 0;

	init();
	map[player->getY()][player->getX()] = '@';
	player->lives = 3;

	for (int i = 0; i < amountEnemies; i++) {
		enemies[i]->chooseDirection(player, map, '|', width, height);
		map[enemies[i]->getY()][enemies[i]->getX()] = 'o';
	}

	while (player->lives > 0)
	{
		if (loop_counter % 5000 == 0)
			moveEnemies();
		movePlayer();
		for (int i = 0; i < 17; i++)
			mvprintw(LINES / 2 - 9 + i, COLS / 2 - 24, strdup(map[i].c_str()));

		attron(COLOR_PAIR(3));
		mvprintw(1, 1, "STARS : %d", stars);
		mvprintw(LINES / 2 - 9 + player->getY(), COLS / 2 - 24 + player->getX(), "@");
		mvprintw(2, 1, "LIVES : %d", player->lives);
		attroff(COLOR_PAIR(3));

		for (int i = 0; i < amountEnemies; i++) {
			attron(COLOR_PAIR(2));
			mvprintw(LINES / 2 - 9 + enemies[i]->getY(), COLS / 2 - 24 + enemies[i]->getX(), "o");
			attroff(COLOR_PAIR(2));
		}
		refresh();
		loop_counter++;
	}
	curs_set(1);
	endwin();
	return (0);
}
