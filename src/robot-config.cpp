#include "robot-config.hpp"

namespace robot {

pros::Controller master(pros::E_CONTROLLER_MASTER);

// Existing drivetrain/lift ports preserved from the original main.cpp.
pros::MotorGroup leftDrive({1, -2, 3});
pros::MotorGroup rightDrive({-4, 5, -6});
pros::MotorGroup lift({7, 8});

pros::Rotation verticalTrackingRotation(ports::kVerticalTracking, kVerticalTrackingReversed);
pros::Rotation horizontalTrackingRotation(ports::kHorizontalTracking, kHorizontalTrackingReversed);
pros::Imu imu(ports::kImu);
pros::Distance frontDistance(ports::kFrontDistance);
pros::Optical intakeOptical(ports::kIntakeOptical);
pros::adi::DigitalIn liftBottomLimit(ports::kLiftBottomLimit);
pros::adi::DigitalIn mechanismLimit(ports::kMechanismLimit);

lemlib::TrackingWheel verticalTrackingWheel(
    &verticalTrackingRotation,
    kVerticalTrackingDiameter,
    kVerticalTrackingOffset);

lemlib::TrackingWheel horizontalTrackingWheel(
    &horizontalTrackingRotation,
    kHorizontalTrackingDiameter,
    kHorizontalTrackingOffset);

lemlib::Drivetrain drivetrain(
    &leftDrive,
    &rightDrive,
    kTrackWidth,
    kDriveWheelDiameter,
    kDriveRpm,
    2.0f);

// Starter PID values. These MUST be tuned on the finished robot.
lemlib::ControllerSettings lateralController(
    10.0f, // kP
    0.0f,  // kI
    3.0f,  // kD
    3.0f,  // anti-windup range
    1.0f,  // small error (in)
    100.0f,// small error timeout (ms)
    3.0f,  // large error (in)
    500.0f,// large error timeout (ms)
    20.0f  // slew
);

lemlib::ControllerSettings angularController(
    2.0f,  // kP
    0.0f,  // kI
    10.0f, // kD
    3.0f,  // anti-windup range
    1.0f,  // small error (deg)
    100.0f,// small error timeout (ms)
    3.0f,  // large error (deg)
    500.0f,// large error timeout (ms)
    0.0f   // slew
);

lemlib::OdomSensors odomSensors(
    &verticalTrackingWheel,
    nullptr,
    &horizontalTrackingWheel,
    nullptr,
    &imu);

lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensors);

void initializeHardware() {
    // Calibrates the IMU and resets LemLib's tracking sensors.
    chassis.calibrate();
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);

    // Optical LED is intentionally kept off by default. Turn it on in a routine
    // when you need reliable color/proximity readings inside the intake.
    intakeOptical.set_led_pwm(0);
}

} // namespace robot
