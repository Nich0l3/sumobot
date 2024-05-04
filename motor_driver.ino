#include <SharpIR.h>

// Sharp IR pin
#define sharpIR A5
SharpIR IR_proxy(sharpIR,1080);

// Motor A connections
int enA = 10;
int in1 = 8;
int in2 = 9;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

// global speed variable
int speed = 0;



// Class defination and initiation
class motorControl {

  private :

    int motor1speed;
    int motor2speed;

    int motordir11, motordir12;
    int motordir21, motordir22;

  public :

    motorControl( int s1, int s2, int dir11, int dir12, int dir21, int dir22){
        this -> motor1speed = s1;
        this -> motor2speed = s2;

        this -> motordir11 = dir11;
        this -> motordir12 = dir12;
        this -> motordir21 = dir21;
        this -> motordir22 = dir22;
   }

    void forw(){
      digitalWrite(motordir11, HIGH);
      digitalWrite(motordir12, LOW);
      digitalWrite(motordir21, HIGH);
      digitalWrite(motordir22, LOW);
    }

    void rev(){
      digitalWrite(motordir11, LOW);
      digitalWrite(motordir12, HIGH);
      digitalWrite(motordir21, LOW);
      digitalWrite(motordir22, HIGH);  
    }


    void accel( int start, int stop){                         // 5 SECONDS TO REACH FULL SPEED
      for (int i = start; i <= stop; i++) {
        analogWrite(motor1speed, i);
        analogWrite(motor2speed, i);
        speed = i;
        delay(10);
      }
    }

    void decel(int start, int stop){                         // 5 SECONDS TO STOP  
      for (int i = start; i >= stop; i--) {
        analogWrite(motor1speed, i);
        analogWrite(motor2speed, i);
        speed = i;
        delay(10);
      }
    }

    void cruise(int speed){
      analogWrite(motor1speed, speed);
      analogWrite(motor2speed, speed);
    }

    void right(){

    }

    void left(){

    }

    float distance(){
      
      //float IRvolt = analogRead(sharpIR) * (refVoltageResolution);
      //float proximity = 29.988 * pow(IRvolt , -1.173);

      float proximity = IR_proxy.distance();

      return proximity; // in cm
    }
};


motorControl Bot (enA, enB, in1, in2, in3, in4);

void setup() {

  Serial.begin(9600);

	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
  /* MOTOR STATES    motorControl( int s1, int s2, int dir11, int dir12, int dir21, int dir22){

  Input1	Input2	Spinning Direction
  Low(0)	Low(0)	  Motor OFF
  High(1)	Low(0)  	Forward
  Low(0)	High(1)	  Backward
  High(1)	High(1)	  Motor OFF
  
  */

	// Turn off motors - Initial state            
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
}

void loop() {

  Bot.forw(); 

  Serial.println(Bot.distance());
//  while (Bot.distance() <= 10.0)
  {
  //  Bot.cruise(speed = 100);
  } 
  
 Bot.cruise(speed = 127);
  
}


// This function lets you control speed of the motors
void speedControl() {
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 127; i < 256; i++) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}

	for (int i = 255; i >= 127; --i) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}  

  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}
