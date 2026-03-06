#pragma once
#include "esphome.h"
#include "DeskBuddyState.h"

class EyeRenderer {
public:
    static void render(esphome::display::Display& display);

private:
    static void renderScaredEyes(esphome::display::Display& display, int lx, int rx, int cy);
    static void renderLoveEyes(esphome::display::Display& display, int lx, int rx, int cy);
    static void renderHappyEyes(esphome::display::Display& display, int lx, int rx, int cy, int eye_w, int eye_h);
    static void renderSadEyes(esphome::display::Display& display, int lx, int rx, int cy, int eye_w, int eye_h);
    static void renderNeutralEyes(esphome::display::Display& display, int lx, int rx, int cy, int eye_w, int eye_h);

    static constexpr esphome::Color EYE_COLOR{0, 255, 255};
    static constexpr esphome::Color LOVE_COLOR{255, 50, 50};
    static constexpr esphome::Color BG_COLOR{0, 0, 0};
};
