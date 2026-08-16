#include "auton-selector.hpp"
#include "autons.hpp"
#include "main.h"

namespace auton_selector {
namespace {

struct Routine {
    const char* name;
    void (*run)();
};

Routine routines[] = {
    {"DO NOTHING", autons::doNothing},
    {"RED LEFT", autons::redLeft},
    {"RED RIGHT", autons::redRight},
    {"BLUE LEFT", autons::blueLeft},
    {"BLUE RIGHT", autons::blueRight},
    {"ODOM TEST", autons::odomTest},
};

constexpr int kRoutineCount = sizeof(routines) / sizeof(routines[0]);
int selected = 0;

void leftCallback() { previous(); }
void centerCallback() { refresh(); }
void rightCallback() { next(); }

} // namespace

void refresh() {
    pros::lcd::set_text(0, "ARCANE | OVERRIDE");
    pros::lcd::set_text(1, "Autonomous Selector");
    pros::lcd::set_text(2, "<      SELECT      >");
    pros::lcd::set_text(3, routines[selected].name);
    pros::lcd::set_text(5, "L/R: change auton");
    pros::lcd::set_text(6, "Selected runs on field");
}

void initialize() {
    pros::lcd::initialize();
    pros::lcd::register_btn0_cb(leftCallback);
    pros::lcd::register_btn1_cb(centerCallback);
    pros::lcd::register_btn2_cb(rightCallback);
    refresh();
}

void previous() {
    selected = (selected - 1 + kRoutineCount) % kRoutineCount;
    refresh();
}

void next() {
    selected = (selected + 1) % kRoutineCount;
    refresh();
}

void runSelected() {
    routines[selected].run();
}

const char* selectedName() {
    return routines[selected].name;
}

} // namespace auton_selector
