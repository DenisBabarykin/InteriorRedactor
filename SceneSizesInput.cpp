#include "SceneSizesInput.h"
#include "ui_SceneSizesInput.h"

SceneSizesInput::SceneSizesInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneSizesInput)
{
    ui->setupUi(this);
}

SceneSizesInput::~SceneSizesInput()
{
    delete ui;
}

int SceneSizesInput::GetLength()
{
    return length;
}

int SceneSizesInput::GetWidth()
{
    return width;
}

void SceneSizesInput::on_buttonBox_accepted()
{
    if (ui->ledtLength->text().toInt() > 0 && ui->lblWidth->text().toInt() > 0)
        emit SceneCreated(ui->ledtLength->text().toInt(), ui->lblWidth->text().toInt());
}
