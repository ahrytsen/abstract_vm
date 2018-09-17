// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AVM.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 13:48:23 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/17 20:22:01 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AVM_HPP
# define AVM_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <map>
# include <regex>
# include <IOperand.hpp>
# include <TOperand.hpp>
# include <OFactory.hpp>

class	AVM
{
	typedef std::map< std::string, void (AVM::*)() >		cmdMap;
	typedef std::map< std::string, eOperandType >	tpMap;
	std::vector< std::string >						_lines;
	std::vector< IOperand const * >					_stack;
	static const OFactory &							_factory;
	static const cmdMap								_cmdmap;
	static const tpMap								_typemap;
	bool											_exit;

	static const cmdMap	init_cmdmap(void);
	static const tpMap	init_typemap(void);
	static eOperandType	parse_type(std::string type);

	void				readlines(std::istream & input);
	void				pop(void);
	void				dump(void);
	void				add(void);
	void				sub(void);
	void				mul(void);
	void				div(void);
	void				mod(void);
	void				print(void);
	void				push(eOperandType type, std::string value);
	void				assert(eOperandType type, std::string value);
	void				exec_line(std::string cmd);
	void				exec_line(std::string cmd, std::string type, std::string value);
public:
	AVM( void );
	AVM( std::string file_path );
	int					run( void );
	~AVM( void );
};

#endif
