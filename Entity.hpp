#ifndef ENTITY_HPP
# define ENTITY_HPP

#include <ncurses.h>
#include <ctime>
#include <iostream>

class Entity
{
	public:

		Entity(int x, int y, unsigned int lives);
		Entity(Entity const &ent);
		~Entity(void);

		void			setX(int x);
		void			setY(int y);
		int				getX(void) const;
		int				getY(void) const;

		int				isAlive(void) const;

		Entity			&operator=(Entity const &ent);

	protected:
		int				_x;
		int				_y;
		unsigned int	_lives;

};

#endif