#include "motorcontrol.h"
#include "sensor.h"

//------------PID---------------------------------------------------------------------------------------
PID::PID(float P, float I, float D) {
  this->p = P;
  this->i = I;
  this->d = D;
}
float PID::P() { return p; }
float PID::I() { return i; }
float PID::D() { return d; }
float PID::OUT(float err, float Lasterr, float accerr) {
  float Out;
  Out = p * err + i * accerr + d * (err - Lasterr);
  return Out;
}

PID GO_DEG(0.4, 0, 0);
PID GO_MM(0.1, 0, 150);
PID GO_V(0.1, 0.1, 0.1);
PID TURN_DEG(1.5,0,10);
PID TURN_DEG_STAKE(1.2,0,5);

PID MOVETO_POWER(2.4,0,10);
PID MOVETO_TURN_POWER(0.6,0,10);

MoveTo_Para::MoveTo_Para(){
  break_distance_err=4;
  break_power=10;
  Power_PID = MOVETO_POWER;
  Turn_Power_PID = MOVETO_TURN_POWER;
}
MoveTo_Para Default_Para = MoveTo_Para();

Pos::Pos(float x,float y,float delta_angle){
  Rotation_B.resetPosition();
  Rotation_R.resetPosition();
  this->x = x;
  this->y = y;
  this->Last_position_r = 0;
  this->Last_position_s = 0;
  this->angle = 0;
  this->lastangle = 0;
  this->delta_angle = delta_angle;
}
Pos pos(0,0,0);

void Pos::Update(){
	double ARCv = (Rotation_R.position(deg) - Last_position_r) * (pi/180) *wheel_v; //弧长
	double ARCh = (Rotation_B.position(deg) - Last_position_s) * (pi/180) *wheel_h;
  double Rv,Rh;//半径
	double Sv,Sh;//弦长 
  double angle = Inertial.rotation(deg)*pi/180;//当前角度
	double delta_angle = angle - lastangle; //角度差
  double half_delta_angle = delta_angle/2.0;
	if (delta_angle != 0){
		Rv = (ARCv / delta_angle) + dis_v; 
    Rh = (ARCh / delta_angle) + dis_h;
		double sinI = sin(half_delta_angle);
		Sv = Rv*sinI*2.0;
		Sh = Rh*sinI*2.0;
	}else{
		Sv = ARCv;
    Sh = ARCh;
	}
	double temp_angle = half_delta_angle + lastangle; 
	double cosP = cos(temp_angle);
	double sinP = sin(temp_angle);

	y += (Sv*cosP - Sh*sinP);
	x += (Sv*sinP + Sh*cosP);

  lastangle = angle;
  Last_position_r = Rotation_R.position(deg);
  Last_position_s = Rotation_B.position(deg);
}

float Pos::X(){
  return this->x;
}
float Pos::Y(){
  return this->y;
}

float Pos::Angle(){
  return this->angle;
}

float slew(float cur, float last, float maxChange) {
    float change = cur - last;
    if (change > maxChange) change = maxChange;
    else if (change < -maxChange) change = -maxChange;
    return last + change;
}

