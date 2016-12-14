#pragma once
#include "DevLoadAbstr.h"
#include "Transport.h"

class Developer: public DevLoadAbstr
{
private:
	float weight_max;//15000t
	float weight_cur;
	int time_load; // 300s
	int time_unload; // 120s
	float len_to_transp;//300m
	float speed;//7 km/h
	float speed_unload;
	float start_pos_to_transp;//200m
	bool ready_load; //wait load to dev
	float moved_pos;
	int timer;
	bool test_fail;
	Transport * transp;
				
public:
	Developer();
	void setTransp(Transport * transp);
	virtual void loadWeightToTransp();
	virtual std::string getString();
	
};
class DeveloperStatic: public DevLoadAbstr
{
private:
	float* time_run; //720s 4000s 500s 1500s 4000s
	float* speed_unload; //80t 88t 0t 83t 0t	
	int cnt_dev;
	int cur_dev;
	int timer;
	bool test_fail;
	float start_pos_to_transp;
	Transport * transp;
public:	
	DeveloperStatic();
	void setTransp(Transport * transp);
	
	virtual std::string getString();
	virtual void loadWeightToTransp();
	~DeveloperStatic();
};
