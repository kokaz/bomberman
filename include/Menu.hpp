#ifndef MENU_HPP_
#define MENU_HPP_

#include "Game.hpp"
#include "Graphics.hpp"

class Menu
{
private:
  bool _show;
  Game *_game;
public:
  Menu();
  ~Menu();
  bool updateMenu(gdl::Input &input);
  void drawMenu(Graphics &ogl);
};

#endif
