#include "scenewidget.h"



namespace sunshine {

// *****************************************************************************
SceneWidget::SceneWidget(QWidget *parent)
    : mProgram(new QOpenGLShaderProgram), rot(0.0f)
{
    mTimer = new QElapsedTimer();
    mTimer->start();
    last = mTimer->elapsed();

    mLightPosition = QVector3D(-5.0f, 15.0f, 0.0f);
}


SceneWidget::~SceneWidget()
{
    // Make sure the context is current and then explicitly
    // destroy all underlying OpenGL resources.
    makeCurrent();
    {
        delete mProgram;

        mVbo.destroy();
        mVao.destroy();
    }
    doneCurrent();

    delete mTimer;
}

// *****************************************************************************
void SceneWidget::initializeGL()
{
    initializeOpenGLFunctions();

    static GLfloat afVertices1[] = {
        -0.5, 0.5, 0.5, 0.5,-0.5,0.5,-0.5,-0.5,0.5,
        0.5, -0.5, 0.5, -0.5,0.5,0.5,0.5,0.5,0.5,
        -0.5, -0.5, -0.5, 0.5,-0.5,-0.5,-0.5,0.5,-0.5,
        0.5, 0.5, -0.5, -0.5,0.5,-0.5,0.5,-0.5,-0.5,

        0.5, -0.5, -0.5, 0.5,-0.5,0.5,0.5,0.5,-0.5,
        0.5, 0.5, 0.5, 0.5,0.5,-0.5,0.5,-0.5,0.5,
        -0.5, 0.5, -0.5, -0.5,-0.5,0.5,-0.5,-0.5,-0.5,
        -0.5, -0.5, 0.5, -0.5,0.5,-0.5,-0.5,0.5,0.5,

        0.5, 0.5,  -0.5, -0.5, 0.5,  0.5,  -0.5,  0.5,  -0.5,
        -0.5,  0.5,  0.5,  0.5,  0.5,  -0.5, 0.5, 0.5,  0.5,
        -0.5,  -0.5, -0.5, -0.5, -0.5, 0.5,  0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,  0.5,  -0.5, -0.5, -0.5,  -0.5, 0.5
    };

    GLfloat afVertices[] = {
        //  X     Y     Z       U     V
        // bottom
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,

        // top
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        // front
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,

        // back
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        // left
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,

        // right
        1.0f,-1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
    };

    GLfloat afNormals[] = {

        0,0,-1, 0,0,-1, 0,0,-1,
        0,0,-1, 0,0,-1, 0,0,-1,
        0,0,1, 0,0,1, 0,0,1,
        0,0,1, 0,0,1, 0,0,1,

        -1,0,0, -1,0,0, -1,0,0,
        -1,0,0, -1,0,0, -1,0,0,
        1,0,0, 1,0,0, 1,0,0,
        1,0,0, 1,0,0, 1,0,0,

        0,-1,0, 0,-1,0, 0,-1,0,
        0,-1,0, 0,-1,0, 0,-1,0,
        0,1,0, 0,1,0, 0,1,0,
        0,1,0, 0,1,0, 0,1,0
    };

    mProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(":/shaders/vs.glsl"));
    mProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(":/shaders/fs.glsl"));
    mProgram->link();
    mProgram->bind();

    QOpenGLVertexArrayObject::Binder vaoBind(&mVao);

    mVbo.create();
    mVbo.bind();
    mVbo.allocate(36 * 6 * sizeof(GLfloat));
    mVbo.write(0, afVertices, sizeof(afVertices));
    mVbo.write(sizeof(afVertices), afNormals, sizeof(afNormals));

    int vertexAttributeLocation = mProgram->attributeLocation("vertex");
    int normalAttributeLocation = mProgram->attributeLocation("normal");

    mProgram->enableAttributeArray(vertexAttributeLocation);
    mProgram->enableAttributeArray(normalAttributeLocation);
    mProgram->setAttributeBuffer(vertexAttributeLocation, GL_FLOAT, 0, 3);
    mProgram->setAttributeBuffer(normalAttributeLocation, GL_FLOAT, 36 * 3 * sizeof(GLfloat), 3);

    mVbo.release();
}


// *****************************************************************************
void SceneWidget::paintGL()
{
    float deltaTime = (mTimer->elapsed() - last) / 1000.0f;
    float totalTime = mTimer->elapsed() / 1000.0f;
    last = mTimer->elapsed();

    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    mLightPosition = QVector3D(10.0f * sinf(0.5f*totalTime), 15.0f, 10.0f * cosf(0.1f*totalTime));


    QMatrix4x4 modelview;

    float aspect = static_cast<float>(this->width()) / static_cast<float>(this->height());
    QMatrix4x4 viewProjection;
    viewProjection.perspective(60.0f, aspect, 0.01f, 100.0f);

    QVector3D camPos(3.0f, 3.0f, 5.0f);
    QMatrix4x4 cameraMatrix;
    cameraMatrix.lookAt(camPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

    QVector3D Ka(0.6, 0.6, 0.6);
    QVector3D Kd(0.5, 0.5, 0.5);
    QVector3D Ks(0.0, 0.0, 0.0);
    float specularExponent = 0;

    mProgram->bind();
    int matrixUniform = mProgram->uniformLocation("matrix");
    mProgram->setUniformValue(matrixUniform, viewProjection * cameraMatrix * modelview);

    int lightUniform = mProgram->uniformLocation("lightPos");
    mProgram->setUniformValue(lightUniform, mLightPosition);

    int matUniform = mProgram->uniformLocation("material.Ka");
    mProgram->setUniformValue(matUniform, Ka);
    matUniform = mProgram->uniformLocation("material.Kd");
    mProgram->setUniformValue(matUniform, Kd);
    matUniform = mProgram->uniformLocation("material.Ks");
    mProgram->setUniformValue(matUniform, Ks);
    matUniform = mProgram->uniformLocation("material.S");
    mProgram->setUniformValue(matUniform, specularExponent);
    matUniform = mProgram->uniformLocation("cameraPosition");
    mProgram->setUniformValue(matUniform, camPos);

    mVao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    mVao.release();
    mProgram->release();
    //Refresh scene
    update();
    rot += 1;
}


// *****************************************************************************
void SceneWidget::resizeGL(int w, int h)
{}


} // namespace sunshine