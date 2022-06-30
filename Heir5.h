#ifndef HEIR5_H
#define HEIR5_H

#include <vector>
#include <string>
#include "Base.h"

class Heir5 : public Base
{
public:
    using Base::Base;

    Heir5(Base *parent, string name);
    void signal(string &command);
    void handler(string command);
};
#endif