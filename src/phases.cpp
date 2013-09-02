#include "phases.h"

#include <stdexcept>
#include <tr1/unordered_map>

typedef std::tr1::unordered_map<std::string, phases *> phase_map;

static phase_map *map;

phases::phases (std::string const &name)
{
  if (map == NULL)
    map = new phase_map;

  phases *&phase = (*map)[name];
  if (phase)
    throw std::logic_error ("phase `" + name + "' already registered");
  phase = this;
}

void
phases::run (std::string const &name, node_ptr doc)
{
  if (map == NULL)
    map = new phase_map;

  phases *phase = (*map)[name];
  if (!phase)
    throw std::logic_error ("phase `" + name + "' does not exist");
  phase->run (doc);
}
