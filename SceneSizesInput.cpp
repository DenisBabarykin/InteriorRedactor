#include "SceneSizesInput.h"
#include "ui_SceneSizesInput.h"
#include <QIntValidator>
#include <QMessageBox>

SceneSizesInput::SceneSizesInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneSizesInput)
{
    ui->setupUi(this);

    sizesValidator = new QIntValidator(200, 20000, this);
    ui->ledtLength->setValidator(sizesValidator);
    ui->ledtWidth->setValidator(sizesValidator);
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

void SceneSizesInput::on_btnOk_clicked()
{
    int pos = 0;
    QString strLength = ui->ledtLength->text();
    QString strWidth = ui->ledtWidth->text();

    if (sizesValidator->validate(strLength, pos) != QValidator::Acceptable ||
            sizesValidator->validate(strWidth, pos) != QValidator::Acceptable)
        QMessageBox::warning(this, "Ошибка", "Недопустимое значение размеров сцены");
    else
    {
        emit SceneCreated(ui->ledtLength->text().toInt(), ui->ledtWidth->text().toInt());
        accept();
    }
}

void SceneSizesInput::on_btnCancel_clicked()
{
    reject();
}
