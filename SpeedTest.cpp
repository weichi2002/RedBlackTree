#include <cstdlib>
#include <ctime>
#include <iostream>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	cout << "Loading..." << endl;
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start))/CLOCKS_PER_SEC;

	cout << "Collected " << rbt.size() << " ID numbers in " << duration << " seconds." << endl;
	//Collected 3700000 ID numbers in 0.95178 seconds.

	// Your code goes here to simulate leaving / joining.

	int rand1 = rand() % 3700000;
	int rand2 = rand() % 3700000;
	int rand3 = rand() % 3700000;
	int rand4 = rand() % 3700000;
	int rand5 = rand() % 3700000;

    
  

	return 0;
}


/*
clock_t start1 = clock();
    rbt.Remove(rand1);
    clock_t stop1 = clock();
    
    clock_t start2 = clock();
    rbt.Remove(rand2);
    clock_t stop2 = clock();
    
    clock_t start3 = clock();
    rbt.Remove(rand3);
    clock_t stop3 = clock();
    
    clock_t start4 = clock();
    rbt.Remove(rand4);
    clock_t stop4 = clock();
    
    clock_t start5 = clock();
    rbt.Remove(rand5);
    clock_t stop5 = clock();
    
    clock_t start6 = clock();
    rbt.Insert(rand1);
    clock_t stop6 = clock();
    
    clock_t start7 = clock();
    rbt.Insert(rand2);
    clock_t stop7 = clock();
    
    clock_t start8 = clock();
    rbt.Insert(rand3);
    clock_t stop8 = clock();
    
    clock_t start9 = clock();
    rbt.Insert(rand4);
    clock_t stop9 = clock();
    
    clock_t start10 = clock();
    rbt.Insert(rand5);
    clock_t stop10 = clock();


    double duration1 = (static_cast<double>(stop1 - start1)) / CLOCKS_PER_SEC;
    double duration2 = (static_cast<double>(stop2 - start2)) / CLOCKS_PER_SEC;
    double duration3 = (static_cast<double>(stop3 - start3)) / CLOCKS_PER_SEC;
    double duration4 = (static_cast<double>(stop4 - start4)) / CLOCKS_PER_SEC;
    double duration5 = (static_cast<double>(stop5 - start5)) / CLOCKS_PER_SEC;
    double duration6 = (static_cast<double>(stop6 - start6)) / CLOCKS_PER_SEC;
    double duration7 = (static_cast<double>(stop7 - start7)) / CLOCKS_PER_SEC;
    double duration8 = (static_cast<double>(stop8 - start8)) / CLOCKS_PER_SEC;
    double duration9 = (static_cast<double>(stop9 - start9)) / CLOCKS_PER_SEC;
    double duration10 = (static_cast<double>(stop10 - start10)) / CLOCKS_PER_SEC;

    int i = 1;
    cout << "Insert: " << endl;
    cout << "Duration " << i << ": " << duration1 << endl; i++;
    cout << "Duration " << i << ": " << duration2 << endl; i++;
    cout << "Duration " << i << ": " << duration3 << endl; i++;
    cout << "Duration " << i << ": " << duration4 << endl; i++;
    cout << "Duration " << i << ": " << duration5 << endl; i++;

	
    i = 1;
    cout << endl << "Remove: " << endl;
    cout << "Duration " << i << ": " << duration6 << endl; i++;
    cout << "Duration " << i << ": " << duration7 << endl; i++;
    cout << "Duration " << i << ": " << duration8 << endl; i++;
    cout << "Duration " << i << ": " << duration9 << endl; i++;
    cout << "Duration " << i << ": " << duration10 << endl; i++;
    */