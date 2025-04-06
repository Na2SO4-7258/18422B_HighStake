#include "auto.h"
#include "motorcontrol.h"

//13,13,-25
void auto_pos_stake_R(){
    MoveTo_Para para;
    //抢底座
    Hook.open();
    Intake(100,1);
    //GoForWard(100,1550,1000,PID(0.4,0,5));
    para.Power_PID = PID(5,0,5);
    pos.MoveTo(-16,87,1000,para);
    Hook.close();
    task::sleep(50);
    while(pos.Y() > 65) Move(-100,-100); 
    Move(-30,-30);
    task::sleep(100);
    Stop(hold);
    Hook.open();
    task::sleep(200);
    Move(-50,-50);
    task::sleep(150);
    Hook.close();
    Stop(hold);
    task::sleep(100);
    Intake(0);

    //夹二墩
    CorrectHeading(116,700);
    task::sleep(50);
    para = MoveTo_Para();
    para.stop_turn_dis = 40;
    pos.MoveTo(-44,56,1000,para);
    Move(-50,-50);
    task::sleep(350);
    Pull.open();
    task::sleep(30);
    Intake(100);
    Stop(hold);
    pos.MoveTo(-30,10,1000);

    //清角
    pos.MoveTo(5,-12,1000);
    task::sleep(50);
    Move(30,30);
    task::sleep(200);
    Stop(hold);
    task::sleep(100);
    for(int i = 0;i<3;i++){
        Intake(-100,1);
        Move(24,24);
        task::sleep(500);
        Intake(100);
        task::sleep(200);
        GoForWard(25,-230,500);
        task::sleep(500);
    }
    Intake(100);
    Move(40,40);
    task::sleep(300);
    Stop(hold);
    Move(-50,-50);
    task::sleep(200);
    Stop(hold);
    Intake(0);
    CorrectHeading(-30,700); 
    Move(-100,-100);
    task::sleep(100);
    Pull.close();
    GoForWard(40,-500,500);

    //夹一墩
    GoForWard(100,300,500);
    CorrectHeading(-170,700);
    pos.MoveTo(-3,56,1000);
    Move(-50,-50);
    task::sleep(220);
    Pull.open();
    task::sleep(30);
    Stop(hold);
}

//48,13,-24
void auto_pos_stake_B(){
    MoveTo_Para para;
    //抢底座
    Hook.open();
    Intake(100,1);
    //GoForWard(100,1550,1000,PID(0.4,0,5));
    para.Power_PID = PID(5,0,5);
    pos.MoveTo(18,85,1000,para);
    Hook.close();
    task::sleep(50);
    while(pos.Y() > 65) Move(-100,-100); 
    Move(-30,-30);
    task::sleep(100);
    Stop(hold);
    Hook.open();
    task::sleep(200);
    Move(-50,-50);
    task::sleep(150);
    Hook.close();
    Stop(hold);
    task::sleep(100);
    Intake(0);

    //夹二墩
    CorrectHeading(-143,700);
    task::sleep(50);
    para = MoveTo_Para();
    para.stop_turn_dis = 40;
    pos.MoveTo(59,48,1000,para);
    Move(-50,-50);
    task::sleep(320);
    Pull.open();
    task::sleep(30);
    Intake(100);
    Stop(hold);
    pos.MoveTo(30,10,1000);

    //清角
    pos.MoveTo(-5,-12,1000);
    task::sleep(50);
    Move(30,30);
    task::sleep(200);
    Stop(hold);
    task::sleep(100);
    for(int i = 0;i<3;i++){
        Intake(-100,1);
        Move(24,24);
        task::sleep(500);
        Intake(100);
        task::sleep(200);
        GoForWard(25,-230,500);
        task::sleep(500);
    }
    Intake(100);
    Move(40,40);
    task::sleep(300);
    Stop(hold);
    Move(-50,-50);
    task::sleep(200);
    Stop(hold);
    Intake(0);
    CorrectHeading(30,700); 
    Move(-100,-100);
    task::sleep(100);
    Pull.close();
    GoForWard(40,-500,500);

    //夹一墩
    GoForWard(100,300,500);
    CorrectHeading(190,700);
    pos.MoveTo(21,64,1000);
    Move(-50,-50);
    task::sleep(220);
    Pull.open();
    task::sleep(30);
    Stop(hold);
}