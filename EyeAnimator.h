#pragma once
#include "esphome.h"
#include "DeskBuddyState.h"

class EyeAnimator {
public:
    static void performBlink();
    static void performRandomAction();
    static void startNeutralAnimation();
    static void handleScaredReaction();
    static void handlePetInteraction();

private:
    static void blinkSequence();
};
