#include "Heir6.h"

Heir6::Heir6(Base *parent, string name) : Base(parent, name)
{
    class_number = 5;
}

void Heir6::signal(string &command)
{
    cout << "\nSignal from " << get_object_path();
    command += " (class: 6)";
}

//Метод обработчика
void Heir6::handler(string command)
{
    cout << "\nSignal to "<< get_object_path() <<" Text: "<<command;
}

