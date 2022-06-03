#pragma once

#include "stdafx.h"

class Buffer :
    public QWidget {
    Q_OBJECT

public:
    Buffer(QWidget* parent = nullptr);

    Buffer(int id, QWidget* parent = nullptr);

    int Id;
    bool full = false;
    string IdStr;
    QLabel* Label;
};

