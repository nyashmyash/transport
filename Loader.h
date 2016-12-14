#pragma once
#include <string>
class Loader
{
private:
	float weight_cur;
	int time_unload; // 150s
	float weight_unload; // 20000t	
	int timer;
	int id_loader;
public:
	Loader()
	{
		weight_cur= 0;
		time_unload = 150;
		weight_unload = 20000;
		timer = 0;
	}
	void setId(int id)
	{
		id_loader = id;
	}
	void getWeight(float weight)
	{
		needUnload();
		weight_cur+=weight;
	}
			
	void needUnload()
	{
		if (timer<time_unload)
			timer++;
		else
		{
			weight_cur-=weight_unload;
			if (weight_cur<0) weight_cur = 0;
			timer = 0;
		}
		
	}
	std::string getString()
	{
		std::string tmp;
		char buf[1000];
   		snprintf(buf, 1000, "current weight=%.2f,weight unload=%.2f, timer=%d \n",weight_cur, weight_unload,timer);
   		tmp = buf;
		return tmp;	
	}
};
