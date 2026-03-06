#pragma once
#include "esphome.h"

class DeskBuddyState {
public:
    static DeskBuddyState& getInstance() {
        static DeskBuddyState instance;
        return instance;
    }

    bool init_in_progress = true;
    int eye_x_target = 0;
    float eye_x_current = 0.0f;
    float eye_height_pct = 1.0f;
    bool is_petted = false;
    bool is_scared = false;
    float happiness_level = 0.0f;

    void updateEyePosition() {
        eye_x_current += (eye_x_target - eye_x_current) * 0.15f;
    }

    void setHappiness(float value) {
        happiness_level = std::max(-100.0f, std::min(100.0f, value));
    }

    void addHappiness(float delta) {
        setHappiness(happiness_level + delta);
    }

private:
    DeskBuddyState() = default;
};
