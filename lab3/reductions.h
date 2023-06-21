#ifndef reductions_h
#define reductions_h
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "logic_processing.h"
using namespace std;

class CountionMethod;
class TableMethod;
class MapMethod;

struct Patterns
{
    vector<vector<int>> content = {{0, 0 ,0, 0, 0, 0}, {0, 0 ,0, 0, 0, 0}};
};

struct AllPatterns{
    vector<Patterns> all_pow_0, all_pow_1, all_pow_2, all_pow_3;
    AllPatterns(){
        Patterns Pattern_1, Pattern_2, Pattern_3, Pattern_4,
        Pattern_5, Pattern_6, Pattern_7, Pattern_8, Pattern_9,
        Pattern_10, Pattern_11, Pattern_12, Pattern_13, Pattern_14,Pattern_15, Pattern_16,
        Pattern_17, Pattern_18, Pattern_19, Pattern_20, Pattern_21, Pattern_22, Pattern_23, Pattern_24,
        Pattern_25, Pattern_26, Pattern_27;
        Pattern_1.content = {{1, 0 ,0, 0}, {0, 0 ,0, 0}};
        Pattern_2.content = {{0, 1 ,0, 0}, {0, 0 ,0, 0}};
        Pattern_3.content = {{0, 0 ,1, 0}, {0, 0 ,0, 0}};
        Pattern_4.content = {{0, 0 ,0, 1}, {0, 0 ,0, 0}};
        Pattern_5.content = {{0, 0 ,0, 0}, {1, 0 ,0, 0}};
        Pattern_6.content = {{0, 0 ,0, 0}, {0, 1 ,0, 0}};
        Pattern_7.content = {{0, 0 ,0, 0}, {0, 0 ,1, 0}};
        Pattern_8.content = {{0, 0 ,0, 0}, {0, 0 ,0, 1}};
        Pattern_9.content = {{1, 1 ,0, 0}, {0, 0 ,0, 0}};
        Pattern_10.content = {{0, 1 ,1, 0}, {0, 0 ,0, 0}};
        Pattern_11.content = {{0, 0 ,1, 1}, {0, 0 ,0, 0}};
        Pattern_12.content = {{0, 0 ,0, 1}, {1, 0 ,0, 0}};
        Pattern_13.content = {{0, 0 ,0, 0}, {1, 1 ,0, 0}};
        Pattern_14.content = {{0, 0 ,0, 0}, {0, 1 ,1, 0}};
        Pattern_15.content = {{0, 0 ,0, 0}, {0, 0 ,1, 1}};
        Pattern_16.content = {{1, 0, 0, 0}, {0, 0, 0, 1}};
        Pattern_17.content = {{1, 1 ,1, 1}, {0, 0 ,0, 0}};
        Pattern_18.content = {{0, 0 ,0, 0}, {1, 1 ,1, 1}};
        Pattern_19.content = {{1, 1 ,0, 0}, {1, 1 ,0, 0}};
        Pattern_20.content = {{0, 1 ,1, 0}, {0, 1 ,1, 0}};
        Pattern_21.content = {{0, 0 ,1, 1}, {0, 0 ,1, 1}};
        Pattern_22.content = {{1, 0 ,0, 1}, {1, 0 ,0, 1}};
        Pattern_23.content = {{1, 1 ,1, 1}, {1, 1 ,1, 1}};
        Pattern_24.content = {{1, 0 ,0, 0}, {1, 0 ,0, 0}};
        Pattern_25.content = {{0, 1 ,0, 0}, {0, 1 ,0, 0}};
        Pattern_26.content = {{0, 0 ,1, 0}, {0, 0 ,1, 0}};
        Pattern_27.content = {{0, 0 ,0, 1}, {0, 0, 0, 1}};
        all_pow_0 = {Pattern_1, Pattern_2, Pattern_3, Pattern_4,
        Pattern_5, Pattern_6, Pattern_7, Pattern_8};
        all_pow_1 = {Pattern_9, Pattern_10, Pattern_11, Pattern_12,
        Pattern_13, Pattern_14, Pattern_15, Pattern_16, Pattern_24, Pattern_25, Pattern_26, Pattern_27};
        all_pow_2 = {Pattern_17, Pattern_18, Pattern_19,Pattern_20, Pattern_21, Pattern_22};
        all_pow_3 = {Pattern_23};
    }  
};

