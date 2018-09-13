// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AVM.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/09/12 17:00:56 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/13 22:00:29 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <AVM.hpp>

const OFactory &	AVM::_factory = OFactory::getInstance();

void	AVM::readlines(std::istream & input) {
	std::string	tmp;

	while (input.good() && !input.eof())
	{
		std::getline(input, tmp);
		if (_interactive && !tmp.compare(0, 2, ";;"))
			break ;
		_lines.push_back(tmp);
		tmp.clear();
	}
}

AVM::AVM() : _interactive(true) {
	readlines(std::cin);
}

AVM::AVM( std::string file_path ) : _interactive(false) {
	std::filebuf	file;
	if (file.open(file_path, std::ios::in))
	{
		std::istream in(&file);
		readlines(in);
	}
	file.close();
}

int		AVM::run( void ) {
	for (std::string line : _lines)
		std::cout << line << std::endl;
	return (0);
}

AVM::~AVM() {
	//if (!_interactive)
}
