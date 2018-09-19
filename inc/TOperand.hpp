// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 13:19:05 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/19 21:44:41 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TOPERAND_HPP
# define TOPERAND_HPP

# include <iostream>
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
	TOperand<T>(T value, eOperandType type);
	T					getValue( void ) const;			// Value of the type of the instance
	int					getPrecision( void ) const;		// Precision of the type of the instance
	eOperandType		getType( void ) const;			// Type of the instance
	IOperand const *	operator+( IOperand const & rhs ) const; // Sum
	IOperand const *	operator-( IOperand const & rhs ) const; // Difference
	IOperand const *	operator*( IOperand const & rhs ) const; // Product
	IOperand const *	operator/( IOperand const & rhs ) const; // Quotient rhs
	IOperand const *	operator%( IOperand const & rhs ) const; // Modulo
	bool				operator==( IOperand const & rhs ) const; // Cmp
	std::string const &	toString( void ) const; // String representation of the instance
	template <typename S>
	static S			getIOperandValue(IOperand const & op);

	virtual ~TOperand( void ) {};
};

template<class T>
std::ostream &	operator<<( std::ostream & out, TOperand<T> const & op ) {
	out << op._value;
	return (out);
}

template<class T>
const OFactory &	TOperand<T>::_factory = OFactory::getInstance();

template <class T>
TOperand<T>::TOperand()
	: _value(static_cast<int8_t>(0)), _precision(0), _type(Int8), _str_val("0") {}

template <class T>
TOperand<T>::TOperand(T value, eOperandType type)
	: _value(value), _precision(sizeof(T)), _type(type), _str_val(std::to_string(value)) {}

template <class T>
int						TOperand<T>::getPrecision( void ) const {return _precision;}

template <class T>
T						TOperand<T>::getValue( void ) const {return _value;}

template <class T>
eOperandType			TOperand<T>::getType( void ) const {return _type;}

template <class T>
IOperand const *		TOperand<T>::operator+( IOperand const & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
	{
		T res = this->getValue() + dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		return (_factory.createTOperand(std::max(_type, rhs.getType()), res));
	}
	case Int16:
		if (_type > Int16) {
			T res = this->getValue() + dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			int16_t	res = this->getValue() +
				dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case Int32:
		if (_type > Int32) {
			T res = this->getValue() + dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			int32_t	res = this->getValue() +
				dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case _Float:
		if (_type > _Float) {
			T res = this->getValue() + dynamic_cast< const TOperand< float > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			float	res = this->getValue() +
				dynamic_cast< const TOperand< float > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case _Double:
	{
		double	res = this->getValue() + dynamic_cast< const TOperand< double > & >(rhs).getValue();
		return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
	}
	}
}

template<class T>
IOperand const *		TOperand<T>::operator-( IOperand const & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
	{
		T res = this->getValue() - dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		return (_factory.createTOperand(std::max(_type, rhs.getType()), res));
	}
	case Int16:
		if (_type > Int16) {
			T res = this->getValue() - dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			int16_t	res = this->getValue() -
				dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case Int32:
		if (_type > Int32) {
			T res = this->getValue() - dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			int32_t	res = this->getValue() -
				dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case _Float:
		if (_type > _Float) {
			T res = this->getValue() - dynamic_cast< const TOperand< float > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			float	res = this->getValue() -
				dynamic_cast< const TOperand< float > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case _Double:
	{
		double	res = this->getValue() - dynamic_cast< const TOperand< double > & >(rhs).getValue();
		return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
	}
	}
}

template <class T>
IOperand const *		TOperand<T>::operator*( IOperand const & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
	{
		T res = this->getValue() * dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		return (_factory.createTOperand(std::max(_type, rhs.getType()), res));
	}
	case Int16:
		if (_type > Int16) {
			T res = this->getValue() * dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			int16_t	res = this->getValue() *
				dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case Int32:
		if (_type > Int32) {
			T res = this->getValue() * dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			int32_t	res = this->getValue() *
				dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case _Float:
		if (_type > _Float) {
			T res = this->getValue() * dynamic_cast< const TOperand< float > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
		else {
			float	res = this->getValue() *
				dynamic_cast< const TOperand< float > & >(rhs).getValue();
			return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
		}
	case _Double:
	{
		double	res = this->getValue() * dynamic_cast< const TOperand< double > & >(rhs).getValue();
		return (_factory.createTOperand(std::max(_type, rhs.getType()),res));
	}
	}
}

template <class T>
IOperand const *		TOperand<T>::operator/( IOperand const & rhs ) const {
	switch (rhs.getType())
	{
	case Int8:
	{
		int8_t rhs_val = dynamic_cast< const TOperand< int8_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										static_cast<T>(this->getValue() / rhs_val)));
	}
	case Int16:
	{
		int16_t rhs_val = dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										(_type > Int16)
										? static_cast<T>(this->getValue() / rhs_val)
										: static_cast<int16_t>(this->getValue() / rhs_val)));
	}
	case Int32:
	{
		int32_t rhs_val = dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										(_type > Int32)
										? static_cast<T>(this->getValue() / rhs_val)
										: static_cast<int32_t>(this->getValue() / rhs_val)));
	}
	case _Float:
	{
		float rhs_val = dynamic_cast< const TOperand< float > & >(rhs).getValue();
		if (rhs_val == 0.0)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										(_type > _Float)
										? static_cast<T>(this->getValue() / rhs_val)
										: static_cast<float>(this->getValue() / rhs_val)));
	}
	case _Double:
	{
		double rhs_val = dynamic_cast< const TOperand< double > & >(rhs).getValue();
		if (rhs_val == 0.0)
			throw std::overflow_error ("Division by zero!");
		return (_factory.createTOperand(std::max(_type, rhs.getType()),
										static_cast<double>(this->getValue() / rhs_val)));
	}
	}
}

template <class T>
IOperand const *		TOperand<T>::operator%( IOperand const & rhs ) const {
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
		return (_factory.createTOperand(type, static_cast<T>(lhs_val % rhs_val)));
	}
	case Int16:
	{
		int16_t rhs_val = dynamic_cast< const TOperand< int16_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Modulo by zero!");
		return (_factory.createTOperand(type,
										(_type > Int16)
										? static_cast<T>(lhs_val % rhs_val)
										: static_cast<int16_t>(lhs_val % rhs_val)));
	}
	case Int32:
	{
		int32_t rhs_val = dynamic_cast< const TOperand< int32_t > & >(rhs).getValue();
		if (!rhs_val)
			throw std::overflow_error ("Modulo by zero!");
		return (_factory.createTOperand(type, static_cast<int32_t>(lhs_val % rhs_val)));
	}
	case _Float:
	case _Double:
	default:
		throw std::logic_error("Modulo of float type");
		return (NULL);
	}
}

template <class T>
bool					TOperand<T>::operator==( IOperand const & rhs ) const {
	if (rhs.getType() != _type
		|| rhs.getPrecision() != _precision
		|| _value != dynamic_cast< TOperand< T > const & >(rhs).getValue())
		return (false);
	return (true);
}

template <class T>
std::string const &		TOperand<T>::toString( void ) const {
	return (_str_val);
}

# endif
