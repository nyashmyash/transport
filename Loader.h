#pragma once
#include <string>
class Loader
{
private:
	float weight_cur;
	int time_unload; // 150s
	float weight_unload_singl; // 20000t	
	float weight_unload; 
	int timer;
	int id_loader;
public:
	Loader()
	{
		weight_cur= 0;
		time_unload = 150;
		weight_unload_singl = 20000;
		weight_unload = 0;
		timer = 0;
	}
	void setId(int id)
	{
		id_loader = id;
	}
	int getId()
	{
		return id_loader;
	}
	void getWeight(float weight)
	{
		needUnload();
		weight_cur+=weight;
		weight_unload+=weight;
	}
			
	void needUnload()
	{
		if (timer<time_unload)
			timer++;
		else
		{
			weight_cur-=weight_unload_singl;
			if (weight_cur<0) weight_cur = 0;
			timer = 0;
		}
		
	}
	std::string getString()
	{
		std::string tmp;
		char buf[1000];
   		snprintf(buf, 1000, "c. w.=%.0f,u. w.=%.0f, t.=%d \n",weight_cur, weight_unload,timer);
   		tmp = buf;
		return tmp;	
	}
};
