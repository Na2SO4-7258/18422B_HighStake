#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
#include "sensor.h"

#include <vector>
#include <string>

#define auto_select 4
#define opcolor (auto_select%2==0?'R':'B')

#define pi 3.1415926
#define wheel_v 2.54  //轮半径
#define wheel_h 2.54  
#define dis_h 12      //侧轮到中心距离
#define dis_v -0.5     //竖轮到中心距离
