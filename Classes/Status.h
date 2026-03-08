#pragma once
#include "esphome.h"
#include "Utilities/FloatAnimator.h"

class Status {
public:
    static Status& getInstance() {
        static Status instance;
        return instance;
    }

    bool isLoved = false;
    bool isScared = false;
    float eyeXCurrent = 0.0f;
    float eyeXTarget = 0.0f;
    float eyeYCurrent = 0.0f;
    Color defaultEyeColor = Color(0, 255, 255);
    Color defaultBackgroundColor = Color(0, 0, 0);
    Utilities::FloatAnimator blinkAnimator = Utilities::FloatAnimator();
    Utilities::FloatAnimator horizontalMoveAnimator = Utilities::FloatAnimator();

    void setHappiness(int value) {
        happinessLevel = std::max(-100, std::min(100, value));
        ESP_LOGI("happiness", "New happiness: %d", happinessLevel);
        lastHappinessChange = esphome::millis();
    }

    void addHappiness(int delta) {
        id(happiness_meter).publish_state(happinessLevel + delta);
    }

    int getHappiness() const {
        return happinessLevel;
    }

    void decayHappiness() {
        if (hasHappinessChanged(900000) || happinessLevel == 0) {
            // Do not decay if happiness has changed in the last 15 minutes
            return;
        }

        int delta = 0;
        if (happinessLevel > 0) {
            delta = (int)std::max(happinessLevel * 0.05f, 1.0f);
        } else if (happinessLevel < 0) {
            delta = (int)std::min(happinessLevel * 0.05f, -1.0f);
        }
        addHappiness(-delta);
    }

    bool hasHappinessChanged(int milliseconds) {
        return lastHappinessChange < esphome::millis() - milliseconds;
    }

private:
    Status() = default;
    int happinessLevel = id(happiness_meter).state;
    int lastHappinessChange = esphome::millis();
};