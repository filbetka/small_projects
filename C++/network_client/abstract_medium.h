#ifndef ABSTRACT_MEDIUM_H
#define ABSTRACT_MEDIUM_H

#include <string>
using namespace std;


class Abstract_Medium
{

    public:

        Abstract_Medium();

    protected:

        // status
        bool is_connected;
        bool is_open;

    public:

        // connection
        virtual bool Connection_Open() = 0;
        virtual void Connection_Close() = 0;

    public:

        // read and write
        virtual void Write(string data) = 0;
        virtual string Read() = 0;

        // get status
        bool Is_Open();
        bool Is_Connected();

};


#endif //ABSTRACT_MEDIUM_H
