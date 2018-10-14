#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::fstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

int count = 1;
string first;
string last = " ";
string state;
char inpt = last.at(0);

vector<string> loadInstructions() {

	vector<string> instructions;

	string filename;
	cout << "\nRules File: ";
	getline(cin, filename);

	fstream fin(filename.c_str());
	if (!fin) {
		cout << "Error opening file " << filename << endl;
		return instructions;
	}

	string line;
	while (getline(fin, line)) {
		if (line.length() > 0 && line.at(0) != '#') {
			instructions.push_back(line);
		}
	}

	fin.close();
	return instructions;
}

vector<string> tokenizeString(string & str) {

	vector<string> tokens;

	int start = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str.at(i) == ',') {
			tokens.push_back(str.substr(start, i - start));
			start = i + 1;
		}
		else if (i == str.length() - 1) {
			tokens.push_back(str.substr(start));
		}
	}

	return tokens;

}

string getCurrentState(vector<string> & instructions) {
	return instructions[0];
}

string getInput(vector<string> & instructions) {
	return instructions[1];
}

string getNewState(vector<string> & instructions) {
	return instructions[2];
}

string getOutput(vector<string> & instructions) {
	return instructions[3];
}

string getMoveDirection(vector<string> & instructions) {
	return instructions[4];
}

//method to take the state and input of an instruction,
//find a matching transition rule, and make the
//appropriate transition.
string transition(string state_curr, char input, string first_curr, vector<string> & instructions) {
	size_t t = instructions.size();//Get the size of the instruction list.
	for (size_t i = 0; i < t; i++) {//Loop as long as you are less than the size of the instruction list.
		vector<string> rule = tokenizeString(instructions[i]);//Tokenize the current instruction.
		if (state_curr == rule[0] && input == rule[1].at(0)) {
			//update first, last, state, and inpt
			if (getMoveDirection(rule) == "R") {
				first.append(getOutput(rule));
				last.erase(last.begin());
				if (last == "") {
					last.append("_");
				}
				state = getNewState(rule);
				
			}
			else if (getMoveDirection(rule) == "L") {
				if (first == "") {
					first.append("_");
				}
				first.erase(first.back());
				if (last == "") {
					last.append("_");
				}
				last.insert(0, getOutput(rule));
				state = getNewState(rule);
			}
			string s = std::to_string(count) + ". ";
			s += first;
			s += "<";
			s += getNewState(rule);
			s += ">";
			s += last;
			++count;
			return s;
		}
	}
	return "error";
}



int main() {
	cout << "Turing Machine Simulator";
	// Get the rules
	vector<string> instructions = loadInstructions();

	//Get the input string
	string input;
	cout << "Input String: ";
	cin >> input;


	vector<string> ruleOneTokens = tokenizeString(instructions[0]);
	string start = ruleOneTokens[0];
	string accept = ruleOneTokens[1];
	string reject = ruleOneTokens[2];

	
	vector<string> programFlow;
	string begin = "0. <" + start + ">" + input;
	programFlow.push_back(begin);

	first = "";
	last = input;
	state = start;
	inpt = last.at(0);
	size_t i = 0;

	do {
		char c = last.at(0);
		string t = transition(state, c, first, instructions);
		programFlow.push_back(t);
		cout << "\n" + programFlow[i];
		i++;
	} while (state != accept && state != reject);
		
	char c = last.at(0);
	string t = transition(state, c, first, instructions);
	programFlow.push_back(t);
	cout << "\n" + programFlow[i];

	if (state == accept) {
		cout << "\nACCEPT";
	}
	else if (state == reject) {
		cout << "\nREJECT";
	}
	else if (state == "error") {
		cout << "\nERROR";
	}
		



	

	std::getchar();
	std::getchar();
}

