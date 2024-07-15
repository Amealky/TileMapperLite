#include "MapGraphicsView.h"



using namespace std;

MapGraphicsView::MapGraphicsView(QWidget *parent) : TileGraphicsView(parent)
{
    map = new Map();
    mapAlreadyOpen = false;
    activeLayer = 4;
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    gridEnabled = false;

    buttonPressed = -1;


}

void MapGraphicsView::initNewMap(int tileNumberX, int tileNumberY, int tileSize)
{
    mapAlreadyOpen = true;
    map->initSize(tileNumberX, tileNumberY, tileSize);

    this->tileSize = tileSize;
    initSceneRect(map->mapSizeInPixelX, map->mapSizeInPixelY);
}

void MapGraphicsView::initExistingMap(vector<vector<QString>> mapDatas)
{
    initNewMap(mapDatas[0][3].toInt(), mapDatas[0][4].toInt(), mapDatas[0][5].toInt());

    //Remove first line of informations
    mapDatas.erase(mapDatas.begin());

    for (int y = 0; y < mapDatas.size(); y++)
    {
        for(int x = 0; x < map->mapSizeX; x++)
        {
            if(y < map->mapSizeY)
            {
                map->tileLayout1[x][y] = mapDatas[y][x];
            }
            else if(y < map->mapSizeY*2)
            {
                map->tileLayout2[x][y - map->mapSizeY] = mapDatas[y][x];
            }
            else if(y < map->mapSizeY*3)
            {
                map->tileLayout3[x][y - map->mapSizeY*2] = mapDatas[y][x];
            }
        }
    }

    drawContent();
}

void MapGraphicsView::changeMapSize(int newSizeX, int newSizeY)
{
    map->changeSize(newSizeX, newSizeY);
    initSceneRect(map->mapSizeInPixelX, map->mapSizeInPixelY);
    drawContent();
}

void MapGraphicsView::drawContent()
{
    for(QGraphicsItem* tile : tiles)
    {
        delete tile;
    }
    tiles.clear();

    scene->clear();

    for(int x = 0; x < sceneSizeX/map->tilesize; x++)
    {
        for(int y = 0; y < sceneSizeY/map->tilesize; y++)
        {

            QString tileForEachLayerAtThisPos[3] = {map->tileLayout1[x][y], map->tileLayout2[x][y], map->tileLayout3[x][y]};

            //For each layers
            for(int layer = 0; layer < 3; layer++)
            {
                //If the tile isnt empty
                if(tileForEachLayerAtThisPos[layer] != "0")
                {
                    if(!map->tilesetTexture.isNull())
                    {
                         QPixmap actualTile = getTileImageForValue(tileForEachLayerAtThisPos[layer]);
                         QGraphicsItem* tileDrawn = scene->addPixmap(actualTile);
                         tiles.push_back(tileDrawn);

                         if(activeLayer != layer+1 && activeLayer != 4)
                         {
                            tileDrawn->setOpacity(0.2);
                         }

                         tileDrawn->setPos(x*map->tilesize, y*map->tilesize);
                         setScene(scene);
                    }

                }
            }
        }
    }

    if(gridEnabled)
    {
        drawGrid();
    }
}

void MapGraphicsView::checkToDrawTile(QPointF mousePos) {
    int tilePosInPixelX = int(mousePos.x()) / tileSize * tileSize;
    int tilePosInPixelY = int(mousePos.y()) / tileSize * tileSize;
    int tilePosX = tilePosInPixelX / tileSize;
    int tilePosY = tilePosInPixelY / tileSize;

    switch(buttonPressed)
    {
        case Qt::LeftButton:
            drawTile(tilePosX, tilePosY, tileActiveValue);
            break;
        case Qt::RightButton:
            drawTile(tilePosX, tilePosY, "0");
            break;
        default:
            break;
    }
}

