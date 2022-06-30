#ifndef MAJOR_H
#define MAJOR_H

#include <vector>
#include <string>
#include <iostream>
#include "Base.h"

class Major : public Base
{
public:
	using Base::Base;

	void bild_tree_objects();

	void exec_app();

    void signal(string &command);
    void handler(string command);

    TYPE_SIGNAL get_signal(Base *object);
    TYPE_HANDLER get_handler(Base *object);
};

#endif