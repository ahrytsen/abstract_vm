// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/26 17:10:16 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/20 16:09:15 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <iostream>

enum	eOperandType {
	Int8,
	Int16,
	Int32,
	_Float,
	_Double
};

class	IOperand {
public:
	virtual int					getPrecision( void ) const = 0;		// Precision of the type of the instance
	virtual eOperandType		getType( void ) const = 0;			// Type of the instance
	virtual IOperand const *	operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const *	operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const *	operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const *	operator/( IOperand const & rhs ) const = 0; // Quotient rhs
	virtual IOperand const *	operator%( IOperand const & rhs ) const = 0; // Modulo
	virtual std::string const & toString( void ) const = 0; // String representation of the instance

	virtual ~IOperand( void ) {}
};

#endif
