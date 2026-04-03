#pragma once

#include "esphome/components/number/number.h"
#include "esphome/core/component.h"
#include "States/BaseState.h"
#include "States/Happy.h"
#include "States/Loved.h"
#include "States/Neutral.h"
#include "States/Sad.h"
#include "States/Scared.h"
#include "States/Sleeping.h"
#include "States/Sleepy.h"
#include "Utilities/FloatAnimator.h"

namespace DeskBuddy {
    class DeskBuddy : public esphome::Component {
    public:
        bool initInProgress;
        bool isLoved;
        bool isScared;
        bool isSleepy;
        bool isSleeping;
        float eyeXCurrent;
        float eyeYCurrent;
        esphome::Color defaultEyeColor;
        esphome::Color defaultBackgroundColor;
        Utilities::FloatAnimator blinkAnimator;
        Utilities::FloatAnimator horizontalMoveAnimator;

        void setup() override;
        void loop() override;
        void dump_config() override;
        void startBlinking();
        void startHorizontalMove();
        void setHappiness(int value, bool updateLastHappinessChange = true, bool publishState = true);
        void addHappiness(int delta, bool updateLastHappinessChange = true);
        int getHappiness();
        void decayHappiness();
        bool hasHappinessChanged(int milliseconds);
        void forceState(std::string state);
        bool hasForcedState(std::string state);
        void setState(std::string state);
        bool hasStateChanged(int milliseconds);
        bool isCurrentState(std::string state);
        void resetState();
        void forceUpdateStateChanged();
        void setHappinessMeter(esphome::number::Number *happiness_meter);
        void setDisplay(esphome::display::Display *display);

    private:
        std::vector<States::BaseState*> states;
        int happiness;
        int lastHappinessChange;
        int lastStateChange;
        std::string currentState;
        std::string forcedState;
        esphome::number::Number *happiness_meter_{nullptr};
        esphome::display::Display *display_{nullptr};
    };
}
