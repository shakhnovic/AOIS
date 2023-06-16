#include <iostream>
#include <array>
#include <vector>
#include <math.h>
using namespace std;
array<int, 16> filled_with_zeros = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
array<int, 32> summ_32(array<int, 32>, array<int, 32>);
struct FloatingPointNumber
{
    array<int, 23> mantissa = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};
    array<int, 16> exponent = filled_with_zeros;
    int sign = 0;
};
struct FixedPointNumber
{
    array<int, 16> integer_part = filled_with_zeros;
    array<int, 16> float_part = filled_with_zeros;
};

int to_int(array<int, 16> tranferable){
    int result = 0;
    for (int iteration = 0; iteration<15;iteration++){
        if (tranferable[iteration] == 1){
            result = result + pow(2, iteration) ;
        }
    }
    return result;
}

bool bigger_binary(array<int, 16> first, array<int, 16> second){
    for (int iteration = 14; iteration >= 0; iteration--){
        if (first[iteration]<second[iteration])
            return false;
        if (first[iteration]>second[iteration])
            return true;
    }
    return true;
}

int exponent_comperhansion(array<int, 16> exponent_1, array<int, 16> exponent_2){
    for (int iteration = 15; iteration >= 0; iteration--){
        if (exponent_1[iteration] > exponent_2[iteration])
            return 1;
        if (exponent_1[iteration] < exponent_2[iteration])
            return 2;
    }
    return 0;
}


array<int, 16> to_binary(int transferable){
    array<int, 16> result = filled_with_zeros;
    if (transferable < 0){
        result[15] = 1;
        transferable = -transferable;
        };
    for (int iteration = 0; iteration<15; iteration++){
        if (transferable % 2 == 1){
            result[iteration] = 1;
        };
        transferable = transferable / 2;
    };
    return result;
}

FixedPointNumber fixed_point_summ(FixedPointNumber first, FixedPointNumber second){
    FixedPointNumber result;
    array<int, 32> full_size_first, full_size_second, full_summ;
    for (int iteration = 0; iteration < 16;iteration++){
        full_size_first[iteration] = first.float_part[iteration];
        full_size_second[iteration] = second.float_part[iteration];
    }
    for (int iteration = 0; iteration < 16;iteration++){
        full_size_first[iteration+16] = first.integer_part[iteration];
        full_size_second[iteration+16] = second.integer_part[iteration];
    }
    full_summ = summ_32(full_size_first, full_size_second);
    for (int iteration = 0; iteration < 16;iteration++){
        result.float_part[iteration] = full_summ[iteration];
    };
    for (int iteration = 0; iteration < 16;iteration++){
        result.integer_part[iteration] = full_summ[iteration+16];
    };
    return result;
}

array<int, 32> summ_32(array<int, 32> first, array<int, 32> second){
    array<int, 32> result = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool in_memory = false;
    for (int iteration = 0; iteration < 32; iteration++){
        if (first[iteration] && second[iteration] && in_memory){
            result[iteration] = 1;
        }
        else if (first[iteration] && second[iteration] && !in_memory)
        {
            in_memory = 1;
        }
        else if (!first[iteration] && !second[iteration] && in_memory)
        {
            in_memory = false;
            result[iteration] = 1;
        }
        else if (!first[iteration] && second[iteration] && !in_memory)
        {
            result[iteration] = 1;
        }
        else if (first[iteration] && !second[iteration] && !in_memory)
        {
            result[iteration] = 1;
        }
    };
    return result;
}

array<int, 16> summ(array<int, 16> first, array<int, 16> second){
    array<int, 16> result = filled_with_zeros;
    bool in_memory = false;
    for (int iteration = 0; iteration < 15; iteration++){
        if (first[iteration] && second[iteration] && in_memory){
            result[iteration] = 1;
        }
        else if (first[iteration] && second[iteration] && !in_memory)
        {
            in_memory = 1;
        }
        else if (!first[iteration] && !second[iteration] && in_memory)
        {
            in_memory = false;
            result[iteration] = 1;
        }
        else if (!first[iteration] && second[iteration] && !in_memory)
        {
            result[iteration] = 1;
        }
        else if (first[iteration] && !second[iteration] && !in_memory)
        {
            result[iteration] = 1;
        }
    };
    if (first[15] == 1 && second[15] == 1){
        result[15] = 1;
    };
    return result;
}

