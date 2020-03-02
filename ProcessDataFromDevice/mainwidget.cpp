#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "mytablemodel.h"



MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //implementation of the signal from "quitButton"
    connect(ui->quitButton , &QPushButton::clicked,[&]()
    {
        QWidget::close();

    });


}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_downloadButton_clicked()
{

    //temporary variable
    dataStruct tempStruct;

    QFile readFile(QFileDialog::getOpenFileName(this));

    if(readFile.open(QIODevice::ReadOnly)){

        QDataStream stream(&readFile);
        stream.setByteOrder(QDataStream::LittleEndian);
        stream.setVersion(QDataStream::Qt_5_10);

        //set the start of reading the file
        stream.device()->seek(51);

        //knowing the size of the packages we read them from the file
        while(stream.readRawData((char*)&tempStruct, sizeof(tempStruct))){

            //additional verification of the start of the package
            if(tempStruct.header == 9887){
                structFromFile.push_back(tempStruct);

                }
                //read the package field "float data[21]" into a separate array
                for (int i = 0; i != 17; ++i) {
                    dataFromSensors.push_back(tempStruct.data[i]);
                }
        }
    }
    else{
        return;
    }

    emit putData();

}

//loads data into the model and displays it on the screen
void MainWidget::putData()
{
    //output fields "id", "time_create" from eight packages
    //in separate arrays: "idData" and "timeCreateData"
    for (int i = 0; i != idData.size(); ++i) {

        idData.at(i) = structFromFile.at(i).id;
        timeCreateData.at(i) = structFromFile.at(i).time_create;

    }


    MyTableModel * model = new MyTableModel(this);


    //registering columns
    model->registerColumn(new SimpleColumn("PacketOne"));
    model->registerColumn(new SimpleColumn("PacketTwo"));
    model->registerColumn(new SimpleColumn("PacketThree"));
    model->registerColumn(new SimpleColumn("PacketFour"));
    model->registerColumn(new SimpleColumn("PacketFive"));
    model->registerColumn(new SimpleColumn("PacketSix"));
    model->registerColumn(new SimpleColumn("PacketSeven"));
    model->registerColumn(new SimpleColumn("PacketEight"));

    //filling in data row 'id' from all packages
    QVariantMap rowId;
    rowId.insert("id", 1);
    rowId.insert("PacketOne", idData.at(0));
    rowId.insert("PacketTwo", idData.at(1));
    rowId.insert("PacketThree", idData.at(2));
    rowId.insert("PacketFour", idData.at(3));
    rowId.insert("PacketFive", idData.at(4));
    rowId.insert("PacketSix", idData.at(5));
    rowId.insert("PacketSeven", idData.at(6));
    rowId.insert("PacketEight", idData.at(7));

    //filling in data row 'time_create' from all packages
    QVariantMap rowTimeCreate;
    rowTimeCreate.insert("id", 2);
    rowTimeCreate.insert("PacketOne", timeCreateData.at(0));
    rowTimeCreate.insert("PacketTwo", timeCreateData.at(1));
    rowTimeCreate.insert("PacketThree", timeCreateData.at(2));
    rowTimeCreate.insert("PacketFour", timeCreateData.at(3));
    rowTimeCreate.insert("PacketFive", timeCreateData.at(4));
    rowTimeCreate.insert("PacketSix", timeCreateData.at(5));
    rowTimeCreate.insert("PacketSeven", timeCreateData.at(6));
    rowTimeCreate.insert("PacketEight", timeCreateData.at(7));

    //filling in data row from third sensors from all packages
    QVariantMap rowDataSensorThree;
    rowDataSensorThree.insert("id", 3);
    rowDataSensorThree.insert("PacketOne", dataFromSensors.at(3));
    rowDataSensorThree.insert("PacketTwo", dataFromSensors.at(20));
    rowDataSensorThree.insert("PacketThree", dataFromSensors.at(37));
    rowDataSensorThree.insert("PacketFour", dataFromSensors.at(54));
    rowDataSensorThree.insert("PacketFive", dataFromSensors.at(71));
    rowDataSensorThree.insert("PacketSix", dataFromSensors.at(88));
    rowDataSensorThree.insert("PacketSeven", dataFromSensors.at(105));
    rowDataSensorThree.insert("PacketEight", dataFromSensors.at(122));

    QVariantMap rowDataSensorFour;
    rowDataSensorFour.insert("id", 4);
    rowDataSensorFour.insert("PacketOne", dataFromSensors.at(4));
    rowDataSensorFour.insert("PacketTwo", dataFromSensors.at(21));
    rowDataSensorFour.insert("PacketThree", dataFromSensors.at(38));
    rowDataSensorFour.insert("PacketFour", dataFromSensors.at(55));
    rowDataSensorFour.insert("PacketFive", dataFromSensors.at(72));
    rowDataSensorFour.insert("PacketSix", dataFromSensors.at(89));
    rowDataSensorFour.insert("PacketSeven", dataFromSensors.at(106));
    rowDataSensorFour.insert("PacketEight", dataFromSensors.at(123));

    QVariantMap rowDataSensorFive;
    rowDataSensorFive.insert("id", 5);
    rowDataSensorFive.insert("PacketOne", dataFromSensors.at(5));
    rowDataSensorFive.insert("PacketTwo", dataFromSensors.at(22));
    rowDataSensorFive.insert("PacketThree", dataFromSensors.at(39));
    rowDataSensorFive.insert("PacketFour", dataFromSensors.at(56));
    rowDataSensorFive.insert("PacketFive", dataFromSensors.at(73));
    rowDataSensorFive.insert("PacketSix", dataFromSensors.at(90));
    rowDataSensorFive.insert("PacketSeven", dataFromSensors.at(107));
    rowDataSensorFive.insert("PacketEight", dataFromSensors.at(124));

    QVariantMap rowDataSensorSix;
    rowDataSensorSix.insert("id", 6);
    rowDataSensorSix.insert("PacketOne", dataFromSensors.at(6));
    rowDataSensorSix.insert("PacketTwo", dataFromSensors.at(23));
    rowDataSensorSix.insert("PacketThree", dataFromSensors.at(40));
    rowDataSensorSix.insert("PacketFour", dataFromSensors.at(57));
    rowDataSensorSix.insert("PacketFive", dataFromSensors.at(74));
    rowDataSensorSix.insert("PacketSix", dataFromSensors.at(91));
    rowDataSensorSix.insert("PacketSeven", dataFromSensors.at(108));
    rowDataSensorSix.insert("PacketEight", dataFromSensors.at(125));

    QVariantMap rowDataSensorSeven;
    rowDataSensorSeven.insert("id", 7);
    rowDataSensorSeven.insert("PacketOne", dataFromSensors.at(7));
    rowDataSensorSeven.insert("PacketTwo", dataFromSensors.at(24));
    rowDataSensorSeven.insert("PacketThree", dataFromSensors.at(41));
    rowDataSensorSeven.insert("PacketFour", dataFromSensors.at(58));
    rowDataSensorSeven.insert("PacketFive", dataFromSensors.at(75));
    rowDataSensorSeven.insert("PacketSix", dataFromSensors.at(92));
    rowDataSensorSeven.insert("PacketSeven", dataFromSensors.at(109));
    rowDataSensorSeven.insert("PacketEight", dataFromSensors.at(126));

    QVariantMap rowDataSensorEight;
    rowDataSensorEight.insert("id", 8);
    rowDataSensorEight.insert("PacketOne", dataFromSensors.at(8));
    rowDataSensorEight.insert("PacketTwo", dataFromSensors.at(25));
    rowDataSensorEight.insert("PacketThree", dataFromSensors.at(42));
    rowDataSensorEight.insert("PacketFour", dataFromSensors.at(59));
    rowDataSensorEight.insert("PacketFive", dataFromSensors.at(76));
    rowDataSensorEight.insert("PacketSix", dataFromSensors.at(93));
    rowDataSensorEight.insert("PacketSeven", dataFromSensors.at(110));
    rowDataSensorEight.insert("PacketEight", dataFromSensors.at(127));

    //adding row to the model
    model->addRow(rowId);
    model->addRow(rowTimeCreate);
    model->addRow(rowDataSensorThree);
    model->addRow(rowDataSensorFour);
    model->addRow(rowDataSensorFive);
    model->addRow(rowDataSensorSix);
    model->addRow(rowDataSensorSeven);
    model->addRow(rowDataSensorEight);

    //adding a model to a widget
    ui->tableView->setModel(model);

}


