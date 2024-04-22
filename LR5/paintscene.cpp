#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
}

PaintScene::~PaintScene()
{

}

int PaintScene::typeFigure() const
{
    return m_typeFigure;
}

void PaintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    tempFigure->setEndPoint(event->scenePos());
    this->update(QRectF(0,0,this->width(), this->height()));
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    tempFigure = [this, &event]() -> Figure* {
        switch (m_typeFigure) {
        case SquareType:   return new Square(event->scenePos()); break;
        case RombType:     return new Romb(event->scenePos()); break;
        case TriangleType: return new Triangle(event->scenePos()); break;
        default:           return new Rectangle(event->scenePos()); break;
        }
    }();
    this->addItem(tempFigure);
}
