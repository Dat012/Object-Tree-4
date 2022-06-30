#ifndef HEIR4_H
#define HEIR4_H

#include <vector>
#include <string>
#include "Base.h"

class Heir4 : public Base
{
public:
    using Base::Base;

    Heir4(Base *parent, string name);
    void signal(string &command);
    void handler(string command);
};
#endif