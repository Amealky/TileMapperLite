#ifndef MAPVIEW_H
#define MAPVIEW_H


#include <QWidget>
#include <QPaintEvent>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <stdlib.h>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QStyleOption>
#include <string>

#include "TileGraphicsView.h"
#include "../dialogs/MapSizeDialog.h"
#include "../models/map.h"

#include <QGraphicsView>

class MapGraphicsView : public TileGraphicsView
{
    Q_OBJECT
public:
    explicit MapGraphicsView(QWidget *parent = 0);
    void initNewMap(int tileNumberX, int tileNumberY, int tileSize);
    void initExistingMap(vector <vector<QString>> mapDatas);
    void changeMapSize(int newSizeX, int newSizeY);

    void drawContent() override;
    void checkToDrawTile(QPointF mousePos);
    void drawTile(int tilePosX, int tilePosY, QString tileValue);

    bool isAMapAlreadyOpen();
    QPixmap getTileImageForValue(QString tileValue);
    QPixmap mapToImage();

    void onTilesetChange(QPixmap tileset);
    void onCurrentTileChange(QPixmap newTileImage, QString newTileValue);
    void onActiveLayoutChange(int layoutValue);

    void mouseMoveEvent(QMouseEvent *evt) override;
    void mousePressEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;


     Map *map;

private:
    bool mapAlreadyOpen;
    int activeLayer;
    int buttonPressed;

    vector<QGraphicsItem*> tiles;

signals:
     void mouseMoveSignal(int x, int y);


};

#endif // MAPVIEW_H



