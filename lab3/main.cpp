#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include "logic_processing.h"
#include "reductions.h"
using namespace std;

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

vector<vector<string>> variables_form_changer(vector<vector<int>> binary_form, vector<char> variables, bool sdnf){
    vector<vector<string>> result  = {};
    for (int iteration = 0;iteration < binary_form.size(); iteration++){
        vector<string> buffer_vector = {};
        for (int current_variable = 0; current_variable < variables.size();current_variable++){
            string current_string = "";
            if (sdnf){
                if (binary_form[iteration][current_variable] == 0){
                    current_string.push_back('!');
                    current_string.push_back(variables[current_variable]);
					buffer_vector.push_back(current_string);
                    }
				else{
                    current_string+=variables[current_variable];
					buffer_vector.push_back(current_string);
                }
			}
			else
			{
				if (binary_form[iteration][current_variable] == 1){
                    current_string.push_back('!');
                    current_string.push_back(variables[current_variable]);
					buffer_vector.push_back(current_string);}
				else{
                    current_string.push_back(variables[current_variable]);
                    buffer_vector.push_back(current_string);}
            }
        }
        result.push_back(buffer_vector);
    }
    return result;
}

int main(){
    string user_input;
    while (user_input !=" "){
    cout<<"Input expression (example: (a+(b*(c=b)))):"<<endl;
    cin>>user_input;
    pair<string, vector<char>> parsed_couple = user_input_parser(user_input);
    cout<<" \n"<<parsed_couple.first<<"\n";
    vector<vector <int>> table_of_truth = table_of_truth_constructor(parsed_couple.second);
    table_of_truth = full_table_of_truth_constructor(table_of_truth, parsed_couple);
    pair <vector<vector<int>>, vector<vector<int>>> sknf_and_sdnf = sknf_and_sdnf_divider(table_of_truth);
    truth_table_output(table_of_truth, parsed_couple.second);
    sknf_visualisation(sknf_and_sdnf.first, parsed_couple.second);
    sdnf_visualisation(sknf_and_sdnf.second, parsed_couple.second);
    vector<vector<string>> sknf_useable_form = variables_form_changer(sknf_and_sdnf.first, parsed_couple.second, false);
    vector<vector<string>> sdnf_useable_form = variables_form_changer(sknf_and_sdnf.second, parsed_couple.second, true);
	TableMethod Table_simplification = TableMethod(sknf_useable_form, sdnf_useable_form);
    CountionMethod Counting_simplification = CountionMethod(sknf_useable_form, sdnf_useable_form);
    if (parsed_couple.second.size() == 3){
        MapMethod Map_simplification = MapMethod(table_of_truth, parsed_couple.second);
    }
    }
}