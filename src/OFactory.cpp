// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OFactory.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/09/11 15:38:27 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/19 19:06:00 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <OFactory.hpp>
#include <TOperand.hpp>

OFactory	OFactory::_instance;

OFactory::OFactory() {}

OFactory::OFactory( OFactory const & f ) { (void)f; }

OFactory &			OFactory::operator=( OFactory const & f ) {
	(void)f;
	return (*this);
}

OFactory::~OFactory() {}

IOperand const *	OFactory::createInt8( std::string const & value ) const {
	int32_t res;
	if (std::regex_match(value, std::regex("[[:digit:]]+\\.[[:digit:]+])?")))
		 throw std::logic_error("A floating point values is not allowed for int8 type!");
	try { res = std::stoi(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows int8!"); }
	if (res < std::numeric_limits<int8_t>::min()
		|| res > std::numeric_limits<int8_t>::max())
		throw std::out_of_range("Value ``" + value + "\" overflows int8!");
	return ( new TOperand<int8_t>(res, Int8) );
}

IOperand const *	OFactory::createInt16( std::string const & value ) const {
	int32_t res;
	if (std::regex_match(value, std::regex("[[:digit:]]+\\.[[:digit:]+])?")))
		throw std::logic_error("A floating point values is not allowed for int16 type!");
	try { res = std::stoi(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows int16!"); }
	if (res < std::numeric_limits<int16_t>::min()
		|| res > std::numeric_limits<int16_t>::max())
		throw std::out_of_range("Value ``" + value + "\" overflows int16!");
	return ( new TOperand<int16_t>(res, Int16) );
}

IOperand const *	OFactory::createInt32( std::string const & value ) const {
	int32_t res;
	if (std::regex_match(value, std::regex("[[:digit:]]+\\.[[:digit:]+])?")))
		throw std::logic_error("A floating point values is not allowed for int32 type!");
	try { res = std::stoi(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows int32!"); }
	return ( new TOperand<int32_t>(res, Int32) );
}

IOperand const *	OFactory::createFloat( std::string const & value ) const {
	float res;
	try { res = std::stof(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows float!"); }
	return ( new TOperand<float>(res, _Float) );
}

IOperand const *	OFactory::createDouble( std::string const & value ) const {
	double res;
	try { res = std::stod(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows double!"); }
	return ( new TOperand<double>(res, _Double) );
}

const OFactory &	OFactory::getInstance() { return _instance; }

IOperand const *	OFactory::createOperand( eOperandType type, std::string const & value ) const {
	static farr	funcs[] = {
		&OFactory::createInt8, &OFactory::createInt16, &OFactory::createInt32,
		&OFactory::createFloat, &OFactory::createDouble
	};
	if (type < Int8 || type > _Double )
		throw std::out_of_range ("Unknown operand type!");
	return ((this->*funcs[type])(value));
}

IOperand const *	OFactory::createTOperand( eOperandType type, int8_t value ) const {
	return (new TOperand<int8_t>(value, type));
}

IOperand const *	OFactory::createTOperand( eOperandType type, int16_t value ) const {
	return (new TOperand<int16_t>(value, type));
}

IOperand const *	OFactory::createTOperand( eOperandType type, int32_t value ) const {
	return (new TOperand<int32_t>(value, type));
}

IOperand const *	OFactory::createTOperand( eOperandType type, float value ) const {
	return (new TOperand<float>(value, type));
}

IOperand const *	OFactory::createTOperand( eOperandType type, double value ) const {
	return (new TOperand<double>(value, type));
}
