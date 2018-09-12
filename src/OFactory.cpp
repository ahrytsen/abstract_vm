// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OFactory.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/09/11 15:38:27 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/12 16:59:03 by ahrytsen         ###   ########.fr       //
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
	try { int res = std::stoi(value); }
	catch ( std::range_error & e) {}
	catch ( std::invalid_argument & e) {}
	return new TOperand<int8_t>();
}

IOperand const *	OFactory::createInt16( std::string const & value ) const {
	try { int res = std::stoi(value); }
	catch ( std::range_error & e) {}
	catch ( std::invalid_argument & e) {}
	return new TOperand<int8_t>();
}

IOperand const *	OFactory::createInt32( std::string const & value ) const {
	try { int res = std::stoi(value); }
	catch ( std::range_error & e) {}
	catch ( std::invalid_argument & e) {}
	return new TOperand<int8_t>();
}

IOperand const *	OFactory::createFloat( std::string const & value ) const {
	try { int res = std::stoi(value); }
	catch ( std::range_error & e) {}
	catch ( std::invalid_argument & e) {}
	return new TOperand<int8_t>();
}

IOperand const *	OFactory::createDouble( std::string const & value ) const {
	try { int res = std::stoi(value); }
	catch ( std::range_error & e) {}
	catch ( std::invalid_argument & e) {}
	return new TOperand<int8_t>();
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
};

IOperand const *	OFactory::createTOperand( eOperandType type, int16_t value ) const {
	return (new TOperand<int16_t>(value, type));
};

IOperand const *	OFactory::createTOperand( eOperandType type, int32_t value ) const {
	return (new TOperand<int32_t>(value, type));
};

IOperand const *	OFactory::createTOperand( eOperandType type, float value ) const {
	return (new TOperand<float>(value, type));
};

IOperand const *	OFactory::createTOperand( eOperandType type, double value ) const {
	return (new TOperand<double>(value, type));
};
