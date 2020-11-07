#include "Scene.h"

Scene::Scene( QWidget *parent ) :
    QGLWidget( parent ),
    x( 0 ),
    y( 100 ),
    rsize( 25 ),
    xstep( 25 ),
    ystep( 1 )
{
    timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ),
             this, SLOT( slotMove() ) );
    timer->start( 33 );

    this->setFocusPolicy( Qt::StrongFocus );
}

void Scene::slotMove()
{
    y -= ystep;

    updateGL();
}

void Scene::initializeGL()
{
    glClearColor( 0.8f, 0.8f, 0.6f, 1.0f );
}

void Scene::paintGL()
{
    // Clear the window with current clearing color
    glClear( GL_COLOR_BUFFER_BIT );

    // Set current drawing color
    glColor3f( 0.0f, 0.5f, 0.5f );

    // Draw a filled rectangle with current color
    glRectf( x, y, x + rsize, y - rsize );
}

void Scene::resizeGL( int w, int h )
{
    // Prevent a divide by zero
    if ( h == 0 ) {
        h = 1;
    }

    // Set Viewport to window dimensions
    glViewport( 0, 0, w, h );

    // Reset coordinate system
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    GLfloat aspectRatio = ( GLfloat ) w / ( GLfloat ) h;

    if ( w <= h ) {
        windowWidth = 100.0f;
        windowHeight = 100.0f / aspectRatio;
        glOrtho( -100.0, 100.0, -windowHeight, windowHeight,
                 1.0, -1.0 );
    } else {
        windowWidth = 100.0 * aspectRatio;
        windowHeight = 100.0;
        glOrtho( -windowWidth, windowWidth, -100.0, 100.0,
                 1.0, -1.0 );
    }

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void Scene::keyPressEvent( QKeyEvent *event )
{
    switch( event->key() ) {
    case Qt::Key_Left:
        x -= xstep;
        break;
    case Qt::Key_Right:
        x += xstep;
        break;
    }
}
