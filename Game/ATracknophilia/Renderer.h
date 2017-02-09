#pragma once
#include "BasicTypes.h"
#include "sdl\SDL.h"
#include "Camera2D.h"
#include "box2d\Box2D.h"

//Responsible for all drawing operations
//abstracts away specfic SDL specific drawing functions
class Renderer 
{
	Vector2D windowSize;

	SDL_Window *window;
	SDL_Renderer *sdl_renderer;
	Camera2D * m_camera;

public:
	Renderer();
	SDL_Renderer * getRenderer();
	bool init(const Vector2D&, const char*, Camera2D* cam);
	void drawRect(const Rect&, const Colour&);
	void present();
	void clear(const Colour&);
	Rect cameraTransform(Rect r);

	void drawImage(SDL_Surface* img);
	void drawTexture(SDL_Texture * img, Rect dst);
	void drawTexture(SDL_Texture * img, Rect _src, Rect _dst);
	void drawTextureWithAngle(SDL_Texture* img, Rect _src, Rect _dst, float angle);
	void drawImage(SDL_Texture* img, Rect rec, double angle);
	void drawImage(SDL_Surface * img, Rect rec);

	void drawBox2DPolygon(b2Body* body);

	void setNewCamera(Camera2D * newCam);
	void drawRectOutline(const Rect& r, const Colour& c);

	void destroy();
	~Renderer();
};