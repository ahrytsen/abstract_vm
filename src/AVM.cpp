// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AVM.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/09/12 17:00:56 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/19 21:07:43 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <AVM.hpp>

const OFactory &		AVM::_factory = OFactory::getInstance();
const AVM::smpl_cmdMap	AVM::_smpl_cmdmap = AVM::init_smpl_cmdmap();
const AVM::arg_cmdMap	AVM::_arg_cmdmap = AVM::init_arg_cmdmap();
const AVM::tpMap		AVM::_typemap = AVM::init_typemap();

const AVM::smpl_cmdMap	AVM::init_smpl_cmdmap(void) {
	AVM::smpl_cmdMap	map;

	map["pop"] = &AVM::pop;
	map["dump"] = &AVM::dump;
	map["add"] = &AVM::add;
	map["sub"] = &AVM::sub;
	map["mul"] = &AVM::mul;
	map["div"] = &AVM::div;
	map["mod"] = &AVM::mod;
	map["print"] = &AVM::print;
	map["exit"] = &AVM::ft_exit;
	return map;
}

const AVM::arg_cmdMap	AVM::init_arg_cmdmap(void) {
	AVM::arg_cmdMap	map;

	map["push"] = &AVM::push;
	map["assert"] = &AVM::ft_assert;
	return map;
}

const AVM::tpMap		AVM::init_typemap(void) {
	AVM::tpMap	map;

	map["int8"] = Int8;
	map["int16"] = Int16;
	map["int32"] = Int32;
	map["float"] = _Float;
	map["double"] = _Double;
	return map;
}

eOperandType			AVM::parse_type(std::string type) {
	const auto & got =  _typemap.find(type);
	if (got != _typemap.end()) return got->second;
	else throw std::invalid_argument(std::string("Unknown type: ``")
									 + type + "\"!");
}

void					AVM::readlines(std::istream & input) {
	int			line_nbr = 0;
	std::string	tmp;

	while (input.good() && !input.eof())
	{
		if (_from_tty) std::cout << ++line_nbr << ": ";
		std::getline(input, tmp);
		if (std::regex_match(tmp, std::regex("^\\s*;;.*$")))
			break ;
		_lines.push_back(tmp);
		tmp.clear();
	}
}

void	AVM::pop(void) {
	if (_stack.size() < 1)
		throw std::underflow_error("pop: Empty stack!");
	std::unique_ptr< const IOperand >(_stack.back());
	_stack.pop_back();
}

void	AVM::dump(void) {
    for (const auto & op : _stack)
		std::cout << op->toString() << std::endl;
}

void	AVM::add(void) {
	if (_stack.size() < 2)
		throw std::logic_error("add: Less then two operands on the stack!");
	std::unique_ptr< const IOperand > op2(_stack.back());
	_stack.pop_back();
	std::unique_ptr< const IOperand > op1(_stack.back());
	_stack.pop_back();
	_stack.push_back(*op1 + *op2);
}

void	AVM::sub(void) {
	if (_stack.size() < 2)
		throw std::logic_error("sub: Less then two operands on the stack!");
	std::unique_ptr< const IOperand > op2(_stack.back());
	_stack.pop_back();
	std::unique_ptr< const IOperand > op1(_stack.back());
	_stack.pop_back();
	_stack.push_back(*op1 - *op2);
}

void	AVM::mul(void) {
	if (_stack.size() < 2)
		throw std::logic_error("mul: Less then two operands on the stack!");
	std::unique_ptr< const IOperand > op2(_stack.back());
	_stack.pop_back();
	std::unique_ptr< const IOperand > op1(_stack.back());
	_stack.pop_back();
	_stack.push_back(*op1 * *op2);
}

void	AVM::div(void) {
	if (_stack.size() < 2)
		throw std::logic_error("div: Less then two operands on the stack!");
	std::unique_ptr< const IOperand > op2(_stack.back());
	_stack.pop_back();
	std::unique_ptr< const IOperand > op1(_stack.back());
	_stack.pop_back();
	_stack.push_back(*op1 / *op2);
}

