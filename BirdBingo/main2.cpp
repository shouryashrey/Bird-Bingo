#include<stdlib.h>
#include<GLUT/glut.h>
#include<time.h>
//#include<dos.h>
#include<stdio.h>
//#include<conio.h>
//#include<Windows.h>
#include<stdio.h>
#include<math.h>
#include<iostream>

using namespace std;

float bspd = 0.3;
char name[25];
float b1x = 50.0, b1y = 0;
float hm = 0.0;
int i = 0, sci = 1; float scf = 1;
char scs[20], slevel[20];
int level = 1, lflag = 1, wflag = 1;

void delay(float secs)
{
    float end = clock() / CLOCKS_PER_SEC + secs;
    while ((clock() / CLOCKS_PER_SEC) < end);
}

void init(void) {
    glClearColor(0.6, 0.8, 0.9, 1.0);
    srand(time(0));
    b1y = (rand() % 45) + 10;
    
}

void drawbird()
{
    
    int birdX = 10;
    int birdY = 45;
    
    //    Body
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(birdX, birdY, 0.0);
    glutSolidSphere(2.1, 100, 100);
    glPopMatrix();
    
    // Head
    glColor3f(1, .5, 0);
    glPushMatrix();
    glTranslatef(birdX + 1.95, birdY + 1.55, 0.0);
    glutSolidSphere(0.99, 50, 50);
    glPopMatrix();
    
    /// Eye
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(birdX + 2, birdY + 1.55, 0.25);
    glutSolidSphere(.4, 50, 50);
    glEnd();
    glPopMatrix();
    
    glColor3f(0, .5, 0);
    /// Lips
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f(birdX + 2.5, birdY + 2, 0.0);
    glVertex3f(birdX + 5, birdY + 1.55, 0.0);
    glVertex3f(birdX + 2.5, birdY + 0.9, 0.0);
    glEnd();
    glPopMatrix();
    
    /// BackWings
    glColor3f(0, .5, 0);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f(birdX + 0.75, birdY, 0.0);
    glVertex3f(birdX - 0.75, birdY, 0.0);
    glVertex3f(birdX, birdY - 1, 0.0);
    glEnd();
    glPopMatrix();
}


