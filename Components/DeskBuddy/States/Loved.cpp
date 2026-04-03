#include "Loved.h"

namespace DeskBuddy {
    namespace States {
        Loved::Loved(::DeskBuddy::DeskBuddy *parent) : BaseState(parent) {}

        std::string Loved::getName() const {
            return "Loved";
        }

        bool Loved::isActive() {
            return parent_->hasForcedState("") && parent_->isLoved || parent_->hasForcedState(getName());
        }

        void Loved::render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) {
            int spacing = 20;
            int size = 60;

            int centerX = display->get_width() / 2;
            int centerY = display->get_height() / 2;

            int leftX = centerX - spacing - size + x;
            int rightX = centerX + spacing + x;

            ::DeskBuddy::Utilities::Draw::heart(display, leftX, centerY - size / 2 + y, size, esphome::Color(255, 0, 0));
            ::DeskBuddy::Utilities::Draw::heart(display, rightX, centerY - size / 2 + y, size, esphome::Color(255, 0, 0));
        }
    }
}
