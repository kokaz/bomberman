#include <ModelLoader.hpp>
#include <ResourceManager.hpp>
#include <TextureLoader.hpp>

void ResourceManager::remove(const std::string& name)
{
  if (!_destroyed)
    _resources.erase(name);
}

ResourceManager::ResourceManager()
  : _destroyed(false)
{
  MediaManager::getInstance()->registerLoader(new TextureLoader, "tga");
  MediaManager::getInstance()->registerLoader(new ModelLoader, "obj,fbx,dae");
}

ResourceManager::~ResourceManager()
{
  _destroyed = true;
}

void ResourceManager::add(const std::string& name, SharedPointer<AResource> resource)
{
  _resources[name] = resource;
}