void renderBitmap(float x, float y, float z, void* font, char* string) {
    char* c; glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    //GameOver Checking
    if ((i == 730 || i == -700) ||
        (((int)b1x == 10 || (int)b1x == 7 || (int)b1x == 4 || (int)b1x == 1) && (int)b1y < 53 + (int)hm && (int)b1y + 35>53 + (int)hm)
        // propeller front checking
        ||
        (((int)b1x == 9 || (int)b1x == 3 || (int)b1x == 6) && (int)b1y < 45 + (int)hm && (int)b1y + 35>45 + (int)hm)
        //lower body checking
        ||
        (((int)b1x == 0) && (int)b1y < 46 + (int)hm && (int)b1y + 35>46 + (int)hm))
        // lower tail checking
    {
        
        glColor3f(0.0, 0.0, 1.0);
        renderBitmap(42, 70, 0, GLUT_BITMAP_HELVETICA_18, (char*)"GAME OVER");
        renderBitmap(22, 58, 0, GLUT_BITMAP_TIMES_ROMAN_24, (char*)"YOU");
        renderBitmap(42, 58, 0, GLUT_BITMAP_TIMES_ROMAN_24, (char*)"SCORED : ");
        renderBitmap(68, 58, 0, GLUT_BITMAP_TIMES_ROMAN_24, scs);
        
        
        glutSwapBuffers();
        glFlush();
        
        std::cout << "\nGAME OVER\n";
        std::cout << "HEY " << name << " YOU SCORED : " << scs;
        std::cout << "\nCLOSE THE TERMINAL TO EXIT\n";
        
        delay(10);
        
        exit(0);
    }
    else if (wflag == 1)//Welcome Screen
    {
        wflag = 0;
        glColor3f(1.0, 0.0, 0.0);
        
        renderBitmap(25,85,0,GLUT_BITMAP_HELVETICA_18,"Thapar Institute of Engineering and Technology");
        renderBitmap(45,80,0,GLUT_BITMAP_HELVETICA_12,"Patiala, Punjab");
        
        
        glColor3f(0.0, 0.0, 1.0);
        renderBitmap(35,65,0,GLUT_BITMAP_8_BY_13,"Project for Computer Graphics : UCS505");
        renderBitmap(35,60,0,GLUT_BITMAP_8_BY_13,"Created By : Shrey, Himanshi, Ansh");
        renderBitmap(45,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"BirdBingo 🐧");
        
        
        renderBitmap(40,45,0,GLUT_BITMAP_TIMES_ROMAN_24,"Welcome");
        renderBitmap(53,45,0,GLUT_BITMAP_TIMES_ROMAN_24,name);
        renderBitmap(43,30,0,GLUT_BITMAP_TIMES_ROMAN_24,"Click To Start");
        renderBitmap(17,24,0,GLUT_BITMAP_9_BY_15,"CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP RELEASE TO GO DOWN");
        
        
        drawbird();
        
        glutSwapBuffers();
        glFlush();
    }
    else
    {
        
        if (sci % 50 == 0 && lflag == 1)
        {
            lflag = 0;
            level++;
            bspd += 0.01;
        }
        
        else if (sci % 50 != 0 && lflag != 1)
        {
            lflag = 1;
        }
        glPushMatrix();
        glColor3f(0.0, 0.5, 0.7);
        glRectf(0.0, 0.0, 100.0, 10.0);
        
        glRectf(0.0, 100.0, 100.0, 90.0);
        
        glColor3f(0.0, 0.0, 0.0);
        
        renderBitmap(1, 3, 0, GLUT_BITMAP_TIMES_ROMAN_24, (char*)"DISTANCE:");
        
        sprintf(slevel, "%d", level); //level
        
        renderBitmap(80, 3, 0, GLUT_BITMAP_TIMES_ROMAN_24, (char*)"LEVEL:");
        renderBitmap(93, 3, 0, GLUT_BITMAP_TIMES_ROMAN_24, slevel);
        
        scf += 0.025;
        
        sci = (int)scf;
        sprintf(scs, "%d", sci);
        
        renderBitmap(20, 3, 0, GLUT_BITMAP_TIMES_ROMAN_24, scs);
        glTranslatef(0.0, hm, 0.0);
        
        drawbird();
        
        if (b1x < -10)
        {
            b1x = 50;
            //total width is 50
            b1y = (rand() % 25) + 20;
            
        }
        else
        {
            b1x -= bspd;
            
            glTranslatef(b1x, -hm, 0.0);
            glColor3f(1.0, 0.0, 0.0);
            glRectf(b1x, b1y, b1x + 5, b1y + 35);
            glPopMatrix();
            glutSwapBuffers();
            glFlush();
        }
    }
}


void moveHeliU()
{
    hm += 0.5;
    i++;
    glutPostRedisplay();
}


void moveHeliD()
{
    hm -= 0.5;
    i--;
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) {
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(moveHeliU);
            else if (state == GLUT_UP)
                glutIdleFunc(moveHeliD);
            break;
        default:
            break;
    }
}


void arrowkeys(int key, int x, int y) {
    switch (key)
    {
        case GLUT_KEY_UP:
            glutIdleFunc(moveHeliU);
            break;
        case GLUT_KEY_DOWN:
            glutIdleFunc(moveHeliD);
            break;
        default:
            break;
    }
}

void keys(unsigned char key, int x, int y)
{
    if (key == 'q') {
        exit(0);
    }
}

void reshape(int w, int h) {
    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    //input name
    std::cout << "ENTER YOUR NAME : ";
    std::cin >> name;
    
    glutInit(&argc, argv); //initialize glut
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("BirdBingo🐧 Game");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMouseFunc(mouse);
    glutSpecialFunc(arrowkeys);
    glutKeyboardFunc(keys);
    glutMainLoop();
    return 0;
}
