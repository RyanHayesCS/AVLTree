//Ryan Hayes
//Project 4
//Fall 2015
//Wheel of Lies

#include "LCMap.h"

//#include <functional>
//#include <string>
//#include <list>
#include <iostream>

int main()
{/*
	WheelOfLies game;

	game.play(); //start game of wheel of lies
	*/	

	LCMap<std::string,int> map;
	map["m"] = 87;
	map.insert("f", 17);
	map.insert("j", 1);
	map["r"] = 98;
	map["c"] = 113;
	map["p"] = 45;
	map["a"] = 78;
	map["y"] = 23;
	map["z"] = 90;
	
	//How the tree should look with avl rotations (left) and without (right) after series of inserts
	/*
			j                         m
		      /   \                     /   \
		     c     p                   f     r  
                    / \   / \                 / \   / \
                   a   f m   y               c   j p   y
                            / \             /           \
                           r   z           a             z */
	
	std::cout << "Node Heights and insert: ";
	if(map.height("r") != map.height("z") || map.height("p") != 2 || 
		map.height("a") != map.height("f"))
	{
		std::cout << "FAILED" << std::endl;
	}
	else
	{
		std::cout << "PASSED" << std::endl;
	}
	
	map.erase("j");//test a balance factor of -2 and a right child bf of 0
	//How the tree should look with avl rotations (left) and without (right) after erase("j")
	/*
		      m                           m
		    /   \                       /   \
                   c     y                     c     p
                  / \   / \                   / \     \
                 a   f p   z                 a   f     y
                        \                               \
                         r                               z  */

				
	map.erase("z");//test a balance factor of 2 and a left child bf of -1
	//How the tree should look with avl rotations (left) and without (right) after erase("z")
        /*
                      m                           m
                    /   \                       /   \
                   c     r                     c     y
                  / \   / \                   / \   / 
                 a   f p   y                 a   f p    
                                                    \                                             / 
                                                     r     */

	

	

	return 0;
}

