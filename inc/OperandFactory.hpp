// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 14:32:20 by ahrytsen          #+#    #+#             //
//   Updated: 2018/07/30 22:21:29 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <string>
# include <vector>

class	OperandFactory
{
	IOperand const *	createInt8( std::string const & value ) const;
	IOperand const *	createInt16( std::string const & value ) const;
	IOperand const *	createInt32( std::string const & value ) const;
	IOperand const *	createFloat( std::string const & value ) const;
	IOperand const *	createDouble( std::string const & value ) const;
public:
	IOperand const *	createOperand( eOperandType type, std::string const & value ) const;
	class	FactoryException : public std::exception
};

#endif
