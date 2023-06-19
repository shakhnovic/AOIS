#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

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
        case '!': buffer.pop();
            {
            int temp_top = buffer.top();buffer.push(!temp_top); break;
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
            buffer.push(temp_top && temp_next);
            break;
            }
        case '+': 
            {
            reassignment(*&temp_top, *&temp_next, *&buffer);
            buffer.push(temp_top || temp_next);
            break;
            }
        default:
            break;
        }
    }
    return buffer.top();
}

vector<vector<int>> full_table_of_truth_constructor(vector<vector <int>> table_of_truth, pair<string, vector<char>> parsed_couple){
    for (int variation = 0; variation < table_of_truth.size(); variation++){
        string filled_with_variables = fill_with_variables(parsed_couple.first, table_of_truth[variation], parsed_couple.second);
        table_of_truth[variation].push_back(solve(filled_with_variables));
    }
    return table_of_truth;
}

pair<vector<vector<int>>, vector<vector<int>>> sknf_and_sdnf_divider(vector<vector <int>> table_of_truth){
    vector<vector<int>> sdnf_combinations, sknf_combinations;
    vector<int> buffered_combination;
    for (int iterations = 0; iterations < table_of_truth.size(); iterations++){
        buffered_combination = table_of_truth[iterations];
        buffered_combination.pop_back();
        if (table_of_truth[iterations][table_of_truth[iterations].size()-1] == 1){
            sdnf_combinations.push_back(buffered_combination);
        }
        else
        {
            sknf_combinations.push_back(buffered_combination);
        }
    }
    pair<vector<vector<int>>, vector<vector<int>>> sknf_and_sdnf = {sknf_combinations, sdnf_combinations};
    return sknf_and_sdnf;
}

void sknf_visualisation(vector<vector<int>> sknf, vector<char> variables){
    for (int iteration = 0; iteration<sknf.size(); iteration++){
        cout<<'(';
        int current_variable = 0;
        for (int subiteration = 0;subiteration<sknf[iteration].size();subiteration++){
            if (sknf[iteration][subiteration] == 0){
                cout<<variables[current_variable];
            }
            else 
                cout<<'!'<<variables[current_variable];
            if ((sknf[iteration].size()-1) == subiteration)
                continue;
            else
                cout<<'+';
            current_variable++;
        }
        if ((sknf.size()-1) == iteration)
            cout<<")";
        else
            cout<<")*";
    }
    cout<<endl;
}

void sdnf_visualisation(vector<vector<int>> sdnf, vector<char> variables){
    for (int iteration = 0; iteration<sdnf.size(); iteration++){
        cout<<'(';
        int current_variable = 0;
        for (int subiteration = 0;subiteration<sdnf[iteration].size();subiteration++){
            if (sdnf[iteration][subiteration] == 1){
                cout<<variables[current_variable];
            }
            else 
                cout<<'!'<<variables[current_variable];
            if ((sdnf[iteration].size()-1) == subiteration)
                continue;
            else
                cout<<'*';
            current_variable++;
        }
        if ((sdnf.size()-1) == iteration)
            cout<<")";
        else
            cout<<")+";
    }
    cout<<endl;
}

int binary_to_int(vector<int> input){
    int result = 0, counter = 0;
    for (int iteration = input.size()-1; iteration>=0; iteration--){
        if (input[iteration] == 1){
            result+=pow(2, counter);
        }
        counter++;
    }
    return result;
}

void numbers_outputs(vector<vector<int>> table_of_truth, vector<vector<int>> sknf, vector<vector<int>> sdnf){
    int index_int = 0, power = 0;
    for (int iteration = 0; iteration < table_of_truth.size(); iteration++){
        if (table_of_truth[iteration][table_of_truth[iteration].size()-1] == 1){
            index_int+=pow(2, power);
            power++;
        }
    }
    cout<<"index:"<<index_int<<endl;
    cout<<"Sknf decimal form = *( ";
    for (int iteration = sknf.size()-1; iteration>=0; iteration--){
        cout<<binary_to_int(sknf[iteration])<<" ";
    }
    cout<<")"<<endl<<"Sdnf decimal form = +( ";
    for (int iteration = 0; iteration < sdnf.size(); iteration++){
         cout<<binary_to_int(sdnf[iteration])<<" ";
    }
    cout<<")"<<endl;
}

int main(){
    string user_input;
    while (user_input !=" "){
    cout<<"Input expression (example: (a+(b*(c=b))):"<<endl;
    cin>>user_input;
    pair<string, vector<char>> parsed_couple = user_input_parser(user_input);
    cout<<" \n"<<parsed_couple.first<<"\n";
    vector<vector <int>> table_of_truth = table_of_truth_constructor(parsed_couple.second);
    table_of_truth = full_table_of_truth_constructor(table_of_truth, parsed_couple);
    pair <vector<vector<int>>, vector<vector<int>>> sknf_and_sdnf = sknf_and_sdnf_divider(table_of_truth);
    truth_table_output(table_of_truth, parsed_couple.second);
    sknf_visualisation(sknf_and_sdnf.first, parsed_couple.second);
    sdnf_visualisation(sknf_and_sdnf.second, parsed_couple.second);
    numbers_outputs(table_of_truth, sknf_and_sdnf.first, sknf_and_sdnf.second);
    }
}