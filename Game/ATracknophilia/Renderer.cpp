#include "stdafx.h"
#include <iostream>
#include "Renderer.h"


using namespace std;

static int *gfxPrimitivesPolyIntsGlobal = NULL;
static int gfxPrimitivesPolyAllocatedGlobal = 0;

#define ABS(a) (((a)<0) ? -(a) : (a))

typedef struct {
        Sint16 x, y;
        int dx, dy, s1, s2, swapdir, error;
        Uint32 count;
} SDL_gfxBresenhamIterator;

int _gfxPrimitivesCompareInt(const void *a, const void *b)
{
	return (*(const int *)a) - (*(const int *)b);
}

int hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y)
{
         return SDL_RenderDrawLine(renderer, x1, y, x2, y);;
}

typedef struct {
	Uint32 color;
	SDL_Surface *dst;
	int u, v;               /* delta x , delta y */
	int ku, kt, kv, kd;     /* loop constants */
	int oct2;
	int quad4;
	Sint16 last1x, last1y, last2x, last2y, first1x, first1y, first2x, first2y, tempx, tempy;
} SDL_gfxMurphyIterator;

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

void Renderer::drawBox2DPolygon(b2PolygonShape * polygonShape, float angle)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
	int lenght = (int)polygonShape->GetVertexCount();

	SDL_Point* points = new SDL_Point[lenght + 1];


	for (int i = 0; i < lenght; i++)
	{
		Camera2D::Point worldPoint;
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

		worldPoint.x = verticesPosX;
		worldPoint.y = verticesPosY;
		worldPoint = m_camera->worldToScreen(worldPoint);
		points[i].x = worldPoint.x;
		points[i].y = worldPoint.y;
	}

	points[lenght].y = points[0].y;
	points[lenght].x = points[0].x;

	SDL_RenderDrawLines(sdl_renderer, points, lenght + 1);
}

int  Renderer::drawFilledPoly(b2Body * body)
{
	b2PolygonShape* polygonShape = (b2PolygonShape*)body->GetFixtureList()->GetShape();

	SDL_Renderer * renderer = sdl_renderer;
	int n = polygonShape->GetVertexCount();
	Sint16 vx[16];
	Sint16 vy[16];

	Camera2D::Point worldPoint;
	for (int i = 0; i < n; i++)
	{
		worldPoint.x = polygonShape->GetVertex(i).x;
		worldPoint.y = polygonShape->GetVertex(i).y;
		worldPoint = m_camera->worldToScreen(worldPoint);
		vx[i] = worldPoint.x;
		vy[i] = worldPoint.y;
	}
	
	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	Uint8 a = 255;
	int **polyInts = NULL;
	int *polyAllocated = NULL;


	int result;
	int i;
	int y, xa, xb;
	int miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *gfxPrimitivesPolyInts = NULL;
	int *gfxPrimitivesPolyIntsNew = NULL;
	int gfxPrimitivesPolyAllocated = 0;

	/*
	* Vertex array NULL check
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check number of edges
	*/
	if (n < 3) {
		return -1;
	}

	/*
	* Map polygon cache
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		/* Use global cache */
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;
	}
	else {
		/* Use local cache */
		gfxPrimitivesPolyInts = *polyInts;
		gfxPrimitivesPolyAllocated = *polyAllocated;
	}

	/*
	* Allocate temp array, only grow array
	*/
	if (!gfxPrimitivesPolyAllocated) {
		gfxPrimitivesPolyInts = (int *)malloc(sizeof(int) * n);
		gfxPrimitivesPolyAllocated = n;
	}
	else {
		if (gfxPrimitivesPolyAllocated < n) {
			gfxPrimitivesPolyIntsNew = (int *)realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
			if (!gfxPrimitivesPolyIntsNew) {
				if (!gfxPrimitivesPolyInts) {
					free(gfxPrimitivesPolyInts);
					gfxPrimitivesPolyInts = NULL;
				}
				gfxPrimitivesPolyAllocated = 0;
			}
			else {
				gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
				gfxPrimitivesPolyAllocated = n;
			}
		}
	}

	/*
	* Check temp array
	*/
	if (gfxPrimitivesPolyInts == NULL) {
		gfxPrimitivesPolyAllocated = 0;
	}

	/*
	* Update cache variables
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		gfxPrimitivesPolyIntsGlobal = gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
	}
	else {
		*polyInts = gfxPrimitivesPolyInts;
		*polyAllocated = gfxPrimitivesPolyAllocated;
	}

	/*
	* Check temp array again
	*/
	if (gfxPrimitivesPolyInts == NULL) {
		return(-1);
	}

	/*
	* Determine Y maxima
	*/
	miny = vy[0];
	maxy = vy[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		}
		else if (vy[i] > maxy) {
			maxy = vy[i];
		}
	}

	/*
	* Draw, scanning y
	*/
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			}
			else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			}
			else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			}
			else {
				continue;
			}
			if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2))) {
				gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

		/*
		* Set color
		*/
		result = 0;
		result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
		result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

		for (i = 0; (i < ints); i += 2) {
			xa = gfxPrimitivesPolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = gfxPrimitivesPolyInts[i + 1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= hline(renderer, xa, xb, y);
		}
	}

	return (result);
}


