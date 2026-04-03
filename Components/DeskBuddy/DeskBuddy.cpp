#include "DeskBuddy.h"
#include "Utilities/FloatAnimator.h"

namespace DeskBuddy {
    static const char *TAG = "DeskBuddy.component";

    void DeskBuddy::setup() {
        this->initInProgress = true;
        this->states = {
            new States::Loved(this),
            new States::Scared(this),
            new States::Sleeping(this),
            new States::Sleepy(this),
            new States::Sad(this),
            new States::Happy(this),
            new States::Neutral(this)
        };
        this->isLoved = false;
        this->isScared = false;
        this->isSleepy = false;
        this->isSleeping = false;
        this->eyeXCurrent = 0.0f;
        this->eyeYCurrent = 0.0f;
        this->defaultEyeColor = esphome::Color(0, 255, 255);
        this->defaultBackgroundColor = esphome::Color(0, 0, 0);
        this->blinkAnimator = Utilities::FloatAnimator();
        this->horizontalMoveAnimator = Utilities::FloatAnimator();
        this->currentState = "";
        this->forcedState = "";
        this->lastStateChange = 0;
    }

    void DeskBuddy::loop() {
        if (this->happiness_meter_ == nullptr || this->display_ == nullptr) {
            return;
        }

        if (this->initInProgress) {
            this->setHappiness((int)this->happiness_meter_->state, true, false);
            this->initInProgress = false;
        }

        float blinkPercentage = 1.0f;
        if (!this->blinkAnimator.isDone()) {
            blinkPercentage = Utilities::FloatAnimator::calculateV(this->blinkAnimator.update());
        }

        this->eyeXCurrent = this->horizontalMoveAnimator.update();

        if (this->hasForcedState("") && !this->hasHappinessChanged(300000)) {
            if (this->isCurrentState("Sleepy") && !this->hasStateChanged(30000)) {
                this->isSleepy = false;

                float randomValue = esp_random() % 100;
                if (randomValue < 50) {
                    this->isSleeping = true;
                } else {
                    this->isSleepy = false;
                }
            } else if (!this->hasStateChanged(300000)) {
                float randomValue = esp_random() % 100;
                if (this->isSleeping) {
                    if (randomValue < 50) {
                        this->isSleeping = false;
                    }
                } else if (randomValue < 10) {
                    this->isSleepy = true;
                } else {
                    ESP_LOGI(TAG, "No idle state change");
                    this->forceUpdateStateChanged();
                }
            }
        }

        for (auto state : states) {
            if (state->isActive()) {
                this->setState(state->getName());
                this->display_->fill(this->defaultBackgroundColor);
                state->render(this->display_, this->eyeXCurrent, this->eyeYCurrent, blinkPercentage,this->defaultEyeColor, this->defaultBackgroundColor);
                break;
            }
        }
    }

    void DeskBuddy::dump_config(){
        ESP_LOGCONFIG(TAG, "DeskBuddy component");
    }

    void DeskBuddy::startBlinking() {
        if (!this->blinkAnimator.isDone()) {
            return;
        }
        this->blinkAnimator.startAnimation(1.0f, 0.0f, 200);
    }

    void DeskBuddy::startHorizontalMove() {
        if (!this->horizontalMoveAnimator.isDone()) {
            return;
        }
        this->horizontalMoveAnimator.startAnimation(this->horizontalMoveAnimator.update(), (float)(esp_random() % 81) - 40, 500);
    }

    void DeskBuddy::setHappiness(int value, bool updateLastHappinessChange, bool publishState) {
        this->happiness = std::max(-100, std::min(100, value));

        if (publishState) {
            this->happiness_meter_->publish_state(this->happiness);
        }

        ESP_LOGI(TAG, "New happiness: %d", happiness);

        if (updateLastHappinessChange) {
            this->lastHappinessChange = esphome::millis();
        }
    }

    void DeskBuddy::addHappiness(int delta, bool updateLastHappinessChange) {
        this->setHappiness(this->happiness + delta, updateLastHappinessChange);
    }

    int DeskBuddy::getHappiness() {
        return this->happiness;
    }

    void DeskBuddy::decayHappiness() {
        if (this->hasHappinessChanged(900000) || this->happiness == 0) {
            // Do not decay if happiness has changed in the last 15 minutes
            return;
        }

        int delta = 0;
        if (this->happiness > 0) {
            delta = (int)std::max(this->happiness * 0.05f, 1.0f);
        } else if (happiness < 0) {
            delta = (int)std::min(this->happiness * 0.05f, -1.0f);
        }
        this->addHappiness(-delta, false);
    }

    bool DeskBuddy::hasHappinessChanged(int milliseconds) {
        return esphome::millis() - this->lastHappinessChange < milliseconds;
    }

    void DeskBuddy::forceState(std::string state) {
        ESP_LOGI(TAG, "Forced state: %s", state.c_str());

        if (state == "Auto") {
            state = "";
        }

        this->forcedState = state;
    }

    bool DeskBuddy::hasForcedState(std::string state) {
        return state.compare(this->forcedState) == 0;
    }

    void DeskBuddy::setState(std::string state) {
        if (this->currentState.compare(state) == 0) {
            return;
        }

        this->currentState = state;
        this->lastStateChange = esphome::millis();

        ESP_LOGI(TAG, "New state: %s", currentState.c_str());
    }

    bool DeskBuddy::hasStateChanged(int milliseconds) {
        return esphome::millis() - this->lastStateChange < milliseconds;
    }

    bool DeskBuddy::isCurrentState(std::string state) {
        return this->currentState.compare(state) == 0;
    }

    void DeskBuddy::resetState() {
        this->isLoved = false;
        this->isSleeping = false;
        this->isSleepy = false;
        this->isScared = false;
    }

    void DeskBuddy::forceUpdateStateChanged() {
        this->lastStateChange = esphome::millis();
    }

    void DeskBuddy::setHappinessMeter(esphome::number::Number *happiness_meter) {
        this->happiness_meter_ = happiness_meter;
    }

    void DeskBuddy::setDisplay(esphome::display::Display *display) {
        this->display_ = display;
    }
}
