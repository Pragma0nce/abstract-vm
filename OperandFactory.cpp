#include "OperandFactory.hpp"
#include "Operand.hpp"
#include "Exceptions.hpp"
#include <iostream>

  // Typedef for the member function pointer, for everyone's sanity.
typedef  IOperand const * (OperandFactory::*MemFn)(std::string const &value) const;
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	long double expected = stod(value);
	if (expected > std::numeric_limits<int8_t>::max())
		throw ExceptionOverflow();
	else if (expected < std::numeric_limits<int8_t>::min())
		throw ExceptionUnderflow();

    return new Operand<int8_t>(std::stoi(value));
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
	long double expected = stod(value);
	if (expected > std::numeric_limits<int16_t>::max())
		throw ExceptionOverflow();
	else if (expected < std::numeric_limits<int16_t>::min())
		throw ExceptionUnderflow();

    return new Operand<int16_t>(std::stoi(value));
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
	long double expected = stod(value);
	if (expected > std::numeric_limits<int32_t>::max())
		throw ExceptionOverflow();
	else if (expected < std::numeric_limits<int32_t>::min())
		throw ExceptionUnderflow();

    return new Operand<int32_t>(std::stoi(value));
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
	long double expected = stod(value);
	if (expected > std::numeric_limits<float>::max())
		throw ExceptionOverflow();
	else if (expected < std::numeric_limits<float>::lowest())
		throw ExceptionUnderflow();
    return new Operand<float>(std::stof(value));
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
	long double expected = stod(value);
	if (expected > std::numeric_limits<double>::max())
		throw ExceptionOverflow();
	else if (expected < std::numeric_limits<double>::lowest())
		throw ExceptionUnderflow();
    return new Operand<double>(std::stod(value));
}




IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	static Memfuncts list[] = {
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	};

    IOperand const * created = nullptr;
	Memfuncts func = list[type];
	created = (this->*func)(value);

	return created;
}
