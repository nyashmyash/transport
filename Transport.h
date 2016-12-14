#pragma once
#include "Loader.h"
#include <string>
class RouteSwitch;
extern int gtimer;
class Transport
{
private:
	int id_transp;
	float cur_weight;
	float * items;
	float speed;//2-4m/s 
	float lenght;//100-1000m
	float pog_weight;// <20t in 1dm
	float max_weight; // pog_weight * lenght
	bool is_load;
	bool is_unload;
	int cnt_items;
	Transport * to_transp;
	float pos_to_transp;
	RouteSwitch * to_switch;
	Loader * to_loader;
	bool is_moved;//one shift
	bool is_run; //go process
	
public:
	Transport();
	void resetMoved();
	void setLoader(	Loader * loader);
	void setSwitch(	RouteSwitch * r_switch);
	void moveTranspItems();
	void getWeightFromAny(float weight, float pos);
	void setToTransp(Transport *tr, float pos);
	std::string getString();
	void setItems(int cnt);
	void setId(int id);
	~Transport() ;
	void setSpeed(float speed_);
	float getSpeed();
	
	
};
struct RouteSwitch
{
	int timer;
	int cur_switch;
	Transport * left;
	Transport *right;
	RouteSwitch()
	{
		left = 0;
		right = 0;
		cur_switch = 0;
	}
	Transport * getSwitch()
	{
		if (cur_switch==0)
			return left;
		else
			return right;
	}
};
