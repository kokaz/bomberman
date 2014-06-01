#include <sstream>
#include "Menu.hpp"

Menu::Menu(PivotingCam *cam)
  : _mapFile("map2.map"), _cam(cam), _state(Running), _select(Start)
{
  _numberIa = 0;
  _numberPlayer = 1;
  _game = NULL;
  _font = new FontText(RES_TEXTURE "font.tga");
  init();
}

Menu::~Menu()
{
}

void Menu::init()
{
  _ortho = glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.0, -1.0, -1.0)), glm::vec3(2.0, 2.0, 2.0));
}

Game *Menu::getGame()
{
  return _game;
}

bool Menu::finish() const
{
  if (_state == Finished)
    return true;
  return false;
}

bool Menu::updateMenu(gdl::Input &input, UNUSED const gdl::Clock &clock)
{
  if (_state != Finished)
    {
      if (input.getKey(SDLK_RETURN, true) && _select == Start)
	{
	  _state = Finished;
	  _game = new ::Game(glm::ivec2(1024, 900), _numberPlayer, _numberIa, _iaFile, _mapFile);
	}
      else if (input.getKey(SDLK_UP, true))
	_select = (selected)(_select - 1);
      else if (input.getKey(SDLK_DOWN, true))
	_select = (selected)(_select + 1);
      if (_select < 0)
	_select = Exit;
      if (_select > 2)
	_select = Start;
    }
  return true;
}

void Menu::drawMenu(UNUSED gdl::Clock const &clock, gdl::AShader* hudshader) const
{
  glm::mat4 textMat = glm::translate(glm::mat4(1), glm::vec3(0.01f, 0.6f, 0.0f));

  hudshader->setUniform("view", _ortho);
  hudshader->setUniform("projection", glm::mat4(1));

  textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.59, 0.0));
  textMat = glm::scale(textMat, glm::vec3(1.5, 1.5, 0.0));
  _font->displayText(std::string("Start"), _select == Start ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
  textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.39, 0.0));
  textMat = glm::scale(textMat, glm::vec3(1.5, 1.0, 0.0));
  _font->displayText(std::string("Options"), _select == Options ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
  textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.19, 0.0));
  textMat = glm::scale(textMat, glm::vec3(1.5, 1.0, 0.0));
  _font->displayText(std::string("Exit"), _select == Exit ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
  /* TODO : draw the curent menu */
}