#define clip_xmin(surface) surface->clip_rect.x
#define clip_xmax(surface) surface->clip_rect.x + surface->clip_rect.w - 1
#define clip_ymin(surface) surface->clip_rect.y
#define clip_ymax(surface) surface->clip_rect.y + surface->clip_rect.h - 1


int _putPixelAlpha(SDL_Surface *dst, Sint16 x, Sint16 y, Uint32 color, Uint8 alpha)
{
        SDL_PixelFormat *format;
        Uint32 Rmask, Gmask, Bmask, Amask;
        Uint32 Rshift, Gshift, Bshift, Ashift;
        Uint32 sR, sG, sB;
        Uint32 dR, dG, dB, dA;

        if (dst == NULL)
        {
                return (-1);
        }

        if (x >= clip_xmin(dst) && x <= clip_xmax(dst) && 
                y >= clip_ymin(dst) && y <= clip_ymax(dst)) 
        {

                format = dst->format;

                switch (format->BytesPerPixel) {
                case 1:
                        {               /* Assuming 8-bpp */
                                Uint8 *pixel = (Uint8 *) dst->pixels + y * dst->pitch + x;
                                if (alpha == 255) {
                                        *pixel = color;
                                } else {
                                        Uint8 R, G, B;
                                        SDL_Palette *palette = format->palette;
                                        SDL_Color *colors = palette->colors;
                                        SDL_Color dColor = colors[*pixel];
                                        SDL_Color sColor = colors[color];
                                        dR = dColor.r;
                                        dG = dColor.g;
                                        dB = dColor.b;
                                        sR = sColor.r;
                                        sG = sColor.g;
                                        sB = sColor.b;

                                        R = dR + ((sR - dR) * alpha >> 8);
                                        G = dG + ((sG - dG) * alpha >> 8);
                                        B = dB + ((sB - dB) * alpha >> 8);

                                        *pixel = SDL_MapRGB(format, R, G, B);
                                }
                        }
                        break;

                case 2:
                        {               /* Probably 15-bpp or 16-bpp */
                                Uint16 *pixel = (Uint16 *) dst->pixels + y * dst->pitch / 2 + x;
                                if (alpha == 255) {
                                        *pixel = color;
                                } else {
                                        Uint16 R, G, B, A;
                                        Uint16 dc = *pixel;

                                        Rmask = format->Rmask;
                                        Gmask = format->Gmask;
                                        Bmask = format->Bmask;
                                        Amask = format->Amask;

                                        dR = (dc & Rmask);
                                        dG = (dc & Gmask);
                                        dB = (dc & Bmask);

                                        R = (dR + (((color & Rmask) - dR) * alpha >> 8)) & Rmask;
                                        G = (dG + (((color & Gmask) - dG) * alpha >> 8)) & Gmask;
                                        B = (dB + (((color & Bmask) - dB) * alpha >> 8)) & Bmask;
                                        *pixel = R | G | B;
                                        if (Amask!=0) {
                                                dA = (dc & Amask);
                                                A = (dA + (((color & Amask) - dA) * alpha >> 8)) & Amask;
                                                *pixel |= A;
                                        }
                                }
                        }
                        break;

                case 3: 
                        {               /* Slow 24-bpp mode, usually not used */
                                Uint8 R, G, B;
                                Uint8 Rshift8, Gshift8, Bshift8;
                                Uint8 *pixel = (Uint8 *) dst->pixels + y * dst->pitch + x * 3;

                                Rshift = format->Rshift;
                                Gshift = format->Gshift;
                                Bshift = format->Bshift;

                                Rshift8 = Rshift >> 3;
                                Gshift8 = Gshift >> 3;
                                Bshift8 = Bshift >> 3;

                                sR = (color >> Rshift) & 0xFF;
                                sG = (color >> Gshift) & 0xFF;
                                sB = (color >> Bshift) & 0xFF;

                                if (alpha == 255) {
                                        *(pixel + Rshift8) = sR;
                                        *(pixel + Gshift8) = sG;
                                        *(pixel + Bshift8) = sB;
                                } else {
                                        dR = *((pixel) + Rshift8);
                                        dG = *((pixel) + Gshift8);
                                        dB = *((pixel) + Bshift8);

                                        R = dR + ((sR - dR) * alpha >> 8);
                                        G = dG + ((sG - dG) * alpha >> 8);
                                        B = dB + ((sB - dB) * alpha >> 8);

                                        *((pixel) + Rshift8) = R;
                                        *((pixel) + Gshift8) = G;
                                        *((pixel) + Bshift8) = B;
                                }
                        }
                        break;

#ifdef DEFAULT_ALPHA_PIXEL_ROUTINE

                case 4:
                        {               /* Probably :-) 32-bpp */
                                Uint32 R, G, B, A;
                                Uint32 *pixel = (Uint32 *) dst->pixels + y * dst->pitch / 4 + x;
                                if (alpha == 255) {
                                        *pixel = color;
                                } else {
                                        Uint32 dc = *pixel;

                                        Rmask = format->Rmask;
                                        Gmask = format->Gmask;
                                        Bmask = format->Bmask;
                                        Amask = format->Amask;

                                        Rshift = format->Rshift;
                                        Gshift = format->Gshift;
                                        Bshift = format->Bshift;
                                        Ashift = format->Ashift;

                                        dR = (dc & Rmask) >> Rshift;
                                        dG = (dc & Gmask) >> Gshift;
                                        dB = (dc & Bmask) >> Bshift;


                                        R = ((dR + ((((color & Rmask) >> Rshift) - dR) * alpha >> 8)) << Rshift) & Rmask;
                                        G = ((dG + ((((color & Gmask) >> Gshift) - dG) * alpha >> 8)) << Gshift) & Gmask;
                                        B = ((dB + ((((color & Bmask) >> Bshift) - dB) * alpha >> 8)) << Bshift) & Bmask;
                                        *pixel = R | G | B;
                                        if (Amask!=0) {
                                                dA = (dc & Amask) >> Ashift;

#ifdef ALPHA_PIXEL_ADDITIVE_BLEND
                                                A = (dA | GFX_ALPHA_ADJUST_ARRAY[alpha & 255]) << Ashift; // make destination less transparent...
#else
                                                A = ((dA + ((((color & Amask) >> Ashift) - dA) * alpha >> 8)) << Ashift) & Amask;
#endif
                                                *pixel |= A;
                                        }
                                }
                        }
                        break;
#endif

#ifdef EXPERIMENTAL_ALPHA_PIXEL_ROUTINE

                case 4:{                /* Probably :-) 32-bpp */
                        if (alpha == 255) {
                                *((Uint32 *) dst->pixels + y * dst->pitch / 4 + x) = color;
                        } else {
                                Uint32 *pixel = (Uint32 *) dst->pixels + y * dst->pitch / 4 + x;
                                Uint32 dR, dG, dB, dA;
                                Uint32 dc = *pixel;

                                Uint32 surfaceAlpha, preMultR, preMultG, preMultB;
                                Uint32 aTmp;

                                Rmask = format->Rmask;
                                Gmask = format->Gmask;
                                Bmask = format->Bmask;
                                Amask = format->Amask;

                                dR = (color & Rmask);
                                dG = (color & Gmask);
                                dB = (color & Bmask);
                                dA = (color & Amask);

                                Rshift = format->Rshift;
                                Gshift = format->Gshift;
                                Bshift = format->Bshift;
                                Ashift = format->Ashift;

                                preMultR = (alpha * (dR >> Rshift));
                                preMultG = (alpha * (dG >> Gshift));
                                preMultB = (alpha * (dB >> Bshift));

                                surfaceAlpha = ((dc & Amask) >> Ashift);
                                aTmp = (255 - alpha);
                                if (A = 255 - ((aTmp * (255 - surfaceAlpha)) >> 8 )) {
                                        aTmp *= surfaceAlpha;
                                        R = (preMultR + ((aTmp * ((dc & Rmask) >> Rshift)) >> 8)) / A << Rshift & Rmask;
                                        G = (preMultG + ((aTmp * ((dc & Gmask) >> Gshift)) >> 8)) / A << Gshift & Gmask;
                                        B = (preMultB + ((aTmp * ((dc & Bmask) >> Bshift)) >> 8)) / A << Bshift & Bmask;
                                }
                                *pixel = R | G | B | (A << Ashift & Amask);

                        }
                           }
                           break;
#endif
                }
        }

        return (0);
}

