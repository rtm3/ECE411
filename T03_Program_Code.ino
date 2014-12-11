/*
  All code written by Robert Tyler McNichols
  October 2014
  Tic Tac Toe
  Full program in process
*/


//initializes all variables/matrix 
// anodes
int redRow[] = {0,1,2};
int grnRow[] = {6,7,8};
// cathodes
int col[] = {3,4,5};

//selected bulbs will display in this array
int selBoard[3][3];
//counts the number of moves
int moveCount = 0;

//value for select button
int selVal = 0;
int selPin = 9;

//Potentiometer selector
int potPin = A0;
int potVal = 0;

//counter for player identity
int player = 0;

//player indicator led
int redPlayer = 12;
int grnPlayer = 10;
int catPlayer = 11;

//used to determine how long the bulb stays on while selecting
const int time = 1;
//used to set how long bulbs stay on during looping
const int onTime = 1;

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

//turn nonselected pins off
void selectedOn()
{
  for (int i=0;i<3;i++)
  {
    for (int j=0;j<3;j++)
    {
     if (selBoard[i][j] == 1)
     {
       digitalWrite(redRow[i], HIGH);
       digitalWrite(col[j], LOW);
       delay(onTime);
       allOff();
     }
     if (selBoard[i][j] == 2)
     {
       digitalWrite(grnRow[i], HIGH);
       digitalWrite(col[j], LOW);
       delay(onTime);
       allOff();
     }
    }
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
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      selBoard[i][j] = 0;
    }
  }
  player = 0;
  moveCount = 0;
  digitalWrite(grnPlayer, LOW);
  digitalWrite(redPlayer, HIGH);
  digitalWrite(catPlayer, LOW);
  delay(1000);
}

//used to check for a winner and then run congratulate function
void checkWin()
{
  //variable used to pass to celebration function
  int plyr = 0;
  
  //selectedOn();
  
  //check for row win
  if (selBoard[0][0] == selBoard[0][1] && selBoard[0][1] == selBoard[0][2] && selBoard[0][0] != 0)
  {
    plyr = selBoard[0][0];
  }
  else if (selBoard[1][0] == selBoard[1][1] && selBoard[1][1] == selBoard[1][2] && selBoard[1][0] != 0)
  {
    plyr = selBoard[1][0];
  }
  else if (selBoard[2][0] == selBoard[2][1] && selBoard[2][1]== selBoard[2][2] && selBoard[2][0] != 0)
  {
    plyr = selBoard[2][0];
  }
    
  //check for col win
  else if (selBoard[0][0] == selBoard[1][0] && selBoard[1][0] == selBoard[2][0] && selBoard[0][0] != 0)
  {
    plyr = selBoard[0][0];
  }
  else if (selBoard[0][1] == selBoard[1][1] && selBoard[1][1] == selBoard[2][1] && selBoard[0][1] != 0)
  {
    plyr = selBoard[0][1];
  }
  else if (selBoard[0][2] == selBoard[1][2] && selBoard[1][2] == selBoard[2][2] && selBoard[0][2] != 0)
  {
    plyr = selBoard[0][2];
  }
  
  //check for diagonal win
  else if (selBoard[0][0] == selBoard[1][1] && selBoard[1][1] == selBoard[2][2] && selBoard[0][0] != 0)
  {
    plyr = selBoard[0][0];
  }
  else if (selBoard[0][2] == selBoard[1][1] && selBoard[1][1] == selBoard[2][0] && selBoard[0][2] != 0)
  {
    plyr = selBoard[0][2];
  }
  
  //check for cats game
  else if (moveCount >= 9)
  {
    plyr = 3;
  }
  
  //check to see if plyr needs to be congratulated
  if (plyr == 0)
    return;
  else
  {
    congratulate(plyr);
  }
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
      selBoard[vert][horiz] = 1;
      digitalWrite(col[horiz], LOW);
      delay(time * 2);
    }
    else
    {
      digitalWrite(grnRow[vert], HIGH);
      selBoard[vert][horiz] = 2;
      digitalWrite(col[horiz], LOW);
      delay(time * 2);
    }
    changePlayer();
    delay(500);
    moveCount++;
  }
  
  //it is not possible to win in less than five moves, so this saves a step in early gameplay
  if (moveCount > 4)
  {
    checkWin();
  }
    
}

//used to select the pin based on the potentiometer reading
void ledSelect()
{
  int horiz = 0;
  int vert = 0;
  
  potVal = analogRead(potPin);
  if (potVal < 110 && selBoard[0][0] == 0)
    {
      vert = 0;
      horiz = 0;
    }
  else if (potVal < 220 && selBoard[0][1] == 0)
    {
      vert = 0;
      horiz = 1;
    }
  else if (potVal < 330 && selBoard[0][2] == 0)
    {
      vert = 0;
      horiz = 2;
    }
  else if (potVal < 440 && selBoard[1][0] == 0)
    {
      vert = 1;
      horiz = 0;
    }
  else if (potVal < 550 && selBoard[1][1] == 0)
    {
      vert = 1;
      horiz = 1;
    }
  else if (potVal < 660 && selBoard[1][2] == 0)
    {
      vert = 1;
      horiz = 2;
    }
  else if (potVal < 770 && selBoard[2][0] == 0)
    {
      vert = 2;
      horiz = 0;
    }
  else if (potVal < 880 && selBoard[2][1] == 0)
    {
      vert = 2;
      horiz = 1;
    }
  else if (potVal < 1024 && selBoard[2][2] == 0)
    {
      vert = 2;
      horiz = 2;
    }
  else
  {
    //keeps values from jumping to first led
    vert = 3;
    horiz = 3;
  }
  
  selectedOn();
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

//where things actually happen
//*******************************************************************************************************
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
  
  ledSelect();
  
  allOff();
  delay(time / 2);
}

