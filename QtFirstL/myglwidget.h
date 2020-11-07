#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class MyGLWidget: public QOpenGLWidget, protected QOpenGLFunctions {
public:
    MyGLWidget(QWidget* parent = nullptr);
    ~MyGLWidget();

    void initializeGL()  override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

};

#endif // MYGLWIDGET_H
