#include <sstream>
#include <iomanip>

#include "EntitiesFactory.hpp"
#include "Game.hpp"
#include "AShader.hh"
#include "ArmagetroCam.hpp"
#include "FreeCam.hpp"
#include "FpsCam.hpp"
#include "TrackCam.hpp"
#include "OrthoCam.hpp"
#include "config.h"
#include <Geometry.hh>

Game::Game(const glm::ivec2& win, std::string const &saveGame)
{
  if (saveGame == "")
    throw nFault("The file name of the game is too short");
  /* TODO : load the saved game in saveGame*/
  init(win);
}

Game::Game(const glm::ivec2& win, int numberPlayer, int numberIA, std::vector<std::string> const & algoFileName,
           std::string const &mapName)
{
  int i, size;

  if (numberIA < 0 || numberPlayer < 0)
    throw nFault("You need two players");

  _currentMap = new Map(mapName);
  Placement place(_currentMap);
  i = 0;
  size = algoFileName.size();
  while (i < numberIA)
    {
      if (size != 0)
        _listIA.push_back(new Ia(_currentMap, place.getNewPos(), algoFileName[i % size]));
      else
        _listIA.push_back(new Ia(_currentMap, place.getNewPos(), "Path/to/default/ia.lua"));
      i++;
    }

  i = 0;
  while (i < numberPlayer)
    {
      _players.push_back(new Player(place.getNewPos(), _currentMap));
      i++;
    }
  for (std::vector<Ia *>::iterator it = _listIA.begin() ; it != _listIA.end(); ++it)
    if (_currentMap->addEntity(*it) != true)
      throw nFault("Error in the initializiation of the map");
  for (std::vector<Player *>::iterator it = _players.begin() ; it != _players.end(); ++it)
    if (_currentMap->addEntity(*it) != true)
      throw nFault("Error in the initializiation of the map");


  init(win);
}

void Game::init(const glm::ivec2& win)
{
  /* TODO : init game and load 3d models */
  glm::vec2 playerPos = _players.front()->getPos();

  //_cam = new FreeCam;
  // _cam = new BasicCam(glm::vec3(playerPos.x, playerPos.y, 0), 10, 3);
   _cam = new TrackCam(glm::vec3(_currentMap->getDimension().x / 2, 0.0, _currentMap->getDimension().y / 2));

  _ground = new Pan(_currentMap->getDimension() / glm::vec2(4, 4));

  _ground->initialize();
  _ground->scale(glm::vec3(0.5f, 0.5f, 1.0f));
  _ground->translate(glm::vec3(-0.5f, 0, -0.5f));
  _ground->scale(glm::vec3(_currentMap->getDimension().x, _currentMap->getDimension().y, 1.0f));

  _ground->translate(glm::vec3(static_cast<float>(_currentMap->getDimension().x) / 2.0, -0.5f,
                               static_cast<float>(_currentMap->getDimension().y) / 2.0));
  _ground->rotate(glm::vec3(1, 0, 0), 90.0);

  _ortho = glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.0, -1.0, -1.0)), glm::vec3(2.0, 2.0, 2.0));

  _skybox.initialize();
  _font = new FontText(RES_TEXTURE "font.tga");
  _ogl.init(win);
}

Game::~Game()
{
  delete _cam;
}

bool Game::updateGame(gdl::Input &input, const gdl::Clock &clock)
{
  glm::vec2 playerPos = _players.front()->getPos();
  _cam->update(glm::vec3(playerPos.x, playerPos.y, 0));
  _cam->update(input, clock);
  _skybox.setPosition(_cam->getPosition());

  /* TODO : move players, explose bomb, ... */
  std::list<IEntity *>	&list = _currentMap->getMap();

  for (std::list<IEntity *>::iterator it = list.begin() ; it != list.end() ; it++)
    {
      (*it)->update(input, clock);
    }
  return true;
}

void Game::drawGame(UNUSED gdl::Input &input, gdl::Clock const &clock)
{
  gdl::AShader *shader = _ogl.getShader();
  gdl::AShader *hudshader = _ogl.getHudShader();

  _ogl.startFrame();
  shader->setUniform("view", _cam->project());

  AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::GROUND)->bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  _ground->draw(shader, clock);

  for (Map::iterator it = _currentMap->begin(); it != _currentMap->end(); ++it)
    (*it)->draw(shader, clock);

  glm::mat4 tmpMat =  glm::translate(glm::mat4(1), glm::vec3(0.0f, 1.0f, 0.0f));
  tmpMat = glm::scale(tmpMat, glm::vec3(16, 16, 16));
  tmpMat = glm::rotate(tmpMat, 63.0f, glm::vec3(0.5, 0.2, 0.3));
  _font->displayText("abcde", glm::vec4(1.0f, 0.0f, 0.0f, 0.6f), tmpMat, shader);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  hudshader->bind();
  glDisable(GL_DEPTH_TEST);

  hudshader->setUniform("view", _cam->project());
  hudshader->setUniform("projection", _ogl.getPerspectiveProj());

  _skybox.draw(hudshader, clock);

  _ogl.processFrame(_cam->getPosition());
  hudshader->bind();

  hudshader->setUniform("view", _ortho);
  hudshader->setUniform("projection", glm::mat4(1));

  glm::mat4 textMat = glm::translate(glm::mat4(1), glm::vec3(0.01f, 0.6f, 0.0f));
  textMat = glm::scale(textMat, glm::vec3(0.25, 0.25, 0.0));
  textMat = glm::rotate(textMat, 45.0f, glm::vec3(0.3f, 0.5f, 0.6));

  std::stringstream ss;
  static double elapsed = 0.0;
  static unsigned int k = 0;
  ++k;
  if (k % 20 == 0)
    elapsed = clock.getElapsed();
  ss << std::setprecision(2) << 1.0 / elapsed << " FPS";

  textMat = glm::translate(glm::mat4(1), glm::vec3(0.8, 0.97, 0.0));
  textMat = glm::scale(textMat, glm::vec3(0.5, 0.5, 0.0));
  _font->displayText(ss.str(), (elapsed <= 0.017) ? glm::vec4(0.0f, 1.0f, 0.0f, 0.8f) : glm::vec4(1.0f, 0.0f, 0.0f, 0.8f), textMat, hudshader);

  glEnable(GL_DEPTH_TEST);
}
