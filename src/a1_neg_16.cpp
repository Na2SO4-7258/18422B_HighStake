#include "auto.h"
#include "motorcontrol.h"

int temp1(){//等待打完环后再抬手
    while(1) if(DistanceSort.objectDistance(mm) < 50) break;
    task::sleep(100);
    Lift(30);
    return 1;
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
    Lift(0);
    GoForWard(100,-250,400);
    Lift(-80);

    MoveTo_Para para = MoveTo_Para();
    para.stop_turn_dis = 100;
    para.break_power = 10;
    para.must_turn_first = true;
    para.Power_PID = PID(2,0,10);
    
    //夹底座
    pos.MoveTo(-13,40,800,para);
    para.stop_turn_dis = 30;
    para.must_turn_first = false;
    Move(-60,-60);
    task::sleep(320);
    Lift(0,coast);
    Pull.open();
    task::sleep(20);
    Stop(hold);
    task::sleep(100);
    CorrectHeading(296,600);
    Intake(100);

    para.Power_PID = PID(4.5,0,10);
    para.break_power = 17;

    //吸三环
    pos.MoveTo(-62,110,1000,para);
    task::sleep(20);
    Move(-100,-100);
    task::sleep(350);
    CorrectHeading(270,400);
    pos.MoveTo(-78,69,1000,para);
    CorrectHeading(360,300);
    pos.MoveTo(-95,115,900,para);
    stopring = true;
    Intake(70);

    para.must_turn_first = true;
    para.Power_PID = PID(1.3,0,10);
    para.break_power = 10;
    para.stop_turn_dis =35;
    pos.MoveTo(-96,-9,1300,para);
    para.stop_turn_dis = 17;
    para.must_turn_first = false;

    Stop(hold);

    //吸角
    task::sleep(150);
    CorrectHeading(215,800);
    Intake(-65,1);
    stopring = false;
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
    stopring = true;
    GoForWard(50,-350,400);
    CorrectHeading(90,600);
    

    //吸二层摸杆
    para.Power_PID = PID(3,0,10);
    stopring = false;
    RaiseHand.open();
    pos.MoveTo(10,15,1000,para);
    GoForWard(50,400,600);
    RaiseHand.close(); 
    CorrectHeading(0,700);
    task t1 = task(temp1);
    GoForWard(100,300,1000);
    Move(20,20);
    task::sleep(500);
    Lift(0,coast);
    Stop(coast);
}

//-14,-17,-133
void auto_neg_16_B(){
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
    pos.MoveTo(15,40,800,para);
    para.stop_turn_dis = 30;
    para.must_turn_first = false;
    Move(-60,-60);
    task::sleep(300);
    Lift(0,coast);
    Pull.open();
    task::sleep(20);
    Stop(hold);
    task::sleep(100);
    CorrectHeading(-298,600);
    Intake(100);

    para.Power_PID = PID(4.5,0,10);
    para.break_power = 17;

    //吸三环
    pos.MoveTo(62,110,1000,para);
    task::sleep(20);
    Move(-100,-100);
    task::sleep(350);
    CorrectHeading(-270,400);
    pos.MoveTo(78,65,1000,para);
    CorrectHeading(-360,300);
    pos.MoveTo(95,110,900,para);
    stopring = true;
    Intake(70);

    para.must_turn_first = true;
    para.Power_PID = PID(1.3,0,10);
    para.break_power = 10;
    para.stop_turn_dis =35;
    pos.MoveTo(94,-9,1300,para);
    para.stop_turn_dis = 17;
    para.must_turn_first = false;

    Stop(hold);

    //吸角
    task::sleep(150);
    CorrectHeading(-218,800);
    Intake(-65,1);
    stopring = false;
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
    stopring = true;
    GoForWard(50,-350,400);
    CorrectHeading(-90,600);
    

    //吸二层摸杆
    para.Power_PID = PID(3,0,10);
    stopring = false;
    RaiseHand.open();
    pos.MoveTo(-10,10,1000,para);
    GoForWard(50,400,600);
    RaiseHand.close(); 
    CorrectHeading(0,700);
    task t1 = task(temp1);
    GoForWard(100,300,1000);
    Move(20,20);
    task::sleep(500);
    Lift(0,coast);
    Stop(coast);
}