//******************************************************************************************************
/*
void congratulateTest(int plyr)
{
  allOff();
  switch (plyr) {
  case 1:
  digitalWrite(col[0], LOW);
  for (int i=0; i<5; i++)
  {
    digitalWrite(redRow[0], HIGH);
    delay(100);
    digitalWrite(redRow[0], LOW);
    delay(100);
  }
  break;
  
  case 2:
  digitalWrite(col[0], LOW);
  for (int i=0; i<5; i++)
  {
    digitalWrite(grnRow[0], HIGH);
    delay(100);
    digitalWrite(grnRow[0], LOW);
    delay(100);
  }
  break;
  
  case 3:
  digitalWrite(col[0], LOW);
  digitalWrite(col[1], LOW);
  for (int i=0; i<10; i++)
  {
    digitalWrite(redRow[0], HIGH);
    digitalWrite(grnRow[0], HIGH);
    delay(100);
    digitalWrite(redRow[0], LOW);
    digitalWrite(grnRow[0], LOW);
    delay(100);
  }
  break;
  }
  
  fullReset();
}
*/

//congratulates winner, or denotes cats game, resets everything
//listed at end due to excessive length
void congratulate(int plyr)
{
  switch (plyr) 
  {
  //red player wins
  case 1:
      digitalWrite(grnPlayer, LOW);
      digitalWrite(redPlayer, HIGH);
      
      for (int j=0; j<10; j++)
      {
        for(int i=0; i<=8; i++)
        {
          digitalWrite(redRow[0], HIGH);
          digitalWrite(col[0], LOW);
          delay(1);
          digitalWrite(col[0], HIGH);
          digitalWrite(col[1], LOW);
          delay(1);
          digitalWrite(col[1], HIGH);
          digitalWrite(col[2], LOW);
          delay(1); 
          digitalWrite(redRow[0], LOW);
          digitalWrite(redRow[1], HIGH);
          delay(1);
          digitalWrite(redRow[1], LOW);
          digitalWrite(redRow[2], HIGH);
          delay(1);
          digitalWrite(col[2], HIGH);
          digitalWrite(col[1], LOW);
          digitalWrite(redRow[2], HIGH);
          delay(1);
          digitalWrite(col[1], HIGH);
          digitalWrite(col[0], LOW);
          delay(1);
          digitalWrite(redRow[2], LOW);
          digitalWrite(redRow[1], HIGH);
          delay(1);
          digitalWrite(redRow[1], LOW);
          digitalWrite(col[0], HIGH);
        }
        allOff();
        delay(50);
      } 
    break;
    
    //green player wins  
    case 2:
      digitalWrite(redPlayer, LOW);
      digitalWrite(grnPlayer, HIGH);
      
      for (int j=0; j<10; j++)
      {
        for(int i=0; i<=8; i++)
        {
          digitalWrite(grnRow[0], HIGH);
          digitalWrite(col[0], LOW);
          delay(1);
          digitalWrite(col[0], HIGH);
          digitalWrite(col[1], LOW);
          delay(1);
          digitalWrite(col[1], HIGH);
          digitalWrite(col[2], LOW);
          delay(1); 
          digitalWrite(grnRow[0], LOW);
          digitalWrite(grnRow[1], HIGH);
          delay(1);
          digitalWrite(grnRow[1], LOW);
          digitalWrite(grnRow[2], HIGH);
          delay(1);
          digitalWrite(col[2], HIGH);
          digitalWrite(col[1], LOW);
          digitalWrite(grnRow[2], HIGH);
          delay(1);
          digitalWrite(col[1], HIGH);
          digitalWrite(col[0], LOW);
          delay(1);
          digitalWrite(grnRow[2], LOW);
          digitalWrite(grnRow[1], HIGH);
          delay(1);
          digitalWrite(grnRow[1], LOW);
          digitalWrite(col[0], HIGH);
        }
        allOff();
        delay(50);
      }
    break;
    
    //cats game
    case 3:
      digitalWrite(redPlayer, LOW);
      digitalWrite(grnPlayer, LOW);
      
      for (int i=0; i<5; i++)
      {
        digitalWrite(redRow[0], HIGH);
        digitalWrite(col[0], LOW);
        digitalWrite(grnRow[2], HIGH);
        digitalWrite(col[2], LOW);   
        delay(100);
        allOff();
        delay(100);        
      }
    
  break; 
  }
  fullReset();
}
