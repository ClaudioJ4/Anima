#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include "game.h"


void unit(int, int);
int random(int, int);


bool comprimento_inc = false;
bool seedflag = false;
extern int pontos;
extern bool game_over;
bool comida = false;
int colunas = 0, linhas = 0;
int sDirection = RIGHT;
int comidax, comiday;
int posx[MAX + 1] = { 4,3,2,1,0,-1,-1 };
int posy[MAX + 1] = { 10,10,10,10,10,10,10 };
int comprimento = 7;

void grade(int x, int y)
{
    colunas = x;
    linhas = y;
}


void desenhar_cobra()
{
    for (int i = comprimento - 1; i > 0; i--)
    {
        posx[i] = posx[i - 1];
        posy[i] = posy[i - 1];
    }
    for (int i = 0; i < comprimento; i++)
    {
        glColor3f(0.4, 0.8, 0.4);
        if (i == 0)
        {
            glColor3f(0.0, 1.0, 0.0);
            switch (sDirection)
            {
            case UP:
                posy[i]++;
                break;
            case DOWN:
                posy[i]--;
                break;
            case RIGHT:
                posx[i]++;
                break;
            case LEFT:
                posx[i]--;
                break;
            }
            if (posx[i] == 0 || posx[i] == colunas - 1 || posy[i] == 0 || posy[i] == linhas - 1)
                game_over = true;
            else if (posx[i] == comidax && posy[i] == comiday)
            {
                comida = false;
                pontos++;
                if (comprimento <= MAX)
                    comprimento_inc = true;
            }
            for (int j = 1; j < comprimento; j++)
            {
                if (posx[j] == posx[0] && posy[j] == posy[0])
                    game_over = true;
            }
        }
        glBegin(GL_QUADS);
        glVertex2d(posx[i], posy[i]); glVertex2d(posx[i] + 1, posy[i]); glVertex2d(posx[i] + 1, posy[i] + 1); glVertex2d(posx[i], posy[i] + 1);
        glEnd();
    }
    if (comprimento_inc)
    {
        comprimento++;
        comprimento_inc = false;
    }
}

void desenhar_comida()
{
    if (!comida)
    {
        comidax = random(2, colunas - 2);
        comiday = random(2, linhas - 2);
        comida = true;
    }
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2d(comidax, comiday); glVertex2d(comidax + 1, comiday); glVertex2d(comidax + 1, comiday + 1); glVertex2d(comidax, comiday + 1);
    glEnd();
}


int random(int _min, int _max)
{
    if (!seedflag)
    {
        srand(time(NULL));
        seedflag = true;
    }
    else
        seedflag = false;
    return _min + rand() % (_max - _min);
}



