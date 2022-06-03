
#include "Consumer.h"
#include "ProducerConsumer.h"

Consumer::Consumer(QWidget* parent) : QWidget(parent) {}

Consumer::Consumer(int id, vector<Buffer*>* buffers, QWidget* parent) : QWidget(parent) {
	Id = id;
	IdStr = "Consumer" + to_string(id);
	Buffers = buffers;
	auto temp = IdStr.c_str();
	Label = new QLabel(temp, this);
	Label->resize(WINDOWWIDTH / 3 - 10, WINDOWHEIGHT / MAXBUFFER - 10);
	Label->setAlignment(Qt::AlignCenter);
	Label->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0);");

	T = new Consume(Id, Buffers, this);

	connect(T, &Consume::SetBuffer, (ProducerConsumer*)(this->parent()), &ProducerConsumer::Consume);

	T->start();
}

void Consume::run() {
	random_device rd;
	while (true) {
		std::this_thread::sleep_for(chrono::milliseconds(rd() % 5000));
		std::this_thread::sleep_for(chrono::milliseconds(1000));
		WaitForSingleObject(productMutex, INFINITE);
		WaitForSingleObject(bufferMutex, INFINITE);
		if (true) {
			for (int i = MAXBUFFER - 1; i >= 0; i--) {
				if ((*Buffers)[i]->full) {
					(*Buffers)[i]->full = false;

					emit SetBuffer(Id, i, (*Buffers)[i]);
					break;
				}
			}
		}
		ReleaseSemaphore(bufferRemainMutex, 1, NULL);
		ReleaseSemaphore(bufferMutex, 1, NULL);
	}
}

