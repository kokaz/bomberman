#include "Ground.hpp"
#include "Pan.hpp"

Ground::Ground(const float x, const float y)
  : _vec(x, y)
{
  _obj = new Pan(IEntity::GROUND);
  _obj->translate(glm::vec3(x, -0.5f, y));
  _obj->scale(glm::vec3(0.5f, 0.5f, 1.0));
  _obj->rotate(glm::vec3(1, 0, 0), 90.0);
}

Ground::~Ground()
{

}

float	Ground::getPosX() const
{
  return _vec.x;
}

float	Ground::getPosY() const
{
  return _vec.y;
}

void	Ground::setPosX(const float x)
{
  _vec.x = x;
}

void	Ground::setPosY(const float y)
{
  _vec.y = y;
}

AObject	*Ground::getObj()
{
  return _obj;
}

void Ground::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}
