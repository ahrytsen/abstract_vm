// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/26 17:45:34 by ahrytsen          #+#    #+#             //

//                                                                            //
// ************************************************************************** //

#ifndef TOPERAND_HPP
# define TOPERAND_HPP

# include <iostream>
# include <IOperand.hpp>

template<class T>
class	TOperand : public IOperand {
	T				_value;
	int				_precision;
	eOperandType	_type;
public:
	TOperand<T>();
	TOperand<T>(std::string value);
	int					getPrecision( void ) const;		// Precision of the type of the instance
	eOperandType		getType( void ) const;			// Type of the instance
	IOperand const *	operator+( IOperand const & rhs ) const; // Sum
	IOperand const *	operator-( IOperand const & rhs ) const; // Difference
	IOperand const *	operator*( IOperand const & rhs ) const; // Product
	IOperand const *	operator/( IOperand const & rhs ) const; // Quotient rhs
	IOperand const *	operator%( IOperand const & rhs ) const; // Modulo

	std::string const &	toString( void ) const; // String representation of the instance

	virtual ~IOperand( void );
};

template <class T>
TOperand<T>::TOperand() : _value(0), _precision(0) {}

template <class T>
TOperand<T>::TOperand(std::string value) {

}

template <class T>
int						TOperand<T>::getPrecision( void ) const {return _precision;}

template <class T>
eOperandType			TOperand<T>::getType( void ) const {

}

# endif
