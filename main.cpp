#include <iostream>
#include <windows.h>
 
#include "Transport.h"
#include "Developers.h"
#include "Loader.h"

using namespace std;
int gtimer = 0;

struct Builder
{
	int cnt_dev;
	int cnt_dev_st;
	int cnt_loader;
	int cnt_tr;
	int cnt_rs;
	std::string path;
	
	Developer * dev_arr[10];
	DeveloperStatic * dev_st_arr[10];
	Transport * tr_arr[50];
	Loader * l_arr[10];
	RouteSwitch * rs_arr[10];
	
	Builder()
	{
		cnt_dev = 3;
		cnt_dev_st = 3;
		cnt_loader = 2;
		cnt_tr = 20;
		cnt_rs = 0;	
		
	}
	void createPath()
	{
		//path="    d1-tr1-tr2-tr3-l1\nd2-tr4-tr5/\n";
		for (int i =0;i<cnt_dev; i++)
		{
			dev_arr[i] = new Developer();
			dev_arr[i]->setId(i+1);
		}
		for (int i =0;i<cnt_dev_st; i++)
		{
			dev_st_arr[i] = new DeveloperStatic();
			dev_st_arr[i]->setId(i+1);
		}
		for (int i =0;i<cnt_tr; i++)
		{
			tr_arr[i] = new Transport();
			tr_arr[i]->setId(i+1);
		}
		for (int i =0;i<cnt_loader; i++)
		{			
			l_arr[i] = new Loader();
			l_arr[i]->setId(i+1);
		}
		for (int i =0;i<cnt_rs; i++)
		{			
			rs_arr[i] = new RouteSwitch();
			rs_arr[i]->setId(i+1);
		}
		tr_arr[1]->setSpeed(3);
		tr_arr[2]->setSpeed(3);
		
		tr_arr[1]->setLenght(400);		
		tr_arr[9]->setLenght(200);
		tr_arr[14]->setLenght(300);
		tr_arr[19]->setLenght(700);
		
		dev_arr[0]->setTransp(tr_arr[0]);
		tr_arr[0]->setToTransp(tr_arr[1], 0);
		tr_arr[1]->setToTransp(tr_arr[2], 0);
		tr_arr[2]->setToTransp(tr_arr[3], 0);
		
		dev_st_arr[0]->setTransp(tr_arr[3]);
		tr_arr[3]->setToTransp(tr_arr[4], 200);
		tr_arr[4]->setLoader(l_arr[0]);
	
		dev_st_arr[1]->setTransp(tr_arr[5]);
		tr_arr[5]->setToTransp(tr_arr[6], 0);
		tr_arr[6]->setToTransp(tr_arr[7], 0);
		tr_arr[7]->setToTransp(tr_arr[8], 100);	
		tr_arr[8]->setToTransp(tr_arr[9], 0);
		tr_arr[9]->setLoader(l_arr[1]);
		
		
		dev_arr[1]->setTransp(tr_arr[10]);
		dev_st_arr[2]->setTransp(tr_arr[11]);
		tr_arr[10]->setToTransp(tr_arr[11], 0);
		tr_arr[11]->setToTransp(tr_arr[12], 0);
		tr_arr[12]->setToTransp(tr_arr[13], 100);	
		tr_arr[13]->setToTransp(tr_arr[14], 0);	
		tr_arr[14]->setLoader(l_arr[1]);
		
		
		dev_arr[2]->setTransp(tr_arr[15]);
		tr_arr[15]->setToTransp(tr_arr[16], 100);	
		tr_arr[16]->setToTransp(tr_arr[17], 0);
		tr_arr[17]->setToTransp(tr_arr[18], 0);
		tr_arr[18]->setToTransp(tr_arr[19], 0);
		tr_arr[19]->setToTransp(tr_arr[12], 50);
	}
		
	void deleteAll()
	{
		for (int i =0; i <cnt_dev; i++ )
			delete dev_arr[i];
		for (int i =0; i <cnt_tr; i++ )
			delete tr_arr[i];
		for (int i =0; i <cnt_loader; i++ )
			delete l_arr[i];
		for (int i =0; i <cnt_rs; i++ )
			delete rs_arr[i];
		for (int i =0; i <cnt_dev_st; i++ )
			delete dev_st_arr[i];
	}
	void resetMov()
	{
		for (int i =0; i <cnt_tr; i++ )
			tr_arr[i]->resetMoved();
	}
} ;
void clear(HANDLE &console)
{
	COORD topLeft  = { 0, 0 };
	SetConsoleCursorPosition(console, topLeft);
	std::string s= "";
	for (int i =0; i<200; i++ )
	{
		s+=' ';
	}
	s+='\n';
	for (int i =0; i<500; i++ )
	{
	 	cout<<s;
	}
	SetConsoleCursorPosition(console, topLeft);
}
void draw(Builder& b, HANDLE &console)
{
	clear(console);
	cout<<b.path;
 	for (int i =1; i <=b.cnt_tr; i++ )
	 {
	 	if (i<10)
	 		cout<<"...TR "<<i<<"...";
	 	else
	 		cout<<"...TR"<<i<<"...";
	 	cout<<b.tr_arr[i-1]->getString(); 
	 }
	 for (int i =1; i <=b.cnt_dev; i++ )
	 {
	 	cout<<"...DEV"<<i<<"...";
	 	cout<<b.dev_arr[i-1]->getString();
	 
	 }
	for (int i =1; i <=b.cnt_dev_st; i++ )
	 {
	 	cout<<"...DEV ST"<<i<<"...";
	 	cout<<b.dev_st_arr[i-1]->getString();
	 
	 }
	 for (int i =1; i <=b.cnt_loader; i++ )
	 {
	 	cout<<"...LOADER"<<i<<"...";
	 	cout<<b.l_arr[i-1]->getString();
	 
	 }

}
int main(int argc, char** argv) {
	Builder b;
	b.createPath();
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	draw(b, console);
	int cnt_sec = 0;
	int cursec = 0;
	while (1)
	{
		if (cursec>=cnt_sec)
		{
			draw(b, console);
			cout<<"help\n";
			cout<<"c. w. - current weight, u. w. - unload weight, pos. - pos to transport, s. u. - speed unload, t. l. - time load \n";
			cout<<"cur time ="<< gtimer<<endl;
			cout<<"input count sec. to run model\n";
		
			cin>>cnt_sec;
			cursec = 0;
		}
		for (int i =0; i <b.cnt_dev; i++ )
		{
			b.dev_arr[i]->loadWeightToTransp();//step 1 sec
		}
		for (int i =0; i <b.cnt_dev_st; i++ )
		{
			b.dev_st_arr[i]->loadWeightToTransp();//step 1 sec
		}	
		b.resetMov();
	
		cursec ++;
		gtimer ++;

	}
	b.deleteAll();
	return 0;
}
