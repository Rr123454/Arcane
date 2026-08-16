#include "main.h"
#include "lemlib/api.hpp"

using namespace pros;
using namespace lemlib;

// -----------------------------------------------------------------------------
// Controller
// -----------------------------------------------------------------------------
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// -----------------------------------------------------------------------------
// Motors
// -----------------------------------------------------------------------------
// These are the same ports that were already in Arcane.
// A negative port means that motor is reversed.
pros::MotorGroup leftMotors({1, -2, 3}, pros::MotorGearset::green);
pros::MotorGroup rightMotors({-4, 5, -6}, pros::MotorGearset::green);
pros::MotorGroup liftMotors({7, 8}, pros::MotorGearset::green);

// -----------------------------------------------------------------------------
// Sensors
// -----------------------------------------------------------------------------
// Change this port to wherever the inertial sensor is actually plugged in.
pros::Imu imu(9);

// -----------------------------------------------------------------------------
// LemLib drivetrain
// -----------------------------------------------------------------------------
// IMPORTANT: these measurements are starter values.
// We will measure the real robot and tune them later.
lemlib::Drivetrain drivetrain(
    &leftMotors,                 // left motor group
    &rightMotors,                // right motor group
    12.0,                        // track width in inches
    lemlib::Omniwheel::NEW_325,  // drive wheel diameter
    200,                         // wheel RPM
    2                            // horizontal drift
);

// -----------------------------------------------------------------------------
// LemLib PID controllers
// -----------------------------------------------------------------------------
// These are starter values only. We will tune them on the real robot.
lemlib::ControllerSettings lateralController(
    10,   // kP
    0,    // kI
    3,    // kD
    3,    // anti-windup range
    1,    // small error range (inches)
    100,  // small error timeout (ms)
    3,    // large error range (inches)
    500,  // large error timeout (ms)
    20    // slew
);

lemlib::ControllerSettings angularController(
    2,    // kP
    0,    // kI
    10,   // kD
    3,    // anti-windup range
    1,    // small error range (degrees)
    100,  // small error timeout (ms)
    3,    // large error range (degrees)
    500,  // large error timeout (ms)
    0     // slew
);

// -----------------------------------------------------------------------------
// Odometry sensors
// -----------------------------------------------------------------------------
// For now we are only using the IMU.
// Later we will add the two tracking wheels here.
lemlib::OdomSensors sensors(
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    &imu     // inertial sensor
);

// -----------------------------------------------------------------------------
// Chassis
// -----------------------------------------------------------------------------
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    sensors
);

// -----------------------------------------------------------------------------
// Initialize
// -----------------------------------------------------------------------------
void initialize() {
    pros::lcd::initialize();
    pros::lcd::set_text(0, "Arcane - LemLib");

    // Calibrates the IMU and prepares LemLib.
    chassis.calibrate();

    // Print the robot pose to the Brain screen.
    pros::Task screenTask([] {
        while (true) {
            pros::lcd::print(1, "X: %.2f", chassis.getPose().x);
            pros::lcd::print(2, "Y: %.2f", chassis.getPose().y);
            pros::lcd::print(3, "Heading: %.2f", chassis.getPose().theta);
            pros::delay(50);
        }
    });
}

void disabled() {}

void competition_initialize() {}

// -----------------------------------------------------------------------------
// Autonomous
// -----------------------------------------------------------------------------
void autonomous() {
    // Tell LemLib where the robot starts.
    chassis.setPose(0, 0, 0);

    // Simple test autonomous.
    // Drive forward 24 inches, then turn to 90 degrees.
    chassis.moveToPoint(0, 24, 2000);
    chassis.turnToHeading(90, 1500);
}

// -----------------------------------------------------------------------------
// Driver control
// -----------------------------------------------------------------------------
void opcontrol() {
    while (true) {
        int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // LemLib arcade drive.
        chassis.arcade(forward, turn);

        // Lift control.
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            liftMotors.move(127);
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            liftMotors.move(-127);
        }
        else {
            liftMotors.brake();
        }

        pros::delay(20);
    }
}
