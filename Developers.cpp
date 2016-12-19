#include "Developers.h"
#include <stdlib.h>
Developer::Developer()
{
	weight_unload = 0;
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
	id_dev = 0;
}
void Developer::setTransp(Transport * tr)
{
	transp = tr;
}
void Developer::setId(int id)
{
	id_dev = id;
}
std::string Developer::getString()
{
	std::string tmp;
	char buf[1000];
   /*	snprintf(buf, 1000, "to TR%d, p.=%.0f, w.=%.0f,w. m.=%.0f, t=%d, s=%.0f ,s. u.=%.0f, l. tr.=%.0f, p. tr.=%.0f, t. l.=%d, t. u.=%d\n" 
	   ,transp->getId(),moved_pos, weight_cur,weight_max, timer,  speed,speed_unload, len_to_transp, start_pos_to_transp,time_load,time_unload);
   	*/
   	snprintf(buf, 1000, "to TR%d, pos.=%.0f,c. w.=%.0f, u. w.=%.0f,s. u.=%.0f\n" 
	   ,transp->getId(), start_pos_to_transp, weight_cur,weight_unload, speed_unload);
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
				weight_unload+=weight_max/time_load;
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
	weight_unload = 0;
	cnt_dev = 5;
	cur_dev = 0;
	test_fail = false;
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
   	snprintf(buf, 1000, "to TR%d, pos.=%.0f, u. w.=%.0f, s. u.=%.0f, t. l.=%.0f\n",
	    transp->getId(), start_pos_to_transp, weight_unload, speed_unload[cur_dev], time_run[cur_dev]);
   	tmp = buf;
	return tmp;			
}
void DeveloperStatic::setId(int id)
{
	id_dev = id;
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
		weight_unload+=cur_speed;
	}
	
	transp->getWeightFromAny(cur_speed, start_pos_to_transp);
}
	

DeveloperStatic::~DeveloperStatic()
{
	delete [] time_run;
	delete [] speed_unload;
}
