struct Route
{
	bool is_free;
	int lvl;
	int lenght;
	DevAbstr* dev;
	
	Route * next;
}