int pixelColor(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color)
{
        Uint8 alpha;
        Uint32 mcolor;
        int result = 0;

        /*
        * Lock the surface 
        */
        if (SDL_MUSTLOCK(dst)) {
                if (SDL_LockSurface(dst) < 0) {
                        return (-1);
                }
        }

        /*
        * Setup color 
        */
        alpha = color & 0x000000ff;
        mcolor =
                SDL_MapRGBA(dst->format, (color & 0xff000000) >> 24,
                (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, alpha);

        /*
        * Draw 
        */
        result = _putPixelAlpha(dst, x, y, mcolor, alpha);

        /*
        * Unlock the surface 
        */
        if (SDL_MUSTLOCK(dst)) {
                SDL_UnlockSurface(dst);
        }

        return (result);
}

int pixelColorNolock(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color)
{
        Uint8 alpha;
        Uint32 mcolor;
        int result = 0;

        /*
        * Setup color 
        */
        alpha = color & 0x000000ff;
        mcolor =
                SDL_MapRGBA(dst->format, (color & 0xff000000) >> 24,
                (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, alpha);

        /*
        * Draw 
        */
        result = _putPixelAlpha(dst, x, y, mcolor, alpha);

        return (result);
}

void _murphyParaline(SDL_gfxMurphyIterator *m, Sint16 x, Sint16 y, int d1)
{
        int p;
        d1 = -d1;

        /*
        * Lock the surface 
        */
        if (SDL_MUSTLOCK(m->dst)) {
                SDL_LockSurface(m->dst);
        }

        for (p = 0; p <= m->u; p++) {

                pixelColorNolock(m->dst, x, y, m->color);

                if (d1 <= m->kt) {
                        if (m->oct2 == 0) {
                                x++;
                        } else {
                                if (m->quad4 == 0) {
                                        y++;
                                } else {
                                        y--;
                                }
                        }
                        d1 += m->kv;
                } else {        
                        x++;
                        if (m->quad4 == 0) {
                                y++;
                        } else {
                                y--;
                        }
                        d1 += m->kd;
                }
        }

        /* Unlock surface */
        if (SDL_MUSTLOCK(m->dst)) {
                SDL_UnlockSurface(m->dst);
        }

        m->tempx = x;
        m->tempy = y;
}

int _bresenhamInitialize(SDL_gfxBresenhamIterator *b, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2)
{
        int temp;

        if (b==NULL) {
                return(-1);
        }

        b->x = x1;
        b->y = y1;

        /* dx = abs(x2-x1), s1 = sign(x2-x1) */
        if ((b->dx = x2 - x1) != 0) {
                if (b->dx < 0) {
                        b->dx = -b->dx;
                        b->s1 = -1;
                } else {
                        b->s1 = 1;
                }
        } else {
                b->s1 = 0;      
        }

        /* dy = abs(y2-y1), s2 = sign(y2-y1)    */
        if ((b->dy = y2 - y1) != 0) {
                if (b->dy < 0) {
                        b->dy = -b->dy;
                        b->s2 = -1;
                } else {
                        b->s2 = 1;
                }
        } else {
                b->s2 = 0;      
        }

        if (b->dy > b->dx) {
                temp = b->dx;
                b->dx = b->dy;
                b->dy = temp;
                b->swapdir = 1;
        } else {
                b->swapdir = 0;
        }

        b->count = (b->dx<0) ? 0 : (unsigned int)b->dx;
        b->dy <<= 1;
        b->error = b->dy - b->dx;
        b->dx <<= 1;    

        return(0);
}


int _bresenhamIterate(SDL_gfxBresenhamIterator *b)
{       
        if (b==NULL) {
                return (-1);
        }

        /* last point check */
        if (b->count==0) {
                return (2);
        }

        while (b->error >= 0) {
                if (b->swapdir) {
                        b->x += b->s1;
                } else  {
                        b->y += b->s2;
                }

                b->error -= b->dx;
        }

        if (b->swapdir) {
                b->y += b->s2;
        } else {
                b->x += b->s1;
        }

        b->error += b->dy;      
        b->count--;             

        /* count==0 indicates "end-of-line" */
        return ((b->count) ? 0 : 1);
}



int lineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
{
        int pixx, pixy;
        int x, y;
        int dx, dy;
        int ax, ay;
        int sx, sy;
        int swaptmp;
        Uint8 *pixel;
        Uint8 *colorptr;

        /*
        * Variable setup 
        */
        dx = x2 - x1;
        dy = y2 - y1;
        sx = (dx >= 0) ? 1 : -1;
        sy = (dy >= 0) ? 1 : -1;

        /* Lock surface */
        if (SDL_MUSTLOCK(dst)) {
                if (SDL_LockSurface(dst) < 0) {
                        return (-1);
                }
        }

        /*
        * Check for alpha blending 
        */
        if ((color & 255) == 255) {

                /*
                * No alpha blending - use fast pixel routines 
                */

                /*
                * Setup color 
                */
                colorptr = (Uint8 *) & color;
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                        color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
                } else {
                        color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
                }

                /*
                * More variable setup 
                */
                dx = sx * dx + 1;
                dy = sy * dy + 1;
                pixx = dst->format->BytesPerPixel;
                pixy = dst->pitch;
                pixel = ((Uint8 *) dst->pixels) + pixx * (int) x1 + pixy * (int) y1;
                pixx *= sx;
                pixy *= sy;
                if (dx < dy) {
                        swaptmp = dx;
                        dx = dy;
                        dy = swaptmp;
                        swaptmp = pixx;
                        pixx = pixy;
                        pixy = swaptmp;
                }

                /*
                * Draw 
                */
                x = 0;
                y = 0;
                switch (dst->format->BytesPerPixel) {
                case 1:
                        for (; x < dx; x++, pixel += pixx) {
                                *pixel = color;
                                y += dy;
                                if (y >= dx) {
                                        y -= dx;
                                        pixel += pixy;
                                }
                        }
                        break;
                case 2:
                        for (; x < dx; x++, pixel += pixx) {
                                *(Uint16 *) pixel = color;
                                y += dy;
                                if (y >= dx) {
                                        y -= dx;
                                        pixel += pixy;
                                }
                        }
                        break;
                case 3:
                        for (; x < dx; x++, pixel += pixx) {
                                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                                        pixel[0] = (color >> 16) & 0xff;
                                        pixel[1] = (color >> 8) & 0xff;
                                        pixel[2] = color & 0xff;
                                } else {
                                        pixel[0] = color & 0xff;
                                        pixel[1] = (color >> 8) & 0xff;
                                        pixel[2] = (color >> 16) & 0xff;
                                }
                                y += dy;
                                if (y >= dx) {
                                        y -= dx;
                                        pixel += pixy;
                                }
                        }
                        break;
                default:                /* case 4 */
                        for (; x < dx; x++, pixel += pixx) {
                                *(Uint32 *) pixel = color;
                                y += dy;
                                if (y >= dx) {
                                        y -= dx;
                                        pixel += pixy;
                                }
                        }
                        break;
                }

        } else {

                /*
                * Alpha blending required - use single-pixel blits 
                */

                ax = ABS(dx) << 1;
                ay = ABS(dy) << 1;
                x = x1;
                y = y1;
                if (ax > ay) {
                        int d = ay - (ax >> 1);

                        while (x != x2) {
                                pixelColorNolock (dst, x, y, color);
                                if (d > 0 || (d == 0 && sx == 1)) {
                                        y += sy;
                                        d -= ax;
                                }
                                x += sx;
                                d += ay;
                        }
                } else {
                        int d = ax - (ay >> 1);

                        while (y != y2) {
                                pixelColorNolock (dst, x, y, color);
                                if (d > 0 || ((d == 0) && (sy == 1))) {
                                        x += sx;
                                        d -= ay;
                                }
                                y += sy;
                                d += ax;
                        }
                }
                pixelColorNolock (dst, x, y, color);

        }

        /* Unlock surface */
        if (SDL_MUSTLOCK(dst)) {
                SDL_UnlockSurface(dst);
        }

        return (0);
}

