#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h> // for Sleep function
#include<time.h>    // for time function

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 27
#define BASKET_SPEED 4 // Adjust the speed of the basket
#define EGG_SPEED 250 // Lower value increases the speed of the egg falling

int basketPosition=SCREEN_WIDTH/2; // initial position of the basket
int score=0;                          // player's score
int eggSpeed=EGG_SPEED;               // initial egg falling speed
void gotoxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void drawBasket()
{
    gotoxy(basketPosition,SCREEN_HEIGHT-1);
    printf("|||||");
}

void eraseBasket()
{
    gotoxy(basketPosition,SCREEN_HEIGHT-1);
    printf("     "); // Erase three characters for "||||"
}

void drawEgg(int x,int y)
{
    gotoxy(x,y);
    printf("0");
}

void eraseEgg(int x,int y)
{
    gotoxy(x,y);
    printf("  ");
}

void drawScore()
{
    gotoxy(SCREEN_WIDTH+20,0);
    printf("USE <,> or A,D");
    gotoxy(SCREEN_WIDTH+20,1);
    printf("P or R");
    gotoxy(SCREEN_WIDTH+20,2);
    printf("Score: %d",score);
    gotoxy(SCREEN_WIDTH+20,3);
    printf("Level: %s",score<=15?"EASY":(score>15?"MEDIUM":(score>=40?"HARD":"DIFFICULT++")));
    if(_kbhit())
        {
        char ch =_getch();
        if(ch=='p'||ch=='P')
        {
            gotoxy(SCREEN_WIDTH+20,4);
            printf("Paused");
            while(1)
            {
                if(_kbhit())
                {
                    char key=_getch();
                    if(key=='r'||key =='R')
                    {
                        gotoxy(SCREEN_WIDTH+20,4);
                        printf("        "); // Clear the "Paused" message
                        break;
                    }
                }
            }
        }
    }
}

void moveBasket()
{
    if (_kbhit())
    {
        char ch=_getch();
        switch(ch)
        {
            case 75:// Left arrow key
            if(basketPosition>0) {
                    eraseBasket();
                    basketPosition-=BASKET_SPEED; // Move left by BASKET_SPEED units
                    drawBasket();
                }
                break;

            case 97: // 'A' key
                if (basketPosition>0) {
                    eraseBasket();
                    basketPosition-=BASKET_SPEED; // Move left by BASKET_SPEED units
                    drawBasket();
                }
                break;
            case 77: // Right arrow key
                if (basketPosition<SCREEN_WIDTH-3)
                {
                    eraseBasket();
                    basketPosition+=BASKET_SPEED; // Move right by BASKET_SPEED units
                    drawBasket();
                }
                break;
            case 100: // 'D' key
                if (basketPosition<SCREEN_WIDTH-3)
                {
                    eraseBasket();
                    basketPosition+=BASKET_SPEED; // Move right by BASKET_SPEED units
                    drawBasket();
                }
                break;
            case 27: // ESC key
                exit(0);
        }
    }
}

int main()
{
    int highscore=0;
    int eggX, eggY=0; // position of the egg
    int basketWidth=5; // width of the basket
    int gameOver=0; // flag to indicate game over
    int pause=0; // flag to indicate pause state
    label:
    srand(time(NULL));

    while(!gameOver)
    {
        if(!pause)
        {
            eggX=rand()%(SCREEN_WIDTH);

            while(eggY<SCREEN_HEIGHT)
            {
                drawEgg(eggX,eggY);
                drawScore();
                moveBasket();

                if((eggY==SCREEN_HEIGHT-1)&&((eggX>=basketPosition)&&(eggX<basketPosition+basketWidth)))
                {
                    score++;
                    eraseEgg(eggX,eggY);
                    break;
                } else if(eggY==SCREEN_HEIGHT-1)
                {
                    gameOver=1; // Egg missed the basket, end the game
                    break;
                }
                if(score%10 ==0) {
                    eggSpeed-=(0.5/100)*eggSpeed; // Increase egg speed by 0.5%
                }

                Sleep(eggSpeed); // Adjusted speed for the egg falling
                eraseEgg(eggX,eggY);
                drawScore();
                moveBasket();
                eggY++;
            }

            eggY=0;
        }
        else
        {
            printf("\nPaused. Press 'R' to resume.\n");
            while(pause)
            {
                if(_kbhit())
                {
                    char key=_getch();
                    if(key=='r'||key =='R')
                    { // resume
                        gotoxy(SCREEN_WIDTH-10,1);
                        printf("        "); // Clear the "Paused" message
                        pause=0;
                        printf("\nResumed.\n");
                    }
                    if(key=='q')
                    {
                        gameOver=1;
                        break;
                    }
                }
            }
        }
    }
    printf("\nGAME OVER !!! ");
    if(score>=highscore)
    {
        highscore=score;
        printf("\nNew High Score = %d",highscore);
    }
    else
    {
        printf("\nHIGHSCORE =%d",highscore);
    }
    printf("\nScore = %d\n",score);
    printf("Press 'C' to Replay or E to exit...\n");
    char restartKey=getche();
    if (restartKey=='c'||restartKey=='C')
    {
        system("cls");
        basketPosition=SCREEN_WIDTH/2;
        score=0;
        eggSpeed=EGG_SPEED;
        basketWidth=5;
        gameOver=0;
        pause=0;
        eggY=0;// Reset egg position
        goto label;
    }
    else if(restartKey=='e'||restartKey=='E')
    {
        exit(0);
    }

    getchar(); // Hold the terminal open

    return 0;
}
