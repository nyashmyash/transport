#include "Developers.h"
#include <stdlib.h>
Developer::Developer()
{
	test_fail = false;
	timer = 0;
	weight_max = 15000;
	time_load = 300;
	time_unload = 120;
	speed_unload = weight_max/time_unload;
	len_to_transp = 300;
	speed = (float)7/3,6;
	start_pos_to_transp = 200;
	ready_load = false ; //wait load to dev
	moved_pos = 0;
	weight_cur = 0;
}
void Developer::setTransp(Transport * tr)
{
	transp = tr;
}
std::string Developer::getString()
{
	std::string tmp;
	char buf[1000];
   	snprintf(buf, 1000, "moved pos=%.2f, current weight=%.2f,weight max=%.2f, timer=%d, speed =%.2f ,speed unload=%.2f, lenght to transp=%.2f, point on transp=%.2f, time load=%d, time unload=%d\n" 
	   ,moved_pos, weight_cur,weight_max, timer,  speed,speed_unload, len_to_transp, start_pos_to_transp,time_load,time_unload);
   	tmp = buf;
	return tmp;			
}
void Developer::loadWeightToTransp()
{
	float curspeed = 0;
	if (moved_pos<len_to_transp)//расстояние меньше тогда идем до набора или к выгрузке
		moved_pos+= speed; 
	else
	{
		timer ++;
	
		if (timer>time_load && !ready_load)
		{
			timer = 0;
			ready_load = true;	
			moved_pos = 0;
		}
		else
		{
			if (timer<=time_load && !ready_load)
			{
				weight_cur+=weight_max/time_load;
			}
			else
			{
				if (timer>time_unload && ready_load) 
				{
					timer = 0;
					ready_load = false;	
					moved_pos = 0;	
					len_to_transp+=1;	
				}
				else
				if (timer<=time_unload && ready_load) //move to transp elem in sec
				{
					weight_cur-=weight_max/time_unload;
					curspeed = weight_max/time_unload;
				}	
			}
		}
	}	
	if (test_fail)
	{
		int rnd = rand()%2000;
		if (rnd>1900)
			curspeed+=rnd;
	}
	transp->getWeightFromAny(curspeed, start_pos_to_transp);
}
DeveloperStatic::DeveloperStatic()
{
	start_pos_to_transp = 100;
	cnt_dev = 5;
	cur_dev = 0;
	test_fail = true;
	time_run = new float[cnt_dev];
	speed_unload = new float[cnt_dev];
	time_run[0] = 720;
	time_run[1] = 4000;
	time_run[2] = 500;
	time_run[3] = 1500;
	time_run[4] = 4000;
	
	speed_unload[0] = 80;
	speed_unload[1] = 88;
	speed_unload[2] = 0;
	speed_unload[3] = 83;
	speed_unload[4] = 0;
}
void DeveloperStatic::setTransp(Transport * tr)
{
	transp = tr;
}
std::string DeveloperStatic::getString()
{
	std::string tmp;
	char buf[1000];
   	snprintf(buf, 1000, "speed unload=%.2f, time load=%.2f, point on transp=%.2f\n",
	    speed_unload[cur_dev], time_run[cur_dev], start_pos_to_transp);
   	tmp = buf;
	return tmp;			
}
void DeveloperStatic::loadWeightToTransp()
{
	timer++;
	float cur_speed = 0;
	float sum_time = 0;
	
	bool find = false;
	for(int i =0; i< cnt_dev; i++)
	{
		if (timer<time_run[i] + sum_time)
			{
				find = true;
				cur_speed = speed_unload[i];
				cur_dev = i;
				break;
			}
			else sum_time+= time_run[i];
	}
	if (!find)
	{
		cur_speed = speed_unload[0];
		timer = 0;
		cur_dev = 0;
	}
	if (test_fail)
	{
		int rnd = rand()%2000;
		if (rnd>1900)
			cur_speed+=rnd;
	}
	
	transp->getWeightFromAny(cur_speed, start_pos_to_transp);
}
	

DeveloperStatic::~DeveloperStatic()
{
	delete [] time_run;
	delete [] speed_unload;
}
