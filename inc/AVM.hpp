// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AVM.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 13:48:23 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/13 21:33:07 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AVM_HPP
# define AVM_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <IOperand.hpp>
# include <OFactory.hpp>

class	AVM
{
	bool							_interactive;
	std::vector< std::string >		_lines;
	std::vector< IOperand * const >	_stack;
	static const OFactory &			_factory;
	void	readlines(std::istream & input);
public:
	AVM( void );
	AVM( std::string file_path );
	int		run( void );
	~AVM( void );
};

#endif
