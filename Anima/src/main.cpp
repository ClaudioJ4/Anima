#include <GL/glut.h>
#include <iostream>
#include "game.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define LINHAS 40.0
#define COLUNAS 40.0
#define FPS 10

bool game_over = false;
extern int sDirection;
int pontos = 0;
int menu_id;
GLuint textura_ID;

void init();
void desenha();
void teclado(int, int, int);
void redimencionar(int, int);
void temporizador(int);
void textura();
void cobra();
void creditos();
void menuOpcao(int);
void criarMenu();



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Jogo da Cobra");
    glutDisplayFunc(desenha);
    glutReshapeFunc(redimencionar);
    glutSpecialFunc(teclado);
    glutTimerFunc(100, temporizador, 0);
    init();

    criarMenu();
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    grade(COLUNAS, LINHAS);
}

void desenha()
{
    if (game_over)
    {
        std::cout << "\n________________________________\n";
        std::cout << "\nSua pontuação foi: " << pontos << "\n";
        std::cout << "\n________________________________\n";
        exit(0);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    textura();
    desenhar_comida();
    desenhar_cobra();
    glutSwapBuffers();
}
void redimencionar(int w, int h)
{
    glViewport(0, 0, (GLfloat)w, GLfloat(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUNAS, 0.0, LINHAS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void temporizador(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, temporizador, 0);
}
void teclado(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (sDirection != DOWN)
            sDirection = UP;
        break;
    case GLUT_KEY_DOWN:
        if (sDirection != UP)
            sDirection = DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if (sDirection != LEFT)
            sDirection = RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if (sDirection != RIGHT)
            sDirection = LEFT;
        break;
    }
}

void textura()
{
    int largura, altura, canais;
    unsigned char* imagem = stbi_load("textures/galaxy.png", &largura, &altura, &canais, 0);
    if (!imagem) {
        printf("Falha no carregamento da textura!\n");
        return;
    }

    GLuint textura_ID;
    glGenTextures(1, &textura_ID);
    glBindTexture(GL_TEXTURE_2D, textura_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagem);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, textura_ID);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-300.0f, -300.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-300.0f, 300.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(300.0f, 300.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(300.0f, -300.0f);
    glEnd();


    stbi_image_free(imagem);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void cobra()
{
    glutDisplayFunc(desenha);
    glutReshapeFunc(redimencionar);
    glutSpecialFunc(teclado);
    init();
}


void menuOpcao(int opcao) {
    switch (opcao) {
        case 0:
        {
            exit(0);
            break;
        }
        case 1:
        {
            cobra();
            break;
        }
        case 2:
        {
            creditos();
            break;
        }
    }
    glutPostRedisplay();
}

void criarMenu()
{
    menu_id = glutCreateMenu(menuOpcao);
    glutAddMenuEntry("Jogar", 1);
    glutAddMenuEntry("Créditos", 2);
    glutAddMenuEntry("Sair", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void creditos()
{
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\n|                   Creditos                | \n";
    std::cout << "\n|               Jogo da Cobrinha            |\n";
    std::cout << "\n|                                           |\n";
    std::cout << "\n| Claudio Jose: Desenvolvedor Full Stack    |  \n";
    std::cout << "\n| Pedro Eduardo: Desenvolvedor Full Stack   | \n";
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}







