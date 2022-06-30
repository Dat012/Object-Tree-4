#include "Base.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

#define SIGNAL_D(  signal_f  ) ( ( void ( * ) ( string & ) ) ( & ( signal_f  ) ) )
#define HENDLER_D( hendler_f ) ( ( void ( * ) ( cl_base *, string & ) ) ( & ( hendler_f )

using namespace std;

Base::Base(Base *parent, string name)  // Конструктор для объектов иерархии
{
	this->parent = parent;  // Присваиваем родителя, переданного в аргументах
	this->name = name;  // Присваиваем имя, переданное в аргументах
	readiness = 1;
	if (parent != nullptr)  // Если родитель, создаваемого объекта не нулевой,
	{
		parent->heirs.push_back(this);  // то мы добавляем этот объект в вектор родителя
	}
}

void Base::set_connect(TYPE_SIGNAL signal, Base *object, TYPE_HANDLER handler)
{
    for (int i = 0; i < destinations.size(); i++)
    {
        if (destinations[i]->signal == signal && destinations[i]->object == object && destinations[i]->handler == handler)
            return;
    }
    connection *temp = new connection();
    temp->signal = signal;
    temp->object = object;
    temp->handler = handler;
    destinations.push_back(temp);

}

void Base::delete_connect(TYPE_SIGNAL signal, Base *object, TYPE_HANDLER handler)
{
    for (int i = 0; i < destinations.size(); i++)
    {
        if (destinations[i]->signal == signal && destinations[i]->object == object && destinations[i]->handler == handler)
        {
            destinations.erase(destinations.begin()+i);
            break;
        }
    }
}

void Base::emit_signal(TYPE_SIGNAL signal, string &command)
{

    if (destinations.size() == 0)
        return;
    if (readiness == 0)
        return;
    (this->*signal)(command);

    for (int i = 0; i < destinations.size(); i++)
    {
        if (destinations[i]->signal == signal && destinations[i]->object -> readiness != 0)
            (destinations[i]->object->*(destinations[i]->handler))(command);
    }
}


void Base::set_name(string name)  // Присваиваем имя объекту
{
	this->name = name;
}

string Base::get_name()  // Получаем имя объекта
{
	return name;
}

int Base::get_readiness() const
{
	return readiness;
}

Base *Base::get_object_root()
{
	if (parent == nullptr) {
		return this;
	}
	Base* parent_previous = parent;

	while (parent_previous->parent != nullptr) {
		parent_previous = parent_previous->parent;
	}
	return parent_previous;
}

Base *Base::get_object(string path)
{
	string name;
	if (path.substr(0, 2) == "//") {  // 1. Если путь задан в формате //ob_1
		name = path.substr(2);
        if (this->get_name() == name)  // Если имя объекта, который вызвал этот метод равно аргументу
        {
            return this;
        }
        for (int i = 0; i < heirs.size(); i++)
        {
            if (heirs[i] -> get_name() == name)
            {
                return heirs[i];
            }
        }

        for (int j = 0; j < heirs.size(); j++)
        {
            if (!heirs[j] -> heirs.empty())
            {
                Base* res = heirs[j]->get_object(path);
                if (res != nullptr)
                {
                    return res;
                }
            }
        }
        return nullptr;
	} else if (path[0] == '/' && path.length() > 1) {  // 2. Если путь задан в формате /ob_1/ob_2/ob_4
		name = path.substr(path.find("/") + 1, path.find("/", path.find("/") + 1) - 1);  // Получение имени объекта после /
        for (int i = 0; i < this->heirs.size(); ++i) {
            if (heirs[i]->get_name() == name)
            {
                if (path.find("/", path.find("/") + 1) == string::npos) {
                    return heirs[i];
                }
                path = path.substr(path.find("/", path.find("/") + 1));
                Base* res = heirs[i]->get_object(path);
                return res;
            }
        }
        return nullptr;
	} else if (path == ".") {  // 3. Если путь задан в формате .
		return this;
	} else if (path[0] == '/' && path.length() == 1) {  // 4. Если путь задан в формате /
		return this->get_object_root();
	} else {  // 5. Если путь задан в формате ob_1/ob_2/ob_3
		path.insert(0, "/");
        Base* res2 = this->get_object(path);
        return res2;
	}
}

void Base::set_object_path(const string &objectPath)
{
	object_path = objectPath;
}

const string &Base::get_object_path() const
{
	return object_path;
}

/* void Base::print_tree_old()  // Печатаем весь вектор объекта, который вызвал этот метод
{
	if (this->parent == nullptr)
	{  // Если у объекта нет parent, то печатаем его в соответствии с условием задачи
		cout << this->get_name() << "\n";
		cout << this->get_name() << "  ";
	}
	for (int i = 0; i < heirs.size() - 1; i++)  // Выводим весь вектор объекта до последнего объекта невключительно
	{
		cout << heirs[i]->get_name() << "  ";  // С двумя пробелами
	}
	cout << heirs[heirs.size() - 1]->get_name();  // Последний объект выводим без пробела

	for (int j = 0; j < heirs.size(); j++)
	{
		if (!heirs[j]->heirs.empty())  // Если вектор parent не пустой
		{
			cout << "\n" << heirs[j]->get_name() << "  ";
			heirs[j]->print_tree_old();  // , то печатаем наследников
		}
	}
} */

void Base::print_tree()
{
	cout << "Object tree\n";
	print_objects(0);
}

void Base::print_objects(int level)
{
	string space;
	if (level > 0) {
		space.append(4 * level, ' ');
	}
	cout << space << get_name();

	level++;
	if (heirs.empty()) {
		return;
	}
	for (int i = 0; i < heirs.size(); ++i)
	{
		cout << endl;
		heirs[i]->print_objects(level);
	}
	level--;
}

void Base::disable_all_under()
{
    this->readiness = 0;
    for (int i = 0; i < heirs.size(); ++i)
    {
        heirs[i]->disable_all_under();
    }
}

int Base::set_readiness(int readiness2)
{
	this->readiness = what_readiness(readiness2);
    if (readiness == 0) {
        for (int i = 0; i < this->heirs.size(); ++i)
        {
            if (!heirs[i]->heirs.empty()) {
                heirs[i]->set_readiness(0);
            }
        }
    }
}

int Base::what_readiness(int readiness2) {
	if (parent == nullptr) {
		return readiness2;
	} else if (parent->readiness == 0 || readiness2 == 0) {
		return 0;
	} else {
		readiness2 = parent->what_readiness(readiness2);
		return readiness2;
	}
}

void Base::set_parent(Base *parent)  // Устанавливаем parent для текущего объекта
{
	if (this->parent !=
		nullptr)  // Если у объекта уже есть родитель, то мы удаляем текущий объект из списка наследников этого родителя
	{
		this->parent->heirs.erase(find(this->parent->heirs.begin(), this->parent->heirs.end(), this));
	}
	this->parent = parent;  // Присваиваем родителя объекту
	parent->heirs.push_back(this);  // Добавляем в вектор этого родителя текущий объект
}

/*void Base::set_parent(Base *parent)
{
	if (parent)
	{
		this->parent=parent;
		parent->heirs.push_back(this);
	}
}*/

Base *Base::get_parent()  // Возвращаем родителя текущего объекта
{
	return parent;
}
