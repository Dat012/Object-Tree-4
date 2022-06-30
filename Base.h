#ifndef BASE_H
#define BASE_H
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(& signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(& handler_f)

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Base {

public:
    typedef void(Base:: *TYPE_SIGNAL)(string &);
    typedef void(Base:: *TYPE_HANDLER)(string);

    struct connection {//объявление структуры связи
        TYPE_SIGNAL signal;//сигнал объекта
        Base * object;//целевой объект
        TYPE_HANDLER handler;//обработчик объекта
    };

    string message;

    vector<connection*> destinations;

	int readiness; //поле готовности

	int class_number; //номер класса

    Base(Base *parent = nullptr, string name = "");

    void set_connect(TYPE_SIGNAL signal, Base* object, TYPE_HANDLER handler);

    void delete_connect(TYPE_SIGNAL signal, Base *object, TYPE_HANDLER handler);

    void emit_signal(TYPE_SIGNAL signal, string& command);

    void disable_all_under();

	Base* get_object_root();

	Base* get_object(string obj_name);

	void set_name(string name);

	string get_name();

    //void print_tree_old();

	void print_tree();

	void print_objects(int level);

	void set_parent(Base *parent);

	Base *get_parent();

	Base *get_object();

	int get_readiness() const;

	int set_readiness(int readiness);

	int what_readiness(int readiness);

	void set_object_path(const string &objectPath);

	const string &get_object_path() const;

private:
    string name;
    string object_path;
    Base *parent;
    vector<Base*> heirs;

    TYPE_SIGNAL signal;
    TYPE_HANDLER handler;

};



#endif