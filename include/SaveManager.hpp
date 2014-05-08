#ifndef _SAVEMANAGER_H_
# define _SAVEMANAGER_H_

# include <list>

# include "Singleton.hpp"
# include "ISerializable.hpp"

typedef std::list<ISerializable*>::const_iterator SMListConstIterator;
typedef std::list<ISerializable*>::iterator SMListIterator;

/**
 * SaveManager is a singleton class which manage all the
 * game save I/O operations
 */
class SaveManager : public Singleton<SaveManager>
{
  friend SaveManager* Singleton<SaveManager>::getInstance();
  friend void Singleton<SaveManager>::kill();

public:
  static void save(const std::list<ISerializable*>& data);
  static void load(std::list<ISerializable*>& data);

private:
  SaveManager();
  virtual ~SaveManager() {}

  SaveManager (const SaveManager&) {}
};

#endif /* _SAVEMANAGER_H_ */
