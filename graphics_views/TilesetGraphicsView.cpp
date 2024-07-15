#include "TilesetGraphicsView.h"

TilesetGraphicsView::TilesetGraphicsView(QWidget *parent) : TileGraphicsView (parent) { }


void TilesetGraphicsView::initTileset(QPixmap tileset, int tileSize)
{
    this->tileSize = tileSize;
    tilesetImage = tileset;

    initSceneRect(tileset.width(), tileset.height());

    drawContent();

}

void TilesetGraphicsView::drawContent()
{
    scene->clear();

    QRect tilesetvisible(0, 0, sceneSizeX, sceneSizeY);
    QPixmap seeTileset = tilesetImage.copy(tilesetvisible);
    scene->addPixmap(seeTileset);
    setScene(scene);

    //If grid is enabled we put the grid above the tileset already draw
    if(gridEnabled)
    {
        drawGrid();
    }

}

void TilesetGraphicsView::mousePressEvent(QMouseEvent *evt)
{


    if(evt->x() < sceneSizeX && evt->y() < sceneSizeY)
    {
        QPointF scenePos = mapToScene(evt->pos());
        int tilePosInPixelX = int(scenePos.x()) / tileSize * tileSize;
        int tilePosInPixelY = int(scenePos.y()) / tileSize * tileSize;
        int tilePosX = tilePosInPixelX / tileSize;
        int tilePosY = tilePosInPixelY / tileSize;


        QRect selectionRect(tilePosInPixelX, tilePosInPixelY, tileSize, tileSize);
        tileActiveImage = tilesetImage.copy(selectionRect);

        QString tileXValue = tilePosX < 10 ? "0"+QString::number(tilePosX) : QString::number(tilePosX);
        QString tileYValue = tilePosY < 10 ? "0"+QString::number(tilePosY) : QString::number(tilePosY);


        tileActiveValue = tileYValue+tileXValue;
        emit tileSelected(tileActiveImage, tileActiveValue);

    }

}


