# Sistema Solar 🪐
**Disciplina:** Computação gráfica 


**Grupo:** 

* Elisa Gabriela Machado de Lucena

* Gabriela Cruz Targino

* Keven Alison dos Santos Bezerra

<p>
  1.) <b>O que faremos?</b> Um sistema solar com a criação de um ambiente 3D que simula a órbita dos planetas ao redor do sol. Os planetas serão representados por esferas, cada um com suas características particulares, e terão movimento circular ao redor do sol central.
</p>

<p>
  2.) <b>Como faremos?</b> Inicialmente, será criada uma janela OpenGL onde a simulação será renderizada. Faremos a modelagem do sol e dos planetas utilizando esferas e definiremos as órbitas dos planetas ao redor do sol. Utilizaremos texturas para representar as aparências dos planetas. Também iremos configurar as fontes de luz para iluminar o sistema solar de forma adequada. Além disso, serão adicionados controles de iteratividade para permitir que o usuário movimente planetas.
</p>

<p>
  3.) <b>Generalidades:</b> Poderão ser adicionados recursos adicionais, como luas orbitando planetas, anéis em torno de planetas gasosos, ou informações sobre cada planeta ao serem clicados.
</p>

```C
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int year = 0, day = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);

   glPushMatrix();
   glutWireSphere(1.0, 20, 16);   /* draw sun */
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
   glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case `d':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case `D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
      case `y':
         year = (year + 5) % 360;
         glutPostRedisplay();
         break;
      case `Y':
         year = (year - 5) % 360;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
```

Alterando o código do livro para um sistema com oito planetas, onde cada planeta é representado por uma função **`drawPlanet()`** que recebe o raio da órbita, a velocidade de rotação e o tamanho do planeta. O loop **`for`** no **`display()`** é responsável por desenhar os oito planetas em suas respectivas órbitas com as velocidades de rotação adequadas.

Atualizações do código

```C
#include <GL/glut.h>

// Variáveis para controlar o ângulo de rotação dos planetas
float angleMercury = 0.0f;
float angleVenus = 0.0f;
float angleEarth = 0.0f;
float angleMars = 0.0f;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo da janela como preto
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	// alteramos a pespectiva
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
		// Colocamos o look at no display
}

