#include "BonusWalk.hpp"

BonusWalk::BonusWalk(const glm::vec2 &pos, double effectTime)
  : ABonus(FASTER, pos, effectTime)
{
}

BonusWalk::~BonusWalk()
{

}

void	BonusWalk::start(APlayer *player)
{
  double currentSpeed = player->getSpeed();


  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);
  std::cout << "speed up !" << std::endl;
  _increaseSpeed = (currentSpeed * 1.3) - currentSpeed;

  std::cout << "speed now at : " << currentSpeed + _increaseSpeed << std::endl;
  player->setSpeed(currentSpeed + _increaseSpeed);
  _status = REMOVE;
}

void	BonusWalk::stop(APlayer *player)
{
  double currentSpeed = player->getSpeed();

  _status = DESTROY;
  player->setSpeed(currentSpeed - _increaseSpeed);
  std::cout << "bonusWalk end : " << player->getSpeed() << std::endl;
}

std::string BonusWalk::toString()
{
  std::stringstream ss("");

  ss << "Faster : " << _increaseSpeed;
  return ss.str();
}
