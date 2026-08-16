#include "autons.hpp"
#include "robot-config.hpp"

namespace autons {

void doNothing() {
    robot::chassis.cancelAllMotions();
}

void redLeft() {
    // TODO: Replace with the final Override red-left route.
    robot::chassis.setPose(0, 0, 0);
}

void redRight() {
    // TODO: Replace with the final Override red-right route.
    robot::chassis.setPose(0, 0, 0);
}

void blueLeft() {
    // TODO: Replace with the final Override blue-left route.
    robot::chassis.setPose(0, 0, 0);
}

void blueRight() {
    // TODO: Replace with the final Override blue-right route.
    robot::chassis.setPose(0, 0, 0);
}

void odomTest() {
    // Safe tuning routine: drive forward 24 in, turn 90 deg, then return near
    // the starting point. Use this only on an open practice field.
    robot::chassis.setPose(0, 0, 0);

    robot::chassis.moveToPoint(0, 24, 2500, {.maxSpeed = 80}, false);
    robot::chassis.turnToHeading(90, 1800, {.maxSpeed = 70}, false);
    robot::chassis.moveToPoint(24, 24, 2500, {.maxSpeed = 80}, false);
}

} // namespace autons
