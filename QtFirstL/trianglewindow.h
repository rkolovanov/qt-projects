#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "OpenGLWindow.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();

    void initialize() override;
    void render() override;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};

#endif // TRIANGLEWINDOW_H
