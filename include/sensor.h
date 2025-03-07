#include "v5.h"
#include "v5_vcs.h"
#include <stdio.h>

using namespace vex;
using signature = vision::signature;

extern brain Brain;
extern controller Controller;

extern motor LeftMotor1;
extern motor LeftMotor2;
extern motor LeftMotor3;
extern motor RightMotor1;
extern motor RightMotor2;
extern motor RightMotor3;
extern motor Intake1;
extern motor Intake2;
extern motor lift;

extern rotation Rotation;

extern inertial Inertial;

extern distance Distance;
extern distance DistanceSort;
extern distance Distancef;

extern optical Optical;

extern pneumatics Pull;
extern pneumatics Hook;
extern pneumatics RaiseHand;

extern rotation Rotation_R;//竖轮
extern rotation Rotation_B;//横轮

void Show();
bool self_check();//检查各项传感器
char hand_state();//返回手臂状态，正在准备上环’m'，低于‘l’，高于‘h’
