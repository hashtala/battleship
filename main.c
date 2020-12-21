#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int Size = 5; //it is the size of table (5X5)
int UserBoard[5][5]; //2D array for user, first representing vertical (Y) coordinate, and second horizontal (X)
int ComputerBoard[5][5]; //Global array ComputerBoard, 2 dimensional array first value will be determining Y coordinate and second X;

void PrintYouLose() // Reads from existing file;
{
   FILE* shmela;  //file pointer variable, I run out of ideas of names of variables so I named this variable that way.
    shmela = fopen("YouLose.txt", "r"); //Reading this file'
    char ReadLine2[100]; //variable for storing file elements;

    while(!feof(shmela)) //until it reaches last character;
    {
        fgets(ReadLine2, 100, shmela); //basic fgets application for file pointer;
        puts(ReadLine2); //printing array, passing by reference;
    }
}


void PrintYouWon()
{

FILE* fZAZA;                   // file pointer, Zaza is a Georgian name, I used this as a variable because I was stressing out and it helped a bit;
    fZAZA = fopen("YouWon.txt", "r"); //reads from this file, procedure is the same as before (YouLose function)
    char ReadLine1[100];

    while(!feof(fZAZA))
    {
        fgets(ReadLine1, 100, fZAZA);
        puts(ReadLine1);
    }

}

void PrintDraw()
{
 FILE* F_Pointer; //Same steps and algorithm that was used before (in 3 cases, YouWin,YouLose PrintIntro)
    F_Pointer = fopen("Draw.txt", "r");
    char ReadLine3[100];

    while(!feof(F_Pointer))
    {
        fgets(ReadLine3, 100, F_Pointer);
        puts(ReadLine3);
    }
}

void PrintIntro()
{
        FILE* fGELA; //Same steps and algorithm that was used before ( in 2 cases, YouWin and YouLose)
    fGELA = fopen("Battleship.txt", "r");
    char ReadLine[100];

    while(!feof(fGELA))
    {
        fgets(ReadLine, 100, fGELA);
        puts(ReadLine);
    }
}


int CheckWinner(int ShipNumber)  //it only needs how many ships are in game to detect winner.
{

int UserShipCounter = ShipNumber;  //every time it is called values of these variables are updated, they count how many ships are in the game;
int ComputerShipCounter = ShipNumber;

int yUser, xUser, yComp, xComp;  //declaration of variables that will be used to scan UserBoard and Computer Board.

for(yUser = 0; yUser < 5; ++yUser)
{
      for(xUser = 0; xUser < 5; ++xUser)
      {
          if(UserBoard[yUser][xUser] == 'X')   //every time X occurs in the table, counter is getting less by 1;
          {
              UserShipCounter--;
              continue;
          }
      }

}


for(yComp = 0; yComp < 5; ++yComp)
{
      for(xComp = 0; xComp < 5; ++xComp)
      {
          if(ComputerBoard[yComp][xComp] == 'X')  //same thing for computer board.
          {
              ComputerShipCounter--;
              continue;
          }
      }

}


 if (UserShipCounter == 0)   //If number of X's that were counted in USER's board equals to number of ships, that means that computer destroyed all ships, so user lose.
{
    system("COLOR 1E"); //it compiler changes color before printing message so it will be noticed more easily;
    PrintYouLose();     //YouLose function is called which reads from a file.
        return 0;
}

else if(ComputerShipCounter == 0)
    {
    system("COLOR 2A");    //if number of X's in computer board equals number of ships, this means that user won
    PrintYouWon();         //YouWin function is called to print appropriate result from a file;
        return 0;
    }
else if ((ComputerShipCounter == 0) && (UserShipCounter == 0))
{
    system("COLOR 6D");      //I do not think that it needs any explanation anymore;
    PrintDraw();
    return 0;
}
else if ((ComputerShipCounter != 0) && (UserShipCounter != 0))
{
    return 1;     // if neither of them is 0, just return one;
}

}


void ShootComputer()
{

     int j = rand()%5;      //restricts range and lets computer to choose coordinates 0-4;
     int i = rand()%5;

     if (UserBoard[j][i] == '0')
     {
         UserBoard[j][i] = '+';          //computer shoots at random places
     }
     else if (UserBoard[j][i] == '*')
        {
         UserBoard[j][i] = 'X';
        }

     else if (UserBoard[j][i] == '+') //if computer already has generated this coordinate it should shoot again, this function should calls itself
                                      // and allows computer to generate another pair of numbers;
        {
            ShootComputer();
        }
}


