all:
	g++ -std=c++14 -Wall -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt
run: 
	./rbt

try: all run
