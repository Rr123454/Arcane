#pragma once

namespace autons {

// Competition routine placeholders. Build each routine here as the robot and
// Override strategy are finalized; the selector can already switch among them.
void doNothing();
void redLeft();
void redRight();
void blueLeft();
void blueRight();
void odomTest();

} // namespace autons
