all:
	g++ -std=c++14 -Wall -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt
	# g++ -std=c++14 -Wall -g RedBlackTree.cpp SpeedTest.cpp -o spd


run: 
	./rbt
	# ./spd

try: all run
