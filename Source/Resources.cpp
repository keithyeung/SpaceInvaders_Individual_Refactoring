#include "Resources.h"
#include <iostream>;

const Texture2D& getTexture(const MyTexture& t) noexcept
{
	return t.get();
}