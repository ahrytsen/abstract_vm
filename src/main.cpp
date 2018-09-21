// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/27 03:18:45 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/21 14:31:26 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <AVM.hpp>
#include <IOperand.hpp>
#include <TOperand.hpp>

int		main(int ac, char **av)
{
	int		st;
	AVM	*	abstract_vm = NULL;
	if (ac < 2)
	{
		try {
			abstract_vm = new AVM();
			st = abstract_vm->run();
		}
		catch (std::exception & e) {
			std::cout << "AVM: " << e.what() << std::endl;
			st = 1;
		}
		delete abstract_vm;
		abstract_vm = NULL;
	}
	for (int i = 1; i < ac; i++)
	{
		try {
			abstract_vm = new AVM(av[i]);
			st = abstract_vm->run();
		}
		catch (std::exception & e) {
			std::cout << "AVM(" << av[i] << "): " << e.what() << std::endl;
			st = 1;
		}
		delete abstract_vm;
		abstract_vm = NULL;
	}
	return (st);
}