array<int, 16> addittional_form(array<int, 16> transferable){
    array<int, 16> result = filled_with_zeros, one = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    result[15] = 1;
    for (int iteration = 0; iteration < 15; iteration ++){
        if (transferable[iteration] == 1)
            result[iteration] = 0;
        else
            result[iteration] = 1;
    };
    result = summ(result, one);
    return result;
}

array<int, 16> subtraction(array<int, 16> first, array<int, 16> second){
    array <int, 16> operable_1 = first, operable_2, result;
    operable_2 = addittional_form(second);
    result = summ(operable_1, operable_2);
    if (bigger_binary(operable_2, operable_1)){
        result[15] = 1;
    }
    return result;
}

void binary_output(array<int, 16> operatable){
    for (int sign = 15; sign >= 0; sign--){
        cout <<operatable[sign]<<" ";
    }
    cout << endl;
}

FloatingPointNumber connector(array<int, 16> first, array<int, 16> second){
    array<int, 32> full_size = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    array<int, 16> exponent = {0, 0, 0, 0, 0, 0, 0, 0};
    array<int, 23> mantissa = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int iteration = 15; iteration >= 0;iteration--){
        full_size[15-iteration] = second[iteration];
    }
    for (int iteration = 0; iteration < 16;iteration++){
        full_size[iteration+16] = first[iteration];
        }
    int start_first = 30, exponent_decimal = 0;
    while (full_size[start_first] == 0)
    {
        start_first--;
    }
    start_first--;
    if (start_first < 15)
        exponent_decimal =127- (15 - start_first);
    else
    exponent_decimal = (start_first-15) + 127;
    for (int iteration = 22; iteration >= 0; iteration --){
        mantissa[iteration] = full_size[start_first - (22-iteration)];
    }
    exponent = to_binary(exponent_decimal);
    FloatingPointNumber result;
    result.exponent = exponent;
    result.mantissa = mantissa;
    return result;
}

array<int, 16> float_to_binary(float transferable){
    array<int, 16> second_part_binary = filled_with_zeros;
    int first_part = transferable;
    float second_part = transferable - first_part, temp_decreser = 0.5, temp_current = second_part;
    for (int iteration = 0; iteration<16; iteration++){
        if (temp_current >= temp_decreser){
            second_part_binary[iteration]  = 1;
            temp_current = temp_current - temp_decreser;
        }
        temp_decreser = temp_decreser / 2;
    }
    return second_part_binary;
}

FixedPointNumber float_to_fixed(FloatingPointNumber transferable){
    int exponent = to_int(transferable.exponent) - 126;
    array<int, 24> transfer_buffer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    array<int, 16> int_buffer = filled_with_zeros, float_buffer = filled_with_zeros;
    for (int iteration = 0; iteration < 23; iteration++){
        transfer_buffer[iteration] = transferable.mantissa[iteration];
    }
    FixedPointNumber result;
    if (exponent >= 0){
        int iteration = 0;
        exponent--;
        for (; iteration <= exponent; iteration++){
            result.integer_part[exponent-iteration] = transfer_buffer[23-iteration];
        }
        int additional_iterator = 0;
        for (; iteration < 23; iteration++){
            result.float_part[15-additional_iterator] = transfer_buffer[23-iteration];
            additional_iterator++;
            if (additional_iterator == 16){
                break;
            }
        }
    }
    else{
        int additional_iterator = 0;
        for (int iteration = 23; iteration >=0; iteration--){
            result.float_part[15-additional_iterator+exponent] = transfer_buffer[iteration];
            additional_iterator++;
            if (additional_iterator == 16){
                break;
            }
        }
    };
    return result;
}

FloatingPointNumber fixed_point_to_float(FixedPointNumber transferable){
    FloatingPointNumber result;
    array <int, 16> reversed_float;
    for (int iteration = 0;iteration<16;iteration++){
        reversed_float[15-iteration] = transferable.float_part[iteration];
    }
    result = connector(transferable.integer_part,reversed_float);
    return result;
}

