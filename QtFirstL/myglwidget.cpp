#include "myglwidget.h"



MyGLWidget::MyGLWidget(QWidget *parent): QOpenGLWidget(parent) {

}

MyGLWidget::~MyGLWidget()
{

}

const char* vertexShader = "attribute vec2 coord2d:\n"
                           "attribute vec3 color:\n"
                           "varying vec3 vColor:\n"
                           "void main(void){\n"
                           "gl_Position = vec4(coord2d.x, coord2d.y, 0.0, 1.0);\n"
                           "vColor = color;\n"
                           "}\n";

GLfloat triangle_vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};

GLfloat triangle_colors[] = {
     0.0, 0.0, 1.0,
     0.0, 1.0, 0.0,
     1.0, 0.0, 0.0,
  };

void MyGLWidget::initializeGL() {
    initializeOpenGLFunctions();

}

void MyGLWidget::resizeGL(int width, int height)
{

}

void MyGLWidget::paintGL()
{

}
