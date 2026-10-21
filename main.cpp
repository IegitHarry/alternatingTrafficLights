// C++ code
//
#define OFF 0
#define TOP 1
#define LEFT 2
#define BOTTOM 3
#define RIGHT 4

void topOn();
void leftOn();
void bottomOn();
void rightOn();
void off();

unsigned long int newMillis;
int state = 1;

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  switch(state) {
    case TOP:
    	if (millis() - newMillis >= 7000) {
    		newMillis = millis();
          	state = LEFT;
  		}
    	else if (millis() - newMillis >= 2000) {
    		topOn();
  		}
    	else {
         	off();
    	}
    	break;
    case LEFT:
    	if (millis() - newMillis >= 7000) {
    		newMillis = millis();
          	state = BOTTOM;
  		}
    	else if (millis() - newMillis >= 2000) {
    		leftOn();
  		}
    	else {
         	off();
    	}
    	break;
    case BOTTOM:
    	if (millis() - newMillis >= 7000) {
    		newMillis = millis();
          	state = RIGHT;
  		}
    	else if (millis() - newMillis >= 2000) {
    		bottomOn();
  		}
    	else {
         	off();
    	}
    	break;
    case RIGHT:
    	if (millis() - newMillis >= 7000) {
    		newMillis = millis();
          	state = TOP;
  		}
    	else if (millis() - newMillis >= 2000) {
    		rightOn();
  		}
    	else {
         	off();
    	}
    	break;
  }
}
void topOn() {
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
}
void leftOn() {
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
}
void bottomOn() {
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
}
void rightOn() {
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
}
void off() {
  digitalWrite(7, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
}