FloatingPointNumber float_summ(FloatingPointNumber first,  FloatingPointNumber second){
    FloatingPointNumber result;
    FixedPointNumber first_operand = float_to_fixed(first), second_operand = float_to_fixed(second), summ_result;
    summ_result = fixed_point_summ(first_operand, second_operand);
    result = fixed_point_to_float(summ_result);
    return result;
}

void floating_viewer(FloatingPointNumber to_view){
    cout <<"sign: "<< to_view.sign << " " << endl;
    cout <<"mantissa: ";
    for (int iteration = 22;iteration >= 0;iteration--){
        cout<<to_view.mantissa[iteration]<<" ";
    }
    cout<<endl<<"exponent: ";
    for (int iteration = 15;iteration >=0;iteration--){
        cout<<to_view.exponent[iteration]<<" ";
    }
    cout<<endl;
}

array<int, 16> step_right(array<int, 16> operatable){
    for (int iteration = 14; iteration >0;iteration--){
        operatable[iteration] = operatable[iteration-1];
    }
    operatable[0] = 0;
    return operatable;
}

array<int, 16> multiplication(array<int, 16> first, array<int, 16> second){
    array<int, 16> result = filled_with_zeros, current_addable = first; 
    for (int iteration = 0; iteration<15;iteration++){
        if (second[iteration] == 1){
            result = summ(result, current_addable);
        }
        current_addable = step_right(current_addable);
    }
    return result;
}

array<int, 16> division(array<int, 16> first, array<int, 16> second){
    array<int, 16> result = filled_with_zeros, operatable = first, one_to_add = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    while (bigger_binary(operatable, second)){
        operatable = subtraction(operatable, second);
        result = summ(result, one_to_add);
    }
    return result;
}

void output_processing_int(int first, int second){
    array <int, 16> operable_1 = to_binary(abs(first)), operable_2 = to_binary(abs(second)), result_1, result_2;
    binary_output(operable_1);
    binary_output(operable_2);
    cout <<"first+second:"<< endl;
    result_1 = summ(operable_1, operable_2);
    binary_output(result_1);
    cout <<"-first-second:"<< endl;
    result_1[15] = 1;
    binary_output(result_1);
    cout <<"first-second:"<< endl;
    result_2 = subtraction(operable_1, operable_2);
    binary_output(result_2);
    cout <<"second-first:"<< endl;
    if (result_2[15] == 0)
        result_2[15] = 1;
    else 
        result_2[15] = 0;
    binary_output(result_2);
    cout<<"first*second:"<<endl;
    binary_output(multiplication(operable_1, operable_2));
    cout<<"first/second:"<<endl;
    binary_output(division(operable_1, operable_2));
}

void output_processing_float(float first, float second){
    int firsts_int_part = first, seconds_int_part = second;
    array<int, 16> firsts_int_part_binary = to_binary(firsts_int_part), seconds_int_part_binary = to_binary(seconds_int_part);
    array<int, 16> firsts_float_part_binary = float_to_binary(first), seconds_float_part_binary = float_to_binary(second);
    FloatingPointNumber first_float = connector(firsts_int_part_binary, firsts_float_part_binary),
    second_float = connector(seconds_int_part_binary, seconds_float_part_binary), result;
    result = float_summ(first_float, second_float);
    floating_viewer(first_float);
    floating_viewer(second_float);
    floating_viewer(result);
}

int main() {
    int choise;
    while (choise != 3){
    cout <<"Input action:\n1) Int operations\n2) Float foperations\n3) Exit\n";
    cin >>choise;
    switch (choise)
    {
    case 1: int first_operable, second_operable;
            cout<<"\nInput first number:";
            cin>>first_operable;
            cout<<"\nInput second number:";
            cin>>second_operable;
        output_processing_int(first_operable, second_operable);
        break;
    case 2: float first_operable_float, second_operable_float;
            cout<<"\nInput first number:";
            cin>>first_operable_float;
            cout<<"\nInput second number:";
            cin>>second_operable_float;
        output_processing_float(first_operable_float, second_operable_float); break;
    default:
        break;
    }
    }

  return 0;
} 