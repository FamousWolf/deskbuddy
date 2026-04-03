#include "Sad.h"

namespace DeskBuddy {
    namespace States {
        Sad::Sad(::DeskBuddy::DeskBuddy *parent) : BaseState(parent) {}

        std::string Sad::getName() const {
            return "Sad";
        }

        bool Sad::isActive() {
            return parent_->hasForcedState("") && parent_->getHappiness() < -50.0f || parent_->hasForcedState(getName());
        }

        void Sad::render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) {
            int spacing = 20;
            int width = 60;
            int height = 60 * blinkPercentage;
            int centerX = display->get_width() / 2;
            int centerY = display->get_height() / 2 + 40;

            int leftX = centerX - spacing - width + x;
            int rightX = centerX + spacing + x;

            ::DeskBuddy::Utilities::Draw::roundedRectangleWithOverlayTriangle(display, leftX, centerY - height / 2 + y, width, height, 15,
                                                    eyeColor, backgroundColor, leftX, centerY + y, true);
            ::DeskBuddy::Utilities::Draw::roundedRectangleWithOverlayTriangle(display, rightX, centerY - height / 2 + y, width, height, 15,
                                                    eyeColor, backgroundColor, rightX + width, centerY + y, false);
        }
    }
}
