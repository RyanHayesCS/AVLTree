//Ryan Hayes
//Project 4
//Fall 2015
//Wheel of Lies

#include "LCMap.h"

//#include <functional>
//#include <string>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	/*LCMap<int, int> map2;
	
	map2.insert(50, 1);
	map2.insert(25, 2);
	map2.insert(75, 3);
	map2.insert(15, 4);
	map2.insert(40, 5);
	map2.insert(60, 6);
	map2.insert(80, 7);
	map2.insert(10, 8);
	map2.insert(20, 9);
	map2.insert(35, 10);
	map2.insert(45, 11);
	map2.insert(65, 12);
	map2.insert(12, 13);
	map2.insert(18, 14);

	if(map2.height(50) != 4 || map2.height(25) != 3 || map2.height(75) != 2 || map2.height(15) != 2 || map2.height(40) != 1  
		|| map2.height(60) != 1 || map2.height(80) != 0 || map2.height(10) != 1 || map2.height(20) != 1 
		|| map2.height(35) != 0 || map2.height(45) != 0 || map2.height(65) != 0 || map2.height(12) != 0 
		|| map2.height(18) != 0)
	{
		std::cout << "FAILED map2 inserts" << std::endl;
	} 
	else
	{
		std::cout << "PASSED map2 inserts" << std::endl;
	}
	
	map2.erase(75);	
	
	if(map2.height(25) != 3 || map2.height(50) != 2 || map2.height(15) != 2 || map2.height(10) != 1
		|| map2.height(20) != 1 || map2.height(40) != 1 || map2.height(65) != 1 || map2.height(12) != 0
		|| map2.height(18) != 0 || map2.height(35) != 0 || map2.height(45) != 0 || map2.height(60) != 0
		|| map2.height(80) != 0)
	{
		std::cout << "FAILED map2 erase" << std::endl;
	}
	else
	{
		std::cout << "PASSED map2 erase" << std::endl;
	}

	LCMap<int, int> map3;
	
	map3.insert(21, 21);
	map3.insert(10, 10);
	map3.insert(35, 35);
	map3.insert(23, 23);
	map3.insert(40, 40);
	map3.insert(45, 45);
	map3.insert(8, 8);
	map3.insert(5, 5);
	map3.insert(60, 60);
	
	if(map3.height(35) != 3 || map3.height(21) != 2 || map3.height(40) != 0 || map3.height(8) != 1
		|| map3.height(23) != 0 || map3.height(45) != 1 || map3.height(5) != 0 || map3.height(10) != 0 || map3.height(60) != 0)
	{
		std::cout << "FAILED outside inserts map3" << std::endl;
	}
	else
	{
		std::cout << "PASSED map3 outside inserts" << std::endl;
	}
		
	LCMap<int, int> map4;

        map4.insert(21, 21);
        map4.insert(10, 10);
        map4.insert(35, 35);
        map4.insert(25, 25);
        map4.insert(40, 40);
        map4.insert(37, 37);
        map4.insert(38, 38);
        map4.insert(23, 23);
        map4.insert(22, 22);
	map4.insert(28, 28);

        if(map4.height(21) != 1 || map4.height(10) != 0 || map4.height(35) != 3 || map4.height(25) != 1
                || map4.height(40) != 0 || map4.height(37) != 0 || map4.height(38) != 1 || map4.height(23) != 2
		|| map4.height(22) != 0 || map4.height(28) != 0)
        {
                std::cout << "FAILED inside inserts map4" << std::endl;
        }
        else
        {
                std::cout << "PASSED map4 inside inserts" << std::endl;
        }*/
	
	   // AVL Tests (add height and iterator tests)
   LCMap<string, int> stringMap;

   stringMap["m"] = 60;
   stringMap.insert("n", 50);
   stringMap.insert("o", 30);
   stringMap["a"] = 30;
   stringMap["b"] = 12;
   stringMap["p"] = 45;

   LCMap<int,string> avlMap;
   // outside inserts
   // (a)
   avlMap.insert(21,"21");
   avlMap[10] =  "10";
   avlMap[35] = "35";
   avlMap.insert(23, "23");
   avlMap.insert(40, "40");
   avlMap[45] = "45";

   // (b)
   avlMap[8] = "8";
   avlMap[5] = "5";

   // (c)
   avlMap.insert(60, "60");

   const int OUT_KEY_COUNT = 9;
   int outside_keys[OUT_KEY_COUNT] = {5, 8, 10, 21, 23, 35, 40, 45, 60};
   string outside_values[OUT_KEY_COUNT] = {"5", "8", "10", "21", "23", "35", "40", "45", "60"};
   int outside_heights[OUT_KEY_COUNT] = {0, 1, 0, 2, 0, 3, 0, 1, 0};
   int i = 0;
   while( i < OUT_KEY_COUNT &&
      avlMap[outside_keys[i]] == outside_values[i] &&
      avlMap.height(outside_keys[i]) == outside_heights[i] ){
     i++;
   }
   //avlMap.printTree();
   if( i < OUT_KEY_COUNT ){
     // TEST
     cout << "key is: " << outside_keys[i] << " value is: " << avlMap[outside_keys[i]] << " value should be: " << outside_values[i] << endl;
     cout << "height is: " << avlMap.height(outside_keys[i]) << " height should be: " << outside_heights[i] << endl;
     // END TEST
     cout << "xxx FAILED xxx: outside insert test" << endl;
   }else{
     cout << "PASSED: outside insert test" << endl;
   }
	
    LCMap<int, int> map4;

    map4[21] = 21;
    map4.insert(10, 10);
    map4.insert(35, 35);
    map4.insert(25, 25);
    map4[40] = 40;
    map4.insert(37, 37);
    map4.insert(38, 38);
    map4.insert(23, 23);
    map4[22] = 22;
    map4[28] = 28;

        if(map4.height(21) != 1 || map4.height(10) != 0 || map4.height(35) != 3 || map4.height(25) != 1
                || map4.height(40) != 0 || map4.height(37) != 0 || map4.height(38) != 1 || map4.height(23) != 2
                || map4.height(22) != 0 || map4.height(28) != 0)
        {
                std::cout << "FAILED inside inserts map4" << std::endl;
        }
        else
        {
                std::cout << "PASSED map4 inside inserts" << std::endl;
        }

	return 0;
}

