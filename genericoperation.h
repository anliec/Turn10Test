#ifndef GENERICOPERATION_H
#define GENERICOPERATION_H

#include "operation.h"

template<int(*op)(int, int)>
/**
 * @brief The GenericOperation class template sub class of Operation, allowing to set the operation with a template
 */
class GenericOperation : public Operation
{
public:
    GenericOperation(std::string description, std::string command, std::string operatorChar):
        Operation(description, command, operatorChar)
    {
    }

    /**
     * @brief compute template version allowing computation of the operation using the provided function
     * @param val1 first value
     * @param val2 second value
     * @return result of the operation
     */
    int compute(int val1, int val2) const
    {
        return op(val1, val2);
    }
};

#endif // GENERICOPERATION_H
