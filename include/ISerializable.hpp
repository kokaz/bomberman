#ifndef _ISERIALIZABLE_H_
# define _ISERIALIZABLE_H_

# include <istream>
# include <ostream>

/**
 * ISerializable is a generic class interface
 * which allow you serialize/deserialize your object
 */
class ISerializable
{
public:
  virtual ~ISerializable() {}

public:
  /**
   * This method is use to serialize your object
   * in an output stream
   */
  virtual void writeObject(std::ostream& os) const = 0;

  /**
   * This method is use to deserialize your object
   * from an input stream
   */
  virtual void readObject(std::istream& is) = 0;
};

#endif /* _ISERIALIZABLE_H_ */

/**
 * See readObject
 */
std::istream& operator>>(std::istream& is, ISerializable* obj)
{
  obj->readObject(is);
  return is;
}

/**
 * See writeObject
 */
std::ostream& operator<<(std::ostream& os, const ISerializable* obj)
{
  obj->writeObject(os);
  return os;
}
