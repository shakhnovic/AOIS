#ifndef logic_processing_h
#define logic_processing_h
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <math.h>
using namespace std;
bool is_operation(char);

bool is_operation(char current_sign){
    return (current_sign == '*' || current_sign == '+' || current_sign == '@' || current_sign == '=' || current_sign == '!'); 
}

int operations_priority(char current_sign){
    switch (current_sign)
    {
    case '!': return 5;
    case '*': return 4;
    case '+': return 3;
    case '@': return 2;
    case '=': return 1;
    case '(': return 0;
    case ')': return 0;
    }
    return -1;
}

int implication(int first, int second){
    if (first == 1 && second == 0)
        return 0;
    else 
        return 1;
}

int logic_not(int current){
    if (current == 0){
        return 1;
    }
    else 
        return 0;
}



pair<string, vector<char>> user_input_parser(string user_input){
    string result = "";
    stack<char> buffer;
    vector<char> variables;
    for (int iteration = 0; iteration < user_input.size(); iteration++){
        if (islower(user_input[iteration])){
            if (count(variables.begin(), variables.end(), user_input[iteration]) == 0){
                variables.push_back(user_input[iteration]);
            }
            result += user_input[iteration];
        }
        else if (is_operation(user_input[iteration])){
            if (buffer.size() > 0){
            while (operations_priority(buffer.top()) > operations_priority(user_input[iteration]))
            {
                result+=buffer.top();
                buffer.pop();
                if (buffer.size() == 0) break;
            }
            }
            buffer.push(user_input[iteration]);
        }
        else if (user_input[iteration] == ')'){
            while (buffer.top() != '('){
                result+=buffer.top();
                buffer.pop();
                }
            buffer.pop();
        }
        else if(user_input[iteration] == '('){
            buffer.push(user_input[iteration]);
        }
    }
    while (buffer.size() != 0){
        result+=buffer.top();
        buffer.pop();
    }
    pair <string, vector<char>> result_pair = {result, variables};
	return result_pair;
}

vector<vector <int>> table_of_truth_constructor(vector<char> variables){
    vector <vector <int>> result;
    for (int variations = 0; variations < pow(2, variables.size());variations++){
        vector<int> current_number_binary;
        int current_number_int = variations;
        for (int iterations = 0; iterations<variables.size();iterations++){
            current_number_binary.insert(current_number_binary.begin(), current_number_int%2);
            current_number_int = current_number_int /2;
        }
        result.push_back(current_number_binary);
    }
    return result;
}

void truth_table_output(vector<vector <int>> table_of_truth, vector<char> variables){
    for (int iteration = 0; iteration < variables.size(); iteration++){
        cout<<variables[iteration]<<' ';
    }
    cout<<"="<<endl;
    for (int iteration = 0; iteration < table_of_truth.size();iteration++){
        for (int subiteration = 0; table_of_truth[iteration].size() > subiteration; subiteration++){
            cout<<table_of_truth[iteration][subiteration]<<' ';
        }
        cout<<endl;
    }
}

string fill_with_variables(string parsed, vector<int> current_conditions, vector<char> variables){
    string result = "";
    for (int iteration = 0; iteration<parsed.size(); iteration++){
        if (islower(parsed[iteration])){
            for (int variable_index = 0; variable_index<variables.size(); variable_index++){
                if (parsed[iteration] == variables[variable_index]){
                    result+=to_string(current_conditions[variable_index]);
                    break;
                }
            }
        }
        else
            result+=parsed[iteration];
    }
    return result;
}

void reassignment(int& temp_top, int& temp_next, stack<int>& buffer){
    temp_top = buffer.top();
    buffer.pop();
    temp_next = buffer.top();
    buffer.pop();
}

int solve(string parsed){
	stack<int> buffer = {};
    for (int iteration = 0; iteration < parsed.size(); iteration++){
        int temp_top, temp_next;
        switch (parsed[iteration]){
        case '0': buffer.push(0);break;
        case '1': buffer.push(1);break;
        case '!':
            {
            temp_top = buffer.top();
            buffer.pop();
            buffer.push(logic_not(temp_top)); break;
            }
        case '@': 
            {
            reassignment(*&temp_top, *&temp_next, *&buffer);
            buffer.push(implication(temp_top, temp_next));break;
            }
        case '=':
            {
            reassignment(*&temp_top, *&temp_next, *&buffer);
            buffer.push(temp_top == temp_next);
            break;
            }
        case '*': 
            {
            reassignment(*&temp_top, *&temp_next, *&buffer);
            buffer.push(temp_top & temp_next);
            break;
            }
        case '+': 
            {
            reassignment(*&temp_top, *&temp_next, *&buffer);
			buffer.push(temp_top | temp_next);
            break;
            }
        default:
			break;
		}
	}
	return buffer.top();
}
#endif