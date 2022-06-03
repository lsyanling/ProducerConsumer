
#include <QtWidgets>
#include <Qt>
#include <Windows.h>
#include <thread>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <mutex>
#include <random>

using namespace std;

extern HANDLE bufferMutex;
extern HANDLE bufferRemainMutex;
extern HANDLE productMutex;
extern HANDLE produce;

extern HANDLE bufferColor;

extern int MAXPRODUCER;
extern int MAXCONSUMER;
extern int MAXBUFFER;
extern int WINDOWWIDTH;
extern int WINDOWHEIGHT;

extern vector<mutex>* BuffersColor;