bool variables_checker(string first, string second){
    if (first.size() == 2){
        first = first[1];
    }
    if (second.size() == 2){
        second = second[1];
    }
    if (first == second)
        return true;
    else
        return false;
}

bool able_to_glue(vector<string> first, vector<string> second){
    if (first.size() == second.size()){
        bool changed = false;
        for (int iteration  = 0; iteration < first.size(); iteration++){
            if (first[iteration]==second[iteration])
                continue;
            else if ((first[iteration] != second[iteration]) && variables_checker(first[iteration], second[iteration])){
                if (changed)
                    return false;
                else
                    changed = true;
            }
            else
                return false;
        }
        return changed;
    }
    else
        return false;
}

vector<string> glueing(vector<string> first, vector<string> second){
    vector<string> result = {};
    for (int iteration = 0; iteration<first.size();iteration++){
        if ((first[iteration] != second[iteration]) && variables_checker(first[iteration], second[iteration])){
            continue;;
        }
        else
            result.push_back(first[iteration]);
    }
    return result;
}

void recursive_glueing(vector<vector<string>> current_condition, vector<vector<string>> &result){
    vector<vector<string>> next_condition = {};
    vector<bool> check_box = {};
    int times_glued = 0;
    for (int iteration = 0; iteration < current_condition.size();iteration++)
        check_box.push_back(false);
    for (int iteration = 0; iteration < current_condition.size();iteration++){
        for (int subiteration = 0; subiteration < current_condition.size(); subiteration++){
            if (able_to_glue(current_condition[iteration], current_condition[subiteration])){
                vector<string> glueing_result = glueing(current_condition[iteration], current_condition[subiteration]);
                if (count(next_condition.begin(), next_condition.end(), glueing_result) == 0)
                    next_condition.push_back(glueing_result);
                check_box[iteration] = true;
                check_box[subiteration] = true;
                times_glued++;
            }
        }
    }
    for (int iteration = 0; iteration < check_box.size();iteration++){
        if (!check_box[iteration])
            next_condition.push_back(current_condition[iteration]);
    }
    if (times_glued==0)
        result = next_condition;
    else 
        recursive_glueing(next_condition, result);
}

pair<vector<string>, vector<string>>  subformulas_connector(vector<vector<string>> sknf, vector<vector<string>> sdnf){
    vector<string> subformulas_sknf = {}, subformulas_sdnf = {};
    for (int iteration = 0; iteration<sknf.size();iteration++){
        string current_subformula = "";
        for (int sign = 0; sign < sknf[iteration].size(); sign++){
            current_subformula+=sknf[iteration][sign]+'+';
        }
        current_subformula.pop_back();
        subformulas_sknf.push_back(current_subformula);
    }
    for (int iteration = 0; iteration< sdnf.size();iteration++){
        string current_subformula = "";
        for (int sign = 0; sign < sdnf[iteration].size(); sign++){
            current_subformula+=sdnf[iteration][sign]+'*';
        }
        current_subformula.pop_back();
        subformulas_sdnf.push_back(current_subformula);
    }
    pair<vector<string>, vector<string>> result = {subformulas_sknf, subformulas_sdnf};
    return result;
}

