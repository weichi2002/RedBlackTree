
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();

	rbt.Insert(30);

	cout << "rbt:" << rbt.ToPrefixString() << "" << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30); // leak here??

	rbt->Insert(15);
	cout << "rbt:" << rbt->ToPrefixString() << endl;


	assert(rbt->ToPrefixString() == " B30  R15 ");
	cout << "here" << endl;
	delete rbt;
	

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Left Right
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;

	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(60);
	rbt->Insert(69); // Right Right
	assert(rbt->ToPrefixString() == " B60  R30  R69 ");
	delete rbt;

	// cout << "here" << endl;

	rbt = new RedBlackTree(); 
	rbt->Insert(20);
	rbt->Insert(40);
	rbt->Insert(30); // Right Left
	assert(rbt->ToPrefixString() == " B30  R20  R40 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10);
	cout << "rbt inorder: " << rbt->ToInfixString() << endl;

	rbt->Insert(20);
	cout << "rbt inorder: " << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B10  B15  R20  B30 ");

	delete rbt;

	cout << "Testing Insert Fourth Node..." << endl;
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(11);
	cout << "rbt inorder: " << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B10  R11  B15  B30 ");

	delete rbt;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	cout << "TESTS MISSING" << endl << endl;
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(15);
	rbt->Insert(5);
	rbt->Insert(13);
	rbt->Insert(7);

	assert(rbt->ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt->ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt->ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	delete rbt;

	
	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(15);
	rbt->Insert(5);
	rbt->Insert(13);
	rbt->Insert(7);
	delete rbt;
	
	
	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(10);
	rbt->Insert(8);
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());
	

	cout << "PASSED!" << endl << endl;	
	cout << "destructor is called here??? " << endl;
}



void TestContains(){
	cout << "Testing Contains..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	assert(rbt->Contains(22));
	assert(rbt->Contains(5) == false);
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->GetMax() == 45);
	assert(rbt->GetMin() == 10);

	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestRemove(){
	cout << "Testing Delete..." << endl;

	RedBlackTree* rbt = new RedBlackTree();

	//root case
	// rbt->Insert(30);
	// rbt->Remove(30);

	// assert(rbt->ToInfixString() == "");

	//add more numbers to the tree
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	rbt->Insert(11);
	rbt->Insert(49);
	rbt->Insert(58);
	cout << endl << "RBT inorder: " << rbt->ToInfixString() << endl;


	//try to remove something that does not exist
	// rbt->Remove(0);

	//remove red leaf
	rbt->Remove(11);
	assert(rbt->ToInfixString() == " B10  R15  B25  B30  R45  B49  R58 ");

	//Sibling Red child and two black children
	rbt->Remove(15);
	cout << endl << "RBT inorder: " << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " R10  B25  B30  R45  B49  R58 ");

	cout << "PASSED!" << endl << endl;

	//remove root node with two black children
	rbt->Remove(30);
	cout << endl << "RBT inorder: " << rbt->ToInfixString() << endl;

	delete rbt;

}

int main(){

	TestSimpleConstructor();
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();
	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();
	TestRemove();

	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
