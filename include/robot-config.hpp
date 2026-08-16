#pragma once

#include "main.h"
#include "lemlib/api.hpp"

namespace robot {

// -----------------------------------------------------------------------------
// Port map
// -----------------------------------------------------------------------------
// The drivetrain/lift ports below preserve the ports already in src/main.cpp.
// Sensor ports are starter assignments for the sensor package discussed for
// Override. Change them here if your physical wiring is different.
namespace ports {
constexpr int kVerticalTracking = 9;
constexpr int kHorizontalTracking = 10;
constexpr int kImu = 11;
constexpr int kFrontDistance = 12;
constexpr int kIntakeOptical = 13;

constexpr char kLiftBottomLimit = 'A';
constexpr char kMechanismLimit = 'B';
} // namespace ports

// -----------------------------------------------------------------------------
// Geometry / tuning
// -----------------------------------------------------------------------------
// IMPORTANT: Measure these on the finished robot before tuning autonomous.
// These defaults are only safe starting values so the project is structured.
constexpr float kTrackWidth = 12.0f;               // inches: left wheel contact center -> right
constexpr float kDriveWheelDiameter = 3.25f;       // inches
constexpr float kDriveRpm = 200.0f;                // wheel RPM after external gearing
constexpr float kVerticalTrackingDiameter = 2.75f; // inches
constexpr float kHorizontalTrackingDiameter = 2.75f;
constexpr float kVerticalTrackingOffset = 0.0f;    // +right / -left of tracking center
constexpr float kHorizontalTrackingOffset = 0.0f;  // +front / -back of tracking center

// Change these if either rotation sensor counts backward when the robot moves
// forward/right respectively.
constexpr bool kVerticalTrackingReversed = false;
constexpr bool kHorizontalTrackingReversed = false;

extern pros::Controller master;

extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;
extern pros::MotorGroup lift;

extern pros::Rotation verticalTrackingRotation;
extern pros::Rotation horizontalTrackingRotation;
extern pros::Imu imu;
extern pros::Distance frontDistance;
extern pros::Optical intakeOptical;
extern pros::adi::DigitalIn liftBottomLimit;
extern pros::adi::DigitalIn mechanismLimit;

extern lemlib::TrackingWheel verticalTrackingWheel;
extern lemlib::TrackingWheel horizontalTrackingWheel;
extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings lateralController;
extern lemlib::ControllerSettings angularController;
extern lemlib::OdomSensors odomSensors;
extern lemlib::Chassis chassis;

// Calibrates LemLib/IMU and resets odometry tracking sensors.
void initializeHardware();

} // namespace robot