pair<bool, bool> is_optimal(vector<vector <int>> table_of_truth, pair<string, vector<char>> parsed_couple){
    bool is_always_true = true, is_always_false = true;
    for (int variation = 0; variation < table_of_truth.size(); variation++){
        string filled_with_variables = fill_with_variables(parsed_couple.first, table_of_truth[variation], parsed_couple.second);
        if (solve(filled_with_variables) == 0){
            is_always_true = false;}
        else 
            is_always_false = false;
    }
    pair <bool, bool> result = {is_always_true, is_always_false};
    return result;
}

void show_sknf(vector<vector<string>> sknf, string current_outpt){
    cout<<current_outpt;
    for (int iteration = 0; iteration<sknf.size();iteration++){
        cout<<"(";
        for (int subiteration = 0; subiteration < sknf[iteration].size(); subiteration++){
            if (subiteration != sknf[iteration].size()-1)
                cout<<sknf[iteration][subiteration]<<'+';
            else
                cout<<sknf[iteration][subiteration];
        }
        if (iteration!=sknf.size()-1)
            cout<<")*";
        else 
            cout<<")";
    }
    cout<<endl;
}

void show_sdnf(vector<vector<string>> sdnf, string current_outpt){
    cout<<current_outpt;
    for (int iteration = 0; iteration<sdnf.size();iteration++){
        cout<<"(";
        for (int subiteration = 0; subiteration < sdnf[iteration].size(); subiteration++){
            if (subiteration != sdnf[iteration].size()-1)
                cout<<sdnf[iteration][subiteration]<<'*';
            else
                cout<<sdnf[iteration][subiteration];
        }
        if (iteration!=sdnf.size()-1)
            cout<<")+";
        else 
            cout<<")";
    }
    cout<<endl;
}

vector<vector<int>> grey_code_constructor(int variables){
    vector<vector<int>> result = {{0}, {1}};
    for (int iteration = 1; iteration!=variables;iteration++){
        for (int subiteration = result.size(), rsubiteration = result.size()-1; rsubiteration>=0;rsubiteration--, subiteration++)
        {
            result.push_back(result[rsubiteration]);
            result[subiteration].insert(result[subiteration].begin(), 1);
            result[rsubiteration].insert(result[rsubiteration].begin(), 0);
        }
    }
    return result;
}

class CountionMethod
{
private:
    vector<vector<string>> to_check_sknf = {}, to_check_sdnf = {};
    pair<vector<vector<string>>,vector<vector<string>>> result;
public:
	CountionMethod(vector<vector<string>>, vector<vector<string>>);
    ~CountionMethod();
};

pair<vector<vector<string>>, vector<vector<string>>>  check_of_necessity(vector<vector<string>> input_sknf, vector<vector<string>> input_sdnf) {
    pair<vector<string>, vector<string>> connected = subformulas_connector(input_sknf, input_sdnf);
    pair<vector<vector<string>>, vector<vector<string>>> result;
    for (int iteration = 0; iteration < input_sknf.size(); iteration++) {
        pair<string, vector<char>> parsed = user_input_parser(connected.first[iteration]);
        vector<vector <int>> table_of_truth = table_of_truth_constructor(parsed.second);
        pair<bool, bool> optimal_pair = is_optimal(table_of_truth, parsed);
        if (!optimal_pair.second and !optimal_pair.first)
            result.first.push_back(input_sknf[iteration]);
    }
    for (int iteration = 0; iteration < input_sdnf.size(); iteration++) {
        pair<string, vector<char>> parsed = user_input_parser(connected.second[iteration]);
        vector<vector <int>> table_of_truth = table_of_truth_constructor(parsed.second);
        pair<bool, bool> optimal_pair = is_optimal(table_of_truth, parsed);
		if (!optimal_pair.second and !optimal_pair.first)
        	result.second.push_back(input_sdnf[iteration]);
    }
    return result;
}

void show_result(pair<vector<vector<string>>, vector<vector<string>>> result) {
    show_sknf(result.first, "Counting Method sknf: ");
    show_sdnf(result.second, "Counting Method sdnf: ");
}