int polygonColor(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color)
{
        int result;
        int i;
        const Sint16 *x1, *y1, *x2, *y2;

        /*
        * Check visibility of clipping rectangle
        */
        if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
                return(0);
        }

        /*
        * Vertex array NULL check 
        */
        if (vx == NULL) {
                return (-1);
        }
        if (vy == NULL) {
                return (-1);
        }

        /*
        * Sanity check 
        */
        if (n < 3) {
                return (-1);
        }

        /*
        * Pointer setup 
        */
        x1 = x2 = vx;
        y1 = y2 = vy;
        x2++;
        y2++;

        /*
        * Draw 
        */
        result = 0;
        for (i = 1; i < n; i++) {
                result |= lineColor(dst, *x1, *y1, *x2, *y2, color);
                x1 = x2;
                y1 = y2;
                x2++;
                y2++;
        }
        result |= lineColor(dst, *x1, *y1, *vx, *vy, color);

        return (result);
}

void _murphyIteration(SDL_gfxMurphyIterator *m, Uint8 miter, 
        Uint16 ml1bx, Uint16 ml1by, Uint16 ml2bx, Uint16 ml2by, 
        Uint16 ml1x, Uint16 ml1y, Uint16 ml2x, Uint16 ml2y)
{
        int atemp1, atemp2;
        int ftmp1, ftmp2;
        Uint16 m1x, m1y, m2x, m2y;      
        Uint16 fix, fiy, lax, lay, curx, cury;
        Sint16 px[4], py[4];
        SDL_gfxBresenhamIterator b;

        if (miter > 1) {
                if (m->first1x != -32768) {
                        fix = (m->first1x + m->first2x) / 2;
                        fiy = (m->first1y + m->first2y) / 2;
                        lax = (m->last1x + m->last2x) / 2;
                        lay = (m->last1y + m->last2y) / 2;
                        curx = (ml1x + ml2x) / 2;
                        cury = (ml1y + ml2y) / 2;

                        atemp1 = (fix - curx);
                        atemp2 = (fiy - cury);
                        ftmp1 = atemp1 * atemp1 + atemp2 * atemp2;
                        atemp1 = (lax - curx);
                        atemp2 = (lay - cury);
                        ftmp2 = atemp1 * atemp1 + atemp2 * atemp2;

                        if (ftmp1 <= ftmp2) {
                                m1x = m->first1x;
                                m1y = m->first1y;
                                m2x = m->first2x;
                                m2y = m->first2y;
                        } else {
                                m1x = m->last1x;
                                m1y = m->last1y;
                                m2x = m->last2x;
                                m2y = m->last2y;
                        }

                        atemp1 = (m2x - ml2x);
                        atemp2 = (m2y - ml2y);
                        ftmp1 = atemp1 * atemp1 + atemp2 * atemp2;
                        atemp1 = (m2x - ml2bx);
                        atemp2 = (m2y - ml2by);
                        ftmp2 = atemp1 * atemp1 + atemp2 * atemp2;

                        if (ftmp2 >= ftmp1) {
                                ftmp1 = ml2bx;
                                ftmp2 = ml2by;
                                ml2bx = ml2x;
                                ml2by = ml2y;
                                ml2x = ftmp1;
                                ml2y = ftmp2;
                                ftmp1 = ml1bx;
                                ftmp2 = ml1by;
                                ml1bx = ml1x;
                                ml1by = ml1y;
                                ml1x = ftmp1;
                                ml1y = ftmp2;
                        }

                        /*
                        * Lock the surface 
                        */
                        if (SDL_MUSTLOCK(m->dst)) {
                                SDL_LockSurface(m->dst);
                        }

                        _bresenhamInitialize(&b, m2x, m2y, m1x, m1y);
                        do {
                                pixelColorNolock(m->dst, b.x, b.y, m->color);
                        } while (_bresenhamIterate(&b)==0);

                        _bresenhamInitialize(&b, m1x, m1y, ml1bx, ml1by);
                        do {
                                pixelColorNolock(m->dst, b.x, b.y, m->color);
                        } while (_bresenhamIterate(&b)==0);

                        _bresenhamInitialize(&b, ml1bx, ml1by, ml2bx, ml2by);
                        do {
                                pixelColorNolock(m->dst, b.x, b.y, m->color);
                        } while (_bresenhamIterate(&b)==0);

                        _bresenhamInitialize(&b, ml2bx, ml2by, m2x, m2y);
                        do {
                                pixelColorNolock(m->dst, b.x, b.y, m->color);
                        } while (_bresenhamIterate(&b)==0);

                        /* Unlock surface */
                        if (SDL_MUSTLOCK(m->dst)) {
                                SDL_UnlockSurface(m->dst);
                        }

                        px[0] = m1x;
                        px[1] = m2x;
                        px[2] = ml1bx;
                        px[3] = ml2bx;
                        py[0] = m1y;
                        py[1] = m2y;
                        py[2] = ml1by;
                        py[3] = ml2by;
                        polygonColor(m->dst, px, py, 4, m->color);                                              
                }
        }

        m->last1x = ml1x;
        m->last1y = ml1y;
        m->last2x = ml2x;
        m->last2y = ml2y;
        m->first1x = ml1bx;
        m->first1y = ml1by;
        m->first2x = ml2bx;
        m->first2y = ml2by;
}

