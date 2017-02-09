#include "stdafx.h"
#include <iostream>
using namespace std;
#include "sdl\SDL.h"
#include "Renderer.h"


Renderer::Renderer() :sdl_renderer(NULL)
{

}

SDL_Renderer * Renderer::getRenderer()
{
	return sdl_renderer;
}

//draw a rectangle in world coordinates
void Renderer::drawWorldRect(const Rect &r, const Colour &c)
{
	drawRect(cameraTransform(r), c);
}

void Renderer::present() { //swap buffers
	SDL_RenderPresent(sdl_renderer);
}

void Renderer::clear(const Colour& col) {
	SDL_SetRenderDrawColor(sdl_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(sdl_renderer);
}

void Renderer::drawImage(SDL_Surface* img)
{
	SDL_Texture* ImageTexture = SDL_CreateTextureFromSurface(sdl_renderer, img);
	SDL_RenderCopy(sdl_renderer, ImageTexture, NULL, NULL);
	SDL_DestroyTexture(ImageTexture);
}

void Renderer::drawTexture(SDL_Texture* img, Rect _dst)
{
	SDL_Rect dst;
	_dst = cameraTransform(_dst);
	dst.x = (int)_dst.pos.x;
	dst.y = (int)_dst.pos.y + (int)_dst.size.h;
	dst.w = (int)_dst.size.w;
	dst.h = -(int)_dst.size.h;
	SDL_RenderCopy(sdl_renderer, img, NULL, &dst);
}

void Renderer::drawTexture(SDL_Texture* img, Rect _src, Rect _dst)
{
	SDL_Rect dst;
	_dst = cameraTransform(_dst);
	dst.x = (int)_dst.pos.x;
	dst.y = (int)_dst.pos.y + (int)_dst.size.h;
	dst.w = (int)_dst.size.w;
	dst.h = -(int)_dst.size.h;

	SDL_Rect src;
	src.x = (int)_src.pos.x;
	src.y = (int)_src.pos.y;
	src.w = (int)_src.size.w;
	src.h = (int)_src.size.h;
	SDL_RenderCopy(sdl_renderer, img, &src, &dst);
}

void Renderer::drawImage(SDL_Texture* img, Rect rec, double angle)
{
	rec = cameraTransform(rec);
	SDL_Point objCentre;
	objCentre.x = rec.size.w / 2;

	SDL_Rect sdlRec;
	sdlRec.h = (int)rec.size.w;
	sdlRec.w = (int)rec.size.w;
	sdlRec.x = (int)rec.pos.x;
	sdlRec.y = (int)rec.pos.y - sdlRec.h;
	//3 blocks in 1
	objCentre.y = sdlRec.h / 2;
	SDL_Texture* ImageTexture = img;
	SDL_RenderCopyEx(sdl_renderer, ImageTexture, NULL, &sdlRec, angle, &objCentre, SDL_FLIP_NONE);

	sdlRec.y -= sdlRec.h + sdlRec.h / 2;
	objCentre.y = sdlRec.h / 2;
	SDL_RenderCopyEx(sdl_renderer, ImageTexture, NULL, &sdlRec, angle, &objCentre, SDL_FLIP_NONE);

	sdlRec.y -= sdlRec.h + sdlRec.h / 2;
	objCentre.y = sdlRec.h / 2;
	SDL_RenderCopyEx(sdl_renderer, ImageTexture, NULL, &sdlRec, angle, &objCentre, SDL_FLIP_NONE);

	sdlRec.y -= sdlRec.h + sdlRec.h / 2;
	objCentre.y = sdlRec.h / 2;
	SDL_RenderCopyEx(sdl_renderer, ImageTexture, NULL, &sdlRec, angle, &objCentre, SDL_FLIP_NONE);

}

void Renderer::drawImage(SDL_Surface* img, Rect rec)
{
	rec = cameraTransform(rec);
	SDL_Point objCentre;
	objCentre.x = rec.size.w / 2;

	SDL_Rect sdlRec;
	sdlRec.h = -(int)rec.size.h;
	sdlRec.w = (int)rec.size.w;
	sdlRec.x = (int)rec.pos.x;
	sdlRec.y = (int)rec.pos.y - sdlRec.h;

	objCentre.y = sdlRec.h / 2;
	SDL_Texture* ImageTexture = SDL_CreateTextureFromSurface(sdl_renderer, img);
	SDL_RenderCopyEx(sdl_renderer, ImageTexture, NULL, &sdlRec, 0, &objCentre, SDL_FLIP_NONE);
}


/**Destroys SDL_Window and SDL_Renderer*/
void Renderer::destroy() {
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(window);
}

Renderer::~Renderer()
{
}




bool Renderer::init(const Size2D& winSize, const char* title, Camera2D* cam) {

	m_camera = cam;
	int e = SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2
	windowSize = winSize;
	if (e != 0) {
		// problem with SDL?...
		cout << "Could not init SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		title,							   // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		(int)winSize.w,                    // width, in pixels
		(int)winSize.h,                    // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize PNG loading
	/*int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
	cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
	return false;
	}*/

	sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == NULL) {
		// In the case that the renderer could not be made...
		cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::setNewCamera(Camera2D * newCam)
{
	m_camera = newCam;
}

void Renderer::drawRectOutline(const Rect& r, const Colour& c)
{
	Rect tRect = cameraTransform(r);
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	SDL_Rect sr;
	sr.h = tRect.size.h;
	sr.w = tRect.size.w;
	sr.x = tRect.pos.x;
	sr.y = tRect.pos.y;
	SDL_RenderDrawRect(sdl_renderer, &sr);
}

void Renderer::drawRect(const Rect& r, const Colour& c) {
	Rect tRect = cameraTransform(r);
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	SDL_Rect sr;
	sr.h = tRect.size.h;
	sr.w = tRect.size.w;
	sr.x = tRect.pos.x;
	sr.y = tRect.pos.y;
	SDL_RenderFillRect(sdl_renderer, &sr);

}

Rect Renderer::cameraTransform(Rect r)
{
	/*r = r * m_camera->getScale();
	r.pos.x -= m_camera->getViewport().pos.x;
	r.pos.y -= m_camera->getViewport().pos.y;*/
	return r;
}