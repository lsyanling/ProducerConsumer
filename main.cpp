
#include "ProducerConsumer.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

HANDLE bufferMutex;
HANDLE bufferRemainMutex;
HANDLE productMutex;
HANDLE produce;

HANDLE bufferColor;

int MAXPRODUCER;
int MAXCONSUMER;
int MAXBUFFER;
int WINDOWWIDTH;
int WINDOWHEIGHT;

vector<mutex>* BuffersColor;

void InitializeMain() {
    MAXPRODUCER = 15;
    MAXCONSUMER = 15;
    MAXBUFFER = 15;
    WINDOWWIDTH = 600;
    WINDOWHEIGHT = 600;

    bufferMutex = CreateSemaphore(NULL, 1, 1, NULL);
    bufferRemainMutex = CreateSemaphore(NULL, MAXBUFFER, MAXBUFFER, NULL);
    productMutex = CreateSemaphore(NULL, 0, MAXBUFFER, NULL);
    produce = CreateSemaphore(NULL, 0, 1, NULL);

    bufferColor = CreateSemaphore(NULL, MAXBUFFER, 1, NULL);

    BuffersColor = new vector<mutex>(MAXBUFFER);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitializeMain();

    ProducerConsumer w;
    w.show();
    return a.exec();
}
