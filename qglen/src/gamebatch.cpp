#include "gamebatch.h"
#include <gamewindow.h>
#include <QPainter>

inline void transformPoint(float out[4], const float m[16], const float in[4])
{
#define M(row,col)  m[col*4+row]
    out[0] =
        M(0, 0) * in[0] + M(0, 1) * in[1] + M(0, 2) * in[2] + M(0, 3) * in[3];
    out[1] =
        M(1, 0) * in[0] + M(1, 1) * in[1] + M(1, 2) * in[2] + M(1, 3) * in[3];
    out[2] =
        M(2, 0) * in[0] + M(2, 1) * in[1] + M(2, 2) * in[2] + M(2, 3) * in[3];
    out[3] =
        M(3, 0) * in[0] + M(3, 1) * in[1] + M(3, 2) * in[2] + M(3, 3) * in[3];
#undef M
}

inline GLint project(float objx, float objy, float objz,
    float model[16], float proj[16],
    int viewport[4],
    int * winx, int * winy, int * winz)
{
    float in[4], out[4];

    in[0] = objx;
    in[1] = objy;
    in[2] = objz;
    in[3] = 1.0f;
    transformPoint(out, model, in);
    transformPoint(in, proj, out);

    if (in[3] == 0.0)
        return GL_FALSE;

    in[0] /= in[3];
    in[1] /= in[3];
    in[2] /= in[3];

    *winx = viewport[0] + (1 + in[0]) * viewport[2] / 2;
    *winy = viewport[1] + (1 + in[1]) * viewport[3] / 2;

    *winz = (1 + in[2]) / 2;
    return GL_TRUE;
}
void gameBatch::drawText(QPainter *painter, const glm::vec3 &textPosWorld, QString text)
{
    //int width = m_pWnd->width();
    int height = m_pWnd->height();

    float model[4][4], proj[4][4];
    int view[4];

    m_pWnd->glGetFloatv(GL_MODELVIEW_MATRIX, &model[0][0]);
    m_pWnd->glGetFloatv(GL_PROJECTION_MATRIX, &proj[0][0]);

    glGetIntegerv(GL_VIEWPORT, &view[0]);
    int textPosX = 0, textPosY = 0, textPosZ = 0;

    project(textPosWorld.x, textPosWorld.y, textPosWorld.z,
                 &model[0][0], &proj[0][0], &view[0],
                &textPosX, &textPosY, &textPosZ);

    textPosY = height - textPosY; // y is inverted

    painter->setPen(Qt::white);
    painter->setFont(QFont("Helvetica", 8));
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->drawText(textPosX, textPosY, text); // z = pointT4.z + distOverOp / 4

}
