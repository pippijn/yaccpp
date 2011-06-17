#pragma once

#include "local.h"
#include "node.h"
#include "phase.h"
#include "phases.h"
#include "visitor.h"
#include "ylcode.h"

#define resume(member)          n.member = n.member->accept (*this)
#define resume_if(member)       if (n.member) resume (member)
#define resume_list()           for (std::list<node_ptr>::iterator it = n.list.begin (), et = n.list.end (); it != et; ++it) *it = (*it)->accept (*this)
