// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 15:28:24 by ahrytsen          #+#    #+#             //
//   Updated: 2018/07/30 21:03:09 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <OperandFactory.hpp>

IOperand const *	OperandFactory::createInt8( std::string const & value ) const
{
	try { int res = std::stoi(value); }
	catch ( std::range_error & e) {}
	catch ( std::invalid_argument & e) {}
	return new TOperand<int8_t>();
}

IOperand const *	OperandFactory::createInt16( std::string const & value ) const
{
	return new TOperand<int16_t>();
}

IOperand const *	OperandFactory::createInt32( std::string const & value ) const
{
	return new TOperand<int32_t>();
}

IOperand const *	OperandFactory::createFloat( std::string const & value ) const
{
	return new TOperand<float>();
}

IOperand const *	OperandFactory::createDouble( std::string const & value ) const
{
	return new TOperand<double>();
}

IOperand const *	OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	static std::vector<auto> const	create{createInt8, createInt16, createInt32, createFloat, createDouble};

	if (type < Int8 || type > Double)
		throw std::exception("unknown type");
	return create[type](value);
}
