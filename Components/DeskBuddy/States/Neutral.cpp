#include "Neutral.h"

namespace DeskBuddy {
    namespace States {
        Neutral::Neutral(::DeskBuddy::DeskBuddy *parent) : BaseState(parent) {}

        std::string Neutral::getName() const {
            return "Neutral";
        }

        bool Neutral::isActive() {
            // Neutral is the default state when all other states are inactive
            return true;
        }

        void Neutral::render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) {
            int spacing = 20;
            int width = 60;
            int height = 80 * blinkPercentage;
            int centerX = display->get_width() / 2;
            int centerY = display->get_height() / 2;

            int leftX = centerX - spacing - width + (int)x;
            int rightX = centerX + spacing + (int)x;

            ::DeskBuddy::Utilities::Draw::roundedRectangle(display, leftX, centerY - height / 2 + (int)y, width, height, 15, eyeColor);
            ::DeskBuddy::Utilities::Draw::roundedRectangle(display, rightX, centerY - height / 2 + (int)y, width, height, 15, eyeColor);
        }
    }
}
