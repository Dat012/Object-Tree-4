#include "Major.h"
#include "Base.h"
#include "Heir2.h"
#include "Heir3.h"
#include "Heir4.h"
#include "Heir5.h"
#include "Heir6.h"
#include <iostream>
#include <vector>
#include <string>



void Major::bild_tree_objects()  // Строим дерево объектов на основе введенных данных
{
	Base *cur_obj = this;  // Создаем основной объект, который равен this по умолчанию
	cur_obj->class_number = 1;  // Номер класса корневого объекта 1

	Base *cp = nullptr;  // Создаем объект наследник, который будет в векторе объекта выше
	string root_name;  // Имя корневого объекта
	string parent_path;  // Имя родителя по отношению к объекту, введенному ниже
	string heir_name;  // Имя наследника для родителя, введенного выше
	int cl_number;
	cin >> root_name;  // Вводим имя корневого объекта
	cur_obj->set_name(root_name);  // Имя текущего объекта теперь равно имени корневого объекта
	cur_obj->set_object_path("/");
	cin >> parent_path >> heir_name >> cl_number;  // На следующей строке вводим имя родительского объекта
	while (parent_path != "endtree")  // Цикл по вводу имен parent + heir
	{
        Base* fixed_object = this;
		if (parent_path != cur_obj->get_object_path())  // Если имя родителя не равно имени текущего объекта,
		{
			cur_obj = get_object(parent_path);  // то текущим объектом становится наследник, которого мы ввели после родителя
		}
		switch (cl_number)
		{
			case 2:
				cp = new Heir2(cur_obj, heir_name);  // Создаем объект наследника, родителем которого является текущий объект
				break;
			case 3:
				cp = new Heir3(cur_obj, heir_name);  // Создаем объект наследника, родителем которого является текущий объект
				break;
			case 4:
				cp = new Heir4(cur_obj, heir_name);  // Создаем объект наследника, родителем которого является текущий объект
				break;
			case 5:
				cp = new Heir5(cur_obj, heir_name);  // Создаем объект наследника, родителем которого является текущий объект
				break;
			case 6:
				cp = new Heir6(cur_obj, heir_name);  // Создаем объект наследника, родителем которого является текущий объект
		}
		cp->class_number = cl_number;
		cp->set_object_path(cp->get_parent()->get_object_path() + heir_name + "/");
		//cout << cp->get_name() << ": " << cp->get_object_root()->get_name() << endl;
		cin >> parent_path;
		if (parent_path == "endtree")
		{

            this->print_tree();

            string hendler;
            string signal;

            Base* hendler_ptr;
            Base* signal_ptr;

            cin >> hendler;
            while (true)
            {
                if (hendler == "end_of_connections") {
                    break;
                }
                cin >> signal;

                hendler_ptr = this->get_object(hendler);
                signal_ptr = this->get_object(signal);

                if (hendler_ptr == nullptr) {
                    cout << "\nObject " << hendler <<" not found";
                } else if (signal_ptr == nullptr) {
                    cout << "\nObject " << signal_ptr <<" not found";
                } else {
                    hendler_ptr->set_connect(get_signal(hendler_ptr), signal_ptr, get_handler(signal_ptr));
                }

                cin >> hendler;
            }

            string command;
            string handler_path;
            string signal_path;
            int state;
            string message;

            Base* hend;
            Base* sig;


			while (true)
			{
				cin >> command;

                if (command == "END")
                {
                    exit(0);
                }

                if (command == "EMIT")
                {
                    cin >> handler_path;
                    getline(cin,message);
                    hend = get_object(handler_path);
                    if (hend) {
                        hend->emit_signal(get_signal(hend), message);
                    } else {
                        cout << "\nObject " << handler_path << " not found";
                    }
                } else if (command == "SET_CONNECT")
                {
                    cin >> handler_path >> signal_path;
                    hend = get_object(handler_path);
                    sig = get_object(signal_path);
                    if (hend == nullptr) {
                        cout << "\nHandler object " << handler_path << " not found";
                    } else if (sig == nullptr) {
                        cout << "\nObject " << signal_path << " not found";
                    } else {
                        hend->set_connect(get_signal(hend), sig, get_handler(sig));
                    }
                } else if (command=="DELETE_CONNECT") {
                    cin >> handler_path >> signal_path;
                    hend = get_object(handler_path);
                    sig = get_object(signal_path);
                    if (hend == nullptr) {
                        cout << "\nHandler object " << handler_path << " not found";
                    } else if (sig == nullptr) {
                        cout << "\nObject " << signal_path << " not found";
                    } else {
                        hend->delete_connect(get_signal(hend), sig, get_handler(sig));
                    }
                } else if(command=="SET_CONDITION"){
                    cin >> handler_path >> state;
                    hend = get_object(handler_path);
                    if (hend) {
                        if (state == 0) {
                            hend->disable_all_under();
                        } else {
                            hend->set_readiness(state);
                        }
                    } else {
                        cout << "\nObject " << handler_path << " not found";
                    }
                }


                /*
                cout << endl;
                if (heir_path == "FIND" || heir_path == "SET") {
                    cout << "Object is not found\n";
                    cin >> heir_path;
                }
                if (command == "FIND") {
                    if (heir_path.substr(0, 2) == "//") {
                        found_object = this->get_object_root()->get_object(heir_path);
                    } else {
                        found_object = fixed_object->get_object(heir_path);
                    }
					if (found_object != nullptr)
					{
						cout << heir_path << "     Object name: " << found_object->get_name();
					}
                    else
                    {
                        cout << heir_path << "     Object is not found";
                    }
				}
                else if (command == "SET"){
                    if (heir_path.substr(0, 2) == "//") {
                        fixed_object = this->get_object_root()->get_object(heir_path);
                    } else {
                        fixed_object = fixed_object->get_object(heir_path);
                    }

                    if (fixed_object != nullptr)
                    {
                        cout << "Object is set: " << fixed_object->get_name();
                    }
                    else
                    {
                        cout << heir_path << "     Object is not found";
                    }

				}*/
				//Base* ready = cp->get_object_root()->get_object(heir_name);
				//int r;
				//cin >> r;
				//ready->set_readiness(r);
			}
			break;
		}
		/* if (parent_name == "endtree")
		{
			while (cin)
			{
				cin >> heir_name;
				if (heir_name == "q") {
					break;
				}
				Base* ready = cp->get_object_root()->get_object(heir_name);
				int r;
				cin >> r;
				ready->set_readiness(r);
			}
			break;
		} */
		cin >> heir_name >> cl_number;  // Далее опять вводим родителя и наследника
	}
}

