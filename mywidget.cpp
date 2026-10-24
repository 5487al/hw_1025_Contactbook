#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    // 設定表格為四個欄位
    ui->contactBook->setColumnCount(4);

    // 設定表格標題
    QStringList colTotal;
    colTotal << "學號" << "班級" << "姓名" << "電話";

    ui->contactBook->setHorizontalHeaderLabels(colTotal);
}

MyWidget::~MyWidget()
{
    delete ui;
}

// 1. 新增聯絡人
void MyWidget::on_insertButton_clicked()
{
    QTableWidgetItem *col1, *col2, *col3, *col4;
    col1 = new QTableWidgetItem(ui->lineEdit_1->text());
    col2 = new QTableWidgetItem(ui->lineEdit_2->text());
    col3 = new QTableWidgetItem(ui->lineEdit_3->text());
    col4 = new QTableWidgetItem(ui->lineEdit_4->text());

    int row = ui->contactBook->rowCount();
    qDebug() << "Inserted at row:" << row;
    ui->contactBook->insertRow(row); // 新增一列
    ui->contactBook->setItem(row, 0, col1);
    ui->contactBook->setItem(row, 1, col2);
    ui->contactBook->setItem(row, 2, col3);
    ui->contactBook->setItem(row, 3, col4);

    // 新增完畢後清空輸入框，方便輸入下一筆
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

// 2. 刪除聯絡人
void MyWidget::on_deleteButton_clicked()
{
    int currentRow = ui->contactBook->currentRow();

    if (currentRow >= 0)
    {
        // 刪除使用者目前滑鼠點選的那一列
        ui->contactBook->removeRow(currentRow);
    }
    else if (ui->contactBook->rowCount() > 0)
    {
        // 如果沒有點選特定列，但表格有資料，則刪除最後一列
        ui->contactBook->removeRow(ui->contactBook->rowCount() - 1);
    }
}
void CbWrite(QString fileName, QString str)
{
    QFile outFile(fileName);
    if (!outFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Open File failed!";
        return;
    }
    QTextStream out(&outFile);
    out.setEncoding(QStringConverter::System);
    out << str;
    outFile.flush();
    outFile.close();
}

// 3. 匯出通訊錄
void MyWidget::on_exportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "匯出通訊錄", QCoreApplication::applicationDirPath(), "csv(*.csv);;text(*.txt)");
    if (fileName.isEmpty())
    {
        return;
    }

    QString saveStr;
    for (int i = 0; i < ui->contactBook->rowCount(); i++)
    {
        for (int j = 0; j < ui->contactBook->columnCount(); j++)
        {
            if (ui->contactBook->item(i, j) != nullptr)
            {
                saveStr += ui->contactBook->item(i, j)->text() + ",";
            }
            else
            {
                saveStr += ",";
            }
        }
        saveStr += "\n";
    }

    CbWrite(fileName, saveStr);
}

// 4. 匯入通訊錄
void MyWidget::on_importButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "匯入通訊錄", QCoreApplication::applicationDirPath(), "csv(*.csv);;text(*.txt)");
    if (fileName.isEmpty())
    {
        return;
    }

    QFile inFile(fileName);
    if (!inFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open File failed!";
        return;
    }

    QTextStream in(&inFile);
    in.setEncoding(QStringConverter::System);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
        {
            continue;
        }

        QStringList fields = line.split(",");
        if (fields.size() >= 4)
        {
            int row = ui->contactBook->rowCount();
            ui->contactBook->insertRow(row);

            for (int col = 0; col < 4; col++)
            {
                ui->contactBook->setItem(row, col, new QTableWidgetItem(fields[col]));
            }
        }
    }

    inFile.close();
}

