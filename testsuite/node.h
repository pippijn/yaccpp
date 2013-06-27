#include <boost/preprocessor.hpp>

#define LIST (a, (b, (c, BOOST_PP_NIL)))
#define ARG_LIST(r, data, elem) r BOOST_PP_CAT (elem, data)

BOOST_PP_LIST_FOR_EACH (ARG_LIST, BOOST_PP_LIST_SIZE (LIST), LIST)
