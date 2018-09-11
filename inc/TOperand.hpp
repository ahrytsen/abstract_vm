// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 13:19:05 by ahrytsen          #+#    #+#             //
//   Updated: 2018/07/30 14:00:04 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TOPERAND_HPP
# define TOPERAND_HPP

# include <iostream>
# include <IOperand.hpp>
# include <OFactory.hpp>
//class	OFactory;
template<class T>
class	TOperand : public IOperand {
	T						_value;
	int						_precision;
	eOperandType			_type;
	static const OFactory &	_factory;
public:
	TOperand<T>();
	TOperand<T>(T value, eOperandType type);
	T					getValue( void ) const;			// Value of the type of the instance
	int					getPrecision( void ) const;		// Precision of the type of the instance
	eOperandType		getType( void ) const;			// Type of the instance
	IOperand const *	operator+( IOperand const & rhs ) const; // Sum
	IOperand const *	operator-( IOperand const & rhs ) const; // Difference
	IOperand const *	operator*( IOperand const & rhs ) const; // Product
	IOperand const *	operator/( IOperand const & rhs ) const; // Quotient rhs
	IOperand const *	operator%( IOperand const & rhs ) const; // Modulo

	std::string const &	toString( void ) const; // String representation of the instance
	template <typename S>
	static S			getIOperandValue(IOperand const & op);

	virtual ~TOperand( void ) {};
};

template<class T>
const OFactory &	TOperand<T>::_factory = OFactory::getInstance();

template <class T>
TOperand<T>::TOperand() : _value(static_cast<int8_t>(0)), _precision(0), _type(Int8) {}

template <class T>
TOperand<T>::TOperand(T value, eOperandType type)
	: _value(value), _precision(sizeof(T)), _type(type) {}

template <class T>
int						TOperand<T>::getPrecision( void ) const {return _precision;}

template <class T>
T						TOperand<T>::getValue( void ) const {return _value;}

template <class T>
eOperandType			TOperand<T>::getType( void ) const {return _type;}

template <class T>
IOperand const *		TOperand<T>::operator+( const IOperand & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										+ dynamic_cast< const TOperand< int8_t > & >(rhs).getValue()));
	case Int16:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										+ dynamic_cast< const TOperand< int16_t > & >(rhs).getValue()));
	case Int32:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										+ dynamic_cast< const TOperand< int32_t > & >(rhs).getValue()));
	case _Float:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										+ dynamic_cast< const TOperand< float > & >(rhs).getValue()));
	case _Double:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										+ dynamic_cast< const TOperand< double > & >(rhs).getValue()));
	}
}

template<class T>
IOperand const *		TOperand<T>::operator-( const IOperand & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										- dynamic_cast< const TOperand< int8_t > & >(rhs).getValue()));
	case Int16:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										- dynamic_cast< const TOperand< int16_t > & >(rhs).getValue()));
	case Int32:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										- dynamic_cast< const TOperand< int32_t > & >(rhs).getValue()));
	case _Float:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										- dynamic_cast< const TOperand< float > & >(rhs).getValue()));
	case _Double:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										- dynamic_cast< const TOperand< double > & >(rhs).getValue()));
	}
}

template <class T>
IOperand const *		TOperand<T>::operator*( const IOperand & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										* dynamic_cast< const TOperand< int8_t > & >(rhs).getValue()));
	case Int16:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										* dynamic_cast< const TOperand< int16_t > & >(rhs).getValue()));
	case Int32:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										* dynamic_cast< const TOperand< int32_t > & >(rhs).getValue()));
	case _Float:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										* dynamic_cast< const TOperand< float > & >(rhs).getValue()));
	case _Double:
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										this->getValue()
										* dynamic_cast< const TOperand< double > & >(rhs).getValue()));
	}
}

template <class T>
IOperand const *		TOperand<T>::operator/( const IOperand & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
	{
		int8_t rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()), this->getValue() / rhs_val));
	}
	case Int16:
	{
		int16_t rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()), this->getValue() / rhs_val));
	}
	case Int32:
	{
		int32_t rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()), this->getValue() / rhs_val));
	}
	case _Float:
	{
		float rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (rhs_val == 0.0)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()), this->getValue() / rhs_val));
	}
	case _Double:
	{
		double rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (rhs_val == 0.0)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()), this->getValue() / rhs_val));
	}
	}
}

template <class T>
IOperand const *		TOperand<T>::operator%( const IOperand & rhs ) const {
	eOperandType	type = std::max(_type, rhs.getType());
	if (type > Int32)
		throw std::logic_error("Modulo of float type");
	int32_t	lhs_val = this->getValue();
	switch (rhs.getType())
	{
	case Int8:
	{
		int8_t rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Modulo by zero!");
		return (_factory.createTOperand(type, lhs_val / rhs_val));
	}
	case Int16:
	{
		int16_t rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Modulo by zero!");
		return (_factory.createTOperand(type, lhs_val / rhs_val));
	}
	case Int32:
	{
		int32_t rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Modulo by zero!");
		return (_factory.createTOperand(type, lhs_val / rhs_val));
	}
	case _Float:
	case _Double:
	default:
		return (NULL);
	}
}

template <class T>
std::string const &		TOperand<T>::toString( void ) const
{
	std::string	*ret = new std::string(std::to_string(_value));
	return (*ret);
}

# endif
