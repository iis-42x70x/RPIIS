#include "boolean.h"

int main() {
    boolean generator;
    if (!generator.readInputFromFile("input.txt")) {
        cout << "Error reading input file" << endl;
        return 1;
    }

    //cout << "Loaded " << generator.elementCount << " elements" << endl;

    generator.generateBoolean();
    generator.printResult();

    if (!generator.writeOutputFile("output.txt")) {
        cout << "Error writing output file" << endl;
        return 1;
    }
    return 0;
}