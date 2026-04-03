#include "Happy.h"

namespace DeskBuddy {
    namespace States {
        Happy::Happy(::DeskBuddy::DeskBuddy *parent) : BaseState(parent) {}

        std::string Happy::getName() const {
            return "Happy";
        }

        bool Happy::isActive() {
            return parent_->hasForcedState("") && parent_->getHappiness() > 50.0f || parent_->hasForcedState(getName());
        }

        void Happy::render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) {
            int spacing = 20;
            int width = 60;
            int height = 20 * blinkPercentage;
            int centerX = display->get_width() / 2;
            int centerY = display->get_height() / 2 - 40;

            int leftX = centerX - spacing - width + x;
            int rightX = centerX + spacing + x;

            if (height <= 7) {
                ::DeskBuddy::Utilities::Draw::topHalfOval(display, leftX, centerY - height / 2 + y, width, height, eyeColor);
                ::DeskBuddy::Utilities::Draw::topHalfOval(display, rightX, centerY - height / 2 + y, width, height, eyeColor);
            } else {
                ::DeskBuddy::Utilities::Draw::topHalfDonut(display, leftX, centerY - height / 2 + y, width, height, 7, eyeColor);
                ::DeskBuddy::Utilities::Draw::topHalfDonut(display, rightX, centerY - height / 2 + y, width, height, 7, eyeColor);
            }
        }
    }
}
