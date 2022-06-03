
#pragma once

#include "stdafx.h"
#include "Buffer.h"

class Consume;

class Consumer :
    public QWidget {
	Q_OBJECT

public:
	Consumer(QWidget* parent = nullptr);

	Consumer(int id, vector<Buffer*>* buffers, QWidget* parent = nullptr);

	int Id;
	string IdStr;
	QLabel* Label;
	vector<Buffer*>* Buffers;
	Consume* T;
private:
	QPicture* avatar;
};

class Consume : public QThread {
	Q_OBJECT

public:
	Consume(int id, vector<Buffer*>* buffers, QObject* parent = nullptr) :QThread(parent), Buffers(buffers), Id(id) {}
	void run();

	int Id;
	vector<Buffer*>* Buffers;
signals:
	void SetBuffer(int, int, Buffer*);
};