
#include "Buffer.h"

Buffer::Buffer(QWidget* parent) :QWidget(parent) {}

Buffer::Buffer(int id, QWidget* parent) {
	Id = id;
	IdStr = "Buffer" + to_string(id);
	auto temp = IdStr.c_str();
	Label = new QLabel(temp, this);
	Label->resize(WINDOWWIDTH / 3 - 10, WINDOWHEIGHT / MAXBUFFER - 10);
	Label->setAlignment(Qt::AlignCenter);
	Label->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0);");
	"background-color: rgb(100, 150, 230);";
}
