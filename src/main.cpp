#include <iostream>
#include <string>
#include <map>
#include <algorithm>
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

    PyObject *GetObjectBySymbol(const string &symbol) {
        PyObject *value = nullptr;
        PyDictObject *env = (PyDictObject*) local_env_;

        for (auto &item : env->dict) {
            auto key = item.first;
            auto keyStr = (PyStringObject*) key;
            if (keyStr->value == symbol) {
                value = PyObject_GetItem(local_env_, key);
                break;
            }
        }

        if (value == nullptr) {
            cout << "[Error] : " << symbol << " is not defined!!!" << endl;
        }

        return value;
    }

    void ExecutePrint(string symbol) {
        symbol = RemoveSpaces(symbol);
        PyObject *object = GetObjectBySymbol(symbol);
        if (object != nullptr) {
            PyObject_Print(object);
        }
    }

    bool IsAllDigit(string& str) {
        int len = str.size();
        int i = 0;
        while (i < len && str[i] == ' ') i++;
        while (len > 0 && str[len - 1] == ' ') len --;
        for (; i < len; i++) {
            if (!std::isdigit(str[i])) return false;
        }

        return true;
    }

    void ExecuteAdd(string &target, string &source) {
        string::size_type pos;
        PyObject* strValue = nullptr;
        PyObject* resultValue = nullptr;
        if (IsAllDigit(source)) {

            PyObject *intValue = PyInt_Create(std::stol(source));
            PyObject *key = PyStr_Create(target.c_str());
            PyObject_SetItem(local_env_, key, intValue);
            result_ = intValue;
        } else if (source.find("\"") != string::npos) {

            strValue = PyStr_Create(source.substr(1, source.size() - 2).c_str());
            PyObject *key = PyStr_Create(target.c_str());
            PyObject_SetItem(local_env_, key, strValue);
            result_ = strValue;
        } else if ((pos = source.find("+")) != string::npos) {
            PyObject* leftObject = GetObjectBySymbol(source.substr(0, pos));
            PyObject* rightObject = GetObjectBySymbol(source.substr(pos + 1));

            if (leftObject != nullptr && rightObject != nullptr && Py_TYPE(leftObject) == Py_TYPE(rightObject)) {
                resultValue = (Py_TYPE(leftObject)->tp_as_number->nb_add(leftObject, rightObject));
                PyObject *key = PyStr_Create(target.c_str());
                PyObject_SetItem(local_env_, key, resultValue);
            }

            result_ = resultValue;
            // PyObject_Print(local_env_);
        }

    }

    string RemoveSpaces(string& s) {
        auto iter = std::remove(s.begin(), s.end(), ' ');
        s.erase(iter, s.end());
        return s;
    }

    void ExecueCommand(string & command) {
        string::size_type pos = 0;
        if ((pos = command.find("print")) != string::npos) {

            string::size_type start_pos = command.find("(");
            string::size_type end_pos = command.find(")");
            if (start_pos != string::npos && end_pos != string::npos) {
                ExecutePrint(command.substr(start_pos + 1, end_pos - start_pos - 1));
            }
        } else if ((pos = command.find("=")) != string::npos) {

            string target = command.substr(0, pos);
            string source = command.substr(pos + 1);
            ExecuteAdd(target, source);
            PyObject_Print(result_);
        }
    }


    void Execute() {
        cout << info << endl;
        cout << prompt;
        while (getline(cin, command_)) {
            command_ = RemoveSpaces(command_);
            if (command_.size() == 0) {
                cout << prompt;
                continue;
            } else if (command_ == "exit") {
                return;
            } else {
                ExecueCommand(command_);
                cout << prompt;
            }
        }
    }

private:
    string command_;
    PyObject* result_;
    PyObject* local_env_;
};


int main() {
    PythonExecute exec;
    exec.Execute();

    return 0;
}