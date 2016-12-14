#include <iostream>
#include <windows.h>
 
#include "Transport.h"
#include "Developers.h"
#include "Loader.h"

using namespace std;
int gtimer = 1;

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
		cnt_dev = 1;
		cnt_dev_st = 1;
		cnt_loader = 1;
		cnt_tr = 5;
		cnt_rs = 0;	
		
	}
	void createPath()
	{
		path="    d1-tr1-tr2-tr3-l1\nd2-tr4-tr5/\n";
		dev_arr[0] = new Developer();dev_arr[0]->setId(1);
		dev_st_arr[0] = new DeveloperStatic();dev_st_arr[0]->setId(1);
		tr_arr[0]= new Transport();tr_arr[0]->setId(1);
		tr_arr[1] = new Transport();tr_arr[0]->setId(2); 	tr_arr[1]->setSpeed(3);
		tr_arr[2] = new Transport();tr_arr[0]->setId(3);	tr_arr[2]->setSpeed(3);
		tr_arr[3] = new Transport();tr_arr[0]->setId(4);
		tr_arr[4] = new Transport();tr_arr[0]->setId(5);
		l_arr[0] = new Loader();l_arr[0]->setId(1);
		
		dev_arr[0]->setTransp(tr_arr[0]);
		tr_arr[0]->setToTransp(tr_arr[1], 0);
		tr_arr[1]->setToTransp(tr_arr[2], 0);
		tr_arr[2]->setLoader(l_arr[0]);
		
		dev_st_arr[0]->setTransp(tr_arr[3]);
		tr_arr[3]->setToTransp(tr_arr[4], 0);
		tr_arr[4]->setToTransp(tr_arr[1], 100);
			
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
	for (int i =0; i<200; i++ )
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
	 	cout<<"...TRANSPORT"<<i<<"...";
	 	cout<<b.tr_arr[i-1]->getString();
	 	//cout<<".................NEXT.................\n";
	 
	 }
	 for (int i =1; i <=b.cnt_dev; i++ )
	 {
	 	cout<<"...DEVELOPER"<<i<<"...";
	 	cout<<b.dev_arr[i-1]->getString();
	 	//cout<<".................NEXT.................\n";
	 
	 }
	for (int i =1; i <=b.cnt_dev_st; i++ )
	 {
	 	cout<<"...DEVELOPER STATIC"<<i<<"...";
	 	cout<<b.dev_st_arr[i-1]->getString();
	 	//cout<<".................NEXT.................\n";
	 
	 }
	 for (int i =1; i <=b.cnt_loader; i++ )
	 {
	 	cout<<"...LOADER"<<i<<"...";
	 	cout<<b.l_arr[i-1]->getString();
	 	//cout<<".................NEXT.................\n";
	 
	 }

}
int main(int argc, char** argv) {
	Builder b;
	b.createPath();
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	draw(b, console);
	while (1)
	{
	
		Sleep(100);
		for (int i =0; i <b.cnt_dev; i++ )
		{
			b.dev_arr[i]->loadWeightToTransp();//step 1 sec
		}
		for (int i =0; i <b.cnt_dev_st; i++ )
		{
			b.dev_st_arr[i]->loadWeightToTransp();//step 1 sec
		}	
		b.resetMov();
		if (gtimer%200==0)
		{
			draw(b, console);		
		}
		gtimer ++;
		//cnt_sec++;
	}
	b.deleteAll();
	return 0;
}
