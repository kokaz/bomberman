#include "Box.hpp"

Box::Box(const glm::vec2 &pos) : _vec(pos)
{
  _status = OK;
  _obj = new Cube();
  _obj->scale(glm::vec3(.5f, .5f, .5f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::BOX);
}

Box::~Box()
{
}

const glm::vec2	&Box::getPos() const
{
  return _vec;
}

void	Box::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void	Box::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{
}

void	Box::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  if (_status == OK) {
      _texture->bind();
      _obj->draw(shader, clock);
  }
}

IEntity::Type Box::getType() const
{
  return IEntity::BOX;
}

IEntity::Status Box::getStatus() const
{
  return _status;
}

void Box::setStatus(IEntity::Status status)
{
  _status = status;
}
