// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/27 03:18:45 by ahrytsen          #+#    #+#             //
//   Updated: 2018/09/11 22:33:39 by ahrytsen         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <IOperand.hpp>
#include <TOperand.hpp>

int		main()
{
	TOperand<int16_t>	lolka((int16_t)5, Int16);
	TOperand<float>	keka((float)3.5, _Float);

	try
	{
		const IOperand		*bek = lolka % keka;
	}
	catch(std::exception & e)
	{
		std::cout<< e.what() << std::endl;
	}


}
