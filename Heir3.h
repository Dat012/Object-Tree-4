#ifndef HEIR3_H
#define HEIR3_H

#include <vector>
#include <string>
#include "Base.h"

class Heir3 : public Base
{
public:
	using Base::Base;

    Heir3(Base *parent, string name);
    void signal(string &command);
    void handler(string command);
};

#endif