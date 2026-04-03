#pragma once

namespace DeskBuddy {
    namespace Utilities {
        class FloatAnimator {
        public:
            FloatAnimator() : start(0.0f), target(0.0f), startTime(0), durationMs(0) {}
            static float calculateV(float input);
            void startAnimation(float newStart, float newTarget, int newDurationMs);
            float update();
            void done();
            bool isDone();

        private:
            float start;
            float target;
            int startTime;
            int durationMs;
        };
    }
}
