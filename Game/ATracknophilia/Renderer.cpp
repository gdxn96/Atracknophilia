#include "stdafx.h"
#include <iostream>
using namespace std;
#include "sdl\SDL.h"
#include "Renderer.h"
#include "Vector2D.h"

Renderer::Renderer() :sdl_renderer(NULL)
{
}

SDL_Renderer * Renderer::getRenderer()
{
	return sdl_renderer;
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

void Renderer::drawBox2DPolygon(b2PolygonShape * polygonShape, Vector2D position, float angle)
{
	int lenght = (int)polygonShape->GetVertexCount();

	SDL_Point* points = new SDL_Point[lenght + 1];


	for (int i = 0; i < lenght; i++)
	{
		Vector2D worldPoint;
		float verticesPosX = polygonShape->GetVertex(i).x; 
		float verticesPosY = polygonShape->GetVertex(i).y; 

		float s = sin(angle);
		float c = cos(angle);

		// translate point back to origin:
		verticesPosX -= 0;
		verticesPosY -= 0;

		// rotate point
		float xnew = verticesPosX* c - verticesPosY * s;
		float ynew = verticesPosX * s + verticesPosY * c;

		// translate point back:
		verticesPosX = xnew + 0;
		verticesPosY = ynew + 0;

		worldPoint.x = verticesPosX + position.x;
		worldPoint.y = verticesPosY + position.y;
		worldPoint = worldPoint * m_camera->getScale();
		points[i].x = worldPoint.x;
		points[i].y = worldPoint.y;
	}

	points[lenght].y = points[0].y;
	points[lenght].x = points[0].x;

	SDL_RenderDrawLines(sdl_renderer, points, lenght + 1);
}

void Renderer::drawBox2DBody(b2Body * body)
{
	SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
	for (b2Fixture* b2Fixture = body->GetFixtureList(); b2Fixture != 0; b2Fixture = b2Fixture->GetNext())
	{
		b2Shape::Type shapeType = b2Fixture->GetType();
		
		if (shapeType == b2Shape::e_polygon)
		{
			b2PolygonShape* polygonShape = (b2PolygonShape*)b2Fixture->GetShape();
			drawBox2DPolygon(polygonShape, (b2Fixture->GetBody()->GetPosition()), b2Fixture->GetBody()->GetAngle());
		}
	}
}


/**Destroys SDL_Window and SDL_Renderer*/
void Renderer::destroy() 
{
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(window);
}

Renderer::~Renderer()
{
}

bool Renderer::init(const Vector2D& winSize, const char* title, Camera2D* cam) 
{
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
	r = r * m_camera->getScale();
	r.pos.x -= m_camera->getViewport().pos.x;
	r.pos.y -= m_camera->getViewport().pos.y;
	return r;
}