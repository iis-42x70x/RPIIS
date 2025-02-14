#include "Queue.hpp"
#include <iostream>

void printTakenValue(std::string res){
    if(res != ""){
        std::cout << "Retrieved value: " << res << std::endl;
    }
}

void test1(){
    Queue myQueue;
    printTakenValue(myQueue.takeNode());
    printTakenValue(myQueue.takeNode());
    printTakenValue(myQueue.takeNode());
}

void test2(){
    Queue myQueue;
    myQueue.addNode("He");
    myQueue.addNode("llo");
    myQueue.addNode(" ");
    myQueue.addNode("world!");
    myQueue.displayData();
    printTakenValue(myQueue.takeNode());
    printTakenValue(myQueue.takeNode());
    myQueue.displayData();
}

void test3(){
    Queue myQueue;
    myQueue.displayData();
    myQueue.addNode("Bam");
    myQueue.addNode("Bom");
    myQueue.displayData();
    printTakenValue(myQueue.takeNode());
    printTakenValue(myQueue.takeNode());
    printTakenValue(myQueue.takeNode());
    myQueue.displayData();
}

void joke(){
    Queue myQueue;
    myQueue.addNode("Knock-Knock");
    myQueue.addNode("Who's there?");
    myQueue.addNode("Nobel");
    myQueue.addNode("Nobel who?");
    myQueue.addNode("Nobel...that's why I knocked");
    myQueue.displayData();
}