void Pos::MoveTo(float tar_x,float tar_y,int fulltime,MoveTo_Para Para){
  float err_x;//横坐标误差
  float err_y;//纵坐标误差

  float dis;//两点间距
  float last_dis;
  float acc_dis = 0;

  float err_ang;//角度差
  float last_ang;
  float acc_ang=0;

  float power;//直行功率
  float turn_power;//转弯功率
  float last_turn_power=0;
  float last_power=0;
  float power_maxchange=15;//每次循环允许的直行功率最大变化
  //float turn_power_maxchange=30;//每次循环允许的直行功率最大变化

  float max_power = 100;
  timer time;

  float cur_x = this->x;
  float cur_y = this->y;
  err_x = tar_x-cur_x;
  err_y = tar_y-cur_y;
  err_ang = atan2f(err_x,err_y) * (180 / 3.1415) - Inertial.rotation(deg);
  float last_err = err_ang;
  while(err_ang > 90)err_ang -= 180;
  while(err_ang < -90)err_ang += 180;
  
  timer lesspower_break_time;
  while(fabs(err_ang) > 20 && lesspower_break_time < 40){
    task::sleep(10);
    cur_x = this->x;
    cur_y = this->y;
    err_x = tar_x-cur_x;
    err_y = tar_y-cur_y;
    err_ang = atan2f(err_x,err_y) * (180 / 3.1415) - Inertial.rotation(deg);
    while(err_ang > 90)err_ang -= 180;
    
    while(err_ang < -90)err_ang += 180;
    
    float out = PID(1.8,0,10).OUT(err_ang,last_err,0);
    last_err = err_ang;

    if(fabs(out) > 10) lesspower_break_time = 0;
    
    Move(out,-out);
  }
  
  timer break_time;
  lesspower_break_time = 0;
  while(break_time < 40 && time < fulltime && lesspower_break_time < 40){
    cur_x = this->x;
    cur_y = this->y;
    err_x = tar_x-cur_x;
    err_y = tar_y-cur_y;
    float distance = sqrt(err_x*err_x + err_y*err_y);
    dis = distance*cos(atan2f(err_x,err_y) - ((3.1415926/180)*Inertial.rotation(deg)));

    bool close = distance < 18;

    err_ang = atan2f(err_x,err_y) * (180 / 3.1415) - Inertial.rotation(deg);

    while(err_ang > 90)err_ang -= 180;
    
    while(err_ang < -90)err_ang += 180;


    //直行功率计算
    power = Para.Power_PID.OUT(dis,last_dis,acc_dis);
    if(distance < 25)max_power = 50;
    if(close)max_power = 20;
    
    power = std::min(power,max_power);
    power = std::max(power,-max_power);
    power = slew(power,last_power,power_maxchange);

     //旋转功率计算
    turn_power = Para.Turn_Power_PID.OUT(err_ang,last_ang,acc_ang);

    if(turn_power > 100)turn_power = 100;
    else if(turn_power<-100)turn_power=-100;

    if(fabs(err_ang) > 3 && !close){
      if(turn_power > 0 && turn_power < 40)turn_power = 40;
      else if(turn_power < 0 && turn_power > -40)turn_power = -40; 
    }
    if(fabs(err_ang) < 7 || distance < 25)turn_power = 0;
    
    //if(turn_power != 0)turn_power=slew(turn_power,last_turn_power,turn_power_maxchange);
  
    double lpower = power+turn_power;
    double rpower = power-turn_power;
    double maxpower = (fabs(lpower)>fabs(rpower))?lpower:rpower;
    double ratio = fabs(maxpower/100);
    if(ratio > 1){
      lpower/=ratio;
      rpower/=ratio;
    }
    Move(lpower,rpower);

    if(distance > Para.break_distance_err)break_time = 0;

    if(fabs(lpower) > Para.break_power || fabs(rpower) > Para.break_power)lesspower_break_time = 0;
    

    last_dis = dis;
    acc_dis += dis;
    last_ang = err_ang;
    acc_ang += err_ang;
    last_power = power;
    last_turn_power = turn_power;
    
    // Brain.Screen.printAt(100,60,"err_dis: %f",sqrt(err_x*err_x + err_y*err_y));
    // Brain.Screen.printAt(100,80,"err_ang: %f",err_ang);
    // Brain.Screen.printAt(100,100,"power: %f",lpower);
    // Brain.Screen.printAt(100,120,"turnpower: %f",turn_power);
    // Brain.Screen.printAt(100,140,"x: %f",x);
    // Brain.Screen.printAt(100,160,"y: %f",y);

    task::sleep(10);
  }
  Stop(hold);
  Brain.Screen.clearScreen();
}

