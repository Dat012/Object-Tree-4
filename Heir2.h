#ifndef HEIR2_H
#define HEIR2_H

#include <vector>
#include <string>
#include "Base.h"

class Heir2 : public Base
{
public:
	using Base::Base;

    Heir2(Base *parent, string name);
    void signal(string &command);
    void handler(string command);
};

#endif