#pragma once

#include <QtOpenGL>

class MainWindow: public QGLWidget { Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;
};
