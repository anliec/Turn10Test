#ifndef OPERATION_H
#define OPERATION_H

#include <string>

/**
 * @brief The Operation class is the base class for an operation object
 */
class Operation
{
private:
    std::string description;
    std::string commandStr;
    std::string operatorStr;

public:
    /**
     * @brief Operation
     * @param description string descrition of the operation, for help purpose
     * @param command string command that should trigger this operation
     * @param opperatorStr string mathematical representation of the operator
     */
    Operation(std::string description, std::string command, std::string opperatorStr);

    /**
     * @brief describe return a string description of the operation
     * @return describtion of the operation
     */
    const std::string & describe() const {return description;}

    /**
     * @brief get_command return the command which triger this operation
     * @return command for this operation
     */
    const std::string & get_command() const {return commandStr;}

    /**
     * @brief get_operator return the operator representing this operation in math
     * @return text operator for this operation
     */
    const std::string & get_operator() const {return operatorStr;}

    /**
     * @brief compute Virtual method to be implemented in sub class, compute
     * @param val1 first value of the operation
     * @param val2 second value of the operation
     * @return result of the operation
     */
    virtual int compute(int val1, int val2) const = 0;
};

#endif // OPERATION_H
