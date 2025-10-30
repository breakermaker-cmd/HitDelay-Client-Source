#include "modules.hpp"

void modules::auto_sprint::run(::cache& cache)
{
	cache.player.setSprinting(JNI_TRUE);
}
