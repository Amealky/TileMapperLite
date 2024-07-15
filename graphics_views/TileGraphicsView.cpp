#include "TileGraphicsView.h"

TileGraphicsView::TileGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0, width(), height());
    setScene(scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setRenderHints(QPainter::Antialiasing);
    setCursor(QCursor(Qt::CrossCursor));
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    gridEnabled = false;
}


void TileGraphicsView::initSceneRect(int contentSizeX, int contentSizeY)
{
    setEnabled(true);

    // the scene have to be a multiple of the tilesize
    // cause we scroll tile by tile ( its a design choise )
    sceneSizeX = contentSizeX / tileSize * tileSize;
    sceneSizeY = contentSizeY / tileSize * tileSize;
    scene->setSceneRect(0,0, sceneSizeX, sceneSizeY);

    horizontalScrollBar()->setSingleStep(tileSize);
    verticalScrollBar()->setSingleStep(tileSize);
    horizontalScrollBar()->setPageStep(tileSize);
    verticalScrollBar()->setPageStep(tileSize);

    horizontalScrollBar()->setEnabled(horizontalScrollBar()->maximum() > 0);
    verticalScrollBar()->setEnabled(verticalScrollBar()->maximum() > 0);
}

void TileGraphicsView::drawGrid()
{
    for(int i = 0; i < sceneSizeX / tileSize; i++) //Visible width
    {
        for(int j = 0; j < sceneSizeY / tileSize; j++) //Visible height
        {
              QRect rect(i*tileSize, j*tileSize, tileSize, tileSize);
              scene->addRect(rect); //We draw square
        }
    }
}

void TileGraphicsView::onGridChecked(bool checked)
{
    if(isEnabled())
    {
        gridEnabled = checked;
        //Redraw the content to take grid into account above
        drawContent();
    }
}

void TileGraphicsView::scrollContentsBy(int dx, int dy)
{
    int hValue = horizontalScrollBar()->value();
    int vValue = verticalScrollBar()->value();

    // Round the scroll values to the nearest multiple of tileSize
    int newHValue = (hValue / tileSize) * tileSize;
    int newVValue = (vValue / tileSize) * tileSize;

    if (newHValue != hValue) {
        horizontalScrollBar()->setValue(newHValue);
    }
    if (newVValue != vValue) {
        verticalScrollBar()->setValue(newVValue);
    }

    QGraphicsView::scrollContentsBy(dx, dy);
}

void TileGraphicsView::mouseMoveEvent(QMouseEvent *evt)
{

    if(evt->x() < sceneSizeX && evt->y() < sceneSizeY)
    {
        drawContent();

        QPointF scenePos = mapToScene(evt->pos());
        int tilePosInPixelX = int(scenePos.x()) / tileSize * tileSize;
        int tilePosInPixelY = int(scenePos.y()) / tileSize * tileSize;

        QColor mainColor("#502cc9b6");
        QRect selectionRect(tilePosInPixelX, tilePosInPixelY, tileSize, tileSize);
        QPen pen(mainColor, Qt::SolidLine);

        QBrush brush(mainColor);

        scene->addRect(selectionRect, pen, brush);
        setScene(scene);
    }
}

