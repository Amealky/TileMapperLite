
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QIcon icon(":/Assets/icon.png");

    this->setWindowIcon(icon);

    tilesize = 32;
    ui->setupUi(this);


    //Event connection
    connect(ui->graphicview_tileset, SIGNAL(tileSelected(QPixmap, QString)), SLOT(onTileSelectedInTileset(QPixmap, QString)));
    connect(ui->graphicview_map, SIGNAL(mouseMoveSignal(int,int)), SLOT(positionLabelUpdate(int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newMap() {
    if(ui->graphicview_map->isAMapAlreadyOpen())
    {
       askForSave();
    }

    MapSizeDialog mapSizeDialog;
    if(mapSizeDialog.exec() == QDialog::Accepted)
    {
       ui->graphicview_map->initNewMap(mapSizeDialog.getSizeX(), mapSizeDialog.getSizeY(), 32);
       loadTileset();
    }
}

void MainWindow::loadMap() {
    if(ui->graphicview_map->isAMapAlreadyOpen())
    {
        askForSave();
    }

    QString filter = "Tile Mapper Lite File (*.tmap);;Text File (*.txt);;All files (*.*)";

    QFileDialog loadMapDialog(this,"Load Map","Path",filter);

    if(loadMapDialog.exec())
    {
        QString fileName = loadMapDialog.selectedFiles()[0];
        QFile filemap(fileName);
        QString ext = fileName.section('.', -1);

        if(ext == "tmap" || ext == "TMAP" || ext == "txt" || ext == "TXT")
        {
            if(filemap.exists())
            {
                if(filemap.open(QIODevice::ReadOnly| QIODevice::Text))
                {
                    vector <vector<QString>> mapDatas;
                    vector <QString> lignes;

                    QTextStream flux(&filemap);
                    QStringList strlist;
                    QString strbuf;

                    while(!flux.atEnd())
                    {
                        strbuf += flux.readLine();

                        strlist = strbuf.split(' ');
                        for(int i = 0; i < strlist.length(); i++)
                        {
                            lignes.push_back(QString::fromLatin1(strlist.at(i).toLatin1()));
                        }
                        if(lignes.size())
                        {
                            mapDatas.push_back(lignes);
                        }

                        strlist.clear();
                        strbuf.clear();
                        lignes.clear();

                    }
                    filemap.close();

                    ui->graphicview_map->initExistingMap(mapDatas);
                    if(ui->graphicview_map->map->tilesetTexture.isNull())
                    {
                        loadTileset();
                    }
                    else
                    {
                        if(QMessageBox::question(this,"Use another tileset ?", "Do you want to use another tileset with this map ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
                        {
                             loadTileset();

                        }
                    }

                }
                else
                {
                    QMessageBox::critical(this, "Open Error", "Unable to open file", QMessageBox::Ok);
                }
            }
            else
            {
                QMessageBox::critical(this, "Open Error", "File do not exist", QMessageBox::Ok);
            }

        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Its not a valid file", QMessageBox::Ok);
    }

}

void MainWindow::saveMap() {
    if(ui->graphicview_map->isAMapAlreadyOpen())
    {
        QString Filtre = "TMAP File (*.tmap);;Text File (*.txt);;All Files (*.*)";
        QString path = QFileDialog::getSaveFileName(this,"Save Map","my_super_map.tmap", Filtre);

        QFile file(path);

        file.open(QIODevice::WriteOnly | QIODevice::Text);

        QTextStream flux(&file);

        QString space = " ";
        QString jump = "\n";

        file.flush();

        QString stringToAdd;
        stringToAdd = "0"+space+"0"+space+"0"+space+QString::number(ui->graphicview_map->map->mapSizeX)+space+QString::number(ui->graphicview_map->map->mapSizeY)+space+QString::number(tilesize)+jump;
        flux << stringToAdd;

        for(int i = 0; i < 3; i++)
        {
            for(int y = 0; y < ui->graphicview_map->map->mapSizeY; y++)
            {
                for(int x = 0; x < ui->graphicview_map->map->mapSizeX; x++)
                {
                    stringToAdd = "";

                    if(i == 0) {
                        stringToAdd = ui->graphicview_map->map->tileLayout1[x][y];
                    }
                    else if(i == 1)
                    {
                        stringToAdd = ui->graphicview_map->map->tileLayout2[x][y];
                    }
                    else if(i == 2)
                    {
                        stringToAdd = ui->graphicview_map->map->tileLayout3[x][y];
                    }

                    if(x < ui->graphicview_map->map->mapSizeX-1)
                    {
                        stringToAdd += space;
                    }
                    flux << stringToAdd;

                }

                 stringToAdd = jump;
                 flux << stringToAdd;
            }
        }

        file.close();

    }
    else
    {
        QMessageBox::warning(this, "Warning", "Please open a map", QMessageBox::Ok);
    }

}

void MainWindow::loadTileset()
{
    if(ui->graphicview_map->isAMapAlreadyOpen())
    {
        QString imgFilter = "Images (*.png *.bmp *.jpg *.jpeg)";

        QFileDialog openTilesetDialog(this,"Open Tileset", "", imgFilter);

        if(openTilesetDialog.exec())
        {
            QString imgFileName = openTilesetDialog.selectedFiles()[0];
            QPixmap tilesetTexture;
            tilesetTexture.load(imgFileName);
            ui->graphicview_tileset->initTileset(tilesetTexture, tilesize);
            ui->graphicview_map->onTilesetChange(tilesetTexture);
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Please open a map", QMessageBox::Ok);
    }


}

void MainWindow::resizeMap() {
    if(ui->graphicview_map->isAMapAlreadyOpen())
    {
        MapSizeDialog mapSizeDialog;
        mapSizeDialog.setDefaultValue(ui->graphicview_map->map->mapSizeX, ui->graphicview_map->map->mapSizeY);
        if(mapSizeDialog.exec() == QDialog::Accepted)
        {
           ui->graphicview_map->changeMapSize(mapSizeDialog.getSizeX(), mapSizeDialog.getSizeY());
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Please open a map", QMessageBox::Ok);
    }
}

void MainWindow::exportMapAsImage() {
    if(ui->graphicview_map->isAMapAlreadyOpen())
    {
        QString filter = "Images (*.png)";

        QString path = QFileDialog::getSaveFileName(this,"Export as Image","my_super_map.png",filter); //Demande de choisir un fichier selon le filtre

        QFile file(path);
        if(file.open(QIODevice::WriteOnly))
        {
            QPixmap imageMap = ui->graphicview_map->mapToImage();
            imageMap.save(&file, "PNG");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Please open a map", QMessageBox::Ok);
    }
}

void MainWindow::askForSave() {
    QMessageBox::StandardButton save;
    save = QMessageBox::question(this, "Save Map", "Save before open a new map ?", QMessageBox::Yes|QMessageBox::No);

    if(save == QMessageBox::Yes)
    {
        saveMap();
    }
}


void MainWindow::positionLabelUpdate(int x, int y)
{

    QString tilePosXString = "Column : %1";
    QString tilePosYString = "Row : %1";

    int tilePosX = (x /  tilesize);
    int tilePosY = (y /  tilesize);
    tilePosXString = tilePosXString.arg(tilePosX);
    tilePosYString = tilePosYString.arg(tilePosY);

    ui->la_mousex->setText(tilePosXString);
    ui->la_mousey->setText(tilePosYString);
}


void MainWindow::onTileSelectedInTileset(QPixmap tileImage, QString tileValue)
{
    QGraphicsScene *scene;
    scene = new QGraphicsScene(ui->graphicview_tileset);

    scene->clear();
    scene->addPixmap(tileImage);
    ui->graphicview_current_tile->setScene(scene);
    ui->graphicview_map->onCurrentTileChange(tileImage, tileValue);

}




void MainWindow::on_btn_new_map_clicked()
{
    newMap();
}


void MainWindow::on_btn_load_map_clicked()
{
    loadMap();
}

void MainWindow::on_btn_save_map_clicked()
{
    saveMap();
}


void MainWindow::on_btn_resize_map_clicked()
{
    resizeMap();
}

void MainWindow::on_btn_export_map_clicked()
{
    exportMapAsImage();
}

void MainWindow::on_btn_import_tileset_clicked()
{
    loadTileset();
}

void MainWindow::on_checkbox_grid_toggled(bool checked)
{
     ui->graphicview_tileset->onGridChecked(checked);
     ui->graphicview_map->onGridChecked(checked);

}

void MainWindow::on_rb_layout_all_toggled(bool checked)
{
    if(checked)
    {
        ui->graphicview_map->onActiveLayoutChange(4);
    }
}


void MainWindow::on_rb_layout_back_toggled(bool checked)
{
    if(checked)
    {
        ui->graphicview_map->onActiveLayoutChange(1);
    }
}

void MainWindow::on_rb_layout_mid_toggled(bool checked)
{
    if(checked)
    {
        ui->graphicview_map->onActiveLayoutChange(2);
    }
}

void MainWindow::on_rb_layout_front_toggled(bool checked)
{
    if(checked)
    {
        ui->graphicview_map->onActiveLayoutChange(3);
    }
}

