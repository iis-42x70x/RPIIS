#include "library.h"

int main(){
    const char* filename = "input.txt"; 
    
    string str = readSets(filename);
    int numSets = checkString(str);

    if(numSets==-1){
	    cout << "Incorrect input!\n";
	    return 0;
    }
	
    vector<string> rawSets = parseString(numSets, str);
    vector<string>* sets = new vector<string>[numSets];

    for(int j = 0; j<numSets; j++){
	    sets[j] = addSets(rawSets[j]);
    }

    vector<string> Cross = cross(sets[0], sets[1]);
    for(int i = 2; i<numSets; i++)
	Cross = cross(Cross, sets[i]);

    //cout << "{";
    for(int i = 0; i<Cross.size(); i++)
	    cout << Cross[i] << ", ";
   // cout << "}\n";
    
    delete [] sets;
    return 0;
}
