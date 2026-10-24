#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget() override;

private slots:
    void on_insertButton_clicked(); // 新增按鈕
    void on_deleteButton_clicked(); // 刪除按鈕
    void on_exportButton_clicked(); // 匯出按鈕
    void on_importButton_clicked(); // 匯入按鈕

private:
    Ui::MyWidget *ui;
};
#endif // MYWIDGET_H