void drawPlanet(float radius, float distanceFromSun, float angle, float red, float green, float blue)
{
    glPushMatrix();
// ao invés da relação de dia e ano, usamos um ângulo de rotação para cada planeta
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(distanceFromSun, 0.0f, 0.0f);
    glColor3f(red, green, blue);
// ao invés de usar uma wire sphere, usaremos uma solid sphere
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Posiciona a câmera em uma posição adequada
    gluLookAt(0.0f, 15.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Desenha o sol
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(2.0f, 50, 50);

    /* Desenha os planetas com a função draw planet
			a função recebe como parâmetros o raio da órbita,
		 a velocidade de rotação e o tamanho do planeta.
		 Além disso, adicionamos as cores do RGB como 
		parâmetros na função para definir as cores dos planetas */

    drawPlanet(0.5f, 10.0f, angleMercury, 0.6f, 0.6f, 0.6f);
    drawPlanet(0.7f, 15.0f, angleVenus, 0.8f, 0.5f, 0.2f);
    drawPlanet(0.8f, 20.0f, angleEarth, 0.0f, 0.0f, 1.0f);
    drawPlanet(0.6f, 25.0f, angleMars, 1.0f, 0.0f, 0.0f);

    // Atualiza o ângulo de rotação dos planetas
    angleMercury += 1.0f;
    angleVenus += 0.8f;
    angleEarth += 0.6f;
    angleMars += 0.4f;

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
```
Observações do professor:

→ Colocar textura

→ Colocar iluminação

## Teste 1 - Colocando órbitas

``` C
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// Variáveis para controlar o ângulo de rotação dos planetas
float angleMercury = 0.0f;
float angleVenus = 0.0f;
float angleEarth = 0.0f;
float angleMars = 0.0f;
float angleJupiter = 0.0f;
float angleSaturno = 0.0f;
float angleUrano = 0.0f;
float angleNetuno = 0.0f;

// Variáveis para controlar a posição do mouse
int lastMouseX = 0;
int lastMouseY = 0;
bool isDragging = false;

// Variável global para controlar a distância da câmera
float cameraDistance = 1.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo da janela como preto
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0, (float)width / (float)height, 0.1, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawPlanet(float radius, float distanceFromSun, float angle, float red, float green, float blue)
{
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(distanceFromSun, 0.0f, 0.0f);
    glColor3f(red, green, blue);
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}

void drawOrbit(float radius)
{
    glBegin(GL_LINE_LOOP);
    glColor3f(0.3f, 0.3f, 0.3f);
    for (int i = 0; i < 360; i++)
    {
        float theta = 2.0f * 3.1415926f * i / 360.0f;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posiciona a câmera em uma posição adequada
    gluLookAt(0.0f, 10.0f, 30.0f * cameraDistance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Aplica o ângulo da câmera
    glRotatef(cameraAngleY, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleX, 0.0f, 1.0f, 0.0f);

    // Desenha o sol
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(2.0f, 50, 50);

    // Habilita o teste de profundidade
    glEnable(GL_DEPTH_TEST);

    // Desenha as órbitas dos planetas
    drawOrbit(10.0f);
    drawOrbit(18.62f);
    drawOrbit(25.86f);
    drawOrbit(70.69f);
    drawOrbit(231.86f);
    drawOrbit(246.55f);
    drawOrbit(494.83f);
    drawOrbit(775.86f);

    // Desenha os planetas
    drawPlanet(0.5f, 10.0f, angleMercury, 0.6f, 0.6f, 0.6f);
    drawPlanet(0.7f, 18.62f, angleVenus, 0.8f, 0.5f, 0.2f);
    drawPlanet(0.8f, 25.86f, angleEarth, 0.0f, 0.0f, 1.0f);
    drawPlanet(0.6f, 70.69f, angleMars, 1.0f, 0.0f, 0.0f);
    drawPlanet(1.2f, 231.86f, angleJupiter, 1.0f, 0.0f, 0.0f);
    drawPlanet(1.3f, 246.55f, angleSaturno, 0.8f, 0.5f, 0.2f);
    drawPlanet(0.8f, 494.83f, angleUrano, 0.0f, 0.0f, 1.0f);
    drawPlanet(0.8f, 775.86f, angleNetuno, 0.0f, 0.0f, 0.66f);

    // Desabilita o teste de profundidade
    glDisable(GL_DEPTH_TEST);

    // Atualiza o ângulo de rotação dos planetas
    angleMercury += 1.0f;
    angleVenus += 0.738397f;
    angleEarth += 0.628692f;
    angleMars += 0.508439f;
    angleJupiter += 0.276371f;
    angleSaturno += 0.204641f;
    angleUrano += 0.143460f;
    angleNetuno += 0.113924f;

    glutSwapBuffers();
}

void reset()
{
    angleMercury = 0.0f;
    angleVenus = 0.0f;
    angleEarth = 0.0f;
    angleMars = 0.0f;
    angleJupiter = 0.0f;
    angleSaturno = 0.0f;
    angleUrano = 0.0f;
    angleNetuno = 0.0f;

    // Variáveis para controlar a posição do mouse
    lastMouseX = 0;
    lastMouseY = 0;
    isDragging = false;

    // Variável global para controlar a distância da câmera
    cameraDistance = 1.0f;
    cameraAngleX = 0.0f;
    cameraAngleY = 0.0f;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        isDragging = true;
        lastMouseX = x;
        lastMouseY = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        isDragging = false;
    }
}

void motion(int x, int y)
{
    if (isDragging)
    {
        cameraAngleX += (x - lastMouseX) * 0.5f;
        cameraAngleY += (y - lastMouseY) * 0.5f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    init();
    glutMainLoop();
    return 0;
}
```
### Código com anel de saturno e lua na terra
Foram implementadas funções para criar luas e anéis nos planetas.
```C
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Variáveis para controlar o ângulo de rotação dos planetas
float angleMercury = 0.0f;
float angleVenus = 0.0f;
float angleEarth = 0.0f;
float angleMars = 0.0f;
float angleJupiter = 0.0f;
float angleSaturno = 0.0f;
float angleUrano = 0.0f;
float angleNetuno = 0.0f;
float angleMoon = 0.0f;

// Variáveis para controlar a posição do mouse
int lastMouseX = 0;
int lastMouseY = 0;
bool isDragging = false;

// Variável global para controlar a distância da câmera
float cameraDistance = 1.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;

GLfloat dashedPattern[] = { 1.0f, 5.0f }; // Padrão de linha tracejada
bool drawOrbits = true;
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo da janela como preto
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
    glEnable(GL_LIGHTING);  // Habilita a iluminação
    glEnable(GL_LIGHT0);   // Habilita a luz 0 (Sol)
    glEnable(GL_COLOR_MATERIAL);  // Habilita o rastreamento de cor dos materiais
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0, (float)width / (float)height, 0.1, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawOrbit(float radius)
{
    if(drawOrbits){ 	
	    glPushMatrix();
	    glColor3f(0.6f, 0.6f, 0.6f); // Cor da órbita
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Gira a órbita para ficar na horizontal
	    glLineWidth(1.0f); // Espessura da linha da órbita

	    // Desenha a órbita como uma linha contínua
	    glBegin(GL_LINE_LOOP);
	    for (int i = 0; i <= 360; i++)
	    {
		float angle = i * (3.14159f / 180.0f);
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex3f(x, y, 0.0f);
	    }
	    glEnd();

	    glPopMatrix();
    }
}

void drawRing(float innerRadius, float outerRadius)
{
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Cor do anel
    glRotatef(60.0f, 1.0f, 0.0f, 0.0f); // Gira o anel para ficar na horizontal
    glutSolidTorus(innerRadius, outerRadius, 2, 50);
    glPopMatrix();
}

void drawMoon(float radius, float distanceFromPlanet, float angle, float red, float green, float blue)
{	
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(distanceFromPlanet, 0.0f, 0.0f);
    glColor3f(red, green, blue);
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}

void drawPlanet(float radius, float distanceFromSun, float angle, float red, float green, float blue, bool hasMoon, bool hasRing)
{   	
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(distanceFromSun, 0.0f, 0.0f);
    glColor3f(red, green, blue);
    glutSolidSphere(radius, 50, 50);
    if (hasMoon){
        drawMoon(radius / 3.0f, radius + 1.0f, angleMoon, 0.5f, 0.5f, 0.5f);
    }  
    if (hasRing){
        drawRing(1.7f, 1.9f);
    }
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posiciona a câmera em uma posição adequada
    gluLookAt(0.0f, 10.0f, 30.0f * cameraDistance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Aplica o ângulo da câmera
    glRotatef(cameraAngleY, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleX, 0.0f, 1.0f, 0.0f);

    // Habilita o teste de profundidade
    glEnable(GL_DEPTH_TEST);

    // Desenha o sol
    GLfloat light0Position[] = { 0.0f, 0.0f, 0.0f, 1.0f };   // Posição da luz (x, y, z, w)
    GLfloat light0Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };    // Componente ambiente da luz (r, g, b, a)
    GLfloat light0Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // Componente difusa da luz (r, g, b, a)
    GLfloat light0Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Componente especular da luz (r, g, b, a)

    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(5.0f, 50, 50);
    

    // Desenha os planetas
    drawOrbit(10.0f); // Órbita de Mercúrio
    drawPlanet(0.66f, 10.0f, angleMercury, 0.7f, 0.7f, 0.7f, false, false);
    drawOrbit(15.62f); // Órbita de Venus
    drawPlanet(0.83f, 15.62f, angleVenus, 1.0f, 0.5f, 0.2f, false, false);
    drawOrbit(20.86f); // Órbita de Terra
    drawPlanet(0.8f, 20.86f, angleEarth, 0.0f, 0.0f, 1.0f, true, false);
    drawOrbit(25.69f); // Órbita de Marte
    drawPlanet(0.75f, 25.69f, angleMars, 0.8f, 0.2f, 0.2f, false, false);
    drawOrbit(30.86f); // Órbita de Jupiter
    drawPlanet(1.87f, 30.86f, angleJupiter, 0.8f, 0.6f, 0.4f, false, false);
    drawOrbit(35.55f); // Órbita de Saturno
    drawPlanet(1.62f, 35.55f, angleSaturno, 1.0f, 1.0f, 0.6f, false, true);
    drawOrbit(40.72f); // Órbita de Urano
    drawPlanet(1.25f, 40.72f, angleUrano, 0.4f, 0.8f, 0.8f, false, false);
    drawOrbit(45.86f); // Órbita de Netuno
    drawPlanet(1.20f, 45.86f, angleNetuno, 0.2f, 0.2f, 0.8f, false, false);

    // Desabilita o teste de profundidade
    glDisable(GL_DEPTH_TEST);

    // Atualiza o ângulo de rotação dos planetas
    angleMercury += 1.0f;
    angleVenus += 0.738397f;
    angleEarth += 0.628692f;
    angleMars += 0.508439f;
    angleJupiter += 0.276371f;
    angleSaturno += 0.204641f;
    angleUrano += 0.143460f;
    angleNetuno += 0.113924f;
    angleMoon += 2.5f;
    
    
    glutSwapBuffers();
    
}

void reset(){
	angleMercury = 0.0f;
	angleVenus = 0.0f;
	angleEarth = 0.0f;
	angleMars = 0.0f;
	angleJupiter = 0.0f;
	angleSaturno = 0.0f;
	angleUrano = 0.0f;
	angleNetuno = 0.0f;

// Variáveis para controlar a posição do mouse
	lastMouseX = 0;
	lastMouseY = 0;
	isDragging = false;


}
void specialKeys(int key, int x, int y)
{
    // Verifique se a tecla pressionada é uma das setas do teclado
    switch (key)
    {
    case GLUT_KEY_UP:
        // Aproxima a visualização
        cameraDistance -= 0.1f;
        break;
    case GLUT_KEY_DOWN:
        // Afasta a visualização
        cameraDistance += 0.1f;
        break;
    }
    // Redesenha a cena
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
    case 'p':
    case 'P': 
    	reset();
    	break;
    case 'o':
    case 'O':
    drawOrbits = !drawOrbits;
    break;
    }	
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // Inicia o arrasto do mouse
            lastMouseX = x;
            lastMouseY = y;
            isDragging = true;
        }
        else if (state == GLUT_UP)
        {
            // Finaliza o arrasto do mouse
            isDragging = false;
        }
    }
}

void motion(int x, int y)
{
    if (isDragging)
    {
        // Calcula a diferença entre a posição atual do mouse e a posição anterior
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        // Atualiza o ângulo da câmera de acordo com o movimento do mouse
        cameraAngleX += dx * 0.1f;
        cameraAngleY += dy * 0.1f;

        // Atualiza a última posição do mouse
        lastMouseX = x;
        lastMouseY = y;

        // Redesenha a cena
        glutPostRedisplay();
    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
```

