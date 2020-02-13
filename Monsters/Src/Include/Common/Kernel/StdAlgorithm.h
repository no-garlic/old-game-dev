
#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "Kernel/Types.h"
#include <algorithm>


// --------------------------------------------------------------------
// Name: RemoveFirstFromVector
// Temp: The type of objects contained in the vector
// Desc: Removes the first occurence of the requested object in the 
//       vector
// Parm: Array<T *> &vec - the vector
// Parm: T *pobj       - the object
// Retn: bool          - true if found and removed, otherwise false
// --------------------------------------------------------------------
template <class T>
  bool RemoveFirstFromVector(Array<T *> &vec, T *pobj)
{
  Array<T *>::iterator iter = vec.begin();
  Array<T *>::iterator end  = vec.end();

  for (; iter != end; ++iter)
  {
    if ((* iter) == pobj)
    {
      vec.erase(iter);
      return true;
    } // if
  } // for

  return false;
} // RemoveFirstFromVector


// --------------------------------------------------------------------
// Name: FindInVector
// Temp: The type of objects contained in the vector
// Desc: Searches for the given object in the vector
// Parm: Array<T *> &vec - the vector
// Parm: T *pobj       - the object
// Retn: bool          - true if the object is in the vector
// --------------------------------------------------------------------
template <class T>
  bool FindInVector(Array<T *> &vec, T *pobj)
{
  Array<T *>::iterator iter = vec.begin();
  Array<T *>::iterator end  = vec.end();

  for (; iter != end; ++iter)
  {
    if ((* iter) == pobj)
      return true;
  } // for

  return false;
} // FindInVector


// --------------------------------------------------------------------
// Name: DestroyObject (struct)
// Desc: A struct that deletes an object using a unary call operator
// --------------------------------------------------------------------
template <class T> 
struct DestroyObject
{
  // ----------------------------------------------------------------
  // Name: operator
  // Desc: The call operator that deletes the object
  // ----------------------------------------------------------------
  void operator()(T *ptr)
  {
    delete ptr;
  } // operator()
}; // struct DestroyObject


// --------------------------------------------------------------------
// Name: DestroyVector
// Temp: The type of objects contained in the vector
// Desc: Destroys all objects between the start and end iterators
// Parm: typename Array<T *>::iterator &begin - start iterator
// Parm: typename Array<T *>::iterator &end   - end iterator
// --------------------------------------------------------------------
template <class T> 
  void DestroyVector(typename Array<T *>::iterator &begin, typename Array<T *>::iterator &end)
{
  std::for_each(begin, end, DestroyObject<T>());
} // DestroyVector


// --------------------------------------------------------------------
// Name: DestroyVector
// Temp: The type of objects contained in the vector
// Desc: Destroys all objects in the vector, then clears the vector if
//       requested.
// Parm: typename Array<T *> &vec - the vector
// Parm: bool clear_vector = true       - flag to clear the vector
// --------------------------------------------------------------------
template <class T> 
  void DestroyVector(Array<T *> &vec, bool clear_vector = true)
{
  std::for_each(vec.begin(), vec.end(), DestroyObject<T>());

  if (clear_vector)
    vec.clear();
} // DestroyVector


// --------------------------------------------------------------------
// Name: DestroyList
// Temp: The type of objects contained in the list
// Desc: Destroys all objects between the start and end iterators
// Parm: typename List<T *>::iterator &begin - start iterator
// Parm: typename List<T *>::iterator &end   - end iterator
// --------------------------------------------------------------------
template <class T> 
  void DestroyList(typename List<T *>::iterator &begin, typename List<T *>::iterator &end)
{
  std::for_each(begin, end, DestroyObject<T>());
} // DestroyList


// --------------------------------------------------------------------
// Name: DestroyList
// Temp: The type of objects contained in the list
// Desc: Destroys all objects in the list, then clears the list if
//       requested.
// Parm: typename List<T *> &vec - the list
// Parm: bool clear_list = true       - flag to clear the list
// --------------------------------------------------------------------
template <class T> 
  void DestroyList(List<T *> &list, bool clear_list = true)
{
  std::for_each(list.begin(), list.end(), DestroyObject<T>());

  if (clear_list)
    list.clear();
} // DestroyList


// --------------------------------------------------------------------
// Name: DestroyMapSecond
// Temp: K - the key type in the map
// Temp: V - the value type in the map
// Desc: Destroys all objects between the start and end iterators
// Parm: typename Map<K, V>::iterator &begin - start iterator
// Parm: typename Map<K, V>::iterator &end   - end iterator
// --------------------------------------------------------------------
template <class K, class V> 
  void DestroyMapSecond(typename Map<K, V *>::iterator &begin, typename Array<K, V *>::iterator &end)
{
  std::for_each(begin, end, DestroyObject<V>());
} // DestroyMapSecond


// --------------------------------------------------------------------
// Name: DestroyMapSecond
// Temp: K - the key type in the map
// Temp: V - the value type in the map
// Desc: Destroys all objects in the map, then clears the map if
//       requested.
// Parm: typename Map<K, V> &map - the map
// Parm: bool clear_map = true        - flag to clear the map
// --------------------------------------------------------------------
template <class K, class V> 
  void DestroyMapSecond(Map<K, V *> &map, bool clear_map = true)
{
  std::for_each(map.begin(), map.end(), DestroyObject<V>());

  if (clear_map)
    map.clear();
} // DestroyMapSecond


#endif // _ALGORITHM_H_

// -- EOF

