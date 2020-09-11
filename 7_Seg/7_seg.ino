/*

Created by: Ashish Kurian

	To on the 7 segment display - Slide Switch
    To reset the display		- Push Button
    Changing the numbers/score	- 0-9 on IR Remote
    To increment/decrement		- Arrow up and Arrow dowm
    
    Project done as Task-2: Scoreboard
    PRODDEC CEC HardWare Team

*/


#include<IRremote.h>
IRrecv ir_receiver(2); 
decode_results results;          

int i, j, k, start=13, count = 0;
int now = 0;

int BCD[10][4] ={		//Binary of 0-9
{0,0,0,0},
{0,0,0,1},
{0,0,1,0},
{0,0,1,1},
{0,1,0,0},
{0,1,0,1},
{0,1,1,0},
{0,1,1,1},
{1,0,0,0},
{1,0,0,1}};

int segment[4]= {6,5,4,3};	//Segment pins initialization


void setup()
{
  for(i=3; i<=6; i++)
  {pinMode(i, OUTPUT);}
  pinMode(7,INPUT_PULLUP);
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  ir_receiver.enableIRIn();
}


void display(int num)
{
    for(k=0; k<4; k++)
     {
      digitalWrite(segment[k], BCD[num][k]);
      
     }
     delay(500);
  
}


void ir()
{
    int recieved=ir_receiver.decode(&results);

if (recieved==1)
{
int data=results.value;

  switch(data){
case 2295:		//1
    display(1);
    now = 1;
    break;
case -30601:	//2
    display(2);
    now = 2;
    break;
case 18615:		//3
    display(3);
    now = 3;
    break;
case 10455:		//4
    display(4);
    now = 4;
    break;
case -22441: 	//5
    display(5);
    now = 5;
    break;
case 26775:  	//6
    display(6);
    now = 6;
    break;
case 6375: 		//7
    display(7);
    now = 7;
    break;
case -26521:	//8
    display(8);
    now = 8;
    break;  
case 22695:     //9
    display(9);
    now = 9;
    break; 
case 12495: 	//0
    display(0);
    now = 0;
    break;
case 20655: 	// UP 
    display(now++);
    break;
case 4335: 	// DOWN 
    display(now--);
    break;
}
  ir_receiver.resume(); 
    delay(200);
}}


void loop()
{
  if(digitalRead(A0)==0)
  {
    digitalWrite(12, HIGH);
    display(0);
    delay(750);
    digitalWrite(12, LOW);
  }
    
  else if(digitalRead(13) == 0)
    for(k=0; k<4; k++)
      digitalWrite(segment[k], 1);
     
  else
   ir();

}