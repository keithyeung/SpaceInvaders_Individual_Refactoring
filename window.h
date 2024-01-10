#pragma once
#include "raylib.h"
#include <string>

class Window
{
public:
	Window(int screen_widht, int screen_height, std::string_view title)noexcept {
		InitWindow(screen_widht, screen_height, title.data());
		SetTargetFPS(60);
	}

	Window(const Window& other) noexcept = delete;
	Window& operator=(const Window& other) noexcept = delete;

	Window(Window&& other) = delete;
	Window& operator=(Window&& other) = delete;

	~Window() noexcept {
		CloseWindow();
	}

	bool ShouldClose() const noexcept
	{
		return WindowShouldClose();
	}
};