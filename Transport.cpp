#include "Transport.h"
#include <stdio.h>

Transport::Transport()
{
	to_transp = 0;
	to_switch = 0;
	to_loader = 0;
	cur_weight = 0;
	is_moved = false;
	speed = 4;
	lenght = 500;
	pog_weight = 20; //Xt in item / 10
	cnt_items = lenght/10;
	max_weight = pog_weight*lenght*10;
	is_load = false;
	pos_to_transp = 0;
	setItems(cnt_items);
	is_run = true;
	id_transp = 0;
}
void Transport::setLoader(	Loader * loader)
{
	to_loader = loader;
}
void Transport::setSwitch(	RouteSwitch * r_switch)
{
	to_switch = r_switch;
}
void Transport::setToTransp(Transport *tr, float pos)
{
	to_transp = tr;
	pos_to_transp = pos;
}
void Transport::resetMoved()
{
	is_moved = false;
}
void Transport::setSpeed(float speed_)
{
	speed = speed_;
}
float Transport::getSpeed()
{
	return speed;
}
void Transport::moveTranspItems()
{
	bool tmp = false;
//	if(to_transp)
//		tmp = gtimer%((int)(10/to_transp->getSpeed())+1)== (int)(10/to_transp->getSpeed()) ;
	if (gtimer%((int)(10/speed))== 0 && !is_moved)
	{

			if(to_transp)
				to_transp->getWeightFromAny(items[cnt_items-1], pos_to_transp);
			if(to_loader)
				to_loader->getWeight(items[cnt_items-1]);	
			if(to_switch)
				to_switch->getSwitch()->getWeightFromAny(items[cnt_items-1], pos_to_transp);
			cur_weight -= items[cnt_items-1];
			
		for(int i = cnt_items-1; i>0;i--)
				items[i]= items[i-1];	
			items[0] =0;
			
		is_moved = true;
	}
		
	
} 
void Transport::getWeightFromAny(float weight, float pos)
{
	int indx = pos/10;
	if ((items[indx]+weight)/100>pog_weight)
	{
		is_run = false;
	}
	if(is_run)
		moveTranspItems();
		
	{
		items[indx]+=weight;
		cur_weight +=weight;
	}

}

std::string Transport::getString()
{
	std::string tmp;
	char buf[1000];
  		snprintf(buf, 1000, "current weight=%.2f, speed=%.2f, lenght=%.2f, pog weight=%.2F, max weight =%.2f, pos to transp=%.2f\n", cur_weight, speed, lenght, pog_weight, max_weight,pos_to_transp);
  		tmp = buf;
  		
	for (int i=0; i < cnt_items; i++)
	{
		if (items[i]!=0)
		{
			char buf[10];
			snprintf(buf, 10,"|%.0f", items[i]);
			tmp+=buf;
		}
		else
			tmp+="___";
	}
	tmp+='\n';
	return tmp;		
}
void Transport::setItems(int cnt)
{
	items = new float[cnt];
	for (int i=0; i < cnt_items; i++)
	{
		items[i]=0;
	}
}
void Transport::setId(int id)
{
	id_transp = id;
}
Transport::~Transport() 
{
	delete[] items;
}	
	
