#include "map.h"

Map::Map()
{
    mapSizeX = 0;
    mapSizeY = 0;
    mapSizeInPixelX = 0;
    mapSizeInPixelY = 0;

}

void Map::initSize(int maxX, int maxY, int tileSize) {
    mapSizeX = maxX;
    mapSizeY = maxY;
    this->tilesize = tileSize;

    mapSizeInPixelX = mapSizeX * tilesize;
    mapSizeInPixelY = mapSizeY * tilesize;

    tileLayout1.clear();
    tileLayout2.clear();
    tileLayout3.clear();

    for(int x = 0; x <= mapSizeX; x++)
    {
        tileLayout1.push_back(vector<QString>(mapSizeY));
        tileLayout2.push_back(vector<QString>(mapSizeY));
        tileLayout3.push_back(vector<QString>(mapSizeY));
        for(int y = 0; y < mapSizeY; y++)
        {
            tileLayout1[x][y] = tileLayout2[x][y] = tileLayout3[x][y] = "0";

        }
    }
}

void Map::changeSize(int newMaxX, int newMaxY) {
    vector<vector<QString>> newTileLayout1;
    vector<vector<QString>> newTileLayout2;
    vector<vector<QString>> newTileLayout3;

    for(int x = 0; x <= newMaxX; x++)
    {
        newTileLayout1.push_back(vector<QString>(newMaxY));
        newTileLayout2.push_back(vector<QString>(newMaxY));
        newTileLayout3.push_back(vector<QString>(newMaxY));
        for(int y = 0; y < newMaxY; y++)
        {
            if(x < mapSizeX && y < mapSizeY)
            {
              newTileLayout1[x][y] = tileLayout1[x][y];
              newTileLayout2[x][y] = tileLayout2[x][y];
              newTileLayout3[x][y] = tileLayout3[x][y];
            }
            else
            {
              newTileLayout1[x][y] = newTileLayout2[x][y] = newTileLayout3[x][y] = "0";
            }

        }
    }
    tileLayout1 = newTileLayout1;
    tileLayout2 = newTileLayout2;
    tileLayout3 = newTileLayout3;

    mapSizeX = newMaxX;
    mapSizeY = newMaxY;

    mapSizeInPixelX = mapSizeX * tilesize;
    mapSizeInPixelY = mapSizeY * tilesize;


}

