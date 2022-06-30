#include "Heir4.h"

Heir4::Heir4(Base *parent, string name) : Base(parent, name)
{
    class_number = 4;
}

void Heir4::signal(string &command)
{
    cout << "\nSignal from " << get_object_path();
    command += " (class: 4)";
}

//Метод обработчика
void Heir4::handler(string command)
{
    cout << "\nSignal to "<< get_object_path() <<" Text: "<<command;
}

