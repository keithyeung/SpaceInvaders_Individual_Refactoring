#pragma once
#include "raylib.h"
#include "vector"
#include <string>
#include <stdexcept>
#include <format>

using namespace std::literals::string_view_literals;

static inline float GetScreenHeightF() noexcept {
	return static_cast<float>(GetScreenHeight());
}

static inline float GetScreenWidthF() noexcept {
	return static_cast<float>(GetScreenWidth());
}


struct MyTexture
{
	Texture2D tex;
	explicit MyTexture(std::string_view path)
	{
		tex = LoadTexture(path.data());
		if (tex.id <= 0)
		{
			throw(std::runtime_error(std::format("Unable to load texture: {}"sv, path)));
		}
	}

	MyTexture(const MyTexture& other) noexcept = delete;
	MyTexture& operator=(const MyTexture& other) noexcept = delete;

	MyTexture(MyTexture&& other) noexcept
	{
		std::swap(other.tex, tex);
	}
	MyTexture& operator=(MyTexture&& other) noexcept
	{
		std::swap(other.tex, tex);
		return *this;
	}

	~MyTexture()
	{
		UnloadTexture(tex);
	}

	const Texture2D& get() const noexcept
	{
		return tex;
	}

};

const Texture2D& getTexture(const MyTexture& t) noexcept;

struct Resources 
{
	std::vector<MyTexture> shipTextures;

	Resources()
	{
		shipTextures.reserve(3);
		shipTextures.emplace_back("./Assets/Ship1.png"sv);
		shipTextures.emplace_back("./Assets/Ship2.png"sv);
		shipTextures.emplace_back("./Assets/Ship3.png"sv);
	}

	MyTexture alienTexture = MyTexture("./Assets/Alien.png"sv);
	MyTexture barrierTexture = MyTexture("./Assets/Barrier.png"sv);
	MyTexture laserTexture = MyTexture("./Assets/Laser.png"sv);


};