#include <vex.h>

#define WHEEL_DIAMETER_R 4 
#define WHEEL_DIAMETER_S 4  

typedef class PID{
  private:
  float p;
  float i;
  float d;

  public:
  PID(float p,float i,float d);
  float P();
  float I();
  float D();
  float OUT(float err,float Lasterr,float accerr);
} PID;

extern PID GO_DEG;
extern PID GO_MM;
extern PID GO_V;
extern PID TURN_DEG;

extern PID MOVETO_POWER;
extern PID MOVETO_TURN_POWER;

typedef class MoveTo_Para{
  public:
    MoveTo_Para();
    float break_distance_err;//跳出距离
    float break_power;//跳出功率
    PID Power_PID=PID(0,0,0);//直行pid
    PID Turn_Power_PID=PID(0,0,0);//转动pid
}MoveTo_Para;
extern MoveTo_Para Default_Para;


typedef class Pos{
  private:
    double x;
    double y;
    double Last_position_s;//横轮Last
    double Last_position_r;//竖轮Last
    double angle;
    double lastangle;
    double delta_angle;//角度偏置值
  public:
    Pos(float x,float y,float delta_angle);
    void Init();
    void Update();
    float X();
    float Y();
    float Angle();
    void MoveTo(float tar_x,float tar_y,int fulltime,MoveTo_Para Para = Default_Para);
}Pos;
extern Pos pos;

//--------------------------------------------

void Update();

//吸环分环控制----------------------------------
extern timer sort_time;
extern float intake_power_1;
extern float intake_power_2;
extern bool sort_flag;//总开关
extern timer self_time;//距离上一次看到自己的圈有多久
void Intake (float Power,int flag = 0); 
void Intake_control();
//-------------------------------------

//摇臂控制-------------------------------------------
extern bool Lift_in_prosses;//在LiftToAngle进程内的时候为真
extern float Lift_Tar;
void Lift(float Power,brakeType type = hold);
int LiftToAngle();
//-------------------------------------------

char get_color();
void ResetMotor();  
void Move (float lpower,float rpower);  
void Stop (vex::brakeType type = vex::hold);  


void GoForWard(float Power, float Target, float FullTime,PID pid = GO_DEG);
void CorrectHeading(float Target, float FullTime,float Lrate = 1,float Rrate = -1, PID pid = TURN_DEG,float out_err = 1.5);