void ShootUser(int* RowComp, int* ColComp)
{


  printf("Give HORIZONTAL coordinate where you want to fire your canon:\n");
  scanf("%d", RowComp);


while (1<2)
 {

  if ((*RowComp > 4) || (*RowComp < 0))
  {
      printf("Range is 0-4, try again:\n");
      scanf("%d", RowComp);

  }                                               //this thing here ensures that user does not exceed limits;
   else
   {
       *RowComp = *RowComp;
       break;
   }
   break;
 }

 printf("Give VERTICAL coordinate where you want to fire your canon:\n");
  scanf("%d", ColComp);

  while (1<2)
 {

  if ((*ColComp > 4) || (*ColComp < 0))
  {
      printf("Range is 0-4, try again:\n");  //this piece of code also restrict users from entering invalid input;
      scanf("%d", ColComp);

  }
   else
   {
       *ColComp = *ColComp;
       break;
   }
   break;
 }




 if (ComputerBoard[*ColComp][*RowComp] == '0')
 {
     ComputerBoard[*ColComp][*RowComp] = '+';
     printf("\n");
     printf("You missed, try again\n");        // if user shoot a void it tells that user missed and repalces void (0) with + so suer will know he/she shot there;
 }

 else if (ComputerBoard[*ColComp][*RowComp] == '*') //if user shoots one of the ships X is written so user knows there was a ship
 {
     ComputerBoard[*ColComp][*RowComp] = 'X';
     printf("\n");
     printf("NICE SHOOT:\n");
 }

 else if (ComputerBoard[*ColComp][*RowComp] == '+')
 {
     printf("You already shot there choose different coordinates:\n");     //if user entered coordinates which were already used this part notifies suer about this and lets him/her shoot again by calling itself;
     ShootUser(RowComp, ColComp); // 5th case of recursion ^-^;
 }
 else if (ComputerBoard[*ColComp][*RowComp] == 'X')
 {
     printf("You already shot there choose different coordinates:\n");
     ShootUser(RowComp, ColComp); // 6th case of recursion ^-^;
 }



}

void CopmuterAligningShips(int* RowC, int* ColumnC)
{
   int Y, X;
   Y = rand()%5;
   X = rand()%5;

   // computer randomly places ships, first two commands restrict the computer from generating invalid coordinates;
  *RowC = X;
  *ColumnC = Y;

  if (ComputerBoard[Y][X] == '*')
  {
      CopmuterAligningShips(RowC, ColumnC);// if computer already set a ship on a point and it is trying to
                                           //set another ship on that point this command forces computer to choose
                                           //different coordinates
                                            //7th case of recusrion.
  }

}


int NumberOfShips()
{
     int NumShips;

    printf("How many ships do you want to be in this battle ?\n");
    scanf("%d", &NumShips);


    while(1 > 0)
      {
        if ((NumShips > 25) || (NumShips < 1)) //on 5X5 tables it is impossible to have 26 ships and 0 ships have no meaning
        {
            printf("Minimum number of ships is 1 and max 25, try again:\n");
            scanf("%d", &NumShips);
        }
        else
        {
            NumShips = NumShips;
            break;
        }

      }


  return NumShips;


}


void PrintWithCoordinates(int* HOR, int* VERT, int* RowComp, int* ColumnComp)
{

 //calls other function it does not have anything original but it is useful in order to make the code to be more clear;
 UserBoard[*VERT][*HOR] = '*';
 ComputerBoard[*ColumnComp][*RowComp] = '*';

 PrintUserArray();
 PrintComputerArray();

}



void Coordinate_Set_And_Limit_Check(int* RowUser, int* ColumnUser)
{

printf("Give HORIZONTAL coordinate:\n");
scanf("%d", RowUser);
if (*RowUser == 555)
{
    system("COLOR 2A");
    PrintYouWon();
}
else if(*RowUser == 556)         //these are secret codes for winning and losing,
{                                //I did this in order to avoid playing with computer at least two times to demonstrate program
    system("COLOR 1E");
    PrintYouLose();
}
else if(*RowUser == 557)
{
    system("COLOR 6B");
    PrintDraw();
}

int j = 2;

while (j != 1){
if ((*RowUser > Size -1 ) || (*RowUser < 0))
{
    printf("Your HORIZONTAL coordinate should be in range 0-4, try again:\n");
    scanf("%d", RowUser);              //this chalk of code restricts user from giving invalid inputs;
}
else if ((*RowUser < Size - 1) && (*RowUser >= 0)){
    RowUser = RowUser;
    break;
}

 else
 {
     break;
 }



}



int c = 2;

while (c != 0)
{
    printf("Now give your VERTICAL coordinate:\n");
    scanf("%d", ColumnUser);

    if ((*ColumnUser > 4) || (*ColumnUser < 0))
    {
        printf("Your VERTICAL coordinates should be in range 0-4, try again:\n"); //this is also written in order to restrict invalid inputs;
        scanf("%d", ColumnUser);
    }
    else if ((*ColumnUser < 4) && (ColumnUser >= 0))
             {
                 ColumnUser = ColumnUser;
                 break;
             }
 break;
}



    if (UserBoard[*ColumnUser][*RowUser] == '*')
    {
        printf("You already have a ship on this location, try again\n");
        Coordinate_Set_And_Limit_Check(RowUser,ColumnUser); //recursion, function checks whether there is a ship on this location or not, if there is it calls itself to let user give another coordinates.
    }



}


