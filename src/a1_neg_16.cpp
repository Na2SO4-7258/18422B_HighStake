#include "auto.h"
#include "motorcontrol.h"

int task1(){
    while(Rotation.angle(deg) > 0 && Rotation.angle(deg) < 350){Lift(-100);}Lift(0,coast);return 1;
}

//14,-17,128
void auto_neg_16_R(){
    //打联队
    Intake(0);
    Lift(70);
    Move(20,20);
    task::sleep(300);
    Stop(coast);
    task::sleep(210);
    Lift(0,coast);
    Move(-60,-60);
    task::sleep(250);
    task t = task(task1);

    MoveTo_Para para = MoveTo_Para();
    para.break_power = 15;
    
    //夹底座
    pos.MoveTo(-10,35,1000,para);
    Move(-55,-35);
    task::sleep(300);
    Pull.open();
    task::sleep(100);
    Stop(hold);
    CorrectHeading(310,600);
    Intake(100);

    para.Power_PID = PID(4.5,0,10);
    para.break_power = 17;

    //吸三环
    pos.MoveTo(-57,114,1000,para);
    task::sleep(20);
    Move(-100,-100);
    task::sleep(350);
    CorrectHeading(270,400);
    pos.MoveTo(-80,69,1000,para);
    CorrectHeading(360,300);
    pos.MoveTo(-95,115,1000,para);

    para.Power_PID = PID(1.8,0,10);
    para.break_power = 10;
    pos.MoveTo(-99,-1,800,para);

    //吸角
    task::sleep(150);
    CorrectHeading(218,800);
    Intake(-65,1);
    Move(30,30);
    task::sleep(400);
    Intake(100);
    task::sleep(400);
    GoForWard(25,-220,500);
    task::sleep(400);
    RaiseHand.open();
    task::sleep(80);
    Intake(-50,1);
    Move(30,30);
    task::sleep(500);
    Stop(coast);
    Intake(100);
    task::sleep(500);

    //吸二层摸杆
    pos.MoveTo(-5,8,1000);
    task::sleep(100);
    CorrectHeading(93,700);
    task::sleep(100);
    GoForWard(50,400,600);
    CorrectHeading(0,700);
    RaiseHand.close();    
    GoForWard(100,300,1000);
    Move(20,20);
    task::sleep(500);
    Lift(0,coast);
    Stop(coast);
}

//-14,-17,-128
void auto_neg_16_B(){
    //打联队
    Intake(0);
    Lift(70);
    Move(20,20);
    task::sleep(300);
    Stop(coast);
    task::sleep(210);
    Lift(0,coast);
    Move(-60,-60);
    task::sleep(250);
    task t = task(task1);

    MoveTo_Para para = MoveTo_Para();
    para.break_power = 15;
    
    //夹底座
    pos.MoveTo(10,35,1000,para);
    Move(-35,-55);
    task::sleep(300);
    Pull.open();
    task::sleep(100);
    Stop(hold);
    CorrectHeading(-310,600);
    Intake(100);

    para.Power_PID = PID(4.5,0,10);
    para.break_power = 17;

    //吸三环
    pos.MoveTo(57,114,1000,para);
    task::sleep(20);
    Move(-100,-100);
    task::sleep(350);
    CorrectHeading(-270,400);
    pos.MoveTo(80,69,1000,para);
    CorrectHeading(-360,300);
    pos.MoveTo(95,115,1000,para);

    para.Power_PID = PID(1.8,0,10);
    para.break_power = 10;
    pos.MoveTo(99,-1,800,para);

    //吸角
    task::sleep(150);
    CorrectHeading(-218,800);
    Intake(-65,1);
    Move(30,30);
    task::sleep(400);
    Intake(100);
    task::sleep(400);
    GoForWard(25,-220,500);
    task::sleep(400);
    RaiseHand.open();
    task::sleep(80);
    Intake(-50,1);
    Move(30,30);
    task::sleep(500);
    Stop(coast);
    Intake(100);
    task::sleep(500);

    //吸二层摸杆
    pos.MoveTo(5,8,1000);
    task::sleep(100);
    CorrectHeading(-93,700);
    task::sleep(100);
    GoForWard(50,400,600);
    CorrectHeading(0,700);
    RaiseHand.close();    
    GoForWard(100,300,1000);
    Move(20,20);
    task::sleep(500);
    Lift(0,coast);
    Stop(coast);
}