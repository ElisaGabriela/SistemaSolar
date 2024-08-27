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