void Pos::Init(){
  this->x = 0;
  this->y = 0;
  this->Last_position_r = 0;
  this->Last_position_s = 0;
}
//----------------------------------------------------------------------------
char get_color() {
  if (DistanceSort.objectDistance(mm) < 100 && DistanceSort.objectDistance(mm) > 10) {
    if(Optical.hue() > 100 && Optical.hue() < 300) return 'B';
    else if(Optical.hue() < 30 || Optical.hue() > 350) return 'R';
    else return ' ';
  }
  return ' ';
}

void ResetMotor() {
  LeftMotor1.setBrake(coast);
  LeftMotor2.setBrake(coast);
  LeftMotor3.setBrake(coast);
  RightMotor1.setBrake(coast);
  RightMotor2.setBrake(coast);
  LeftMotor1.resetPosition();
  LeftMotor2.resetPosition();
  LeftMotor3.resetPosition();
  RightMotor1.resetPosition();
  RightMotor2.resetPosition();
  RightMotor3.resetPosition();
  LeftMotor1.setMaxTorque(2, Nm);
  LeftMotor2.setMaxTorque(2, Nm);
  RightMotor1.setMaxTorque(2, Nm);
  RightMotor2.setMaxTorque(2, Nm);
  LeftMotor1.setVelocity(0, pct);
  LeftMotor2.setVelocity(0, pct);
  RightMotor1.setVelocity(0, pct);
  RightMotor2.setVelocity(0, pct);
}
void Move(float lpower, float rpower) {
  LeftMotor1.spin(fwd, 0.128 * lpower, voltageUnits::volt);
  LeftMotor2.spin(fwd, 0.128 * lpower, voltageUnits::volt);
  LeftMotor3.spin(fwd, 0.128 * lpower, voltageUnits::volt);
  RightMotor1.spin(fwd, 0.128 * rpower, voltageUnits::volt);
  RightMotor2.spin(fwd, 0.128 * rpower, voltageUnits::volt);
  RightMotor3.spin(fwd, 0.128 * rpower, voltageUnits::volt);
}

void Stop(brakeType type) {
  LeftMotor1.stop(type);
  LeftMotor2.stop(type);
  LeftMotor3.stop(type);
  RightMotor1.stop(type);
  RightMotor2.stop(type);
  RightMotor3.stop(type);
}

