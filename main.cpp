#include <iostream>
#include <vector>

#include "operation.h"
#include "genericoperation.h"

int add(int val1, int val2);
int sub(int val1, int val2);
int mul(int val1, int val2);
int division(int val1, int val2);

/**
 * @brief parseInputLine Parse the given line into the four other sub string, return false if error while parsing
 * @param line input line to be read
 * @param user output for the user field
 * @param cmd output for the command field
 * @param val1 output for the first value string
 * @param val2 output for the second value string
 * @return return true if everything is read correctly, false otherwise
 */
bool parseInputLine(const std::string &line, std::string &user, std::string &cmd, std::string &val1, std::string &val2);

/**
 * @brief help print a description of what this program do and the command available
 * @param ops array of the command available
 */
void help(std::vector<Operation*> ops);


/**
 * @brief main run a basic calculator in a terminal, perform operation on integer, whithout overflow check.
 * @return
 */
int main()
{

    /** Fill the list of operation that the application handle **/
    std::vector<Operation*> ops;

    GenericOperation<add> addition("Perform the addition of the two given numbers", "SUM", "+");
    ops.push_back(&addition);
    GenericOperation<sub> substraction("Perform the substraction of the two given numbers", "SUBTRACT", "-");
    ops.push_back(&substraction);
    GenericOperation<mul> multiplication("Perform the addition of the two given numbers", "MULTIPLY", "*");
    ops.push_back(&multiplication);
    GenericOperation<division> divide("Perform the interger division of the first number by the second", "DIVIDE", "/");
    ops.push_back(&divide);
    // Any new operation can be added by simply adding a subclass of Operation to the ops vector.

    // Print a help / welcome message
    help(ops);

    while(true)
    {
        // Print prompt and read line
        std::cout << ">>> ";
        std::string line;
        std::getline(std::cin, line);

        if(line.compare("EXIT") == 0){
            break;
        }

        // Parse input line into strings
        std:: string user, cmd, val1, val2;
        if(!parseInputLine(line, user, cmd, val1, val2)){
            std::cout << "Unexpected input format" << std::endl;
            std::cout << "Input should be: \"User;operation;val1;val2\" with val1 and val2 integer values or \"EXIT\" to quit" << std::endl;
            continue;
        }

        // Convert string into integer values
        // TODO: handle none int value? long, double..?
        int v1, v2;
        try {
            v1 = stoi(val1);
            v2 = stoi(val2);
        } catch (const std::invalid_argument& ia) {
            std::cerr << "The provided values cannot be converted to integer: " << ia.what() << std::endl;
            continue;
        } catch (const std::out_of_range& oof) {
            std::cerr << "The provided values is out of range of this machine integer value: " << oof.what() << std::endl;
            continue;
        }

        // Process the operation requested by the user by finding the operation corresponding to cmd in ops array
        bool operationProcessed = false;
        for(Operation* & op : ops){
            if(op->get_command().compare(cmd) == 0){
                // if the command are the same, compute the value and display the result
                operationProcessed = true;
                int r;
                try {
                    r = op->compute(v1, v2);
                } catch (std::runtime_error & e) {
                    std::cout << e.what() << std::endl;
                    break;
                }
                std::cout << user << " - " << op->get_command() << " - " << v1 << op->get_operator() << v2 << "=" << r << std::endl;
                // TODO: define a method for Operation to print itself? (overkill for this task)
                break;
            }
        }
        if(!operationProcessed){
            std::cerr << "Unknow operation: \"" << cmd << "\"" << std::endl;
            continue;
        }
    }
    return 0;
}

int add(int val1, int val2)
{
    return val1 + val2;
}

int sub(int val1, int val2)
{
    return val1 - val2;
}

int mul(int val1, int val2)
{
    return val1 * val2;
}

int division(int val1, int val2)
{
    if (val2 == 0) {
        throw std::runtime_error("Math error: divide by Zero");
    }
    return val1 / val2;
}

bool parseInputLine(const std::string &line, std::string &user, std::string &cmd, std::string &val1, std::string &val2)
{
    int i = 0;
    for(const char & c : line)
    {
        if(c == ';'){
            i++;
        }
        else if (i == 0){
            user.push_back(c);
        } else if (i == 1) {
            cmd.push_back(c);
        } else if (i == 2) {
            if(c == '-' || (c <= '9' && c >= '0')){
                val1.push_back(c);
            } else{
                return false;
            }
        } else if (i == 3) {
            if(c == '-' || (c <= '9' && c >= '0')){
                val2.push_back(c);
            } else{
                return false;
            }
        } else {
            return false;
        }
    }

    return i == 3;
}

void help(std::vector<Operation*> ops)
{
    std::cout << "Command line calculator performing basic integer operation" << std::endl;
    std::cout << "expected input should follow the format: \"user;command;value1;value2\"" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "The command available are:" << std::endl;
    for(const Operation * op : ops){
        std::cout << "  - " << op->get_command() << ": " << op->describe() << std::endl;
    }
    std::cout << "" << std::endl;
    std::cout << "The input \"EXIT\" is also accepted to close the programme." << std::endl;
}


