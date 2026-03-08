#pragma once
#include "esphome.h"

namespace Utilities {
    class FloatAnimator {
    public:
        static float calculateV(float input) {
            if (input <= 0.0f || input >= 1.0f) return 1.0f;
            return 2.0f * std::abs(input - 0.5f);
        }

        void startAnimation(float newStart, float newTarget, int newDurationMs) {
            start = newStart;
            target = newTarget;
            startTime = esphome::millis();
            durationMs = newDurationMs;
        }

        float update() {
            if (durationMs <= 0) {
                return target;
            }

            const float percentage = (float)(esphome::millis() - startTime) / durationMs;
            if (percentage >= 1.0f) {
                done();
                return target;
            }

            return std::lerp(start, target, percentage);
        }

        void done() {
            durationMs = 0;
        }

        bool isDone() const {
            return durationMs <= 0;
        }

    private:
        float start = 0.0f;
        float target = 0.0f;
        int startTime = 0;
        int durationMs = 0;
    };
};