void MapGraphicsView::drawTile(int tilePosX, int tilePosY, QString tileValue)
{

    if(tilePosX < sceneSizeX/map->tilesize && tilePosY < sceneSizeY/map->tilesize)
    {
        if(activeLayer == 1)
        {
            map->tileLayout1[tilePosX][tilePosY] = tileValue;
        }
        else if(activeLayer == 2)
        {
            map->tileLayout2[tilePosX][tilePosY] = tileValue;
        }
        else if(activeLayer == 3)
        {
            map->tileLayout3[tilePosX][tilePosY] = tileValue;
        }

        drawContent();
    }

}




QPixmap MapGraphicsView::mapToImage()
{

        QPixmap mapImage = QPixmap(map->mapSizeInPixelX, map->mapSizeInPixelY);
        mapImage.fill(Qt::transparent);
        QPainter painter(&mapImage);
        QPoint posToDraw = QPoint(0,0);


        for(int x = 0; x < map->mapSizeX; x++)
        {
            posToDraw.setX(x*map->tilesize);
            for(int y = 0; y < map->mapSizeY; y++)
            {
                posToDraw.setY(y*map->tilesize);

                QString tileForEachLayerAtThisPos[3] = {map->tileLayout1[x][y], map->tileLayout2[x][y], map->tileLayout3[x][y]};
                for(int layer = 0; layer < 3; layer++) {
                    QPixmap actualTile = getTileImageForValue(tileForEachLayerAtThisPos[layer]);
                    painter.drawPixmap(posToDraw, actualTile);
                }
            }

        }
        painter.end();

        return mapImage;
}


bool MapGraphicsView::isAMapAlreadyOpen() {
    return this->mapAlreadyOpen;
}


QPixmap MapGraphicsView::getTileImageForValue(QString tileValue)
{
    int tileStartY = tileValue.mid(0,2).toInt();
    int tileStartX = tileValue.mid(2, 2).toInt();

    int tileStartYinPixel = tileStartY*map->tilesize;
    int tileStartXinPixel = tileStartX*map->tilesize;

    QRect tileRect(tileStartXinPixel, tileStartYinPixel, map->tilesize, map->tilesize);

    QPixmap tile;

    if(!map->tilesetTexture.isNull())
    {
        if(tileStartXinPixel >= map->tilesetTexture.width() || tileStartYinPixel >= map->tilesetTexture.height())
        {
            //Set default tile
            tile.load(":/Assets/default_tile.png");
        }
        else
        {
            tile = map->tilesetTexture.copy(tileRect);
        }
    }

    return tile;

}



void MapGraphicsView::onTilesetChange(QPixmap tileset) {
    if(tileset.isNull())
    {
        setEnabled(false);
        mapAlreadyOpen = false;
        QMessageBox::warning(this, "Warning !", "Please open a tileset", QMessageBox::Ok);
        return;
    }
    map->tilesetTexture = tileset;
    drawContent();

}


void MapGraphicsView::onCurrentTileChange(QPixmap newTileImage, QString newTileValue) {
    tileActiveImage = newTileImage;
    tileActiveValue = newTileValue;
}

void MapGraphicsView::onActiveLayoutChange(int layoutValue) {
    activeLayer = layoutValue;
    if(mapAlreadyOpen)
    {
        drawContent();
    }

}

void MapGraphicsView::mouseMoveEvent(QMouseEvent *evt) {
    TileGraphicsView::mouseMoveEvent(evt);
    emit mouseMoveSignal(evt->x(), evt->y());

    QPointF mousePos = mapToScene(evt->pos());
    checkToDrawTile(mousePos);
}

void MapGraphicsView::mousePressEvent(QMouseEvent *evt)
{
    buttonPressed = evt->button();
    QPointF mousePos = mapToScene(evt->pos());
    checkToDrawTile(mousePos);
}

void MapGraphicsView::mouseReleaseEvent(QMouseEvent *evt)
{
    buttonPressed = -1;
}

