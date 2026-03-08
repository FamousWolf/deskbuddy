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

    void setHappiness(int value, bool updateLastHappinessChange = true, bool doNotPublishState = false) {
        happinessLevel = std::max(-100, std::min(100, value));

        if (!doNotPublishState) {
            id(happiness_meter).publish_state(happinessLevel);
        }

        ESP_LOGI("happiness", "New happiness: %d", happinessLevel);

        if (updateLastHappinessChange) {
            lastHappinessChange = esphome::millis();
        }
    }

    void addHappiness(int delta, bool updateLastHappinessChange = true, bool doNotPublishState = false) {
        setHappiness(happinessLevel + delta, updateLastHappinessChange, doNotPublishState);
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
        addHappiness(-delta, false);
    }

    bool hasHappinessChanged(int milliseconds) {
        return lastHappinessChange < esphome::millis() - milliseconds;
    }

    void forceState(std::string state) {
        ESP_LOGI("forcestate", "Forced state: %s", state.c_str());

        if (state == "Auto") {
            state = "";
        }

        forcedState = state;
    }

    bool hasForcedState(std::string state) {
        return state == forcedState;
    }

private:
    Status() = default;
    int happinessLevel = id(happiness_meter).state;
    int lastHappinessChange = esphome::millis();
    std::string forcedState = "";
};