

#include "bitarr.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

bool Knight(int x, int y);
bool KnightsTour(char *buffer, word_t board, int x_coordinate, int y_coordinate);
void PrintTour(char *buffer);



int main()
{
    if(sizeof(size_t) < 8)
    {
        puts("cant work");
        return 0;
    }
    Knight(0, 0);
    return 0;

}

bool Knight(int x, int y)
{
    char *buffer = (char*)malloc(64 * 4);
    /*char *try = (char*)malloc(64 * 4);*/
    char ans = '0';
    word_t board = 0;
    FILE * tour = fopen("tour2.txt", "w");
    assert(1 == KnightsTour(buffer, board, x, y));

    /*try = "2,3>4,2>6,1>8,0>7,2>5,1>7,0>8,2>6,3>8,4>6,5>8,6>6,7>4,6>2,5>4,4>5,2>7,1>5,0>3,1>1,0>2,2>3,0>1,1>3,2>4,0>2,1>1,3>3,4>5,3>7,4>5,5>7,6>5,7>4,5>6,4>8,3>
    6,2>8,1>6,0>4,1>2,0>1,2>3,3>1,4>2,6>4,7>6,6>8,7>7,5>5,4>7,3>8,5>7,7>5,6>3,7>1,6>2,4>4,3>3,5>2,7>1,5>3,6>1,7>";*/
    while(1)
    {
        ans = '0';
        puts("tour is ready, press 'y' to print, 'n' to save and exit");
        scanf("%c",&ans);

        if(ans == 'y')
        {
            PrintTour(buffer);
        }
        else if (ans == 'n')
        {

            fputs(buffer, tour);
            fclose(tour);
            free(buffer);
            exit(0);
        }
    }

    /*printf("%s\n",buffer);*/
    /*free(buffer);*/
    return 1;
}

bool KnightsTour(char *buffer, word_t board, int x, int y)
{
    word_t new_board = 0;

    if(x > 7 ||
       y > 7 ||
       x < 0 ||
       y < 0 ||
       (y*8+x > 64) ||
       (y*8+x < 0))
    {
        return 0;
    }

    if(BA_IsSet(board, y*8+x))
    {
        return 0;
    }

    new_board = BA_SetBit (board, y*8+x);

    if(new_board == 0xffffffffffffffff)
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }

/*1*/
    if(KnightsTour(buffer+4, new_board, x+2, y+1))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
/*2*/
    if(KnightsTour(buffer+4, new_board, x+1, y+2))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
/*3*/
    if(KnightsTour(buffer+4, new_board, x-1, y+2))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
/*4*/
    if(KnightsTour(buffer+4, new_board, x-2, y+1))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
/*5*/
    if(KnightsTour(buffer+4, new_board, x-2, y-1))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
/*6*/

    if(KnightsTour(buffer+4, new_board, x-1, y-2))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
/*7*/

    if(KnightsTour(buffer+4, new_board, x+1, y-2))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
/*8*/


    if(KnightsTour(buffer+4, new_board, x+2, y-1))
    {
        buffer[0] = '0'+x;
        buffer[1] = ',';
        buffer[2] = '0'+y;
        buffer[3] = '>';
        return 1;
    }
    return 0;
}

void PrintTour(char *buffer)
{
    int i = 0, row = 0, col = 0;
    char grid[8][8] = {0};

    memset(grid, '_', 64);
    system("clear");
    for(i = 0 ; i < (64 * 4) ; i += 4)
    {
        int x = buffer[i] - '0';
        int y = buffer[i+2] - '0';
        printf("%c %c", buffer[i],buffer[i+2]);
        grid[x][y] = 'x';
        puts("____________________");

        for(row = 0; row < 8 ; ++row)
        {
            for(col = 0; col< 8 ; ++col)
            {
                printf("|%c",grid[row][col]);
                putchar('|');

            }
            putchar(10);
        }

        puts("________________________");
        sleep(1);
        system("clear");


    }


}

