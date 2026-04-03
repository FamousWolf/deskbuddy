#pragma once
#include "esphome.h"
#include "esphome/components/display/display.h"

namespace DeskBuddy {
    class DeskBuddy;

    namespace States {
        class BaseState {
        public:
            BaseState(::DeskBuddy::DeskBuddy *parent) : parent_(parent) {}

            virtual std::string getName() const {
                return "Unknown";
            }

            virtual bool isActive() = 0;

            virtual void render(esphome::display::Display* display, float x, float y, float blinkPercentage, esphome::Color eyeColor, esphome::Color backgroundColor) = 0;

        protected:
            ::DeskBuddy::DeskBuddy *parent_;
        };
    }
}
