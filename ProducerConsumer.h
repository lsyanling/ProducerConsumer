#pragma once

#include "stdafx.h"
#include "ui_ProducerConsumer.h"

#include "Producer.h"
#include "Consumer.h"
#include "Buffer.h"

class ProducerConsumer : public QMainWindow {
	Q_OBJECT

public:
	ProducerConsumer(QWidget* parent = Q_NULLPTR);
	virtual void closeEvent(QCloseEvent* event);
	void InitializeProducerConsumer();

	vector<Producer*> producers;
	vector<Consumer*> consumers;
	vector<Buffer*> buffers;

	QGridLayout* mainLayout;
	QGridLayout* producerLayout;
	QGridLayout* consumerLayout;
	QGridLayout* bufferLayout;

	QPushButton* addProducerButton;
	QPushButton* addConsumerButton;
	QPushButton* deleteProducerButton;
	QPushButton* deleteConsumerButton;
	QPushButton* StartButton;

public slots:
	void AddProducer();
	void AddConsumer();
	void DeleteProducer();
	void DeleteConsumer();
	void Start();

	void Produce(int, int, Buffer*);
	void ProduceEnd(Producer*);
	void Consume(int, int, Buffer*);
	void ConsumeEnd(Consumer*);

private:
	Ui::ProducerConsumerClass ui;
};

class SetProduce : public QThread {
	Q_OBJECT

public:
	SetProduce(Producer* p, QObject* parent = nullptr) :QThread(parent), P(p) {}
	void run();

	Producer* P;
signals:
	void ProduceEnd(Producer*);
};

class SetConsume : public QThread {
	Q_OBJECT

public:
	SetConsume(Consumer* c, QObject* parent = nullptr) :QThread(parent), C(c) {}
	void run();

	Consumer* C;
signals:
	void ConsumeEnd(Consumer*);
};