Base::TYPE_SIGNAL Major::get_signal(Base *object){
    if(object->class_number==1)
        return SIGNAL_D(Major::signal);
    if(object->class_number==2)
        return SIGNAL_D(Heir2::signal);
    if(object->class_number==3)
        return SIGNAL_D(Heir3::signal);
    if(object->class_number==4)
        return SIGNAL_D(Heir4::signal);
    if(object->class_number==5)
        return SIGNAL_D(Heir5::signal);
    return SIGNAL_D(Heir6::signal);
}

Base::TYPE_HANDLER Major::get_handler(Base *object)
{
    if (object->class_number == 1)
        return HANDLER_D(Major::handler);
    if (object->class_number == 2)
        return HANDLER_D(Heir2::handler);
    if (object->class_number == 3)
        return HANDLER_D(Heir3::handler);
    if (object->class_number == 4)
        return HANDLER_D(Heir4::handler);
    if (object->class_number == 5)
        return HANDLER_D(Heir5::handler);

    return HANDLER_D(Heir6::handler);
}

void Major::signal(string &command){
    cout << "\nSignal from " << get_object_path();
    command+=" (class: 1)";
}

void Major::handler(string command){
    cout << "\nSignal to "<< get_object_path() << " Text: "<< command;
}

void Major::exec_app()  //  Метод запуска приложения
{
	//this->print_tree_old();  // Печатаем все дерево
	this->print_tree();
}