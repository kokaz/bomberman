#include "Ia.hpp"

int iaGetPos(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;

  if (argc != 1)
    throw nFault("iaGetPos need 1 argument (thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  lua_pushnumber(L, ptr->getX());
  lua_pushnumber(L, ptr->getY());
  return 2; //number of return values
}

int iaGetMap(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;
  int x, y;

  if (argc != 3)
    throw nFault("iaGetMap need 3 arguments (x, y, thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  y = lua_tonumber(L, lua_gettop(L)); //the order of args is inverse
  x = lua_tonumber(L, lua_gettop(L));
  lua_pushnumber(L, ptr->getMap(x, y));
  return 1;
}

int iaAction(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;
  int act;

  if (argc != 2)
    throw nFault("iaAction need 2 arguments (act, thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  act = lua_tonumber(L, lua_gettop(L));
  ptr->action(act);
  return 0;
}

int iaLaunch(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;

  if (argc != 1)
    throw nFault("iaLaunch need 1 arguments (thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  ptr->action(-1);
  return 0;
}

void *iaStart(void *ptr)
{
  return (static_cast<Ia *> (ptr))->init();
}

Ia::Ia(Map *currentMap, int x, int y, std::string const &fileName)
: _condAct(_mutex), _thread(iaStart, this)
{
  _running = false;
  _x = x;
  _y = y;
  _vec.x = x;
  _vec.y = y;
  _dead = false;
  _fileName = fileName;
  _L = luaL_newstate();
  if (_L == NULL)
    throw nFault("Init lua fail");

  _currentMap = currentMap;

  luaL_openlibs(_L);

  lua_pushcfunction(_L, iaGetPos);
  lua_setglobal(_L, "iaGetPos");
  lua_pushcfunction(_L, iaGetMap);
  lua_setglobal(_L, "iaGetMap");
  lua_pushcfunction(_L, iaLaunch);
  lua_setglobal(_L, "iaLaunch");
  lua_pushcfunction(_L, iaAction);
  lua_setglobal(_L, "iaAction");
  lua_pushlightuserdata(_L, this);
  lua_setglobal(_L, "thisptr");

  _thread.start();
}

Ia::~Ia()
{
  _dead = true;
  lua_close(_L);
}

void *Ia::init()
{
  try
    {
      _running = true;
      luaL_dofile(_L,"script/test.lua");
      //  luaL_dofile(_L,_fileName.c_str());
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  _running = false;
  _mutex.lock();
  _condAct.notifyAll();
  _mutex.unlock();
  return NULL;
}

int Ia::getMap(const int x, const int y) const
{
  IEntity::Type elem;

  elem = _currentMap->getTypeAt(x, y);
  return (static_cast<int> (elem));
}

int Ia::exec()
{
  if (_running)
    {
      _mutex.lock();
      _condAct.notifyAll();
      _condAct.wait();
      _mutex.unlock();
    }
  return _act;
}

void Ia::action(int act)
{
  _act = act;
  _mutex.lock();
  if (_act != -1)
    _condAct.notifyAll();
  _condAct.wait();
  _mutex.unlock();
  if (_dead)
    {
      _running = false;
      _mutex.lock();
      _condAct.notifyAll();
      _mutex.unlock();
      pthread_exit(&act);
    }
}

int Ia::getX() const
{
  return _x;
}

int Ia::getY() const
{
  return _y;
}

void Ia::setX(const int x)
{
  _x = x;
}

void Ia::setY(const int y)
{
  _y = y;
}

void Ia::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
  _x = new_pos.x;
  _y = new_pos.y;
}

void Ia::update(gdl::Input &input, gdl::Clock const &clock)
{
  (void) input;
  (void) clock;
}

void Ia::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  (void) shader;
  (void) clock;
}

const glm::vec2 &Ia::getPos() const
{
  return _vec;
}
