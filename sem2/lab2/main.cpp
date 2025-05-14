#include <iostream>
#include <fstream>
#include <variant>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct various;
using Set = set<various>;
using Tuple = vector<various>;
using Element = variant<int, Set, Tuple>;

struct various {
    Element value;
    bool operator<(const various& element) const {
        return value < element.value;
    }
};

struct Parser {
    string input;
    int pos = 0;
    
    void ignore_w() {
        while(pos < input.size() && isspace(input[pos])) pos++;
    }
    
    various parse_element() {
        ignore_w();
        if(pos >= input.size()) {
            throw runtime_error("out of bounds");
        }
        if(input[pos] == '{') return parse_set();
        if(input[pos] == '<') return parse_tuple();
        if(isdigit(input[pos]) || (input[pos] == '-' && pos+1 < input.size() && isdigit(input[pos+1]))) 
            return parse_int();
        throw runtime_error("Unexpected character");
    }
    
    various parse_set() {
        pos++;
        Set set;
        while(true) {
            ignore_w();
            if(pos < input.size() && input[pos] == '}') {
                pos++;
                break;
            }
            set.insert(parse_element());
            ignore_w();
            if(pos < input.size() && input[pos] == ',') pos++;
        }
        return various{set};
    }
    
    various parse_tuple() {
        pos++;
        Tuple tuple;
        while(true) {
            ignore_w();
            if(pos < input.size() && input[pos] == '>') {
                pos++;
                break;
            }
            tuple.push_back(parse_element());
            ignore_w();
            if(pos < input.size() && input[pos] == ',') pos++;
        }
        return various{tuple};
    }
    
    various parse_int() {
        int start = pos;
        if(input[pos] == '-') pos++;
        while(pos < input.size() && isdigit(input[pos])) pos++;
        return various{stoi(input.substr(start, pos-start))};
    }
    
public:
    various parse(const string& str) {
        input = str;
        pos = 0;
        ignore_w();
        if(pos >= input.size()) throw runtime_error("Empty input");
        // либо сет либо кортеж
        if(input[pos] == '{') {
            various result = parse_set();
            ignore_w();
            if(pos != input.size()) throw runtime_error("incorrect input");
            return result;
        } else if(input[pos] == '<') {
            various result = parse_tuple();
            ignore_w();
            if(pos != input.size()) throw runtime_error("incorrect input");
            return result;
        } else {
            throw runtime_error("Input must start with '{' or '<'");
        }
    }
};

void writeVariousToFile(ofstream& outfile, const various& data) {
    if(holds_alternative<int>(data.value)) {
        outfile << get<int>(data.value);
    }
    else if(holds_alternative<Tuple>(data.value)) {
        outfile << '<';
        Tuple tuple = get<Tuple>(data.value);
        for(int i = 0; i < tuple.size(); i++) {
            writeVariousToFile(outfile, tuple[i]);
            if(i < tuple.size()-1) outfile << ", ";
        }
        outfile << '>';
    }
    else if(holds_alternative<Set>(data.value)) {
        outfile << '{';
        Set set = get<Set>(data.value);
        int count = 0;
        for(auto item : set) {
            writeVariousToFile(outfile, item);
            if(++count != set.size()) outfile << ", ";
        }
        outfile << '}';
    }
}

void generateSubsets(vector<various>& elements, int n, int index, vector<various>& current, set<Set>& res) {
    if(current.size() == n) {
        Set subset(current.begin(), current.end());
        res.insert(subset);
        return;
    }
    if(index == elements.size()) return;
    
    current.push_back(elements[index]);
    generateSubsets(elements, n, index+1, current, res);
    current.pop_back();
    generateSubsets(elements, n, index+1, current, res);
}

set<Set> getAllSubsets(Set& input, int n) {
    set<Set> res;
    vector<various> elements(input.begin(), input.end());
    vector<various> current;
    
    generateSubsets(elements, n, 0, current, res);
    return res;
}

int main() {
    ifstream inputFile("input.txt");
    if(!inputFile) {
        cout << "file not opened" << endl;
        return 1;
    }
    string stringvariant;
    getline(inputFile, stringvariant);
    inputFile.close();
    
    Parser parser;
    try {
        various MyData = parser.parse(stringvariant);
        
       
        if(holds_alternative<Set>(MyData.value)) {
            Set inputSet = get<Set>(MyData.value);
            
            std::cout << "enter n for subsets: ";
            int n;
            cin >> n;
            
            set<Set> allSubs = getAllSubsets(inputSet, n);
            
            ofstream outfile("output.txt");
            if(!outfile) {
                cout << "file open failure";
                return 1;
            }
            outfile << "all subsets of size " << n << ":\n";
            for(const auto& subsets : allSubs) {
                outfile << "{";
                for(auto& item : subsets) {
                    writeVariousToFile(outfile, item);
                    outfile << " ";
                }
                outfile << "}\n";
            }
            outfile.close();
        } else if(holds_alternative<Tuple>(MyData.value)) {
            cout << "Top level is a tuple. Subsets are only generated from sets." << endl;
           
        }
    } catch(const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}