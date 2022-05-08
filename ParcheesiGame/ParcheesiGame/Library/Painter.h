#ifndef __PAINTER__
#define __PAINTER__

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Painter {
    private:
        const SDL_Color CYAN_COLOR      = {   0, 255, 255 };
        const SDL_Color BLUE_COLOR      = {   0,   0, 255 };
        const SDL_Color ORANGE_COLOR    = { 255, 165,   0 };
        const SDL_Color YELLOW_COLOR    = { 255, 255,   0 };
        const SDL_Color LIME_COLOR      = {   0, 255,   0 };
        const SDL_Color PURPLE_COLOR    = { 128,   0, 128 };
        const SDL_Color RED_COLOR       = { 255,   0,   0 };
        const SDL_Color WHITE_COLOR     = { 255, 255, 255 };
        const SDL_Color BLACK_COLOR     = {   0,   0,   0 };
        const SDL_Color GREEN_COLOR     = { 0  , 128,   0 };
        const SDL_Color DEFAULT_COLOR   = WHITE_COLOR;
        SDL_Renderer* renderer;

    protected:
        SDL_Texture* texture;

        string pathImg;
        SDL_Rect rect;
        SDL_Rect clip;

        float x, y;
        float angle;
        SDL_Color color;

    public:
        Painter(SDL_Window* window, SDL_Renderer* renderer);
        Painter() {}
        ~Painter();

        void setPosition(float x, float y);
        float getPosition_x() const { return x; }
        float getPosition_y() const { return y; }

        void setAngle(float angle);
        float getAngle() const { return angle; }

        void setColor(SDL_Color color);
        SDL_Color getColor() const { return color; }

        void clearWithBgColor(SDL_Color bgColor);
        bool createRenderingImage(SDL_Renderer* renderer, SDL_Rect clip, SDL_Rect rect);
        bool createImage(SDL_Texture* texture, SDL_Rect rect);
        bool createImageFullWindow(SDL_Texture* texture);
        bool displayImage();

        bool loadTexture(SDL_Renderer* renderer, string path);

        SDL_Texture* loadTexture(string path);
        SDL_Texture* getTexture() { return texture; }

        SDL_Rect getRect()  { return rect; }
        SDL_Rect getClip()  { return clip; }
        string getPathImg() { cout << "***" << pathImg << '\n'; return pathImg; }

        void setObject(SDL_Rect rect, SDL_Rect clip, string pathImg);

        void setRect(SDL_Rect rect)     { this->rect = rect; }
        void setClip(SDL_Rect clip)     { this->clip = clip; }
        void setPathImg(string pathImg) { this->pathImg = pathImg; }
};

#endif // __PAINTER__