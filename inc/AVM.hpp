// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AVM.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/30 13:48:23 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/19 18:40:17 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AVM_HPP
# define AVM_HPP

# include <algorithm>
# include <memory>
# include <unistd.h>
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <unordered_map>
# include <regex>
# include <IOperand.hpp>
# include <TOperand.hpp>
# include <OFactory.hpp>

class	AVM
{
	typedef std::unordered_map< std::string, void (AVM::*)(void) >	smpl_cmdMap;
	typedef std::unordered_map< std::string,
								void (AVM::*)(eOperandType, std::string) >	arg_cmdMap;
	typedef std::unordered_map< std::string, eOperandType >			tpMap;
	std::vector< std::string >						_lines;
	std::vector< IOperand const * >					_stack;
	static const OFactory &							_factory;
	static const smpl_cmdMap						_smpl_cmdmap;
	static const arg_cmdMap							_arg_cmdmap;
	static const tpMap								_typemap;
	bool											_from_tty;
	bool											_exit;

	static const smpl_cmdMap	init_smpl_cmdmap(void);
	static const arg_cmdMap		init_arg_cmdmap(void);
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
	void				ft_exit(void);
	void				push(eOperandType type, std::string value);
	void				ft_assert(eOperandType type, std::string value);
	void				exec_line(std::string cmd, std::string type, std::string value);
public:
	AVM( void );
	AVM( std::string file_path );
	int					run( void );
	~AVM( void );
};

#endif
