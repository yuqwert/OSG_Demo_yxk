#ifndef OSGWINDOW_H
#define OSGWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_osgwindow.h"

#include <QTimer>
#include <osgViewer/Viewer>

class OSGWindow : public QMainWindow
{
	Q_OBJECT

public:
	OSGWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OSGWindow();

private:
	Ui::OSGWindowClass ui;


private:
	QTimer* _timer;		// 计时器，每25ms触发一次事件
	osgViewer::Viewer* viewer;


	// 初始化设置osg
	void initOSG();

private slots:
	// 定时更新帧的槽函数
	void updateFrame();	

};

#endif // OSGWINDOW_H
