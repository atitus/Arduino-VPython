#define DELAY 10

int YSENSOR = 7;
int XSENSOR = 4;
unsigned long pulseX;
unsigned long pulseY;
int accelX, accelY, xtilt, ytilt; //values it sends python
int received;		       	  // characters received
char buffer[10];		  // input buffer
int N;			          // how many measurements to make
char temp;
boolean done = false;

void setup() {
        pinMode(YSENSOR, INPUT);
        pinMode(XSENSOR, INPUT);
	Serial.begin(9600);
}

int calcAccel(int time1) {
  //A(g) = ([Pulse Time in microsec]/10ms - 0.5)/20%
  return (8 * (time1/10 - 500));
}

double calcTilt(int accel) {
   //angle = k (arc degree/g) * Ax (or Ay)
   double angle = 57.50 * (accel/1000.0);
   return angle;
}

void loop() {
	received = 0;
	buffer[received] = '\0';
	temp = ' ';
	done = false;

	// Check input on serial line.
	while (!done) {
		if (Serial.available()) {	// Something is in the buffer
			N = Serial.read();	// so get the number byte
			done = true;
		}
	}

	// Now we know how many to get, so get them.
	for (byte j=0;j<N;j++) {
		Serial.print(millis(), DEC);
		Serial.print('\t');
                //Calculate length of pulse in microsec
		pulseX = pulseIn(XSENSOR, HIGH);
                pulseY = pulseIn(YSENSOR, HIGH);
                //Calculate acceleration
                accelX = calcAccel(pulseX);
                accelY = calcAccel(pulseY);
                //Calculate approx. tilt
                xtilt = calcTilt(accelX);
                ytilt = calcTilt(accelY);
                //Print results to serial
                Serial.print(accelX);
                Serial.print('\t');
                Serial.print(accelY);
                Serial.print('\t');
                Serial.print(xtilt);
                Serial.print('\t');
                Serial.print(ytilt);
                Serial.print('\n');
		delay(DELAY);
	}
}


