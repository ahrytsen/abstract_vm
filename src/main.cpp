// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/27 03:18:45 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/13 17:37:16 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <AVM.hpp>
#include <IOperand.hpp>
#include <TOperand.hpp>

int		main(int ac, char **av)
{
	int		st;
	AVM	*	abstract_vm;

	if (ac < 2)
	{
		abstract_vm = new AVM();
		st = abstract_vm->run();
		delete abstract_vm;
		return (st);
	}
	for (int i = 1; i < ac; i++)
	{
		abstract_vm = new AVM(av[i]);
		abstract_vm->run();
		delete abstract_vm;
	}
}
