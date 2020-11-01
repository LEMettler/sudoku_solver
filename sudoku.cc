#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//a triplet of position and last value for the queue of visited fields
struct queue_element{
	int i;
	int j;
	int last;
};

void update_current_element(queue_element& current, const queue_element& update){
	current.i = update.i;
	current.j = update.j;
	current.last = update.last;
}

//fill the 2d-array with given values of the sudoku from a txt
void readFile(int s[][9]){
	cout << "Sudoku-File: ";
	string name;
	cin >> name;
	ifstream file;
	file.open(name);
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			file >> s[i][j];
		}
	}
	file.close();
}

//check the i-row for "num" entries
bool testRow(int s[][9], int i, int j, int num){
	for(int x=0; x<9; x++){
		if(x != j){
			if(s[i][x] == num){
				return false;
			}
		}
	}
	return true;
}

//check the j-column for "num" entries
bool testColumn(int s[][9], int i, int j, int num){
	for(int x=0; x<9; x++){
		if(x != i){
			if(s[x][j] == num){
				return false;
			}
		}
	}
	return true;
}

//check 3x3 box for num entries
bool testBox(int s[][9], int i, int j, int num){
	int x = int(i/3)*3;
	int y = int(j/3)*3; //s[x][y] is the top left entry in relevant box
	for(int u=x; u<x+3; u++){
		for(int v=y; v<y+3; v++){
			if(u != i && v != j){
				if(s[u][v] == num){
					return false;
				}
			}
		}
	}
	return true;
}

bool testNumber(int s[][9], int i, int j, int num){
	return testRow(s, i, j, num) && testColumn(s, i, j, num) && testBox(s, i, j, num) && num != 0;
}

//find the next position to fill (contains a 0)
//when all positions are filled return -1 as i
queue_element nextPosition(int s[][9]){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if(s[i][j] == 0){
				queue_element elem;
				elem.i = i;
				elem.j = j;
				elem.last = 0;
				return elem;
			}
		}
	}
	queue_element elem;
	elem.i = -1;
	elem.j = -1;
	elem.last = 0;
	return elem;
}
//console representation
void printField(int s[][9]){
	cout << "_________________________" << endl;
	for(int i=0; i<9; i++){
		cout << "| ";
		for(int j=0; j<9; j++){
			cout << s[i][j] << " ";
			if(j%3 ==2){
				cout << "| ";
			}
		}
		cout << endl;
		if(i%3 == 2){
			cout << "-------------------------" << endl;
		}
	}
}


//--------------------main---------------------------
int main(){
	int s[9][9];
	readFile(s);
	printField(s);
	
	//queue to save the visited positions for backtracking
	vector<queue_element> queue;
	//contains current positions (i, j) and last value (intially 0)
	queue_element current_element;
	update_current_element(current_element, nextPosition(s));
	
	//loop until all positions contain a valid solution
	while(current_element.i != -1){
		bool found = false;
		int n = 0;
		//test numbers 1-9, start with 1 intially or last valid value+1 when backtracking
		for(int num=current_element.last+1; num<10; num++){
			found = testNumber(s, current_element.i, current_element.j, num);
			if(found){
				n = num;
				break;
			}
		}
		s[current_element.i][current_element.j] = n;
		current_element.last = n;
		if(found){
			//when a new solution for this position has been found
			//add it to the queue and find the next position
			queue.push_back(current_element);
			update_current_element(current_element, nextPosition(s));
		}else{
		//no solution was found here, therefore backtrack to the last position
			update_current_element(current_element, queue.back());
			queue.pop_back();
		}
	}
	
	//output the found solution for the sudoku
	cout << "Solution:" << endl;
	printField(s);
	return 0;
}
