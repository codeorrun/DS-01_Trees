#pragma once

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#else

#define DBG_NEW new

#endif