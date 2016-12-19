#include "Transport.h"
#include <stdio.h>

Transport::Transport()
{
	to_transp = 0;
	to_switch = 0;
	to_loader = 0;
	cur_weight = 0;
	weight_unload = 0;
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
void Transport::setLenght(int len)
{
	delete [] items;
	lenght = len;
	cnt_items = lenght/10;
	setItems(cnt_items);
}
void Transport::moveTranspItems()
{
	bool tmp = false;

	if (gtimer%((int)(10/speed))== 0 && !is_moved)
	{

			if(to_transp)
				to_transp->getWeightFromAny(items[cnt_items-1], pos_to_transp);
			if(to_loader)
				to_loader->getWeight(items[cnt_items-1]);	
			if(to_switch)
				to_switch->getSwitch()->getWeightFromAny(items[cnt_items-1], pos_to_transp);
			cur_weight -= items[cnt_items-1];
			weight_unload += items[cnt_items-1];
			
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
/*	if (to_transp)
  		snprintf(buf, 1000, "to TR%d, pos %.0f, c. w=%.0f, s=%.0f, l=%.0f, pw=%.0F, mw=%.0f, to=%.0f\n",to_transp->getId(),pos_to_transp,cur_weight, speed, lenght, pog_weight, max_weight);
  	if (to_loader)
  		snprintf(buf, 1000, "to LR%d, c. w=%.0f, s=%.0f, l=%.0f, pw=%.0f, mw=%.0f\n", to_loader->getId(),cur_weight, speed, lenght, pog_weight, max_weight);
  */
  	for (int i=0; i < cnt_items; i++)
	{
		if(i%2==0)
		{
			if (items[i]!=0)
			{
				/*char buf[10];
				snprintf(buf, 10,"|%.0f", items[i]+items[i+1]);
				tmp+=buf;*/
				tmp += '#';
			}
			else
				tmp+="_";
		}
	}		
	if (to_transp)
  		snprintf(buf, 1000, "to TR%d, pos.= %.0f, c. w.=%.0f, u. w.=%.0f",to_transp->getId(),pos_to_transp,cur_weight, weight_unload);
  	if (to_loader)
  		snprintf(buf, 1000, "to LR%d, c. w.=%.0f, u. w.=%.0f", to_loader->getId(),cur_weight, weight_unload);
  	
	tmp += buf;
  		

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
int Transport::getId()
{
	return id_transp;
}
Transport::~Transport() 
{
	delete[] items;
}	
	
