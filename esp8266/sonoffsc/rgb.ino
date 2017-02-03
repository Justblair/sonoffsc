
// This function 
void sendColor(char * rgbValues) {

	int effect = 1; 
	int rValue = 0;
	int gValue = 0;
	int bValue = 0;
	int duration = 1000; 
	bool rgb;
	bool timed; 

	// split the data into its parts

	char * strtokIndx; // this is used by strtok() as an index

	// Now check the first value in the string (delimited by commas) for the effect type
	strtokIndx = strtok(rgbValues, ",");	// get the first part - the string
	if (strcmp_P(strtokIndx, "color") == 0) {
		effect = 1;
		rgb = true;
		timed = false;
	}
	if (strcmp_P(strtokIndx, "rainbow") == 0) {
		effect = 2;
		rgb = false;
	}
	if (strcmp_P(strtokIndx, "rainbowStrip") == 0) {
		effect = 3;
		rgb = false; 
	}
	if (strcmp_P(strtokIndx, "knightRider") == 0) {
		effect = 4;
		rgb = true;
	}
	// and more effects to be added here as we go along!
	
	// for effects that need rgb values...
	if (rgb) {
		strtokIndx = strtok(NULL, ",");			// this continues where the previous call left off
		rValue = atoi(strtokIndx);				// convert this part to an integer

		strtokIndx = strtok(NULL, ",");			// this continues where the previous call left off
		gValue = atoi(strtokIndx);				// convert this part to an integer

		strtokIndx = strtok(NULL, ",");
		bValue = atoi(strtokIndx);				// convert this part to an integer
	}

	if (timed) {
		strtokIndx = strtok(NULL, ",");
		duration = atoi(strtokIndx);				// convert this part to an integer
	}
	

	//Now lets send the correct number of variables to the arduino
	if (!rgb && !timed) {
		commSendRGB(effect);
	}
	if (!rgb && timed) {
		commSendRGB(effect, duration);
	}
	if (rgb && !timed) {
		commSendRGB(effect, rValue, gValue, bValue);  // Send it to the Atmega328
	}
	if (rgb && timed) {
		commSendRGB(effect, rValue, gValue, bValue, duration);
	}
}