CountionMethod::CountionMethod(vector<vector<string>> func_inp_sknf, vector<vector<string>> func_inp_sdnf)
{
    recursive_glueing(func_inp_sknf, *&to_check_sknf);
    recursive_glueing(func_inp_sdnf, *&to_check_sdnf);
    result = check_of_necessity(to_check_sknf, to_check_sdnf);
    show_result(result);
}

CountionMethod::~CountionMethod()
{
}

class TableMethod
{
private:
    vector<vector<string>> to_check_sknf, to_check_sdnf;
    pair<vector<vector<string>>,vector<vector<string>>> result;
public:
	TableMethod(vector<vector<string>>, vector<vector<string>>);
	~TableMethod();
};

vector<vector<string>> table_check(vector<vector<string>>,  vector<vector<string>>);
bool substring_check(vector<string>, vector<string>);
bool useability_check(vector<vector<bool>>, int);

TableMethod::TableMethod(vector<vector<string>> func_inp_sknf, vector<vector<string>> func_inp_sdnf)
{
	recursive_glueing(func_inp_sknf, *&to_check_sknf);
	recursive_glueing(func_inp_sdnf, *&to_check_sdnf);
	show_sknf(table_check(func_inp_sknf, to_check_sknf), "Table Method sknf: ");
	show_sdnf(table_check(func_inp_sdnf, to_check_sdnf), "Table Method sdnf: ");
}

vector<vector<string>> table_check(vector<vector<string>> constituents, vector<vector<string>> implicants){
    vector<vector<bool>> main_table = {};
    vector<int> check_list = {};
    vector<vector<string>> result = {};
    for (int iteration = 0; iteration<implicants.size();iteration++){
        check_list.push_back(iteration);
        vector<bool> current_constituents = {};
        for (int subiteration = 0;subiteration<constituents.size();subiteration++){
			if (substring_check(constituents[subiteration], implicants[iteration]))
                current_constituents.push_back(true);
            else
                current_constituents.push_back(false);
        }
        main_table.push_back(current_constituents);
    }
    bool happened = true;
    while (happened){
	happened = false;
    for (int iteration = 0;iteration<main_table.size();iteration++){
		if (useability_check(main_table, iteration)){
            main_table.erase(main_table.begin()+iteration);
            check_list.erase(check_list.begin()+iteration);
            happened=true;
            break;
        }
    }
    }
    for (int iterations = 0;iterations<check_list.size();iterations++){
        result.push_back(implicants[check_list[iterations]]);
    }
    return result;
}

bool substring_check(vector<string> where_to_search, vector<string> what_to_search){
	bool result = true;
    for (int iteration = 0; iteration<what_to_search.size();iteration++){
            string no_denial = "";
            if (what_to_search[iteration].size() == 2){
                no_denial.push_back(what_to_search[iteration][1]);}
            else{
                no_denial.push_back('!');
                no_denial+=what_to_search[iteration];
                }
            if ((count(where_to_search.begin(), where_to_search.end(), no_denial)==0))
                if (count(where_to_search.begin(), where_to_search.end(), what_to_search[iteration])==0)
                    result = false;
    }
    return result;
}

bool useability_check(vector<vector<bool>> main_table, int iteration){
		for (int subiteration = 0; subiteration<main_table[iteration].size(); subiteration++){
            main_table[iteration][subiteration] = false;
        }
        int iter_1=0, iter_2=0;
        for (iter_2 = 0;iter_2<main_table[iter_1].size();iter_2++){
            int counter = 0;
            for (iter_1 = 0; iter_1<main_table.size();iter_1++){
                if (main_table[iter_1][iter_2])
                    counter++;
            }
            if (counter == 0)
                return false;
        }
        return true;
    }

TableMethod::~TableMethod()
{
}

class MapMethod
{
private:
    vector<vector<string>> to_check_sknf, to_check_sdnf;
    pair<vector<vector<string>>,vector<vector<string>>> result;
public:
    MapMethod(vector<vector<int>>, vector<char>);
    ~MapMethod();
};

