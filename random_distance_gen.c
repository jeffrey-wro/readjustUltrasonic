int distance; //dont dirrectly use this variable

int main(){
	//at the beginning of your code
	distanceInit();
	
	//when you need to get the distance
	getDistance();


}


void distanceInit()
{
	//set the initial distance between range of sensor which is 2cm and 450 cm
	distance = getrandomNumber(between 2 and 450); //whatever function it is
}

void updateDistance()
{
	//add a small number of change
	distance += getrandomNumber(between -5 and 5); //whatever function it is
}

///get distance in cm
int getDistance()
{
	updateDistance();
	return distance;
}