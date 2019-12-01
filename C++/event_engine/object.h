#ifndef OBJECT_H
#define OBJECT_H

#include <list>
using namespace std;


class Object
{

    public:

        Object();

    private:

        list<int> signals;

    private:

        void Signal_Done(int signal);

    public:

        virtual void Signal(int type);
        virtual void Slots(int slot);
        static void Connect(
            Object* sender, int signal,
            Object* receiver, int slot);

    friend class Engine;

};


#endif //OBJECT_H
