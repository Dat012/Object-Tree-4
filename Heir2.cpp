#include "Heir2.h"

Heir2::Heir2(Base *parent, string name) : Base(parent, name)
{
    class_number = 2;
}

void Heir2::signal(string &command)
{
    cout << "\nSignal from " << get_object_path();
    command += " (class: 2)";
}

//Метод обработчика
void Heir2::handler(string command)
{
    cout << "\nSignal to "<< get_object_path() <<" Text: "<<command;
}

