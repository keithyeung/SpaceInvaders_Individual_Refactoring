#pragma once
#include "raylib.h"
#include "vector"
#include <string>
#include <stdexcept>
#include <format>
#include <span>

using namespace std::literals::string_view_literals;

static inline float GetScreenHeightF() noexcept {
	return static_cast<float>(GetScreenHeight());
}

static inline float GetScreenWidthF() noexcept {
	return static_cast<float>(GetScreenWidth());
}

static inline float GetRandomValueF(int x, int y) noexcept {
	return static_cast<float>(GetRandomValue(x, y));
}

static inline constexpr int GetIntValue(float x) noexcept {
	return static_cast<int>(x);
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

	[[gsl::suppress(f.6)]]
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

template<typename T>
static inline void render(std::span<T> objects, const MyTexture& tex) noexcept {
	for (const auto& i : objects) {
		i.Render(tex);
	}
}

template<typename T>
static inline void update(std::span<T> objects) noexcept {
	for (auto& i : objects) {
		i.Update();
	}
}