void ArrayIninialize()
{

 int i, j;

    for(i=0; i < Size; ++i)
    {
        for(j=0; j< Size; ++j)
        {
            UserBoard[i][j] = '0';
        }
    }


    for(i=0; i < Size; ++i)
    {
        for(j=0; j< Size; ++j)
        {
            ComputerBoard[i][j] = '0';         //Initializing Arrays;
        }
    }




}

void PrintUserArray()
{

int x, y;




    printf("User Board\n");
printf("  0 1 2 3 4\n");
for(y=0; y < Size; ++y)
    {
        printf("%d ", y);
        for(x=0; x< Size; ++x)       //good old nested loops to print table of coordinates;
        {
            printf("%c ", UserBoard[x][y]);


        }
        printf("\n");
    }



}

void PrintComputerArray()
{

    int X, Y;
    printf("Computer Board\n");   //after main function calls array initialize every member of this array is 0;
    printf("  0 1 2 3 4\n");

    for(Y=0; Y < Size; ++Y)
    {
        printf("%d ", Y);
        for(X=0; X< Size; ++X)
        {
           if (ComputerBoard[X][Y] == '*')       //it prints 0's instead of * so user wont know where computer aligned it's ships;
            {
                printf("0 ");                    //Using very simple nested loop it just prints out all members on 5x5 board;
            continue;
            }
            printf("%c ", ComputerBoard[X][Y]);


        }
        printf("\n");
    }


}


void PrintArray()
{
    PrintUserArray(); //prints user array then skips two lines and prints computer array;
    printf("\n\n");
    PrintComputerArray();
}

int main()

{


    PrintIntro(); // this function reads from file;

    system("COLOR 0F");  //Color of the compiler
    srand(time(0));   //we want to have new random values
    int Horizontal, Vertical;
    int* Horizontal_Coordinate, Vertical_Coodrinate; //these variables are for user
    Horizontal_Coordinate = &Horizontal;
    Vertical_Coodrinate = &Vertical;
    // vertical and horizontal coordinate declaration for user and their pointers respectively.

    int HorizontalComputer, VerticalComputer;
    int* RowC = &HorizontalComputer;
    int* ColC = &VerticalComputer;
    //pretty much the same thing for computer.

    ArrayIninialize(); //lets every elements of array initially be set to 0; which represents free space in the game
    PrintArray(); //it prints both arrays(computer and user)

    int gela; //gela is a male name in Georgia, I user this as a integer name in order to avoid stressing out for too much
    gela = NumberOfShips(); //gela takes value of how many ships are in game.


    int j =0;
  printf("You should set your ships now:\n");
  while( j < gela)
    {
    Coordinate_Set_And_Limit_Check(Horizontal_Coordinate,Vertical_Coodrinate); //this is for user;
    CopmuterAligningShips(RowC, ColC);  //now computer gives coordinates;
    printf("\n");
    PrintWithCoordinates(Horizontal_Coordinate, Vertical_Coodrinate, RowC, ColC);
    j++;
     //program lets user palce ships for gela times, and gela is number of ships.
     //also computer places gela ships

    }

   printf("Now your ships has been set, prepare for the battle!\n");
   printf("\n\n");


int zaza;
zaza = 1;

int WhoShots;

WhoShots = rand()%2; // it can be either 0 or 1, it decides who shots first, computer or user

if (WhoShots == 1)
{
      ShootUser(RowC, ColC);
      ShootComputer();
      PrintArray(Horizontal_Coordinate, Vertical_Coodrinate, RowC, ColC);
      WhoShots = WhoShots + 1; //this restrics this ineger to be 1 or 0, so after another call it wont do anything
}
 else if (WhoShots == 0)
{
    ShootComputer();
    ShootUser(RowC, ColC);
    PrintArray(Horizontal_Coordinate, Vertical_Coodrinate, RowC, ColC);
    WhoShots =WhoShots + 1;      //so to make this game fair, random value decides which shots first, user or computer.
}                                //obviously user does not see who shot firsts, compute

while (zaza > 0)
   {
      if (WhoShots%2 == 1)
{
      ShootUser(RowC, ColC);
      ShootComputer();
      PrintArray(Horizontal_Coordinate, Vertical_Coodrinate, RowC, ColC);
      WhoShots = WhoShots + 1;
}     //when 1 is added WhoShots%2 becomes 0 and now computer is the one who shots first
 else if (WhoShots%2 == 0)     //obviously user does not see that but this more fair because if computer and user both shots their opponent's last ship program would randomly choose winner
{
    ShootComputer();
    ShootUser(RowC, ColC);
    PrintArray(Horizontal_Coordinate, Vertical_Coodrinate, RowC, ColC);
    WhoShots = WhoShots + 1;  //another advantage of this algorithm is when user chooses to play with 25 (max) ships. if the algorithm was operated such way that user shot always first, the user would never lose
}                             // else if computer started shooting it would never lose in the same case.

      zaza = CheckWinner(gela);  // CheckWinner returns 1 if there is no winner
   }


 return 0;
}
