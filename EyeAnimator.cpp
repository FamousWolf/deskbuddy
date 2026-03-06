#include "EyeAnimator.h"

void EyeAnimator::performBlink() {
    auto& state = DeskBuddyState::getInstance();

    // Blink down
    for (int i = 0; i < 5; i++) {
        state.eye_height_pct -= 0.2f;
        esphome::delay(16);
    }

    // Blink up
    for (int i = 0; i < 5; i++) {
        state.eye_height_pct += 0.2f;
        esphome::delay(16);
    }

    state.eye_height_pct = 1.0f;
}

void EyeAnimator::performRandomAction() {
    auto& state = DeskBuddyState::getInstance();

    int choice = esp_random() % 10;
    if (choice < 3) {
        performBlink();
    } else if (choice < 6) {
        state.eye_x_target = (esp_random() % 81) - 40;
    }
}

void EyeAnimator::handleScaredReaction() {
    auto& state = DeskBuddyState::getInstance();

    state.is_scared = true;
    state.addHappiness(-15.0f);
    ESP_LOGI("scare", "Scare! Happiness: %.1f", state.happiness_level);
}

void EyeAnimator::handlePetInteraction() {
    auto& state = DeskBuddyState::getInstance();

    state.is_petted = true;
    state.addHappiness(5.0f);
    ESP_LOGI("touch", "Pet! Happiness: %.1f", state.happiness_level);
}
