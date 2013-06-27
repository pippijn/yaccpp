#pragma once

#include <stdexcept>
#include <vector>

#include <boost/lexical_cast.hpp>

template<size_t MaxBytes>
struct object_pool
{
  ~object_pool ()
  {
    for (size_t i = 0; i < MaxBytes + 1; i++)
      {
        std::vector<void *> &single = pool[i];
        while (!single.empty ())
          {
            operator delete (single.back ());
            single.pop_back ();
          }
      }
  }

  void *alloc (size_t bytes)
  {
    if (__builtin_expect (bytes > MaxBytes, false))
      throw std::runtime_error ("could not allocate " + boost::lexical_cast<std::string> (bytes) + " bytes");
    void *ptr;
    if (!pool[bytes].empty ())
      {
        ptr = pool[bytes].back ();
        pool[bytes].pop_back ();
      }
    else
      {
        ptr = operator new (bytes);
      }
    return ptr;
  }

  void free (void *ptr, size_t bytes)
  {
    pool[bytes].push_back (ptr);
  }

  std::vector<void *> pool[MaxBytes + 1];
};
