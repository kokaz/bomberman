#ifndef PLAYERMANAGER_H
# define PLAYERMANAGER_H

# include <list>

# include <glm/glm.hpp>

# include "IEntity.hpp"
# include "ACamera.hpp"
# include "Player.hpp"
# include "FontText.hpp"
# include "LeaderScores.hpp"

class PlayerManager
{
public:
  PlayerManager(const glm::vec2& pos, Map *map, bool first, const glm::vec4& color,
		const std::string &name);
  ~PlayerManager();

  Player& getPlayer() {return _player;};
  ACamera& getCam() {return *_cam;};

  void update(const Map& map, const gdl::Clock &clock);
  void displayInfo(const FontText &font, const gdl::Clock &clock, gdl::AShader *shader) const;
  const std::list<IEntity*>& getNearList() const {return _nearEntity;};
  bool getDead(LeaderScores *) const;
  void setWin();
private:
  PlayerManager(const PlayerManager& p);
  void updateNearList(const Map& map);
private:
  float _timer;
  Player _player;
  ACamera* _cam;
  int _score;
  std::list<IEntity*> _nearEntity;
  bool _first;
  bool _win;
};

#endif // PLAYERMANAGER_H
