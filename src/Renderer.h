#pragma once

#include <SDL.h>
#include <cmath>
#include <vector>

class Renderer
{
public:

	Renderer(size_t _width, size_t _height) :
		height(_height),
		width(_width),
		frameTicker(0)
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer((int)width, (int)height, 0, &window, &renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		event.type = 0;
	}

	~Renderer()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	bool ShouldExit() const
	{
		return event.type == SDL_QUIT;
	}

	static float GetTimeSec()
	{
		return (float)((double)SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency());
	}

	void BeginFrame()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		if (debugPoints.size() > 0)
		{
			SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
			SDL_RenderDrawPoints(renderer, &debugPoints[0], (int)debugPoints.size());
		}
	}

	void EndFrame()
	{
		SDL_RenderPresent(renderer);

		// Simulate rendering at ~ 15Hz
		{
			frameTicker++;
			Uint32 delayMs = 66;
			int delayOffsetMs = (int)(sinf((float)frameTicker / 10.0f) * (delayMs / 2));
			delayMs += delayOffsetMs;
			SDL_Delay(delayMs);
		}

		SDL_PollEvent(&event);
	}

	void DrawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = width;
		rect.h = height;

		AddDebugPoint(x, y);

		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &rect);
	}

private:

	void AddDebugPoint(int x, int y)
	{
		if (debugPoints.size() > 0)
		{
			const SDL_Point& lastPoint = debugPoints[debugPoints.size() - 1];
			if (lastPoint.x != x || lastPoint.y != y)
				debugPoints.push_back(SDL_Point{
					x = x,
					y = y
				});
		}
		else
		{
			debugPoints.push_back(SDL_Point{
				x = x,
				y = y
			});
		}
	}

	size_t height;
	size_t width;
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	SDL_Event event;
	Uint64 frameTicker;

	std::vector<SDL_Point> debugPoints;
};