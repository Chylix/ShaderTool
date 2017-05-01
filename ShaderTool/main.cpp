#include "ShaderToolMain.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CShaderToolMain w;
	w.show();
	return a.exec();
}
