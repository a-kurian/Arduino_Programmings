/*
Created by: Ashish Kurian

    if distance is less than 200 & PIR get activated 
    	=> WARNING message displays on LCD
        => Alarming buzzer and LEDs ON [Red/Blue]

    if maped value from gas sensor is above 60 
    	=> WARNING message displays on LCD
        => DC Motor starts 
           [Assuming working of water pumb to blow out fire]
        => Alarming buzzer
    
    Project done for HACKWARE Competition.

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 7, 11, 10, 9, 8);

int i, flag = -1;
String message = "";

// for printing message in the top of the lcd.
void set_lcd_first(String message)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
}

// for adding message in the bottom of the lcd.
void set_lcd_second(String message)
{

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void setup()
{

    for (i = 2; i <= 6; i++)
        pinMode(i, INPUT);

    for (i = 13; i < 20; i++)
    {
        if (i <= 15)
            pinMode(i, INPUT);

        else
            pinMode(i, OUTPUT);
    }

    lcd.begin(16, 2);
}

void loop()
{
    digitalWrite(1, LOW);
    int gas = map(analogRead(A1), 306, 745, 0, 100);
    int distance;
    distance = 0.01723 * readDistance(A0, A0);

    if (digitalRead(A4) == HIGH)
    {
        if (gas >= 60)
        {
            set_lcd_first("WARNING...!!");
            set_lcd_second("FIRE DECTECTED");
            fire(gas);
        }

        if (distance < 200)
        {
            digitalWrite(A5, 0);
            SenserOn(distance);
        }
    }

    else
    {
        digitalWrite(A5, 0);
        SensorOff();
    }

    if (flag == -1)
    {
        set_lcd_first("YOU ARE SAFE !!");
        delay(500);
        set_lcd_second("");
    }

    flag = -1;
    analogWrite(A5, 0);
}

long readDistance(int triggerPin, int echoPin) //UltraSonic Distance Senser
{
    pinMode(triggerPin, OUTPUT);
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);

    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    return pulseIn(echoPin, HIGH);
}

void SenserOn(int dist) //Working of Animal/Stranger sensing
{
    flag = 1;
    if (digitalRead(2) == HIGH)
        message = " N";
    else if (digitalRead(3) == HIGH)
        message = "NE";
    else if (digitalRead(4) == HIGH)
        message = "SE";
    else if (digitalRead(5) == HIGH)
        message = " S";
    else if (digitalRead(6) == HIGH)
        message = "SW";
    else if (digitalRead(13) == HIGH)
        message = "NW";
    if (message != "")
    {
        set_lcd_first("WARNING...!!");
        set_lcd_second("Dectected from" + message);
        if (dist <= 130)
            Tone();
        else
        {
            digitalWrite(A3, HIGH);
            delay(250);
            digitalWrite(A3, LOW);
            delay(250);
            digitalWrite(A3, HIGH);
            delay(250);
            digitalWrite(A3, LOW);
            delay(250);
        }
    }
}

void Tone() //To start buzzer and blinking RED LED 
{
    tone(A2, 100, 250);
    tone(A2, 100, 250);
}

void SensorOff() //Switching OFF all Sensors
{
    flag = 1;
    set_lcd_first("The Sensors are ");
    set_lcd_second("in OFF state ");
    for (i = 2; i < 7; i++)
        digitalWrite(i, LOW);
    digitalWrite(13, LOW);
    digitalWrite(A1, 0);
    delay(1000);
}

void fire(int gas) //Fire Sensor
{
    Tone();
    if (gas <= 70)
        analogWrite(A5, 128);
    else if ((gas > 70) && (gas <= 80))
        analogWrite(A5, 256);
    else if ((gas > 80) && (gas <= 90))
        analogWrite(A5, 512);
    else
        analogWrite(A5, 1024);
   
    delay(500);
    flag = 1;
}
