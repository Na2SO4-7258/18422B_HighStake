#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
#include "sensor.h"

#include <vector>
#include <string>

#define auto_select 1
#define opcolor (auto_select%2==0?'R':'B')

#define pi 3.1415926
#define wheel_r 2.54  //轮半径aaa
#define wheel_s 2.54  
#define Ss 12      //侧轮到中心距离
#define Sr 0.5     //竖轮到中心距离
