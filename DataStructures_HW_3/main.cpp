//Program 2: uses glDrawElement
//Jenn Chan (chanj6) and Nail Hanov

#include <iostream>
#include <time.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

int N = 0;

static float vertices[] = 
{
   0.0, 0.0, 0.0,
   3.0, 0.0, 0.0,
   3.0, 3.0, 0.0,
   0.0, 3.0, 0.0
};
 
static float colors[] =
{
   1.0, 0.0, 0.0,
   0.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   0.0, 0.0, 1.0
};

int alist;
static unsigned char stripIndices[]={0,1,2,3};

void drawScene(void) 
{
   double diff;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   clock_t begin = clock();  
   for (int i = 0; i < N; i++)
   { 
      glTranslatef(0.5, 0.5, 0.0);
      glCallList(alist);
 
      glFlush();
   }
   clock_t end = clock();
   diff = difftime(end, begin)/ (double)CLOCKS_PER_SEC;
   cout << "It took " << diff << " seconds to draw the polygons." << endl;
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    alist = glGenLists(1);
    glNewList(alist, GL_COMPILE);
       glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, stripIndices);
    glEndList();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Main routine.
int main(int argc, char **argv) 
{
   cout << "Enter number of polygons: ";
   cin >> N;
   if (N < 1) {
      cout << "That number is invalid. It must be at least 1." << endl;
      return 1;
   }

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutInitWindowSize(700, 700);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("program2.cpp");
   setup();
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}