//---------------------------------------------------------------------------------------
bool lift_self_check = false;
bool Lift_in_prosses = false;
float Lift_Tar = 0;
void Lift(float Power,brakeType type) {
  if (Power == 0) lift.stop(type);
  else lift.spin(fwd, 0.128 * Power, voltageUnits::volt);
}
int LiftToAngle(){
    Lift_in_prosses = true;
    lift_self_check = true;
    float cur = Rotation.angle(deg) > 350?0:Rotation.angle(deg);
    float err = Lift_Tar-cur;
    float Last_err = err;
    float acc_err = 0;
    float out = 0;
    timer break_time;
    while(Lift_in_prosses && fabs(err) > 2){
      cur = Rotation.angle(deg) > 350?0:Rotation.angle(deg);
      err = Lift_Tar-cur;

      PID p = cur > 30?PID(0.6,0,0.5):PID(1.3,0,1);
      out = p.OUT(err,Last_err,acc_err);
      if(out > 0 && out < 20) out = 20;
      if(out < 0 && out > -10) out = -10;
      Lift(out);

      Last_err = err;
      acc_err+=err;

      task::sleep(10);

      if(fabs(err) > 1) break_time = 0;
      if(break_time > 40)break;
      
    }
    Lift(0);
    Lift_in_prosses = false;
    return 0;
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------
timer sort_time;
float intake_power_1 = 0;
float intake_power_2 = 0;
bool sort_flag = true;
timer self_time;
void Intake(float Power,int flag) {
  if(flag == 0){
    intake_power_1 = Power;
    intake_power_2 = Power;
  }else if(flag == 1) intake_power_1 = Power;
  else intake_power_2 = Power;
  
}
void Intake_control(){
  //分环判断
  if(get_color() == opcolor && sort_time > 300  && hand_state() != 'm' && self_time > 200)  sort_time = 0;
  
  if(get_color() != opcolor && get_color() != ' ' && self_time > 800) self_time = 0;
  
  //状态机
  if(intake_power_2 != 0){
    if(sort_time > 110 && sort_time < 300 && sort_flag) Intake2.spin(fwd,-1,volt);
    else Intake2.spin(fwd,0.128 * intake_power_2,volt);
    
  }else Intake2.stop(coast);
  

  if(intake_power_1 == 0 )Intake1.stop(coast);
  else Intake1.spin(fwd,0.128 * intake_power_1,volt);
}
//-----------------------------------------------------------------------

void GoForWard(float Power, float Target, float FullTime, PID pid) {
  ResetMotor();
  float curR, errR, LasterrR, accerrR, outR;
  float curL, errL, LasterrL, accerrL, outL;
  float out;
  int Time, LastTime, Date_Time;
  curR = (RightMotor1.position(deg) + RightMotor2.position(deg) + RightMotor3.position(deg)) / 3;
  curL = (LeftMotor1.position(deg) + LeftMotor2.position(deg) + RightMotor3.position(deg)) / 3;
  errR = Target - curR;
  errL = Target - curL;
  LasterrL = errL;
  LasterrR = errR;
  accerrR = 0;
  accerrL = 0;
  timer time;
  timer lesspower_breaktime;
  while (time < FullTime && lesspower_breaktime < 40) {
    Time = time;
    Date_Time = Time - LastTime;
    LastTime = Time;
    curR = (RightMotor1.position(deg) + RightMotor2.position(deg) + RightMotor3.position(deg)) / 3;
    curL = (LeftMotor1.position(deg) + LeftMotor2.position(deg) + RightMotor3.position(deg)) / 3;
    errR = Target - curR;
    errL = Target - curL;
    LasterrL = errL;
    LasterrR = errR;
    accerrL += errL;
    accerrR += errR;

    outL = pid.OUT(errL, LasterrL, accerrL);
    outR = pid.OUT(errR, LasterrR, accerrR);
    out = (outL + outR) / 2;

    if(fabs(out) > Power) out = Target>0?Power:-Power;
    if(time < 150 && fabs(Power) > 55) out = Target>0?55:-55;//缓慢起速
    if(fabs(Power) <10) out = Target>0?10:-10;

    Move(out, out);
    if (fabs(errL) < 10 || fabs(errR) < 10) break;
    if(out > 10) lesspower_breaktime = 0;
  }
  Stop(hold);
}

void CorrectHeading(float Target, float FullTime, float Lrate, float Rrate,
                    PID pid,float out_err) {
  float cur = Inertial.rotation(deg);
  float err = Target - cur;
  float out;
  float Lasterr = err;
  float accerr = 0;
  float max_power = 30;
  timer time;
  timer breaktime;
  timer lesspower_breaktime;

  while (time < FullTime && breaktime < 40 && lesspower_breaktime < 40) {
    task::sleep(10);
    cur = Inertial.rotation(deg);
    Lasterr = err;
    err = Target - cur;
    accerr += err;
    out = pid.OUT(err, Lasterr, accerr);

    if(fabs(err) < 30){
      out = std::min(max_power,out);
      out = std::max(-max_power,out);
    }

    if(out < 12 && out > 0)out = 12;
    if(out > -12 && out < 0)out = -12;
    
    
    Move(Lrate * out, Rrate * out);

    if (fabs(err) > 1.5) breaktime = 0;
    if (fabs(out) > 10) lesspower_breaktime = 0;
    
  }
  Stop(hold);
}