#include "esphome.h"
#include "FloatAnimator.h"

namespace DeskBuddy {
    namespace Utilities {
        float FloatAnimator::calculateV(float input) {
            if (input <= 0.0f || input >= 1.0f) return 1.0f;
            return 2.0f * std::abs(input - 0.5f);
        }

        void FloatAnimator::startAnimation(float newStart, float newTarget, int newDurationMs) {
            start = newStart;
            target = newTarget;
            startTime = esphome::millis();
            durationMs = newDurationMs;
        }

        float FloatAnimator::update() {
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

        void FloatAnimator::done() {
            durationMs = 0;
        }

        bool FloatAnimator::isDone() {
            return durationMs <= 0;
        }
    }
}
