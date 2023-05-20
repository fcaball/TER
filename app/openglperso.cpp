#include "openglperso.h"

OpenGLPerso::OpenGLPerso(QWidget *parent) : QOpenGLWidget{parent}
{

}

void OpenGLPerso::initializeGL() {
    initializeOpenGLFunctions();
    float r,g,b,a=1.0f;
    QColor* C=Qt::red;
    r=1 .0f;
    g=0.0f;
    b=0.0f;

    glClearColor(r,g,b,a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OpenGLPerso::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void OpenGLPerso::resizeGL(int width, int height) {
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 }





