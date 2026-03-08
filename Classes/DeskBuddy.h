#pragma once
#include "esphome.h"
#include "Status.h"
#include "States/BaseState.h"
#include "States/Happy.h"
#include "States/Loved.h"
#include "States/Neutral.h"
#include "States/Sad.h"
#include "States/Scared.h"

class DeskBuddy {
public:
    static DeskBuddy& getInstance() {
        static DeskBuddy instance;
        return instance;
    }

    bool initInProgress = true;

    void render(esphome::display::Display& display) {
        Status& status = Status::getInstance();

        float blinkPercentage = 1.0f;
        if (!status.blinkAnimator.isDone()) {
            blinkPercentage = Utilities::FloatAnimator::calculateV(status.blinkAnimator.update());
        }

        status.eyeXCurrent = status.horizontalMoveAnimator.update();

        for (auto state : states) {
            if (state->isActive()) {
                state->render(display, status.eyeXCurrent, status.eyeYCurrent, blinkPercentage, status.defaultEyeColor, status.defaultBackgroundColor);
                break;
            }
        }
    }

    void startBlinking() {
        auto& status = Status::getInstance();

        if (!status.blinkAnimator.isDone()) {
            return;
        }

        status.blinkAnimator.startAnimation(1.0f, 0.0f, 200);
    }

    void startHorizontalMove() {
        auto& status = Status::getInstance();

        if (!status.horizontalMoveAnimator.isDone()) {
            return;
        }

        status.horizontalMoveAnimator.startAnimation(status.horizontalMoveAnimator.update(), (float)(esp_random() % 81) - 40, 500);
    }

private:
    std::vector<States::BaseState*> states = {
        new States::Loved(),
        new States::Scared(),
        new States::Sad(),
        new States::Happy(),
        new States::Neutral()
    };

    DeskBuddy() = default;
};
