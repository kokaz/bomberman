#ifndef MAP_HPP_
# define MAP_HPP_

# include <string>
# include <list>
# include <iostream>
# include <cstdlib>
# include <ctime>
# include "IEntity.hpp"
# include "Wall.hpp"
# include "Box.hpp"
# include "Bomb.hpp"

class Map
{
  typedef std::list<IEntity *> LMap;

  enum Type
    {
      BOX = 0,
      WALL = 1
    };

private:
  int	_x;
  int	_y;
  LMap	_map;

public:
  Map(const int x, const int y);
  Map(std::string const &mapFileName);
  ~Map();

private:
  bool		loadMapFromFile(std::string const &fileName);
  void		loadRandomMap();
  IEntity	*getEntityForMap(const int x, const int y) const;

  //Debug methods
public:
  void	displayDebugMap() const;
};

#endif /* !MAP_HPP_ */
