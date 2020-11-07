#pragma once

#include <QtOpenGL>
#include <QGLWidget>

class MyGLDrawer : public QGLWidget
  {
      Q_OBJECT        // must include this if you use Qt signals/slots

  public:
      MyGLDrawer(QWidget *parent = nullptr)
          : QGLWidget(parent) {}

  protected:

      void initializeGL() override
      {
          // Set up the rendering context, define display lists etc.:

          glClearColor(0.0, 0.0, 0.0, 0.0);
          glEnable(GL_DEPTH_TEST);

      }

      void resizeGL(int w, int h) override
      {
          // setup viewport, projection etc.:
          glViewport(0, 0, (GLint)w, (GLint)h);



      }

      void paintGL() override
      {
          // draw the scene:

          glBegin(GL_QUADS);
    }

  };
