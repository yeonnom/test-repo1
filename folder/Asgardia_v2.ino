//asgardia v 0.2



//Library
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

//Digital pin mapping
//*********** Heimadal **************
const int trigPin1 = 2;
const int echoPin1 = 3;
int motor = 6;
int door_led = 9;
//**********************************
int pinDHT11 = 4; //DHT

// Objects
Servo myservo; //Heimdal
LiquidCrystal_I2C lcd(0x27,16,2); //poseidon
// set the LCD address to 0x27 for a 16 chars and 2 line display
SimpleDHT11 dht11; // 
//variables
long duration1, distance1; // Heimdal


void DHT_run(){


// start working...
Serial.println("=================================");
Serial.println("Sample DHT11...");

// read without samples.
byte temperature = 0;
byte humidity = 0;
if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
Serial.print("Read DHT11 failed.");
return;
}
Serial.print("Sample OK: ");
Serial.print((int)temperature); Serial.print(" *C, ");
Serial.print((int)humidity); Serial.println(" %");


// write a temperature
lcd.setCursor(0,0);
lcd.print("T:");
lcd.setCursor(2,0);
lcd.print((int)temperature);
lcd.setCursor(4,0);
lcd.print("C");

// write a humidity
lcd.setCursor(7,0);
lcd.print("H:");
lcd.setCursor(9,0);
lcd.print((int)humidity);
lcd.setCursor(11,0);
lcd.print("%");

}



void setup_Poseidon()
{
lcd.init();
// Print a message to the LCD.
lcd.backlight();
//lcd.setCursor(0,0); //첫줄
//lcd.print("Hello, world!");
//lcd.setCursor(0,1);// 둘째줄
//lcd.print("Asgardia Arduino");
}

void setup_Heimdal()
{
myservo.attach(6);
pinMode(trigPin1,OUTPUT);
pinMode(echoPin1,INPUT);
pinMode(door_led,OUTPUT);

}
void gate_open() {

digitalWrite(door_led,HIGH);
Serial.println("GATE OPEN");
lcd.setCursor(0,1); //첫줄
lcd.print("GATE OPEN");
delay(1000);


myservo.write(0);
delay(10);
myservo.write(80);
delay(3000);
digitalWrite(door_led,LOW);
}

void gate_close()
{

digitalWrite(motor, LOW);
Serial.println("GATE CLOSED");
lcd.setCursor(0,1); //첫줄
lcd.print("GATE CLOSED");
digitalWrite(door_led,LOW);

}

void Heimdal_run()
{
long duration1, distance1;
digitalWrite(trigPin1,LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1 = (duration1/2) / 29.1;
if ((distance1 < 5) && (distance1 > 0))
{
gate_open();
}
else
{
gate_close();
}

myservo.write(0);
//delay(1000); // moved to main loop
}

void Poseidon_run()
{
//lcd.setCursor(0,0); //첫줄
//lcd.print("Poseidon running");
DHT_run();
}

void setup() {
// put your setup code here, to run once:
// Set console baud rate
Serial.begin(115200);
setup_Heimdal();
setup_Poseidon();

}

void loop() {
// put your main code here, to run repeatedly:
Heimdal_run();
Poseidon_run();

delay(1000);
}
