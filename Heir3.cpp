#include "Heir3.h"

Heir3::Heir3(Base *parent, string name) : Base(parent, name)
{
    class_number = 3;
}

void Heir3::signal(string &command)
{
    cout << "\nSignal from " << get_object_path();
    command += " (class: 3)";
}

//Метод обработчика
void Heir3::handler(string command)
{
    cout << "\nSignal to "<< get_object_path() <<" Text: "<<command;
}

