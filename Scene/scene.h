#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>

class Scene : public QGLWidget
{
    Q_OBJECT

public:
    Scene( QWidget *parent = 0 );

private slots:
    void slotMove();

private:
    void initializeGL()  override;
    void paintGL()  override;
    void resizeGL( int w, int h )  override;

    void keyPressEvent( QKeyEvent * event );

private:
    // Square position and size
    int x;
    int y;
    const int rsize;

    // Step size in x and y directions
    // (number of pixels to move each time)
    int xstep;
    int ystep;

    // Keep track of windows changing width and height
    GLfloat windowWidth;
    GLfloat windowHeight;

    // Timer
    QTimer *timer;
};

#endif // SCENE_H
