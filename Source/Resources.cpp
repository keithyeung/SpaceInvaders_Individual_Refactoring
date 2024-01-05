#include "Resources.h"


const Texture2D& getTexture(const MyTexture& t) noexcept
{
	return t.get();
}