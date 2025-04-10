#include "auto.h"
#include "motorcontrol.h"
#include "sensor.h"
#include "vex.h"

using namespace vex;
vex::competition Competition;
using signature = vision::signature;
using code = vision::code;

void Initializing() {
  Brain.Screen.setFont(vex::fontType::mono40);
  int color = 0;
  timer printtime;
  while (Inertial.isCalibrating()) {
    Controller.Screen.clearScreen();
    if (color >= 0) {
      Brain.Screen.setPenColor(purple);
    }
    if (color >= 50) {
      Brain.Screen.setPenColor(blue);
    }
    if (color >= 100) {
      Brain.Screen.setPenColor(cyan);
    }
    if (color >= 150) {
      Brain.Screen.setPenColor(green);
    }
    Brain.Screen.printAt(80, 136, "Initializing...");
    task::sleep(10);
    color++;
  }
  Brain.Screen.clearScreen();
}

int Auton = auto_select;
void runauto() {
  while (Inertial.isCalibrating()) {
    task::sleep(10);
  }
  switch (Auton) {
  }
  
}

void autonomous(void) { runauto(); }
void drivercontrol(void) {
  Controller.Screen.clearScreen();
  int Ch1, Ch2, Ch3, Ch4;
  bool L1, L2, R1, R2, BtnA, BtnB, BtnX, BtnY, BtnU, BtnD, BtnL, BtnR;
  bool pull_flag = false, pull_CD;
  bool hook_flag = false, hook_CD;
  bool hand_flag = false, hand_CD;
  timer sorttime;
  bool lift_flag = false;
  float Tar;
  int n = 0; 
  while(true){
    if((Controller.ButtonR1.pressing() && Controller.ButtonUp.pressing() && Controller.ButtonB.pressing())) break;
  }
  while (true) {
    Show();
    Ch1 = Controller.Axis1.value();
    Ch2 = Controller.Axis2.value();
    Ch3 = Controller.Axis3.value();
    Ch4 = Controller.Axis4.value();
    L1 = Controller.ButtonL1.pressing();
    L2 = Controller.ButtonL2.pressing();
    R1 = Controller.ButtonR1.pressing();
    R2 = Controller.ButtonR2.pressing();
    BtnA = Controller.ButtonA.pressing();
    BtnB = Controller.ButtonB.pressing();
    BtnX = Controller.ButtonX.pressing();
    BtnY = Controller.ButtonY.pressing();
    BtnU = Controller.ButtonUp.pressing();
    BtnD = Controller.ButtonDown.pressing();
    BtnL = Controller.ButtonLeft.pressing();
    BtnR = Controller.ButtonRight.pressing();

    if(BtnD){
      pos.MoveTo(30,30,2000);
      task::sleep(200);
      task::sleep(1000);
      //runauto();
    }
    if(Ch1 > 50){
      sort_flag = true;
    }else if(Ch1 < -50){
      sort_flag = false;
    }

    if(abs(Ch3) > 15 || abs(Ch4) > 15) {
      Move(Ch3 + 0.8*Ch4, Ch3 - 0.8*Ch4);
    } else {
      if(BtnY){
        Stop(hold);
      }else{
        Stop(coast);
      }
    }

  

      if (R1) {
        if(Ch2 < -50){
          Intake(100,1);
          Intake(0,2);
        }else{
          Intake(100);
        }
      }
      else if (L2) {
        Intake(-100);
      }
      else {
        if(fabs(Rotation.angle(deg) - 334) < 10 && abs(Ch2) < 20){
          Intake(5);
          Intake1.stop(coast);
        }else{
          Intake(0);
        }
      }

      if (R2) {
        if (pull_CD) {
          pull_CD = false;
          pull_flag = !pull_flag;
        }
      } else {
        pull_CD = true;
      }

      if (pull_flag) {
        Pull.open();
      } else {
        Pull.close();
      }

      if (BtnA) {
        if (hook_CD) {
          hook_CD = false;
          hook_flag = !hook_flag;
        }
      } else {
        hook_CD = true;
      }

      if (hook_flag){
        Hook.open();
      } else {
        Hook.close();
      }

      
      if (BtnB) {
        if (hand_CD) {
          hand_CD = false;
          hand_flag = !hand_flag;
        }
      } else {
        hand_CD = true;
      }

      if (hand_flag) {
        RaiseHand.open();
      } else {
        RaiseHand.close();
      }

      if(L1){
        Lift_Tar = (Rotation.angle(deg) > 350?0:Rotation.angle(deg))>50?33:27;
        task Lift_prosses = task(LiftToAngle);
      }
      if(BtnX){
        Lift_Tar = 160;
        task Lift_prosses = task(LiftToAngle);
      }
      if (abs(Ch2) > 15) {
        Lift(Ch2);
        Lift_in_prosses = false;
      }else if(!Lift_in_prosses) {
        Lift(0);
      }

    }
  }

  int show(){
    while(1){
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("%f", pos.X());
      Controller.Screen.setCursor(2, 1);
      Controller.Screen.print("%f", pos.Y());
      Controller.Screen.setCursor(3, 1);
      Controller.Screen.print("%f",Inertial.rotation(deg));
    }
    return 1;
  }

  int main() {
    Optical.setLightPower(100);
    Pull.close();
    Hook.close();
    Inertial.startCalibration();
    Initializing();

    if(!self_check()){

    }

    Competition.autonomous(autonomous);

    Competition.drivercontrol(drivercontrol);

    task task_show = task(show,15);

    Rotation_B.resetPosition();
    Rotation_R.resetPosition();
    pos.Init();

    while (1) {
      Intake_control();
      pos.Update();
      task::sleep(5);
    }
  }
