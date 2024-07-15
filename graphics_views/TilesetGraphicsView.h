#ifndef TILESETVIEW_H
#define TILESETVIEW_H

#include <QWidget>
#include <QDebug>
#include <QGraphicsScene>
#include <string>
#include <iostream>


#include "TileGraphicsView.h"
#include "../models/map.h"

class TilesetGraphicsView : public TileGraphicsView
{
    Q_OBJECT
public:
    explicit TilesetGraphicsView(QWidget *parent = 0);
    void initTileset(QPixmap tileset, int tileSize);
    void drawContent() override;


private:
    void mousePressEvent(QMouseEvent *evt);

    QPixmap tilesetImage;

signals:
    void tileSelected(QPixmap tileImage, QString tileValue);

};

#endif // TILESETVIEW_H
