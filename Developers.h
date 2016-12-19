#pragma once
#include "Transport.h"

class Developer
{
private:
	int id_dev;
	float weight_max;//15000t
	float weight_cur;
	float weight_unload;
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
	void setId(int id);
	void setTransp(Transport * transp);
	void loadWeightToTransp();
	std::string getString();
	
};
class DeveloperStatic
{
private:
	int id_dev;
	float* time_run; //720s 4000s 500s 1500s 4000s
	float* speed_unload; //80t 88t 0t 83t 0t	
	float weight_unload;
	int cnt_dev;
	int cur_dev;
	int timer;
	bool test_fail;
	float start_pos_to_transp;
	Transport * transp;

public:	
	DeveloperStatic();
	void setTransp(Transport * transp);
	void setId(int id);
	std::string getString();
	void loadWeightToTransp();
	~DeveloperStatic();
};