#define HYPOT(x,y) sqrt((double)(x)*(double)(x)+(double)(y)*(double)(y)) 

 void Renderer::_murphyWideline(SDL_gfxMurphyIterator *m, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, Uint8 miter)
 {       
    float offset = (float)width / 2.f;
 
    Sint16 temp;
    Sint16 ptx, pty, ptxx, ptxy, ml1x, ml1y, ml2x, ml2y, ml1bx, ml1by, ml2bx, ml2by;
 
    int d0, d1;             /* difference terms d0=perpendicular to line, d1=along line */
 
    int q;                  /* pel counter,q=perpendicular to line */
    int tmp;
 
    int dd;                 /* distance along line */
    int tk;                 /* thickness threshold */
    double ang;             /* angle for initial point calculation */
    double sang, cang;
 
    /* Initialisation */
    m->u = x2 - x1; /* delta x */
    m->v = y2 - y1; /* delta y */
 
    if (m->u < 0) { /* swap to make sure we are in quadrants 1 or 4 */
            temp = x1;
            x1 = x2;
            x2 = temp;
            temp = y1;
            y1 = y2;
            y2 = temp;              
            m->u *= -1;
            m->v *= -1;
    }
 
    if (m->v < 0) { /* swap to 1st quadrant and flag */
            m->v *= -1;
            m->quad4 = 1;
    } else {
            m->quad4 = 0;
    }
 
    if (m->v > m->u) {      /* swap things if in 2 octant */
            tmp = m->u;
            m->u = m->v;
            m->v = tmp;
            m->oct2 = 1;
    } else {
            m->oct2 = 0;
    }
    m->ku = m->u + m->u;    /* change in l for square shift */
    m->kv = m->v + m->v;    /* change in d for square shift */
    m->kd = m->kv - m->ku;  /* change in d for diagonal shift */
    m->kt = m->u - m->kv;   /* diag/square decision threshold */
 
    d0 = 0;
    d1 = 0;
    dd = 0;
 
    ang = atan((double) m->v / (double) m->u);      /* calc new initial point - offset both sides of ideal */       
    sang = sin(ang);
    cang = cos(ang);
 
    if (m->oct2 == 0) {
            ptx = x1 + (Sint16)lrint(offset * sang);
            if (m->quad4 == 0) {
                    pty = y1 - (Sint16)lrint(offset * cang);
            } else {
                    pty = y1 + (Sint16)lrint(offset * cang);
            }
    } else {
            ptx = x1 - (Sint16)lrint(offset * cang);
            if (m->quad4 == 0) {
                    pty = y1 + (Sint16)lrint(offset * sang);
            } else {
                    pty = y1 - (Sint16)lrint(offset * sang);
            }
    }
 
    /* used here for constant thickness line */
    tk = (int) (4. * HYPOT(ptx - x1, pty - y1) * HYPOT(m->u, m->v));
 
    if (miter == 0) {
            m->first1x = -32768;
            m->first1y = -32768;
            m->first2x = -32768;
            m->first2y = -32768;
            m->last1x = -32768;
            m->last1y = -32768;
            m->last2x = -32768;
            m->last2y = -32768;
    }
    ptxx = ptx;
    ptxy = pty;
 
    for (q = 0; dd <= tk; q++) {    /* outer loop, stepping perpendicular to line */
 
            _murphyParaline(m, ptx, pty, d1);       /* call to inner loop - right edge */
            if (q == 0) {
                    ml1x = ptx;
                    ml1y = pty;
                    ml1bx = m->tempx;
                    ml1by = m->tempy;
            } else {
                    ml2x = ptx;
                    ml2y = pty;
                    ml2bx = m->tempx;
                    ml2by = m->tempy;
            }
            if (d0 < m->kt) {       /* square move */
                    if (m->oct2 == 0) {
                            if (m->quad4 == 0) {
                                    pty++;
                            } else {
                                    pty--;
                            }
                    } else {
                            ptx++;
                    }
            } else {        /* diagonal move */
                    dd += m->kv;
                    d0 -= m->ku;
                    if (d1 < m->kt) {       /* normal diagonal */
                            if (m->oct2 == 0) {
                                    ptx--;
                                    if (m->quad4 == 0) {
                                            pty++;
                                    } else {
                                            pty--;
                                    }
                            } else {
                                    ptx++;
                                    if (m->quad4 == 0) {
                                            pty--;
                                    } else {
                                            pty++;
                                    }
                            }
                            d1 += m->kv;
                    } else {        /* double square move, extra parallel line */
                            if (m->oct2 == 0) {
                                    ptx--;
                            } else {
                                    if (m->quad4 == 0) {
                                            pty--;
                                    } else {
                                            pty++;
                                    }
                            }
                            d1 += m->kd;
                            if (dd > tk) {
                                    _murphyIteration(m, miter, ml1bx, ml1by, ml2bx, ml2by, ml1x, ml1y, ml2x, ml2y);
                                    return; /* breakout on the extra line */
                            }
                            _murphyParaline(m, ptx, pty, d1);
                            if (m->oct2 == 0) {
                                    if (m->quad4 == 0) {
                                            pty++;
                                    } else {
 
                                            pty--;
                                    }
                            } else {
                                    ptx++;
                            }
                    }
            }
            dd += m->ku;
            d0 += m->kv;
    }
 
    _murphyIteration(m, miter, ml1bx, ml1by, ml2bx, ml2by, ml1x, ml1y, ml2x, ml2y);
 }

 int thickLineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, Uint32 color)
 {
	int wh;
	SDL_gfxMurphyIterator m;
	
	if (dst == NULL) return -1;
	if (width < 1) return -1;
	
	///* Special case: thick "point" */
	//if ((x1 == x2) && (y1 == y2)) 
	//{
	//	wh = width / 2;
	//	return boxColor(dst, x1 - wh, y1 - wh, x2 + width, y2 + width, color);	
	//}
	
	m.dst = dst;
	m.color = color;
	
	_murphyWideline(&m, x1, y1, x2, y2, width, 0);
	_murphyWideline(&m, x1, y1, x2, y2, width, 1);
	
	return(0);
}

