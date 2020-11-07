#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QGLWidget(parent) {

}

void MainWindow::initializeGL() {
    init
    qglColor(Qt::white);
}

void MainWindow::resizeGL(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, static_cast<GLint>(width),  static_cast<GLint>(height));
    glOrtho(0, 100, 100, 0, -1, 1);
}

void MainWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(0, 100);

        glColor3f(0, 1, 0);
        glVertex2f(100, 100);

        glColor3f(0, 0, 1);
        glVertex2f(100, 0);

        glColor3f(1, 1, 1);
        glVertex2f(0, 0);
    glEnd();
}
