// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OFactory.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/09/11 14:50:37 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/11 21:06:38 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OFACTORY_HPP
# define OFACTORY_HPP

# include <iostream>
# include <vector>
# include <IOperand.hpp>

class OFactory;

typedef IOperand const * (OFactory::*farr)( std::string const & ) const;

class	OFactory {
	static OFactory	_instance;

	OFactory();
	OFactory( OFactory const & );
	OFactory &			operator=( OFactory const & );
	~OFactory();
	IOperand const *	createInt8( std::string const & value ) const;
	IOperand const *	createInt16( std::string const & value ) const;
	IOperand const *	createInt32( std::string const & value ) const;
	IOperand const *	createFloat( std::string const & value ) const;
	IOperand const *	createDouble( std::string const & value ) const;
public:
	static const OFactory &	getInstance();
	IOperand const *	createOperand( eOperandType type, std::string const & value ) const;
	IOperand const *	createTOperand( eOperandType type, int8_t value ) const;
	IOperand const *	createTOperand( eOperandType type, int16_t value ) const;
	IOperand const *	createTOperand( eOperandType type, int32_t value ) const;
	IOperand const *	createTOperand( eOperandType type, float value ) const;
	IOperand const *	createTOperand( eOperandType type, double value ) const;
};

#endif
