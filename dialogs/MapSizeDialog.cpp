#include "MapSizeDialog.h"
#include "ui_MapSizeDialog.h"

MapSizeDialog::MapSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSizeDialog)
{
    ui->setupUi(this);
    ui->edittext_sizeX->setText("0");
    ui->edittext_sizeY->setText("0");

    ui->edittext_sizeX->setFocus();
}

MapSizeDialog::~MapSizeDialog()
{
    delete ui;
}

int MapSizeDialog::getSizeX()
{
    if(ui->edittext_sizeX->text().toInt() > 999)
    {
        return 999;
    }
    else if(ui->edittext_sizeX->text().toInt() < 0)
    {
        return 0;
    }
    else
    {
        return ui->edittext_sizeX->text().toInt();
    }
}

int MapSizeDialog::getSizeY()
{
    if(ui->edittext_sizeY->text().toInt() > 999)
    {
        return 999;
    }
    else if(ui->edittext_sizeY->text().toInt() < 0)
    {
        return 0;
    }
    else{
        return ui->edittext_sizeY->text().toInt();
    }
}

void MapSizeDialog::setDefaultValue(int defaultSizeX, int defaultSizeY) {
    ui->edittext_sizeX->setText(QString::number(defaultSizeX));
    ui->edittext_sizeY->setText(QString::number(defaultSizeY));
}