vector<vector<int>> map_constructor(vector<vector<int>>);
vector<vector<int>> grey_code_connector(vector<vector<int>>, vector<vector<int>>);

bool pattern_check(vector<vector<int>> filled_MAP, Patterns current, vector<vector<int>> &check_list){
    int same_counter = 0, all_counter=0, already_been=0;
    for (int iteration_x = 0, iteration_y = 0;;iteration_x++){
        if (iteration_x == filled_MAP[iteration_y].size()){
            iteration_x = 0;
            iteration_y++;
            if (iteration_y==filled_MAP.size()){
                break;
            }
        }
        if (current.content[iteration_y][iteration_x] == 1){
            all_counter++;
            if (filled_MAP[iteration_y][iteration_x] == 1){
                same_counter++;
            }
            if (check_list[iteration_y][iteration_x] == 1){
                already_been++;
            }
        }
    }
    bool result = (same_counter != 0) && (already_been>0) && (same_counter==all_counter);
    if (result){
        for (int iteration_x = 0, iteration_y = 0;;iteration_x++){
        if (iteration_x == filled_MAP[iteration_y].size()){
            iteration_x = 0;
            iteration_y++;
            if (iteration_y==filled_MAP.size()){
                break;
            }
        }
        if ((current.content[iteration_y][iteration_x] == 1) && (check_list[iteration_y][iteration_x] == 1)){
            check_list[iteration_y][iteration_x] = 0;
        }
        }   
    }
    return result;
}

int changed(vector<int> current, vector<int> previous){
    for (int iteration = 0; iteration<current.size(); iteration++){
        if (current[iteration] != previous[iteration]){
            return iteration;
        }
    }
    return -1;
}

vector<string> pattern_filler(Patterns current,vector<char> all_variables){
    vector<vector<int>> first_variable = grey_code_constructor(1), second_and_third_variable = grey_code_constructor(2);
    vector<vector<int>> to_compare = grey_code_connector(first_variable, second_and_third_variable), result_changes;
    vector<int> line_form_curent, check_box = {0, 0, 0};
    vector<string> output;
    for (int iteration_y = 0, iteration_x = 0;;iteration_x++){
        if (iteration_x == current.content[iteration_y].size()){
            iteration_x = 0;
            iteration_y++;
            if (iteration_y==current.content.size()){
                break;
            }
        }
        line_form_curent.push_back(current.content[iteration_y][iteration_x]);
    }
    for (int iteration = 0; iteration<line_form_curent.size();iteration++){
        if (line_form_curent[iteration] == 1){
            result_changes.push_back(to_compare[iteration]);
        }
    }
    vector<int> previous = result_changes[0];
    for (int iteration = 1; iteration < result_changes.size(); iteration++){
        if (changed(result_changes[iteration], previous) != -1){
            check_box[changed(result_changes[iteration], previous)] = 1;
        }
    }
    for (int iteration= 0; iteration<3; iteration++){
        if (check_box[iteration] == 0){
            string current = "";
            if (previous[iteration] == 0){
                current.push_back('!');
                current.push_back(all_variables[iteration]);
            }
            else {
                current.push_back(all_variables[iteration]);
            }
            output.push_back(current);
        }
    }
    return output;
}

