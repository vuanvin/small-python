#include <iostream>
#include <string>
#include "Python.h"

const char info[] = "************ Python Research ************";
const char prompt[] = ">>> ";

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;

class PythonExecute {
public:
    PythonExecute() {
        this->local_env_ = PyDict_Create();
    }

    PyObject *GetObjectBySymbol(string &symbol) {
        PyObject *key = PyStr_Create(symbol.c_str());
        PyObject *value = PyObject_GetItem(local_env_, key);
        if (value == nullptr) {
            cout << "[Error] : " << symbol << "is not defined!!!" << endl;
        }
        return value;
    }

    void ExecutePrint(string symbol) {
        PyObject *object = GetObjectBySymbol(symbol);
        if (object != nullptr) {
            PyObject_Print(object);
        }
    }

    void ExecuteAdd(string &target, string &source) {
        string::size_type pos;
        PyObject* strValue = nullptr;
        PyObject* resultValue = nullptr;
        if (IsSourceAllDigit(source)) {
            PyObject *intValue = PyInt_Create(std::atol(source));
            PyObject *key = PyStr_Create(target.c_str);
        } else if (source.find("\"") != string::npos) {
            strValue = PyStr_Create(source.substr(1, source.size() - 2).c_str());
            PyObject *key = PyStr_Create(target.c_str());
        }

    }

    void ExecueCommand(string & command) {
        string::size_type pos = 0;
        if ((pos = command.find("print")) != string::npos) {
            ExecutePrint(command.substr(6));
        } else if ((pos = command.find(" = ")) != string::npos) {
            string target = command.substr(0, pos);
            string source = command.substr(pos + 3);
            ExecuteAdd(target, source);
        }
    }


    void Execute() {

        cout << info << endl;
        cout << prompt;
        while (getline(cin, command)) {
            if (command.size() == 0) {
                cout << prompt;
                continue;
            } else if (command == "exit") {
                return;
            } else {
                ExecueCommand(command);
            }
        }
    }

private:
    string command_;
    PyObject* local_env_;
}


int main() {
    Execute();
}