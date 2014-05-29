#ifndef _CUBE6FACE_H_
# define _CUBE6FACE_H_

# include <Texture.hh>
# include <Geometry.hh>
# include <iostream>

# include "IEntity.hpp"
# include "AObject.hpp"
# include "AssetsManager.hpp"

class Cube6Face : public AObject
{
public:
  Cube6Face();
  virtual ~Cube6Face();
  virtual bool	initialize();
  virtual void draw(gdl::AShader *shader, const gdl::Clock &clock);

private:
  gdl::Geometry _geometry;
};

#endif /* _CUBE6FACE_H_ */
