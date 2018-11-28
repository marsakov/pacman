#include "Entity.hpp"

Entity::Entity(int x, int y, unsigned int lives) {
	_x = x;
	_y = y;
	_lives = lives;
}

Entity::Entity(Entity const &ent)
{
	*this = ent;
}

Entity::~Entity(void)
{
}


Entity	&Entity::operator=(Entity const &ent)
{
	if (this != &ent)
	{
		_x = ent._x;
		_y = ent._y;
		_lives = 0;
	}
	return (*this);
}

void	Entity::setX(int x)
{
	_x = x;
}

void	Entity::setY(int y)
{
	_y = y;
}

int		Entity::getX(void) const
{
	return (_x);
}

int		Entity::getY(void) const
{
	return (_y);
}

int		Entity::isAlive(void) const
{
	return (_lives > 0);
}
