// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OFactory.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/09/11 15:38:27 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/20 16:04:59 by ahrytsen         ###   ########.fr       //
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
	int32_t		res;
	std::smatch	m;
	if (!std::regex_match(value, m, std::regex("^[+|-]?[[:digit:]]+(\\.([[:digit:]]+))?")))
		throw std::logic_error("Wrong value format!");
	else if (m[1].length())
		throw std::logic_error("A floating point values is not allowed for int8 type!");
	try { res = std::stoi(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows int8!"); }
	if (res < std::numeric_limits<int8_t>::min()
		|| res > std::numeric_limits<int8_t>::max())
		throw std::out_of_range("Value ``" + value + "\" overflows int8!");
	return ( new TOperand<int8_t>(Int8, 0, res) );
}

IOperand const *	OFactory::createInt16( std::string const & value ) const {
	int32_t		res;
	std::smatch	m;
	if (!std::regex_match(value, m, std::regex("^[+|-]?[[:digit:]]+(\\.([[:digit:]]+))?")))
		throw std::logic_error("Wrong value format!");
	else if (m[1].length())
		throw std::logic_error("A floating point values is not allowed for int16 type!");
	try { res = std::stoi(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows int16!"); }
	if (res < std::numeric_limits<int16_t>::min()
		|| res > std::numeric_limits<int16_t>::max())
		throw std::out_of_range("Value ``" + value + "\" overflows int16!");
	return ( new TOperand<int16_t>(Int16, 0, res) );
}

IOperand const *	OFactory::createInt32( std::string const & value ) const {
	int32_t		res;
	std::smatch	m;
	if (!std::regex_match(value, m, std::regex("^[+|-]?[[:digit:]]+(\\.([[:digit:]]+))?")))
		throw std::logic_error("Wrong value format!");
	else if (m[1].length())
		throw std::logic_error("A floating point values is not allowed for int32 type!");
	try { res = std::stoi(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows int32!"); }
	return ( new TOperand<int32_t>(Int32, 0, res) );
}

IOperand const *	OFactory::createFloat( std::string const & value ) const {
	float		res;
	std::smatch	m;
	if (!std::regex_match(value, m, std::regex("^[+|-]?[[:digit:]]+(\\.([[:digit:]]+))?")))
		throw std::logic_error("Wrong value format!");
	try { res = std::stof(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows float!"); }
	return ( new TOperand<float>(_Float, m[2].length(), res) );
}

IOperand const *	OFactory::createDouble( std::string const & value ) const {
	double		res;
	std::smatch	m;
	if (!std::regex_match(value, m, std::regex("^[+|-]?[[:digit:]]+(\\.([[:digit:]]+))?")))
		throw std::logic_error("Wrong value format!");
	try { res = std::stod(value); }
	catch (...) { throw std::out_of_range("Value ``" + value + "\" overflows double!"); }
	return ( new TOperand<double>(_Double, m[2].length(), res) );
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
