#include <iostream>
#include "forward_list.h"

#include <vector>

void main()
{
	forward_list fw_list = {3, 5, 8, 13, 21};
	/*for (int i = 0; i < 10; i++) {
		fw_list.push_front(i);
		fw_list.debug();
	}
	*/
	forward_list::iterator it = fw_list.begin(),
		end = fw_list.end();
	while (it != end) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
	
	fw_list.push_back(133);
	fw_list.debug();
	fw_list.pop_front();
	fw_list.debug();
	fw_list.pop_back();
	fw_list.debug();
	fw_list.erase(3);
	fw_list.debug();
	try {
		fw_list.erase(3);
		fw_list.debug();
	}
	catch (std::exception e) {
		std::cerr << std::endl << e.what() << std::endl << std::endl;
	}
	fw_list.erase_value(8);
	fw_list.debug();
	fw_list.erase_value(13);
	fw_list.debug();
	fw_list.erase_value(5);
	fw_list.debug();
}