void	AVM::mod(void) {
	if (_stack.size() < 2)
		throw std::logic_error("mod: Less then two operands on the stack!");
	std::unique_ptr< const IOperand > op2(_stack.back());
	_stack.pop_back();
	std::unique_ptr< const IOperand > op1(_stack.back());
	_stack.pop_back();
	_stack.push_back(*op1 % *op2);
}

void	AVM::print(void) {
	if (_stack.empty())
		throw std::logic_error("print: Empty stack!");
	if (_stack.back()->getType() != Int8)
		throw std::logic_error("print: Can`t print operand of non int8 type!");
	std::cout << dynamic_cast< const TOperand< int8_t > & >(*_stack.back()).getValue();
}

void	AVM::ft_exit(void) {
	_exit = 1;
}

void	AVM::push(eOperandType type, std::string value) {
	_stack.push_back(_factory.createOperand(type, value));
}

void	AVM::ft_assert(eOperandType type, std::string value) {
	std::unique_ptr< const IOperand >	ass(_factory.createOperand(type, value));
	if (_stack.empty())
		throw std::logic_error("assert: Empty stack!");
	auto 								peak = _stack.back();
	if (type != peak->getType())
		throw std::logic_error("assert: Types differ!");
	else if (ass->getPrecision() != peak->getPrecision())
		throw std::logic_error("assert: Precision differ!");
	else if (!(*peak == *ass))
		throw std::logic_error("assert: Value differ!");
}

void	AVM::exec_line(std::string cmd, std::string type, std::string value)
{
	std::transform(cmd.begin(), cmd.end(),
				   cmd.begin(), (int (*)(int))std::tolower);
	std::transform(type.begin(), type.end(),
				   type.begin(), (int (*)(int))std::tolower);
	const auto	smpl_got = _smpl_cmdmap.find(cmd);
	const auto	arg_got = _arg_cmdmap.find(cmd);
	void	(AVM::*smpl_cmd)(void) = (smpl_got != _smpl_cmdmap.end()
									  ? smpl_got->second : nullptr);
	void	(AVM::*arg_cmd)(eOperandType, std::string) =
		(arg_got != _arg_cmdmap.end() ? arg_got->second : nullptr);

	if (cmd == "push") return push(parse_type(type), value);

	if (!smpl_cmd && !arg_cmd)
		throw std::invalid_argument(std::string("Unknown instruction: ``")
									 + cmd + "\"!");
	else if (smpl_cmd && type.size())
		throw std::invalid_argument(std::string("Instruction ``") + cmd
									+ "\" do not require an argument!");
	else if (arg_cmd && !type.size())
		throw std::invalid_argument(std::string("Instruction ``") + cmd
									+ "\" require an argument!");
	else if	(smpl_cmd) (this->*smpl_cmd)();
	else (this->*arg_cmd)(parse_type(type), value);
}

AVM::AVM() : _from_tty(isatty(fileno(stdin))), _exit(false) {
	readlines(std::cin);
}

AVM::AVM( std::string file_path ) : _from_tty(false), _exit(false) {
	std::filebuf	file;
	if (file.open(file_path, std::ios::in))
	{
		std::istream in(&file);
		readlines(in);
	}
	file.close();
}

int		AVM::run( void ) {
	int			st = 0;
    std::smatch	m;
	int			line_nbr = 0;
    std::regex	regex("^\\s*([[:alpha:]]+)(\\s+([[:alnum:]]+)\\s*"
					  "\\(\\s*([+|-]?[0-9]+(\\.[0-9]+)?)\\s*\\))?\\s*(;.*)?$");

    for (const auto &line : _lines) {
		line_nbr++;
		if (_exit)
			break ;
		if (!std::regex_match(line, std::regex("^\\s*(;.*)?")))
		{
			try {
				if (std::regex_match(line, m, regex))
					exec_line(m[1].str(), m[3].str(), m[4].str());
				else throw std::invalid_argument ("Syntax error!");
			}
			catch (std::exception & e) {
				st = 1;
				std::cerr << "AVM: Line " << line_nbr << ": "
						  << e.what() << std::endl;
			}
		}
	}
	if (!_exit) throw std::logic_error("No exit statement!");
	return (st);
}

AVM::~AVM() {
	for (const auto & op : _stack)
		delete op;
}
