#include "osgwindow.h"

#include <osgDB/ReadFile>
#include <osg/Group>
#include <osg/Node>
#include <osg/Camera>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>

#include "GraphicsWindowQt.h"	// 这个是本地自己建的。所以用双引号


OSGWindow::OSGWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	_timer = new QTimer;
	viewer = new osgViewer::Viewer;


	initOSG();
}

OSGWindow::~OSGWindow()
{
	delete _timer;
	delete viewer;
}


void OSGWindow::initOSG()
{
	// 设置模型
	osg::ref_ptr<osg::Group> root = new osg::Group;
	// 显示cow.osg 模型
	//root->addChild(osgDB::readNodeFile("cow.osg"));
	// 显示 .earth 文件中的地球模型
	root->addChild(osgDB::readNodeFile("D:/Project/OSG_project/OSGEarth_project/earthfile/china-simple.earth"));


	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;//声明是否显示窗口的描述
	traits->x = 50;
	traits->y = 50;
	traits->width = 800;
	traits->height = 600;
	traits->doubleBuffer = true;//创建图形窗口是否使用双缓存


	////设置照相机
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, 800, 600));
	camera->setProjectionMatrixAsPerspective(30.0f, 800.0f/600.0f, 1.0f, 10000.0f);


	//设置渲染器
	viewer->setCamera(camera);
	viewer->setSceneData(root);	
	viewer->setCameraManipulator(new osgGA::TrackballManipulator);
	viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//创建为单线程
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->addEventHandler(new osgViewer::StatsHandler);


	osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());

	ui.horizontalLayoutOSG->addWidget((QWidget*)(gw->getGLWidget()));

	_timer = new QTimer;
	QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
	_timer->start(5);	// 每5ms触发一次帧的刷新

}


void OSGWindow::updateFrame()
{
	viewer->frame();
}

