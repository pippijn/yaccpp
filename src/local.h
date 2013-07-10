#pragma once

struct local_base
{
};

template<typename T>
struct local_holder
  : local_base
{
  T const prev;
  T *ref;

  local_holder (T &ref)
    : prev (ref)
    , ref (&ref)
  {
  }

  local_holder (local_holder &l)
    : prev (l.prev)
    , ref (l.ref)
  {
    l.ref = 0;
  }

  ~local_holder ()
  {
    if (ref)
      *ref = prev;
  }

  local_holder (local_holder const &l);
};


template<typename T>
local_holder<T>
local_create (T &ref)
{
  local_holder<T> local (ref);
  return local;
}


// perldoc -f local
#define local(ref) local_base const &local_ ## ref = local_create (ref); ref
