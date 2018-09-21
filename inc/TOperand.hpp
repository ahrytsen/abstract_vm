// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 13:19:05 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/21 14:07:08 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TOPERAND_HPP
# define TOPERAND_HPP

# include <iostream>
# include <sstream>
# include <IOperand.hpp>
# include <OFactory.hpp>

template<class T>
class	TOperand : public IOperand {
	T						_value;
	int						_precision;
	eOperandType			_type;
	std::string				_str_val;
	static const OFactory &	_factory;
public:
	TOperand<T>();
	TOperand<T>(eOperandType type, size_t precision, T value);
	T					getValue( void ) const;			// Value of the type of the instance
	int					getPrecision( void ) const;		// Precision of the type of the instance
	eOperandType		getType( void ) const;			// Type of the instance
	IOperand const *	operator+( IOperand const & rhs ) const; // Sum
	IOperand const *	operator-( IOperand const & rhs ) const; // Difference
	IOperand const *	operator*( IOperand const & rhs ) const; // Product
	IOperand const *	operator/( IOperand const & rhs ) const; // Quotient rhs
	IOperand const *	operator%( IOperand const & rhs ) const; // Modulo
	std::string const &	toString( void ) const; // String representation of the instance

	virtual ~TOperand( void ) {};
};

template <typename S>
S						getIOperandValue(IOperand const & op)
{
	switch(op.getType()) {
	case Int8: return dynamic_cast< TOperand< int8_t > const & >(op).getValue();
	case Int16: return dynamic_cast< TOperand< int16_t > const & >(op).getValue();
	case Int32: return dynamic_cast< TOperand< int32_t > const & >(op).getValue();
	case _Float: return dynamic_cast< TOperand< float > const & >(op).getValue();
	case _Double: return dynamic_cast< TOperand< double > const & >(op).getValue();
	}
}

template<class T>
const OFactory &	TOperand<T>::_factory = OFactory::getInstance();

template <class T>
TOperand<T>::TOperand()
	: _value(static_cast<int8_t>(0)), _precision(0), _type(Int8), _str_val("0") {}

template <class T>
TOperand<T>::TOperand(eOperandType type, size_t precision, T value)
	: _value(value), _precision(precision), _type(type) {
	std::stringstream	tmp;
	tmp.setf( std::ios::fixed, std::ios::floatfield );
	tmp.precision(_precision);
	if (_type == Int8) tmp << static_cast<int>(value);
	else tmp << value;
	_str_val = tmp.str();
}

template <class T>
int						TOperand<T>::getPrecision( void ) const {return _precision;}

template <class T>
T						TOperand<T>::getValue( void ) const {return _value;}

template <class T>
eOperandType			TOperand<T>::getType( void ) const {return _type;}

template <class T>
IOperand const *		TOperand<T>::operator+( IOperand const & rhs ) const {
	size_t			max_precision = std::max(_precision, rhs.getPrecision());
	eOperandType	max_type = std::max(_type, rhs.getType());
	long			l_res;
	long double		ld_res;
	if (max_type < _Float) {
		l_res = this->getValue() + getIOperandValue< long >(rhs);
		return _factory.createTOperand(max_type, max_precision, l_res);
	}
	else {
		ld_res = this->getValue() + getIOperandValue< long double >(rhs);
		return _factory.createTOperand(max_type, max_precision, ld_res);
	}
}

template<class T>
IOperand const *		TOperand<T>::operator-( IOperand const & rhs ) const {
	size_t			max_precision = std::max(_precision, rhs.getPrecision());
	eOperandType	max_type = std::max(_type, rhs.getType());
	long			l_res;
	long double		ld_res;
	if (max_type < _Float) {
		l_res = this->getValue() - getIOperandValue< long >(rhs);
		return _factory.createTOperand(max_type, max_precision, l_res);
	}
	else {
		ld_res = this->getValue() - getIOperandValue< long double >(rhs);
		return _factory.createTOperand(max_type, max_precision, ld_res);
	}
}

template <class T>
IOperand const *		TOperand<T>::operator*( IOperand const & rhs ) const {
	size_t			max_precision = std::max(_precision, rhs.getPrecision());
	eOperandType	max_type = std::max(_type, rhs.getType());
	long			l_res;
	long double		ld_res;
	if (max_type < _Float) {
		l_res = this->getValue() * getIOperandValue< long >(rhs);
		return _factory.createTOperand(max_type, max_precision, l_res);
	}
	else {
		ld_res = this->getValue() * getIOperandValue< long double >(rhs);
		return _factory.createTOperand(max_type, max_precision, ld_res);
	}
}

template <class T>
IOperand const *		TOperand<T>::operator/( IOperand const & rhs ) const {
	size_t			max_precision = std::max(_precision, rhs.getPrecision());
	eOperandType	max_type = std::max(_type, rhs.getType());
	long			l_res;
	long double		ld_res;
	if (getIOperandValue< double >(rhs) == 0.0)
		throw std::logic_error ("Division by zero!");
	else if (max_type < _Float) {
		l_res = this->getValue() / getIOperandValue< long >(rhs);
		return _factory.createTOperand(max_type, max_precision, l_res);
	}
	else {
		ld_res = this->getValue() / getIOperandValue< long double >(rhs);
		return _factory.createTOperand(max_type, max_precision, ld_res);
	}
}

template <class T>
IOperand const *		TOperand<T>::operator%( IOperand const & rhs ) const {
	size_t			max_precision = std::max(_precision, rhs.getPrecision());
	eOperandType	max_type = std::max(_type, rhs.getType());
	int32_t			value = this->getValue();
	long			res;
	if (getIOperandValue< double >(rhs) == 0.0)
		throw std::logic_error ("Modulo by zero!");
	else if (max_type >= _Float)
 		throw std::logic_error("Modulo of float type");
	res = value % getIOperandValue< long >(rhs);
	return _factory.createTOperand(max_type, max_precision, res);
}

template <class T>
std::string const &		TOperand<T>::toString( void ) const {
	return (_str_val);
}

# endif
