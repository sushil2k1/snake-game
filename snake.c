#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

int height = 30, width = 30;
int speed=1;
int flag = 0;
char c = '^';
int x, y, fruitX, fruitY, gameover, score = 0;
struct Node
{
    int x, y;
    struct Node *next;
};
struct Node *head = NULL;
void addNode(int x, int y)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        struct Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void setup()
{
    gameover = 0;
    x = height / 2; // snake position
    y = width / 2;

    head = (struct Node *)malloc(sizeof(struct Node));
    head->x = x;
    head->y = y;
    head->next = NULL;

label1:
    fruitX = rand() % 28; // fruit position
    if (fruitX == 0)
        goto label1;

label2:
    fruitY = rand() % 28;
    if (fruitY == 0)
        goto label2;
    score = 0;
}

void draw()
{
    system("cls");
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printf("*");
            }
            else
            {
                struct Node *temp = head;
                int printed = 0;
                if (head->x == i && head->y == j)
                {
                    printf("%c", c);
                    printed = 1;
                }
                else
                {
                    temp = head->next;
                    while (temp != NULL)
                    {
                        if (temp->x == i && temp->y == j)
                        {
                            printf("o");
                            printed = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                }
                if (!printed)
                {
                    if (i == fruitX && j == fruitY)
                    {
                        printf("f");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }

    printf("\n\nTotal score : %d\n", score);
    printf("Press 'X' to Exit the Game\n");
}

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'a':
            if (flag != 4)
            {
                flag = 1;
                c = '<';
            }
            break;
        case 's':
            if (flag != 3)
            {
                flag = 2;
                c = 'v';
            }
            break;
        case 'w':
            if (flag != 2)
            {
                flag = 3;
                c = '^';
            }
            break;
        case 'd':
            if (flag != 1)
            {
                flag = 4;
                c = '>';
            }

            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void run()
{

    struct Node *temp = head;
    int prevX = temp->x, prevY = temp->y;
    int tempX, tempY;

    switch (flag)
    {
    case 1:
        temp->y--;
        break;
    case 2:
        temp->x++;
        break;
    case 3:
        temp->x--;
        break;
    case 4:
        temp->y++;
        break;
    default:
        break;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
        tempX = temp->x;
        tempY = temp->y;
        temp->x = prevX;
        temp->y = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    if (head->x == fruitX && head->y == fruitY)
    {
        score += 10;
        speed++;
        addNode(prevX, prevY);
    label3:
        fruitX = rand() % 28;
        if (fruitX == 0)
            goto label3;
    label4:
        fruitY = rand() % 28;
        if (fruitY == 0)
            goto label4;
    }

    if (head->x < 0 || head->x >= height || head->y < 0 || head->y >= width)
    {
        gameover = 1;
    }

    temp = head->next;
    while (temp != NULL)
    {
        if (head->x == temp->x && head->y == temp->y)
        {
            gameover = 1;
            break;
        }
        temp = temp->next;
    }
}

int main()
{
    setup();
    while (!gameover)
    {

        draw();
        input();
        run();
        usleep(400000-(speed*20000));
    }
    return 0;
}
