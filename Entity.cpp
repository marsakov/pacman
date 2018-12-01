#include "Entity.hpp"

Entity::Entity(int x, int y) {
	_x = x;
	_y = y;
	lives = 0;
	_direction = 0;
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
		lives = ent.lives;
		_direction = ent._direction;
	}
	return (*this);
}

int		Entity::moveLeft(std::string *map, char sep)
{
	if (_x > 1 && map[_y][_x - 1] != sep) {
		_x -= 1;
		return (1);
	}
	return (0);
}

int		Entity::moveRight(std::string *map, char sep, int width)
{
	if (_x < width - 1 && map[_y][_x + 1] != sep) {
		_x += 1;
		return (1);
	}
	return (0);
}

int		Entity::moveUp(std::string *map, char sep)
{
	if (_y > 1 && map[_y - 1][_x] != sep) {
		_y -= 1;
		return (1);
	}
	return (0);
}

int		Entity::moveDown(std::string *map, char sep, int height)
{
	if (_y < height - 1 && map[_y + 1][_x] != sep) {
		_y += 1;
		return (1);
	}
	return (0);
}

void	Entity::chooseDirection(Entity const *ent, std::string *map, char sep, int width, int height)
{
	_direction = 0;
	if (abs(ent->getX() - _x) > abs(ent->getY() - _y))
	{
		if (ent->getX() > _x && moveRight(map, sep, width))
			_direction = 'E';
		else if (ent->getX() < _x && moveLeft(map, sep))
			_direction = 'W';
	}
	if (_direction == 0)
	{
		if (_direction == 0 && ent->getY() > _y && moveDown(map, sep, height))
			_direction = 'S';
		else if (_direction == 0 && ent->getY() < _y && moveUp(map, sep))
			_direction = 'N';
		else if (_direction == 0 && ent->getX() > _x && moveRight(map, sep, width))
			_direction = 'E';
		else if (_direction == 0 && ent->getX() < _x && moveLeft(map, sep))
			_direction = 'W';
	}
	if (_direction == 0)
	{
		if (_direction == 0 && moveDown(map, sep, height))
			_direction = 'S';
		else if (_direction == 0 && moveUp(map, sep))
			_direction = 'N';
		else if (_direction == 0 && moveRight(map, sep, width))
			_direction = 'E';
		else if (_direction == 0 && moveLeft(map, sep))
			_direction = 'W';
	}
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

int		Entity::getDirection(void) const
{
	return (_direction);
}

