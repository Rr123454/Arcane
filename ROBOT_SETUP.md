# Arcane Override Robot Setup

This branch adds a centralized PROS + LemLib robot configuration, odometry sensor setup, and LCD autonomous selector.

## Current motor map

These ports were preserved from the original `src/main.cpp`:

| Device | Ports |
|---|---|
| Left drive | `1, -2, 3` |
| Right drive | `-4, 5, -6` |
| Lift | `7, 8` |

Negative motor ports are reversed.

## Starter sensor map

The repository did not previously contain sensor ports, so these are intentionally centralized in `include/robot-config.hpp` and must match the final wiring:

| Sensor | Starter port |
|---|---|
| Vertical tracking rotation sensor | 9 |
| Horizontal tracking rotation sensor | 10 |
| IMU | 11 |
| Front distance sensor | 12 |
| Intake optical sensor | 13 |
| Lift bottom limit | ADI A |
| Mechanism limit | ADI B |

Do not wire around these numbers blindly. If the physical robot uses different ports, edit only `include/robot-config.hpp`.

## LemLib geometry that must be measured

Before tuning PID or writing a competition autonomous, measure and update:

- `kTrackWidth`
- `kDriveWheelDiameter`
- `kDriveRpm`
- `kVerticalTrackingDiameter`
- `kHorizontalTrackingDiameter`
- `kVerticalTrackingOffset`
- `kHorizontalTrackingOffset`
- tracking sensor reversal flags

The tracking-wheel offsets are especially important. LemLib uses the distance from each tracking wheel to the robot's center of rotation.

## Autonomous selector

Use the Brain LCD buttons while disabled:

- **Left:** previous autonomous
- **Right:** next autonomous
- **Center:** refresh display

Available slots:

1. Do Nothing
2. Red Left
3. Red Right
4. Blue Left
5. Blue Right
6. Odom Test

The red/blue competition routines are intentionally empty placeholders until the robot dimensions and Override strategy are finalized. `Odom Test` is a simple movement routine for early localization tuning and should only be used in an open practice area.

## Recommended tuning order

1. Confirm every motor spins in the correct direction.
2. Confirm pushing the robot forward makes the vertical tracking value increase.
3. Confirm moving the robot to its right makes the horizontal tracking value increase.
4. Confirm IMU heading changes in the expected direction.
5. Measure all geometry values and enter them in `robot-config.hpp`.
6. Tune LemLib lateral PID.
7. Tune LemLib angular PID.
8. Validate odometry by driving known field distances and rotations.
9. Only then write the scoring autonomous routines.

## Still needed from the final mechanism design

The existing repository only identified drivetrain motors and a lift. Once intake, clamp, scoring, or pneumatic mechanisms are finalized, add their ports to `robot-config.hpp`, define their devices in `robot-config.cpp`, and bind their driver/autonomous controls there rather than scattering port numbers throughout the project.
