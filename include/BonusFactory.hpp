#ifndef _BONUSFACTORY_H_
#define _BONUSFACTORY_H_

# include "Singleton.hpp"
# include "BonusWalk.hpp"

class BonusFactory : public Singleton<BonusFactory>
{
  friend BonusFactory* Singleton<BonusFactory>::getInstance();
  friend void Singleton<BonusFactory>::kill();

public:
  ABonus *createBonus(const glm::vec2 &pos, int nbBonus);
private:
  BonusFactory();
  virtual ~BonusFactory();
};

#endif /* _BONUSFACTORY_H_ */
