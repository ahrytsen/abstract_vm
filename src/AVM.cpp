// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AVM.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/09/12 17:00:56 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/17 20:43:35 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <AVM.hpp>

const OFactory &	AVM::_factory = OFactory::getInstance();
const AVM::cmdMap	AVM::_cmdmap = AVM::init_cmdmap();
const AVM::tpMap	AVM::_typemap = AVM::init_typemap();

const AVM::cmdMap	AVM::init_cmdmap(void) {
	AVM::cmdMap	map;

	map["pop"] = &AVM::pop;
	map["dump"] = &AVM::dump;
	map["add"] = &AVM::add;
	map["sub"] = &AVM::sub;
	map["mul"] = &AVM::mul;
	map["div"] = &AVM::div;
	map["mod"] = &AVM::mod;
	map["print"] = &AVM::print;
	map["push"] = reinterpret_cast<void (AVM::*)()>(&AVM::push);
	map["assert"] = reinterpret_cast<void (AVM::*)()>(&AVM::assert);
	return map;
}

const AVM::tpMap	AVM::init_typemap(void) {
	AVM::tpMap	map;

	map["int8"] = Int8;
	map["int16"] = Int16;
	map["int32"] = Int32;
	map["float"] = _Float;
	map["double"] = _Double;
	return map;
}

eOperandType	AVM::parse_type(std::string type) {
	if (type == "int8") return Int8;
	else if (type == "int16") return Int16;
	else if (type == "int32") return Int32;
	else if (type == "float") return _Float;
	else if (type == "double") return _Double;
	else throw std::invalid_argument(std::string("Unknown type: ") + type + '!');
}

void	AVM::readlines(std::istream & input) {
	std::string	tmp;

	while (input.good() && !input.eof())
	{
		std::getline(input, tmp);
		if (std::regex_match(tmp, std::regex("^\\s*;;.*$")))
			break ;
		_lines.push_back(tmp);
		tmp.clear();
	}
}

void	AVM::pop(void) {
	if (_stack.empty())
		throw std::underflow_error("Pop omn empty stack!");
	_stack.pop_back();
}

void	AVM::dump(void) {
    for (const auto & op : _stack)
		std::cout << op->toString() << std::endl;
}

void	AVM::add(void) {

}

void	AVM::sub(void) {

}

void	AVM::mul(void) {

}

void	AVM::div(void) {

}

void	AVM::mod(void) {

}

void	AVM::print(void) {

}

void	AVM::push(eOperandType type, std::string value) {
	_stack.push_back(_factory.createOperand(type, value));
}

void	AVM::assert(eOperandType type, std::string value) {
	(void)type;
	(void)value;
}

void	AVM::exec_line(std::string cmd)
{
	if (cmd == "pop") return pop();
	else if (cmd == "dump") return dump();
	else if (cmd == "add") return add();
	else if (cmd == "sub") return sub();
	else if (cmd == "mul") return mul();
	else if (cmd == "div") return div();
	else if (cmd == "mod") return mod();
	else if (cmd == "print") return print();
	else if (cmd == "exit") exit(0);
	else throw std::invalid_argument(std::string("Unknown instruction: ") + cmd + '!');
}

void	AVM::exec_line(std::string cmd, std::string type, std::string value)
{
	if (cmd == "push") return push(parse_type(type), value);
	else if (cmd == "assert") return assert(parse_type(type), value);
	else throw std::invalid_argument(std::string("Unknown instruction: ") + cmd + '!');
}

AVM::AVM() : _exit(false) {
	readlines(std::cin);
}

AVM::AVM( std::string file_path ) : _exit(false) {
	std::filebuf	file;
	if (file.open(file_path, std::ios::in))
	{
		std::istream in(&file);
		readlines(in);
	}
	file.close();
}

int		AVM::run( void ) {
	"^\s*([[:alpha:]]+)(\s+([[:alnum:]]+)\s*\(\s*([+|-]?[0-9]+(\.[0-9]+)?)\s*\))?\s*(;.*)?$"
    std::regex	regex("^\\s*((pop|dump|add|sub|mul|div|mod|print|exit)"
					  "|((push|assert)\\s+(int8|int16|int32|float|double)"
					  "\\s*(\\(\\s*([+|-]?[0-9]+(\\.[0-9]+)?)\\s*\\))))\\s*(;.*)?$");
    std::smatch	m;
	int			line_nbr = 0;
    for (const auto &line : _lines) {
		line_nbr++;
		if (_exit)
			break ;
		if (!std::regex_match(line, std::regex("^\\s*(;.*)?")))
		{
			try {
				if (std::regex_match(line, m, regex)) {
					if (m[3] != "")
						exec_line(m[4].str(), m[5].str(), m[7].str());
					else
						exec_line(m[2].str());
				}
				else throw std::invalid_argument ("Syntax error!");
			}
			catch (std::exception & e) { std::cerr << "AVM: Line " << line_nbr << ": "
												   << e.what() << std::endl; }
		}
	}
	return 1;
}

AVM::~AVM() {
}
