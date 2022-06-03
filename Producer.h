#pragma once

#include "stdafx.h"
#include "Buffer.h"

class Produce;

class Producer :
	public QWidget {
	Q_OBJECT

public:
	Producer(QWidget* parent = nullptr);

	Producer(int id, vector<Buffer*>* buffers, QWidget* parent = nullptr);

	int Id;
	string IdStr;
	QLabel* Label;
	vector<Buffer*>* Buffers;
	Produce* T;
private:
	QPicture* avatar;
};

class Produce : public QThread {
	Q_OBJECT

public:
	Produce(int id, vector<Buffer*>* buffers, QObject* parent = nullptr) :QThread(parent),Buffers(buffers),Id(id) {}
	void run();

	int Id;
	vector<Buffer*>* Buffers;
signals:
	void SetBuffer(int, int, Buffer*);
};