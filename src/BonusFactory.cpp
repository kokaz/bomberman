#include "BonusFactory.hpp"

BonusFactory::BonusFactory()
{
  _bonus.push_back(&BonusFactory::instanciateBonus<BonusWalk>);
  _bonus.push_back(&BonusFactory::instanciateBonus<BonusBomb>);
  _bonus.push_back(&BonusFactory::instanciateBonus<BonusRange>);
  _bonus.push_back(&BonusFactory::instanciateBonus<BonusFlammePass>);
  _bonus.push_back(&BonusFactory::instanciateBonus<BonusBombPass>);
}

BonusFactory::~BonusFactory()
{
}

ABonus	*BonusFactory::createBonus(const glm::vec2 &pos, int nbBonus)
{
  return (this->*(_bonus[rand() % nbBonus]))(pos);
}
