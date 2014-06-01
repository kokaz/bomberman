#include "GameEngine.hpp"

GameEngine::GameEngine()
  : _state(Intro), _init(false), _intro(NULL), _game(NULL), _context(new gdl::SdlContext)
{
}

GameEngine::~GameEngine()
{
  if (_init)
    {
      delete _game;

      _context->stop();
      delete _context;
    }
}

bool GameEngine::initialize()
{
  const int width = 1024;
  const int heigth = 900;

  if (!_context->start(width, heigth, "Bomberman",
                       SDL_INIT_VIDEO, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
    return false;
  SDL_SetRelativeMouseMode(SDL_TRUE);
  _init = true;
  std::vector<std::string> tmp;
  tmp.push_back("sdf");
  AssetsManager::createAssets();
  _intro = new ::Intro(glm::ivec2(width, heigth));
  //_game = new ::Game(glm::ivec2(width, heigth), 1, 0, tmp, "map2.map");
  return true;
}

bool GameEngine::update()
{
  if (_state == Intro && _intro->finish() == true)
    {
      _state = Menu;
      _menu = new ::Menu(glm::ivec2(1024, 900));
      delete _intro;
    }
  _context->updateClock(_clock);
  _context->updateInputs(_input);
  if (_input.getInput(SDL_BUTTON_LEFT))
    SDL_SetRelativeMouseMode(SDL_TRUE);
  if (_input.getKey(SDLK_LCTRL) && _input.getInput(SDLK_LALT))
    SDL_SetRelativeMouseMode(SDL_FALSE);
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  switch (_state)
    {
    case Intro:
      return _intro->updateIntro(_input, _clock);
    case Menu:
      return _menu->updateMenu(_input, _clock);
    case Game:
    default:
      return _game->updateGame(_input, _clock);
    }
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  switch (_state)
    {
    case Intro:
      _intro->drawIntro(_clock);
      break;
    case Menu:
      _menu->drawMenu(_clock);
      break;
    case Game:
    default:
      _game->drawGame(_input, _clock);
      break;
    }
  _context->flush();
}
