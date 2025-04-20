#include "auto.h"
#include "motorcontrol.h"

//-9-22-124
void auto_pos_14_R(){
    //打联队
    Intake(0);
    Lift(70);
    Move(20,20);
    task::sleep(300);
    Stop(coast);
    task::sleep(210);
    Lift(0);
    GoForWard(100,-250,400);
    Lift(-80);

    MoveTo_Para para = MoveTo_Para();
    para.stop_turn_dis = 100;
    para.break_power = 10;
    para.must_turn_first = true;
    para.Power_PID = PID(2,0,10);
    
    //夹底座
    pos.MoveTo(18,40,1000,para);
    Move(-50,-50);
    task::sleep(290);
    Lift(0,coast);
    Pull.open();
    task::sleep(20);
    Intake(100);

    //吸二层
    CorrectHeading(-135,500);
    RaiseHand.open();
    pos.MoveTo(-25,22,1000);
    RaiseHand.close();
    Move(20,20);
    task::sleep(200);
    pos.MoveTo(18,63,1000);
    task::sleep(50);
    CorrectHeading(-270,800);

    //吸一环
    GoForWard(100,750,1000);
    task::sleep(50);
    CorrectHeading(-180,700);
    task::sleep(50);
    GoForWard(100,1050,1000);
    task::sleep(100);
    pos.MoveTo(105,-15,1300,para);

    //吸角
    Intake(-65,1);
    Move(31,31);
    task::sleep(400);
    Intake(100);
    task::sleep(400);
    GoForWard(25,-220,500);
    task::sleep(400);
    RaiseHand.open();
    task::sleep(80);
    Intake(-50,1);
    Move(30,30);
    task::sleep(450);
    Intake(100);
    RaiseHand.close();
    task::sleep(100);

    //摸杆-------------------------------------
    Move(-80,-80);
    task::sleep(300);
    Stop(hold);
    task::sleep(50);
    Lift_Tar=130;
    task a = task(LiftToAngle);
    CorrectHeading(-45,800);
    Intake(-100,1);
    Stop(hold);
    GoForWard(100,800,1000);
    Move(30,30);
    task::sleep(2000);
}

//9-22-124
void auto_pos_14_B(){
    //打联队
    Intake(0);
    Lift(70);
    Move(20,20);
    task::sleep(300);
    Stop(coast);
    task::sleep(210);
    Lift(0);
    GoForWard(100,-250,400);
    Lift(-80);

    MoveTo_Para para = MoveTo_Para();
    para.stop_turn_dis = 100;
    para.break_power = 10;
    para.must_turn_first = true;
    para.Power_PID = PID(2,0,10);
    
    //夹底座
    pos.MoveTo(-18,40,1000,para);
    Move(-50,-50);
    task::sleep(290);
    Lift(0,coast);
    Pull.open();
    task::sleep(20);
    Intake(100);

    //吸二层
    CorrectHeading(135,500);
    RaiseHand.open();
    pos.MoveTo(25,22,1000);
    RaiseHand.close();
    Move(20,20);
    task::sleep(200);
    pos.MoveTo(-18,63,1000);
    task::sleep(50);
    CorrectHeading(270,800);

    //吸一环
    GoForWard(100,750,1000);
    task::sleep(50);
    CorrectHeading(180,700);
    task::sleep(50);
    GoForWard(100,1050,1000);
    task::sleep(100);
    pos.MoveTo(-105,-15,1300,para);

    //吸角
    Intake(-65,1);
    Move(31,31);
    task::sleep(400);
    Intake(100);
    task::sleep(400);
    GoForWard(25,-220,500);
    task::sleep(400);
    RaiseHand.open();
    task::sleep(80);
    Intake(-50,1);
    Move(30,30);
    task::sleep(450);
    Intake(100);
    RaiseHand.close();
    task::sleep(100);

    //摸杆-------------------------------------
    Move(-80,-80);
    task::sleep(300);
    Stop(hold);
    task::sleep(50);
    Lift_Tar=130;
    task a = task(LiftToAngle);
    CorrectHeading(45,800);
    Intake(-100,1);
    Stop(hold);
    GoForWard(100,800,1000);
    Move(30,30);
    task::sleep(2000);
}