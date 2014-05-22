#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "Cube.hpp"
# include "IEntity.hpp"

class Bomb : public IEntity
{
public:
  enum LevelBomb
    {
      SMALL,
      BIG
    };

private:
  glm::vec2	_vec;
  AObject *_obj;

public:
  Bomb(const glm::vec2 &pos);
  virtual ~Bomb();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
  virtual void  draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
};

#endif /* !BOMB_HPP_ */
