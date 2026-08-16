#include "main.h"
#include "auton-selector.hpp"
#include "robot-config.hpp"

void initialize() {
    auton_selector::initialize();

    pros::lcd::set_text(4, "Calibrating IMU...");
    robot::initializeHardware();
    pros::lcd::clear_line(4);

    auton_selector::refresh();
}

void disabled() {
    // Keep the selected autonomous visible while connected to a competition
    // switch/FMS. Left/right LCD buttons change the selection.
    auton_selector::refresh();
}

void competition_initialize() {
    auton_selector::refresh();
}

void autonomous() {
    pros::lcd::set_text(4, "RUNNING:");
    pros::lcd::set_text(5, auton_selector::selectedName());
    auton_selector::runSelected();
}

void opcontrol() {
    // Driver control currently uses the mechanisms that already existed in the
    // repository: six drive motors and a two-motor lift.
    robot::chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

    while (true) {
        const int throttle = robot::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        const int turn = robot::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // LemLib arcade drive gives one consistent drivetrain definition for
        // autonomous and driver control.
        robot::chassis.arcade(throttle, turn);

        // Lift controls: R1 up, R2 down. The bottom limit switch prevents the
        // lift from driving farther downward once the home position is reached.
        const bool liftUp = robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
        const bool liftDown = robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        const bool atLiftBottom = robot::liftBottomLimit.get_value();

        if (liftUp) {
            robot::lift.move(127);
        } else if (liftDown && !atLiftBottom) {
            robot::lift.move(-127);
        } else {
            robot::lift.move(0);
        }

        // Driver-screen sensor telemetry. This is useful during wiring and
        // tuning: verify the distance sensor, optical sensor and limit inputs
        // before relying on them in an autonomous routine.
        const auto pose = robot::chassis.getPose();
        pros::lcd::print(0, "X %.1f Y %.1f H %.1f", pose.x, pose.y, pose.theta);
        pros::lcd::print(1, "Distance: %d mm", robot::frontDistance.get_distance());
        pros::lcd::print(2, "Optical hue: %.1f", robot::intakeOptical.get_hue());
        pros::lcd::print(3, "Lift limit: %d", static_cast<int>(atLiftBottom));
        pros::lcd::print(4, "Mech limit: %d", static_cast<int>(robot::mechanismLimit.get_value()));

        pros::delay(20);
    }
}