vector<vector<string>> main_processing(vector<vector<int>> filled_truth_table, vector<char> variables){
    AllPatterns pattern;
    vector<vector<int>> filled_MAP = map_constructor(filled_truth_table);
    vector<vector<int>> check_box = filled_MAP;
    vector<Patterns> all_pattern, final_patterns;
    vector<vector<string>> result;
    for (int iteration = 0; iteration<pattern.all_pow_0.size(); iteration++)
        all_pattern.push_back(pattern.all_pow_0[iteration]);
    for (int iteration = 0; iteration<pattern.all_pow_1.size(); iteration++)
        all_pattern.push_back(pattern.all_pow_1[iteration]);
    for (int iteration = 0; iteration<pattern.all_pow_2.size(); iteration++)
        all_pattern.push_back(pattern.all_pow_2[iteration]);
    for (int iteration = 0; iteration<pattern.all_pow_3.size(); iteration++)
        all_pattern.push_back(pattern.all_pow_3[iteration]);
    int left;
    for (int iteration = all_pattern.size()-1; iteration>=0;iteration--){
        if (pattern_check(filled_MAP, all_pattern[iteration], *&check_box)){
            final_patterns.push_back(all_pattern[iteration]);
        }
        left = count(check_box[0].begin(), check_box[0].end(), 1) + count(check_box[1].begin(), check_box[1].end(), 1);
        if (left == 0)
            break;
    }
    for (int iteration = 0; iteration<final_patterns.size();iteration++){
        result.push_back(pattern_filler(final_patterns[iteration], variables));
    }
    return result;
}

MapMethod::MapMethod(vector<vector<int>> filled_truth_table, vector<char> variables)
{
    vector<vector<string>> result_sdnf, result_sknf;
    vector<vector<int>> sknf_truth_table = filled_truth_table;
    for (int iteration_y = 0, iteration_x = filled_truth_table[iteration_y].size()-1; iteration_y<filled_truth_table.size(); iteration_y++){
        if (sknf_truth_table[iteration_y][iteration_x] == 1)
            sknf_truth_table[iteration_y][iteration_x] = 0;
        else 
            sknf_truth_table[iteration_y][iteration_x] = 1; 
    }  
    result_sdnf = main_processing(filled_truth_table, variables);
    result_sknf = main_processing(sknf_truth_table, variables);
    show_sdnf(result_sdnf, "Karno Map Method Sdnf:");
    show_sknf(result_sknf, "Karno Map Method Sknf:");
}

vector<vector<int>> map_constructor(vector<vector<int>> filled_truth_table){
    vector<vector<int>> result = {{0, 0, 0, 0}, {0, 0, 0, 0}},
    first_variable = grey_code_constructor(1), second_and_third_variable = grey_code_constructor(2);
    vector<vector<int>> to_compare = grey_code_connector(first_variable, second_and_third_variable);
    int result_y = 0, result_x = 0;
    vector<int> buffer = filled_truth_table[7];
    filled_truth_table[7] = filled_truth_table[6];
    filled_truth_table[6] = buffer;
    buffer = filled_truth_table[3];
    filled_truth_table[3] = filled_truth_table[2];
    filled_truth_table[2] = buffer;
    for (int iteration = 0;iteration < filled_truth_table.size(); iteration++){
        for (int subiteration = 0;subiteration < filled_truth_table.size();subiteration++)
            if (filled_truth_table[iteration] == to_compare[subiteration]){
                result[result_y][result_x] = 1;
            }
        result_x++;
        if (result_x == result[result_y].size()){
            result_y++;
            result_x = 0;
        }
    }
    return result;
}

vector<vector<int>> grey_code_connector(vector<vector<int>> first, vector<vector<int>> second){
    vector<vector<int>> result;
    int result_size = first.size()*second.size(), first_iterations = 0, second_iterations = 0;
    for (int iteration = 0; iteration<result_size;iteration++){
        vector<int> buffer_vector;
        buffer_vector.push_back(first[first_iterations][0]);
        for (int subiterations = 0; subiterations<second[second_iterations].size();subiterations++){
            buffer_vector.push_back(second[second_iterations][subiterations]);
        }
        second_iterations++;
        buffer_vector.push_back(1);
        result.push_back(buffer_vector);
        if (second_iterations == second.size()){
            second_iterations = 0;
            first_iterations++;
        }
    }
    return result;
}

MapMethod::~MapMethod()
{
}

#endif