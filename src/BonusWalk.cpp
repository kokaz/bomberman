#include "BonusWalk.hpp"

BonusWalk::BonusWalk(const glm::vec2 &pos, double effectTime)
  : ABonus(FASTER, pos, effectTime), _increaseSpeed(0)
{
  _increaseSpeed = 0;
}

BonusWalk::~BonusWalk()
{

}

void	BonusWalk::start(APlayer *player)
{
  double currentSpeed = player->getSpeed();


  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);
  _increaseSpeed += (currentSpeed * 1.3) - currentSpeed;

  player->setSpeed(currentSpeed + _increaseSpeed);
}

void	BonusWalk::stop(APlayer *player)
{
  double currentSpeed = player->getSpeed();

  _status = DESTROY;
  player->setSpeed(currentSpeed - _increaseSpeed);
}

void    BonusWalk::takeAnother(APlayer *player)
{
  double effectTime = _effectTime.getTime();
  double currentSpeed = player->getSpeed();
  double currentIncrease = (currentSpeed * 1.3) - currentSpeed;

  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);

  _increaseSpeed += currentIncrease;

  player->setSpeed(currentSpeed + currentIncrease);
  _effectTime.reset(effectTime);
}

std::string BonusWalk::toString()
{
  std::stringstream ss("");

  ss << "Faster : " << (_increaseSpeed > 0 ? "+" : "-") << _increaseSpeed
     << " (" << static_cast<int>(_effectTime.getRemainingTime()) << ")";;;
  return ss.str();
}
