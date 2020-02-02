#include <iostream>
#include <string>
#include <map>
#include <memory>
using namespace std;


struct Frame
{    
    using Parameters = map<string, string>;
    
    string name;
    Parameters parameters;
};

struct State_Data
{
        
};

enum class STATE_ACTION
{
    CURRENT,
    NEXT
};

class Abstract_State
{
    
    public:
    
        virtual bool Validate(Frame frame) = 0;
        virtual auto Process(Frame frame) 
            -> STATE_ACTION = 0;
    
};

class Ready_State : public Abstract_State
{};

class Init_State : public Abstract_State
{};

class Append_State : public Abstract_State
{};

class Payment_State : public Abstract_State
{};

class Finish_State : public Abstract_State
{};

class State_Manager
{
    
    private:
    
        shared_ptr<State_Data> state_data;
        unique_ptr<Abstract_State> state;
    
    public:
    
        void Process_New_Data(Frame frame)
        {
            // ..
        }
    
};

int main()
{
    
    return 0;
}
