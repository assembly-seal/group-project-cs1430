#include "renderer.h"

void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void Renderer::clear() {
    SDL_RenderClear(this->renderer);
}

void Renderer::draw() {
    SDL_RenderPresent(this->renderer);
    SDL_UpdateWindowSurface(this->window);
}

void Renderer::shutdown() {
    SDL_DestroyWindow(this->window);
}

void Renderer::setRectangle(SDL_Rect& rect, int x, int y, int w, int h) {
    this->rect = {x, y, w, h};
};

void Renderer::drawCircle(int x_pos, int y_pos, int radius) {
    double t1 = radius / 16.0;
    int x = radius;
    int y = 0;

    while (x > y) {
        setRectangle(rect, -x + x_pos, y + y_pos, x * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);
        setRectangle(rect, -y + x_pos, x + y_pos - 1, y * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);
        setRectangle(rect, -x + x_pos, -y + y_pos, x * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);
        setRectangle(rect, -y + x_pos, -x + y_pos + 1, y * 2, 1);
        SDL_RenderDrawRect(this->renderer, &rect);

        y++;
        t1 += y;
        double t2 = t1 - x;
        if (t2 >= 0) {
            t1 = t2;
            x--;
        }
    }
}