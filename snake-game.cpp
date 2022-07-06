#include <iostream>
#include <conio.h> // con i/o input output
#include <windows.h> // needed for sleep apparently
#include <time.h> // for randomness
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
bool debug = false;
int playerX, playerY, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail = 1;
int speed = 1; // cannot exceed 42. 40 is in-game max.
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //eDirection is now a type. (much like int is a type) the list within the parenthesis is the enumerators for that type.
eDirection dir; // dir is now a variable of the eDirection type
void CreateFruit()
{
    for (int i = 0; i <= nTail; i++)
    {
        fruitX = (rand() % width) +1;
        fruitY = (rand() % height);
        while ( (fruitX == playerX && fruitY == playerY) || (fruitX == tailX[i] && fruitY == tailY[i]) )
        {
            fruitX = (rand() % width) +1;
            fruitY = (rand() % height);
        }
        
    }
}
void Setup()
{
    gameOver = false;
    dir = STOP; // the "eDirection" named dir now has a value of STOP, of which the value is always 0
    playerX = width / 2;
    playerY = height / 2;
    srand(time(NULL));
    CreateFruit();
    score = 0;
}
void Draw()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    for (int i = 0; i < width + 2; i++) //the first row, all #
        cout << "# ";
        /*
        (int i = 0;    once at beginning
        i is created with a value of 0 when the loop starts.
        i < width;     condition
        if i is less than width (20), the loop executes.
        i++)           at the end, every time
        After the loop finishes, i increases by one and the loop starts over.
        */
        cout << endl;
    for (int y = 0; y < height; y++) // y represents Y coordinates
    {
        for (int x = 0; x <= width; x++) // x represents X coordinates within each line above
        {
            if (x == 0)
            {
                cout << "# ";
                continue;
            }
            if (y == playerY && x == playerX)
            {
                cout << "O ";
                continue;
            }
            else if (y == fruitY && x == fruitX)
            {
                cout << "F ";
                continue;
            }
            else
            {
                bool print = false;
                for (int i = 0; i < nTail; i++)
                {
                    if (tailX[i] == playerX && tailY[i] == playerY && tailY[i] == y && tailX[i] == x)
                    {
                        print = true;
                        break;
                    }
                    if (tailX[i] == x && tailY[i] == y)
                    {
                        cout << "o ";
                        print = true;
                        break;
                    }
                }
                if (!print)
                        cout << "  ";
            }
            if (x == width)
            {
                cout << "# ";
            }
        }
        cout << endl;

    }
    for (int i = 0; i < width + 2; i++)
        cout << "# "; // the last line
    cout << endl;
    cout << "Score: " << score;
    if (speed < 40)
        cout << "  Speed: " << speed << endl;
    else
        cout << "  Speed: MAX" << endl;
    if (debug = true);
        cout << "Player X/Y: " << playerX << "," << playerY;
        cout << "  Fruit X/Y: " << fruitX << "," << fruitY << endl;
        cout << "Tail Length: " << nTail << endl;    
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'w':
            {
                if (dir != DOWN)
                    dir = UP;
                    break;
            }
            case 'a':
            {
                if (dir != RIGHT)
                dir = LEFT;
                break;
            }
            case 's':
            {
                if (dir != UP)
                dir = DOWN;
                break;
            }
            case 'd':
            {
                if (dir != LEFT)
                dir = RIGHT;
                break;
            }
            case 'x':
            {
                gameOver = true;
                break;
            }
            case 'j':
            {
                if (debug = false)
                    debug = true;
                else
                    debug = false;
                break;
            }
        }
    }
}
void Logic()
{
//    int prevX = tailX[0]; // before updating head location, the first segment of the tail is stored in prevX and prevY. The first time, there will not be anything to store in prevX/prevY. since tailX/tailY have no value yet.
//    int prevY = tailY[0];
//    int prev2X, prev2Y;
//    tailX[0] = playerX;
//    tailY[0] = playerY;
//    for (int i = 1; i < nTail; i++) // the rest of the tail is defined based on the value of nTail, which is increased by 1 when a fruit is devoured. If the value of ntail is 1 or less, this will be skipped
//    {
//        prev2X = tailX[i]; // 
//        prev2Y = tailY[i];
//        tailX[i] = prevX;
//        tailY[i] = prevY;
//        prevX = prev2X;
//        prevY = prev2Y;
//    }
    for (int i = nTail; i > 0; i--)
    {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    tailX[0] = playerX;
    tailY[0] = playerY;
    switch (dir)
    {
        case LEFT:
            playerX--;
            break;
        case RIGHT:
            playerX++;
            break;
        case UP:
            playerY--;
            break;
        case DOWN:
            playerY++;
            break;
        default:
            break;
    }
    if (playerX > width || playerX <= 0 || playerY >= height || playerY < 0) //if player hits wall
    {
        gameOver = true;
    }
    for (int i = 0; i <= nTail; i++)
    {
        if (playerX == tailX[i] && playerY == tailY[i] && dir != STOP)
        {
            gameOver = true;
            break;
        }
    }
    if (playerX == fruitX && playerY == fruitY)
    {
        score += 10;
        CreateFruit();
        nTail++;
        if (speed < 40)
            speed++;
    }
}
void Loser()
{
    cout << "ur a fuken cutie pie lmao" << endl;
    system ("pause");
}
int main()
{
    // srand(time(NULL)); // sets time up  for random number
    Setup();
    while (!gameOver) // this loop is the reason the player keeps moving. it's also the reason the game is redrawing constantly. It draws everything, every tick
    {
        Draw();
        Sleep(210 - (speed * 5));// this slows down the loop so it's not as flickery and the player moves at a reasonable pace
        Input();
        Logic(); 
    }
    Loser();
    return 0; // return gives the value for the int in int main(). For main() specifically, a value of 0 means end the program, anything else means continue
}