#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QStringList>
#include <QString>
#include <QArrayData>
#include <QList>
#include <QVector>
#include <QtWidgets/QFileDialog>
#include <QDataStream>
#include <QVariant>
#include <QFileDialog>
#include <QQueue>
#include <future>

//to find the exact package size we need,
//align the structure fields with the using directive "#pragma pack"
#pragma pack(push,1)
struct dataStruct{
    uint16_t header;
    uint32_t id;
    uint64_t time_create;
    uint8_t status_hardware;
    uint8_t status_in_out;
    uint8_t status_device;
    uint8_t reserved;
    float data[21];
    uint16_t crc;
};
#pragma pack(pop)


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE



class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void putData();

private slots:
    void on_downloadButton_clicked();


private:
    Ui::MainWidget *ui;

    QVector<dataStruct> structFromFile;
    QVector<float> dataFromSensors;
    std::array<long long, 8> idData, timeCreateData;

};
#endif // MAINWIDGET_H
