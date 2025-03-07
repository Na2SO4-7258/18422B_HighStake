#include "auto.h"
#include "motorcontrol.h"

int get_stake(){
    task::sleep(600);
    Pull.open();
    Intake(1);
    return 1;
}

void auto_neg_06(){
    task t = task(get_stake);
    GoForWard(60,-1300,1500);
    task::sleep(50);
    CorrectHeading(55,600);
    Intake(100);
    pos.MoveTo(60,115,1000);
    GoForWard(100,-700,1000);
    pos.MoveTo(80,80,1000);
    pos.MoveTo(97,120,1000);
    task::sleep(100);
    pos.MoveTo(83,25,1000);
    task::sleep(50);
    CorrectHeading(135,800);
    task::sleep(50);
    GoForWard(100,500,1000);
    Intake(-100,1);
    Move(40,40);
    task::sleep(500);
    Intake(100);
    Stop(hold);
    task::sleep(400);
    pos.MoveTo(30,90,1500);
    CorrectHeading(-45,700);
    Move(20,20);
    Lift(100);
    task::sleep(500);
    Lift(0);
    Stop(coast);
}