void Renderer::drawTexture(SDL_Texture* img, Rect _dst)
{
	SDL_Rect dst;
	_dst = cameraTransform(_dst);
	dst.x = (int)_dst.pos.x;
	dst.y = (int)_dst.pos.y;
	dst.w = (int)_dst.size.w;
	dst.h = (int)_dst.size.h;
	SDL_RenderCopy(sdl_renderer, img, NULL, &dst);
}

void Renderer::drawTexture(SDL_Texture* img, Rect _src, Rect _dst)
{
	SDL_Rect dst;
	_dst = cameraTransform(_dst);
	dst.x = (int)_dst.pos.x;
	dst.y = (int)_dst.pos.y;
	dst.w = (int)_dst.size.w;
	dst.h = (int)_dst.size.h;

	SDL_Rect src;
	src.x = (int)_src.pos.x;
	src.y = (int)_src.pos.y;
	src.w = (int)_src.size.w;
	src.h = (int)_src.size.h;
	SDL_RenderCopy(sdl_renderer, img, &src, &dst);
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

void Renderer::drawLine(Vector2D _start, Vector2D _end, Colour c)
{
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	auto start = m_camera->worldToScreen(Camera2D::Point(_start.x, _start.y));
	auto end = m_camera->worldToScreen(Camera2D::Point(_end.x, _end.y));
	SDL_RenderDrawLine(sdl_renderer, start.x, start.y, end.x, end.y);
}

void Renderer::drawTextureWithAngle(SDL_Texture* img, Rect _src, Rect _dst, float angle)
{
	SDL_Rect dst;
	_dst = cameraTransform(_dst);
	dst.x = (int)_dst.pos.x;
	dst.y = (int)_dst.pos.y;
	dst.w = (int)_dst.size.w;
	dst.h = (int)_dst.size.h;

	SDL_Rect src;
	src.x = (int)_src.pos.x;
	src.y = (int)_src.pos.y;
	src.w = (int)_src.size.w;
	src.h = (int)_src.size.h;
	SDL_RenderCopyEx(sdl_renderer, img, &src, &dst, angle, NULL, SDL_FLIP_NONE);
}

void Renderer::drawTextureWithAngle(SDL_Texture * img, Rect _dst, float angle)
{
	SDL_Rect dst;
	_dst = cameraTransform(_dst);
	dst.x = (int)_dst.pos.x;
	dst.y = (int)_dst.pos.y;
	dst.w = (int)_dst.size.w;
	dst.h = (int)_dst.size.h;

	SDL_RenderCopyEx(sdl_renderer, img, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
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
			drawBox2DPolygon(polygonShape, b2Fixture->GetBody()->GetAngle());
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

bool Renderer::init(const Vector2D& winSize, const char* title, Camera2D::Camera* cam)
{
	m_camera = cam;
	int e = SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2
	windowSize = winSize;
	if (e != 0) {
		// problem with SDL?...
		std::cout << "Could not init SDL: " << SDL_GetError() << std::endl;
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
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize PNG loading
	/*int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
	std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
	return false;
	}*/

	sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == NULL) {
		// In the case that the renderer could not be made...
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::setNewCamera(Camera2D::Camera * newCam)
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

void Renderer::drawRect(const Rect& r, const Colour& c) 
{
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
	SDL_Rect rect = m_camera->worldToScreen(CustomRect(r.pos.x, r.pos.y, r.size.w, r.size.h));
	
	return Rect(rect.x, rect.y, rect.w, rect.h);
}