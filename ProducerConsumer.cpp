
#include "ProducerConsumer.h"
#include "stdafx.h"

ProducerConsumer::ProducerConsumer(QWidget* parent)
	: QMainWindow(parent) {
	ui.setupUi(this);

	InitializeProducerConsumer();
}

void ProducerConsumer::closeEvent(QCloseEvent* event) {
	for (auto& i:producers) {
		i->T->terminate();
	}
	for (auto& i : consumers) {
		i->T->terminate();
	}
	QWidget::closeEvent(event);
}

void ProducerConsumer::InitializeProducerConsumer() {
	resize(WINDOWWIDTH, WINDOWHEIGHT);

	mainLayout = new QGridLayout(ui.centralWidget);
	producerLayout = new QGridLayout(ui.centralWidget);
	consumerLayout = new QGridLayout(ui.centralWidget);
	bufferLayout = new QGridLayout(ui.centralWidget);

	addProducerButton = new QPushButton("增加生产者", this);
	addConsumerButton = new QPushButton("增加消费者", this);
	deleteProducerButton = new QPushButton("减少生产者", this);
	deleteConsumerButton = new QPushButton("减少消费者", this);
	StartButton = new QPushButton("开始生产", this);

	producerLayout->addWidget(addProducerButton, 0, 0);
	producerLayout->addWidget(deleteProducerButton, 0, 1);

	consumerLayout->addWidget(addConsumerButton, 0, 0);
	consumerLayout->addWidget(deleteConsumerButton, 0, 1);

	bufferLayout->addWidget(StartButton, 0, 0, 1, 2);

	mainLayout->addLayout(producerLayout, 0, 0);
	mainLayout->addLayout(bufferLayout, 0, 1);
	mainLayout->addLayout(consumerLayout, 0, 2);

	connect(addProducerButton, &QPushButton::clicked, this, &ProducerConsumer::AddProducer);
	connect(deleteProducerButton, &QPushButton::clicked, this, &ProducerConsumer::DeleteProducer);

	connect(addConsumerButton, &QPushButton::clicked, this, &ProducerConsumer::AddConsumer);
	connect(deleteConsumerButton, &QPushButton::clicked, this, &ProducerConsumer::DeleteConsumer);

	connect(StartButton, &QPushButton::clicked, this, &ProducerConsumer::Start);

	auto p = new Producer(0, &buffers, this);
	producers.push_back(p);
	producerLayout->addWidget(p, 1, 0, 1, 2);

	auto c = new Consumer(0, &buffers, this);
	consumers.push_back(c);
	consumerLayout->addWidget(c, 1, 0, 1, 2);

	for (int i = 0; i < MAXBUFFER; i++) {
		auto b = new Buffer(i, this);
		buffers.push_back(b);
		bufferLayout->addWidget(b, i + 1, 0, 1, 2);
	}
}

void ProducerConsumer::AddProducer() {
	int size = producers.size();
	if (size < MAXPRODUCER) {
		auto temp = new Producer(size, &buffers, this);
		producers.push_back(temp);
		producerLayout->addWidget(temp, size + 1, 0, 1, 2);
	}
}

void ProducerConsumer::DeleteProducer() {
	int size = producers.size();
	if (size > 1) {
		producers[size - 1]->T->terminate();
		delete producers[size - 1];
		producers.pop_back();
	}
}

void ProducerConsumer::AddConsumer() {
	int size = consumers.size();
	if (size < MAXCONSUMER) {
		auto temp = new Consumer(size, &buffers, this);
		consumers.push_back(temp);
		consumerLayout->addWidget(temp, size + 1, 0, 1, 2);
	}
}

void ProducerConsumer::DeleteConsumer() {
	int size = consumers.size();
	if (size > 1) {
		consumers[size - 1]->T->terminate();
		delete consumers[size - 1];
		consumers.pop_back();
	}
}

void ProducerConsumer::Start() {
	if (StartButton->text()=="开始生产") {
		StartButton->setText("停止生产");

		deleteProducerButton->setEnabled(false);
		deleteConsumerButton->setEnabled(false);

		ReleaseSemaphore(produce, 1, NULL);	
	}
	else {
		StartButton->setText("开始生产");

		deleteProducerButton->setEnabled(true);
		deleteConsumerButton->setEnabled(true);

		WaitForSingleObject(produce, INFINITE);
	}
}

void ProducerConsumer::Produce(int Id, int i, Buffer* buffer) {
	producers[Id]->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0); background-color: rgb(255, 197, 181);");
	buffer->Label->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0); background-color: rgb(100, 149, 237);");

	SetProduce* T = new SetProduce(producers[Id]);
	connect(T, &SetProduce::ProduceEnd, this, &ProducerConsumer::ProduceEnd);
	T->start();
}

void ProducerConsumer::ProduceEnd(Producer* P) {
	P->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0); background-color: rgb(240, 240, 240);");
}

void ProducerConsumer::Consume(int Id, int i, Buffer* buffer) {
	consumers[Id]->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0); background-color: rgb(255, 197, 181);");
	buffer->Label->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0); background-color: rgb(240, 240, 240);");

	SetConsume* T = new SetConsume(consumers[Id]);
	connect(T, &SetConsume::ConsumeEnd, this, &ProducerConsumer::ConsumeEnd);
	T->start();
}

void ProducerConsumer::ConsumeEnd(Consumer* C) {
	C->setStyleSheet("border-width: 2px; border-style: solid; border-color: rgb(255, 170, 0); background-color: rgb(240, 240, 240);");
}

void SetProduce::run() {
	WaitForSingleObject(bufferColor, INFINITE);
	std::this_thread::sleep_for(chrono::milliseconds(300));
	emit ProduceEnd(P);
}

void SetConsume::run() {
	WaitForSingleObject(bufferColor, INFINITE);
	std::this_thread::sleep_for(chrono::milliseconds(300));
	emit ConsumeEnd(C);
}
