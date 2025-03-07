#include "sensor.h"
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;
controller Controller;

motor LeftMotor1(PORT17, gearSetting::ratio6_1,1);
motor LeftMotor2(PORT19, gearSetting::ratio6_1,1);
motor LeftMotor3(PORT18, gearSetting::ratio6_1,0);
motor RightMotor1(PORT13, gearSetting::ratio6_1,1);
motor RightMotor2(PORT15, gearSetting::ratio6_1,0);
motor RightMotor3(PORT16, gearSetting::ratio6_1,0);
motor Intake1(PORT11, gearSetting::ratio6_1,0);
motor Intake2(PORT4,gearSetting::ratio6_1,1);
motor lift(PORT2,gearSetting::ratio6_1,0);

inertial Inertial(PORT20);
rotation Rotation(PORT5);

optical Optical(PORT6);
distance DistanceSort(PORT7);

pneumatics Pull(Brain.ThreeWirePort.B);
pneumatics Hook(Brain.ThreeWirePort.C);
pneumatics RaiseHand(Brain.ThreeWirePort.D);

rotation Rotation_R(PORT14);//竖轮
rotation Rotation_B(PORT12);//横轮

void Show() {

}

bool self_check(){
    // if (!LeftMotor1.installed()) return false;
    // if (!LeftMotor2.installed()) return false;
    // if (!LeftMotor3.installed()) return false;
    // if (!RightMotor1.installed()) return false;
    // if (!RightMotor2.installed()) return false;
    // if (!RightMotor3.installed()) return false;
    // if (!Intake1.installed()) return false;
    // if (!Intake2.installed()) return false;
    // if (!lift.installed()) return false;

    // if (!Inertial.installed()) return false;
    // if (fabs(Inertial.rotation(deg) > 3)) return false;

    // if(!Rotation.installed()) return false;
    // if(Rotation.angle(deg) < 355 || Rotation.angle(deg) > 5) return false;

    // if(!Rotation_B.installed()) return false;
    // if(Rotation_B.angle(deg) < 355 || Rotation_B.angle(deg) > 5) return false;

    // if(!Rotation_R.installed()) return false;
    // if(Rotation_R.angle(deg) < 355 || Rotation_R.angle(deg) > 5) return false;

    // if(!Optical.installed()) return false;
    // if(!DistanceSort.installed()) return false;

    return true;
}

char hand_state(){
    if (Rotation.angle(deg) > 355 || Rotation.angle(deg) < 20) return 'l';
    if (Rotation.angle(deg) < 35) return 'm';
    return 'h';
}