#include "Heir5.h"

Heir5::Heir5(Base *parent, string name) : Base(parent, name)
{
    class_number = 5;
}

void Heir5::signal(string &command)
{
    cout << "\nSignal from " << get_object_path();
    command += " (class: 5)";
}

//Метод обработчика
void Heir5::handler(string command)
{
    cout << "\nSignal to "<< get_object_path() <<" Text: "<<command;
}

