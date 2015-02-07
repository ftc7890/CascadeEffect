int delayTime=0;//by default no wait
bool kickstand = false;


void setupMenu(){
	menuLength = 1;//how many lines
	menuParameter parameters[1];//same number as one above

	//set up delay
	parameters[0].name="Delay: ";
	parameters[0].var=&delayTime; //reset wait time
	parameters[0].type='i';
	parameters[0].min=0;
	parameters[0].max=15;//max wait time

	menu = &parameters;//commit variables
}
