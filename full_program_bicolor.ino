/*
  Full program in process
*/


//initializes all variables/matrix 
// anodes
int redRow[] = {0,5,10};
int grnRow[] = {1,6,11};
// cathodes
int col[] = {2,7,12};

//all spots open
int openBoard[2][2];
//selected bulbs will display in this array
int selBoard[2][2];
//number of spots left in int form
int spotsLeft = 9;

//value for select button
int selVal = 0;
int selPin = 13;

//Potentiometer selector
int potPin = A0;
int potVal = 0;

//counter for player identity
int player = 0;

//player indicator led
//not totally necessary if worst comes to worst
int redPlayer = 3;
int grnPlayer = 9;
int catPlayer = 8;

//used to determine how long the bulb stays on while selecting
const int time = 500;

//clears the board
void allOff()
{
  for (int i=0;i<3;i++)
  {
    digitalWrite(redRow[i], LOW);
    digitalWrite(grnRow[i], LOW);
    digitalWrite(col[i], HIGH);
  }
}

//increments player counter to switch between red and green
void changePlayer()
{
  player++;
  if (chkPlayer() == 0)
    {
      digitalWrite(redPlayer, HIGH);
      digitalWrite(grnPlayer, LOW);
    }  
  else
  {
    digitalWrite(redPlayer, LOW);
    digitalWrite(grnPlayer, HIGH);
  }
}

//used to check players turn
int chkPlayer()
{
  int result = player % 2;
  return result;  
}

//clears the board and resets the player
void fullReset()
{
  allOff();
  player = 0;
  spotsLeft = 9;
}

//check to see if button is used to select position, changes turns
void checkSelect(int vert, int horiz)
{
  selVal = digitalRead(selPin);
  if (selVal == LOW)
  {
    if (chkPlayer() == 0)
    {
      digitalWrite(redRow[vert], HIGH);
      digitalWrite(col[horiz], LOW);
      delay(time * 2);
    }
    else
    {
      digitalWrite(grnRow[vert], HIGH);
      digitalWrite(col[horiz], LOW);
      delay(time * 2);
    }
    //change back when hold matrix works
    //spotsLeft--;
    changePlayer();
    
  }
  
}

//better written ledSelect, includes permanent written bits
//IN PROGRESS
//Can't get it to scroll through all the options. Problem with loop?
void newledSelect()
{
  int horiz = 0;
  int vert = 0;
  int increment = 0;
  
  potVal = analogRead(potPin);
  increment = (1023 / spotsLeft);
  
  int valBin[spotsLeft];
  for (int i=0; i < spotsLeft; i++)
  {
    valBin[i] = ((increment * i) + increment); 
  }
  
  int j = 0;
  while (potVal < valBin[j])
  {
    //code to find the coordinates of the potVal
    horiz++;
    if (horiz == 3)
    {
      vert++;
      horiz = 0;
    }
    if (vert == 3)
    {
      vert = 0;
    }
    
    j++; 
  }
  
    if (chkPlayer() == 0)
    {
      digitalWrite(redRow[vert], HIGH);
      digitalWrite(col[horiz], LOW);
    }
    else
    {
      digitalWrite(grnRow[vert], HIGH);
      digitalWrite(col[horiz], LOW);
    } 
  
  checkSelect(vert, horiz);
    
  delay(time); 
}


//used to select the pin based on the potentiometer reading
void ledSelect()
{
  int horiz = 0;
  int vert = 0;
  
  potVal = analogRead(potPin);
  if (potVal < 110)
    {
      vert = 0;
      horiz = 0;
    }
  else if (potVal < 220)
    {
      vert = 0;
      horiz = 1;
    }
  else if (potVal < 330)
    {
      vert = 0;
      horiz = 2;
    }
  else if (potVal < 440)
    {
      vert = 1;
      horiz = 0;
    }
  else if (potVal < 550)
    {
      vert = 1;
      horiz = 1;
    }
  else if (potVal < 660)
    {
      vert = 1;
      horiz = 2;
    }
  else if (potVal < 770)
    {
      vert = 2;
      horiz = 0;
    }
  else if (potVal < 880)
    {
      vert = 2;
      horiz = 1;
    }
  else
    {
      vert = 2;
      horiz = 2;
    }
  
  if (chkPlayer() == 0)
  {
    digitalWrite(redRow[vert], HIGH);
    digitalWrite(col[horiz], LOW);
  }
  else
  {
    digitalWrite(grnRow[vert], HIGH);
    digitalWrite(col[horiz], LOW);
  }
  
  checkSelect(vert, horiz);
    
  delay(time);
}


//initialization
void setup()
{
  pinMode(selPin, INPUT);
  
  pinMode(redPlayer, OUTPUT);
  pinMode(grnPlayer, OUTPUT);
  pinMode(catPlayer, OUTPUT);
  
  
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      openBoard[i][j] = 0;
      selBoard[i][j] = 0;
    }
    pinMode(redRow[i], OUTPUT);
    pinMode(grnRow[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }
  
  digitalWrite(redPlayer, HIGH);
  digitalWrite(catPlayer, LOW);
  allOff();
}

//main gameplay loop
void loop()
{
  
  newledSelect();
  
  //remove allOff once solid matrix is working
  allOff();
  delay(time / 2);
  
}
