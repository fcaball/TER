#ifndef OPENGLPERSO_H
#define OPENGLPERSO_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColor>

class OpenGLPerso:public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLPerso(QWidget *parent = nullptr);
    ~OpenGLPerso();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif // OPENGLPERSO_H
