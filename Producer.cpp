
#include "Producer.h"
#include "ProducerConsumer.h"

Producer::Producer(QWidget* parent) : QWidget(parent) {}

Producer::Producer(int id, vector<Buffer*>* buffers, QWidget* parent)
	: QWidget(parent) {
	Id = id;
	IdStr = "Producer" + to_string(id);
	Buffers = buffers;
	auto temp = IdStr.c_str();
	Label = new QLabel(temp, this);
	Label->resize(WINDOWWIDTH / 3 - 10, WINDOWHEIGHT / MAXBUFFER - 10);
	Label->setAlignment(Qt::AlignCenter);
	Label->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0);");

	T = new Produce(Id, Buffers, this);
	
	connect(T, &Produce::SetBuffer, (ProducerConsumer*)(this->parent()), &ProducerConsumer::Produce);

	T->start();
}

void Produce::run() {
	random_device rd;
	while (true) {
		std::this_thread::sleep_for(chrono::milliseconds(rd() % 5000));
		std::this_thread::sleep_for(chrono::milliseconds(1000));
		WaitForSingleObject(produce, INFINITE);
		ReleaseSemaphore(produce, 1, NULL);
		WaitForSingleObject(bufferRemainMutex, INFINITE);
		WaitForSingleObject(bufferMutex, INFINITE);
		if (true) {
			for (int i = 0; i < MAXBUFFER; i++) {
				if ((*Buffers)[i]->full)
					continue;
				(*Buffers)[i]->full = true;

				emit SetBuffer(Id, i, (*Buffers)[i]);
				break;
			}
		}
		ReleaseSemaphore(productMutex, 1, NULL);
		ReleaseSemaphore(bufferMutex, 1, NULL);
	}
}

