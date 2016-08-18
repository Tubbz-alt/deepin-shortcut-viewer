#include "commandlinemanager.h"
#include <QFile>
#include <QRect>
#include <QDesktopWidget>
#include <QDebug>
CommandLineManager::CommandLineManager():
    m_posOption(QStringList()<<"p"<<"pos",
                 QCoreApplication::translate("main","Expose your  window's central position(x,y) info where the deepin-shorcut-viwer can be center int your window relativly,otherwise it will be center in the current screen. eg: -p=100,50 or --pos=900,50"),
                 " "),
    m_jsonDataOption(QStringList()<<"j"<<"json-data",
                     QCoreApplication::translate("main","Directly convert a json data to this program ,see https://github.com/tommego/deepin-shortcut-viewer  for more information of this decscription"),
                     " ")
{
    m_commandLineParser.setApplicationDescription("Test helper");
    m_commandLineParser.addHelpOption();
    m_commandLineParser.addVersionOption();
    m_commandLineParser.addOption(m_posOption);
    m_commandLineParser.addOption(m_jsonDataOption);
}
void CommandLineManager::process(QApplication &app){
    m_commandLineParser.process(app);
}

QString CommandLineManager::jsonData(){
    return m_commandLineParser.value(m_jsonDataOption);
}

QPoint CommandLineManager::pos(){
    QString posStr = m_commandLineParser.value(m_posOption);

    QStringList posStrs = posStr.split(",");

    QPoint pos(qApp->desktop()->width()/2,qApp->desktop()->height()/2);
    if(posStrs.length()==2){
        pos.setX(QString(posStrs[0]).toInt());
        pos.setY(QString(posStrs[1]).toInt());
    }
    return pos;
}
