#include "EyeRenderer.h"
#include "Draw.h"

void EyeRenderer::render(esphome::display::Display& display) {
    auto& state = DeskBuddyState::getInstance();

    state.updateEyePosition();

    float x_off = state.eye_x_current;
    int eye_w = 60;
    int eye_h = (int)(80 * state.eye_height_pct);
    int spacing = 20;
    int cx = display.get_width() / 2;
    int cy = display.get_height() / 2;

    int lx = cx - spacing - eye_w + (int)x_off;
    int rx = cx + spacing + (int)x_off;

    if (state.is_scared) {
        renderScaredEyes(display, lx, rx, cy);
    } else if (state.is_petted) {
        renderLoveEyes(display, lx, rx, cy);
    } else if (state.happiness_level > 50) {
        renderHappyEyes(display, lx, rx, cy, eye_w, eye_h);
    } else if (state.happiness_level < -50) {
        renderSadEyes(display, lx, rx, cy, eye_w, eye_h);
    } else {
        renderNeutralEyes(display, lx, rx, cy, eye_w, eye_h);
    }
}

void EyeRenderer::renderScaredEyes(esphome::display::Display& display, int lx, int rx, int cy) {
    int jitter_x = (esphome::millis() % 12) - 6;
    int jitter_y = (esphome::millis() % 8) - 4;

    display.filled_circle(lx + 30 + jitter_x, cy + jitter_y, 12, EYE_COLOR);
    display.filled_circle(rx + 30 + jitter_x, cy + jitter_y, 12, EYE_COLOR);
}

void EyeRenderer::renderLoveEyes(esphome::display::Display& display, int lx, int rx, int cy) {
    Draw::heart(display, lx, cy - 30, 60, LOVE_COLOR);
    Draw::heart(display, rx, cy - 30, 60, LOVE_COLOR);
}

void EyeRenderer::renderHappyEyes(esphome::display::Display& display, int lx, int rx, int cy, int eye_w, int eye_h) {
    eye_h = eye_h * 0.25;
    int adjusted_cy = cy - 30;
    Draw::topHalfOval(display, lx, adjusted_cy - (eye_h / 2), eye_w, eye_h, EYE_COLOR);
    Draw::topHalfOval(display, rx, adjusted_cy - (eye_h / 2), eye_w, eye_h, EYE_COLOR);
}

void EyeRenderer::renderSadEyes(esphome::display::Display& display, int lx, int rx, int cy, int eye_w, int eye_h) {
    eye_h = eye_h * 0.75;
    int adjusted_cy = cy + 30;
    Draw::roundedRectangleWithOverlayTriangle(display, lx, adjusted_cy - (eye_h / 2), eye_w, eye_h, 15, EYE_COLOR, BG_COLOR, lx, adjusted_cy, true);
    Draw::roundedRectangleWithOverlayTriangle(display, rx, adjusted_cy - (eye_h / 2), eye_w, eye_h, 15, EYE_COLOR, BG_COLOR, rx + eye_w, adjusted_cy, false);
}

void EyeRenderer::renderNeutralEyes(esphome::display::Display& display, int lx, int rx, int cy, int eye_w, int eye_h) {
    Draw::roundedRectangle(display, lx, cy - (eye_h / 2), eye_w, eye_h, 15, EYE_COLOR);
    Draw::roundedRectangle(display, rx, cy - (eye_h / 2), eye_w, eye_h, 15, EYE_COLOR);
}
