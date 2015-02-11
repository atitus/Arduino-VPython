#define UD A0
#define LR A1
int received;
char buffer[10];		  // input buffer
int N;			          // how many measurements to make
boolean done = false;

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int buttonState=0;             // the current reading from the input pin


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // blink
  digitalWrite(ledPin, HIGH);

}

void loop() {

        buttonState=digitalRead(buttonPin);
        if(buttonState==HIGH) {
           digitalWrite(ledPin,HIGH); 
        }
        else {
           digitalWrite(ledPin,LOW);
        }
        
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
      Serial.print('\t');
      Serial.print(buttonState, DEC);
      Serial.print('\n');
      delay(10);
}
