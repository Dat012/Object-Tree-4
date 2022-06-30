#ifndef HEIR6_H
#define HEIR6_H

#include <vector>
#include <string>
#include "Base.h"

class Heir6 : public Base
{
public:
    using Base::Base;

    Heir6(Base *parent, string name);
    void signal(string &command);
    void handler(string command);
};
#endif