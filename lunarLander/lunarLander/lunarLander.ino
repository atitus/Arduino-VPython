#define UD A0
#define LR A1
int received;
char buffer[10];		  // input buffer
int N;			          // how many measurements to make
boolean done = false;


void setup() {
  Serial.begin(9600);
}

void loop() {
        received = 0;
    	buffer[received] = '\0';
    	done = false;
    
    	// Check input on serial line.
    	while (!done) {
    		if (Serial.available()) {	// Something is in the buffer
    			N = Serial.read();	// so get the number byte
    			done = true;
    		}
    	}
  
      int LRval = analogRead(LR);
      int UDval = analogRead(UD);
      Serial.print(LRval, DEC);
      Serial.print('\t');
      Serial.print(UDval, DEC);
      Serial.print('\n');
      delay(10);
}
