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
		SDL_ShowCursor(SDL_DISABLE);

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
	}

	void EndFrame()
	{
		SDL_RenderPresent(renderer);
		SDL_PollEvent(&event);

		if (ShouldExit()) exit(0);
	}

	SDL_Window* getWindow() const
	{
		return window;
	}

	void DrawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_Rect rect;
		rect.x = x - width/2.0;
		rect.y = y - height/2.0;
		rect.w = width;
		rect.h = height;

		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &rect);
	}

	void DrawCircle(int x0, int y0, int radiusX, int radiusY, Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		//draw one quadrant arc, and mirror the other 4 quadrants
	    float pi  = 3.14159265358979323846264338327950288419716939937510;
	    float pih = pi / 2.0; //half of pi

	    //drew  28 lines with   4x4  circle with precision of 150 0ms
	    //drew 132 lines with  25x14 circle with precision of 150 0ms
	    //drew 152 lines with 100x50 circle with precision of 150 3ms
	    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
	    float theta = 0;     // angle that will be increased each loop

	    //starting point
	    int x  = (float)radiusX * cos(theta);//start point
	    int y  = (float)radiusY * sin(theta);//start point
	    int x1 = x;
	    int y1 = y;

	    //repeat until theta >= 90;
	    float step = pih/(float)prec; // amount to add to theta each time (degrees)
	    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
	    {
	        //get new point location
	        x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
	        y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

	        //draw line from previous point to new point, ONLY if point incremented
	        if( (x != x1) || (y != y1) )//only draw if coordinate changed
	        {
	            SDL_RenderDrawLine(renderer, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
	            SDL_RenderDrawLine(renderer, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
	            SDL_RenderDrawLine(renderer, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
	            SDL_RenderDrawLine(renderer, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
	        }
	        //save previous points
	        x = x1;//save new previous point
	        y = y1;//save new previous point
	    }
	    //arc did not finish because of rounding, so finish the arc
	    if(x!=0)
	    {
	        x=0;
	        SDL_RenderDrawLine(renderer, x0 + x, y0 - y, x0 + x1, y0 - y1);//quadrant TR
			SDL_RenderDrawLine(renderer, x0 - x, y0 - y, x0 - x1, y0 - y1);//quadrant TL
			SDL_RenderDrawLine(renderer, x0 - x, y0 + y, x0 - x1, y0 + y1);//quadrant BL
			SDL_RenderDrawLine(renderer, x0 + x, y0 + y, x0 + x1, y0 + y1 );//quadrant BR
	    }
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