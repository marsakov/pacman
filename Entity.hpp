#ifndef ENTITY_HPP
# define ENTITY_HPP

#include <iostream>
#include <cmath>

class Entity
{
	public:

		int lives;

		Entity(int x, int y);
		Entity(Entity const &ent);
		~Entity(void);

		void			setX(int x);
		void			setY(int y);
		int				getX(void) const;
		int				getY(void) const;
		int				getDirection(void) const;

		int				moveLeft(std::string *map, char sep);
		int				moveRight(std::string *map, char sep, int width);
		int				moveUp(std::string *map, char sep);
		int				moveDown(std::string *map, char sep, int height);
		void			chooseDirection(Entity const *ent, std::string *map, char sep, int width, int height);


		Entity			&operator=(Entity const &ent);

	protected:
		int				_x;
		int				_y;
		char			_direction;

};

#endif