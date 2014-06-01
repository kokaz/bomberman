#ifndef MENU_HPP_
#define MENU_HPP_

#include <Clock.hh>
#include "Game.hpp"
#include "Graphics.hpp"
#include "ACamera.hpp"
#include "PivotingCam.hpp"
#include "Graphics.hpp"

class Menu
{
public:
  Menu(PivotingCam *cam);
  ~Menu();
  bool updateMenu(gdl::Input &input, const gdl::Clock &clock);
  void drawMenu(const gdl::Clock &clock, gdl::AShader* hudshader) const;
  bool finish() const;
private:
  void init();
private:
  PivotingCam *_cam;
  FontText *_font;
  glm::vec3 _pos;
  glm::mat4 _ortho;
  enum {
    Running,
    Finished
  } _state;
  enum selected {
    Start = 0,
    Options,
    Exit
  } _select;
};

#endif
