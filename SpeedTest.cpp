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
	cout << endl << "Loading..." << endl;
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start))/CLOCKS_PER_SEC;

	cout << "Collected " << rbt.size() << " ID numbers in " << duration << " seconds." << endl << endl;
    //Collected 3700000 ID numbers in 1.63783 seconds.
    
    //Leaving
    int i = 1;
	while(i < 6){
        int rand1 = rand() % 3700000;    
        if(rbt.Contains(rand1)){
            clock_t start = clock();
            rbt.Remove(rand1);
            clock_t stop = clock();
            double duration = (static_cast<double>(stop - start))/CLOCKS_PER_SEC;
            cout << "Remove #" << i << " took " << duration << " seconds." << endl;
            i++;
        }
    }
    cout << endl;

    //Joining
    i = 1;
    while(i < 6){
        int rand1 = rand();  
        if(!rbt.Contains(rand1)){
            clock_t start = clock();
            rbt.Insert(rand1);
            clock_t stop = clock();
            double duration = (static_cast<double>(stop - start))/CLOCKS_PER_SEC;
            cout << "Insert #" << i << " took " << duration << " seconds." << endl;
            i++;
        }
    }

    //The ultimate remove test
    for(int i = N-1; i > 0; i--){
        if(rbt.Contains(i)){
             rbt.Remove(i);
        }
    }
    cout << endl << "PASSED THE ULTIMATE TEST" << endl;

	return 0;
}



   
