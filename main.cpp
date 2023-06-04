#include "Controls/kernel.h"
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QDir>
#include <QStandardPaths>
#include <QFileDialog>
#include <QSettings>
#include "mainwindow.h"
#include "Common/fileutil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kernel kernel;
//    MainWindow window(nullptr, 0);
//    window.show();
//    // 创建一个QSettings对象，指定INI格式和配置文件路径
//    QSettings settings("./config.ini", QSettings::IniFormat);

//    // 从配置文件中读取数据
//    QString avatarPath = settings.value("test.jpg/filePath").toString();
//    QString md5 = settings.value("test.jpg/MD5").toString();
//    qDebug() << avatarPath << "  " << md5;
//    // 检查某个键是否存在
////    bool exists = settings.contains("user2/avatarPath");
////    qDebug() << exists;
//    // 删除某个键及其对应的值
//    // settings.remove("user1/avatarPath");

    return a.exec();
}

