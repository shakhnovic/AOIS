from copy import deepcopy
import numpy as np
import random

BIT_SIZE = 16


class Associative_processor:
    def __init__(self):
        self.matrix = np.random.randint(2, size=(BIT_SIZE, BIT_SIZE))
        self.address = [random.randint(0, 1) for _ in range(16)]
        self.g, self.l = 0, 0
        self.diagonal = False
        print(self.matrix.T)

    @staticmethod
    def calculating_g(prev_g, prev_l, digit_a, digit_S):
        g = int(prev_g or (not digit_a and digit_S and not prev_l))
        return g

    @staticmethod
    def calculating_l(prev_g, prev_l, digit_a, digit_S):
        l = int(prev_l or (digit_a and not digit_S and not prev_g))
        return l

    def intervals(self):
        self.g, self.l = 0, 0
        min_value = input("Input min value for interval: ").zfill(16)
        max_value = input("Input max value for interval: ").zfill(16)
        max_value, min_value = max_value[0:16], min_value[0:16]
        result = []
        copy_of_matrix, diagonal_data = deepcopy(self.matrix), self.diagonal
        if diagonal_data is True:
            self.convert_to_straight()
        for num_of_string in range(self.matrix.shape[0]):
            if self.reccure_algorithm_for_intervals(self.matrix[num_of_string], min_value, max_value, self.g,
                                                    self.l) == 1:
                result.append(str(self.matrix[num_of_string]))
        print(f"Words in interval:\n {result}")
        if diagonal_data is True:
            self.convert_to_diagonal()

    def convert_to_straight(self):
        copy_of_matrix = deepcopy(self.matrix)
        self.matrix = []
        for num_of_string, string in enumerate(copy_of_matrix):
            string = list(string)
            self.matrix.append(string[num_of_string:] + string[:num_of_string])
        self.matrix = np.array(self.matrix)
        self.diagonal = False

    def convert_to_diagonal(self):
        copy_of_matrix = deepcopy(self.matrix)
        self.matrix = []
        for num_of_string, string in enumerate(copy_of_matrix):
            string = list(string)
            self.matrix.append(string[(len(string) - num_of_string):] + string[:(len(string) - num_of_string)])
        self.matrix = np.array(self.matrix)
        self.diagonal = True

    def size_of_argument(self, argument):
        if len(argument) > BIT_SIZE:
            argument = argument[0:BIT_SIZE]
        elif len(argument) < BIT_SIZE:
            argument = argument.zfill(BIT_SIZE)
        return argument

    def no_of_first_argument(self, num_of_column, argument1, argument2):
        diagonal_data = self.diagonal
        if diagonal_data is True:
            self.convert_to_straight()
        argument2 = self.negative_of_argument(self.matrix[argument2])
        argument1 = self.matrix[argument1]
        for num_of_string, digit in enumerate(self.matrix[num_of_column]):
            self.matrix[num_of_column][num_of_string] = argument1[num_of_string] * argument2[num_of_string]
        if diagonal_data is True:
            self.convert_to_diagonal()
        print(self.matrix.T)

    def implication(self, num_of_column, argument1, argument2):
        diagonal_data = self.diagonal
        if diagonal_data is True:
            self.convert_to_straight()
        argument1 = self.negative_of_argument(self.matrix[argument1])
        res_argument = Associative_processor.sum_diff_of_numbers(argument1, self.matrix[argument2])
        for num_of_string, digit in enumerate(self.matrix[num_of_column]):
            self.matrix[num_of_column][num_of_string] = res_argument[num_of_string]
        if diagonal_data is True:
            self.convert_to_diagonal()
        print(self.matrix.T)

    def disjunction(self, num_of_column, argument1, argument2):
        diagonal_data = self.diagonal
        if diagonal_data is True:
            self.convert_to_straight()
        res_argument = Associative_processor.sum_diff_of_numbers(self.matrix[argument1], self.matrix[argument2])
        for num_of_string, digit in enumerate(self.matrix[num_of_column]):
            self.matrix[num_of_column][num_of_string] = res_argument[num_of_string]
        if diagonal_data is True:
            self.convert_to_diagonal()
        print(self.matrix.T)

    def pierce_operation(self, num_of_column, argument1, argument2):
        diagonal_data = self.diagonal
        if diagonal_data is True:
            self.convert_to_straight()
        res_argument = self.negative_of_argument(Associative_processor.sum_diff_of_numbers(self.matrix[argument1], self.matrix[argument2]))
        for num_of_string, digit in enumerate(self.matrix[num_of_column]):
            self.matrix[num_of_column][num_of_string] = res_argument[num_of_string]
        if diagonal_data is True:
            self.convert_to_diagonal()
        print(self.matrix.T)

    def logic_operations(self):
        type_of_operations = int(input(
            "Choose type of operation:\n 1 -- NO of first argument\n 2 -- Implication\n 3 -- Disjunction\n 4 -- Pierce operation\n"))
        num_of_column = int(input("Choose column: "))
        argument1 = int(input("Input column of the first argument: "))
        argument2 = int(input("Input column of the second argument: "))
        match type_of_operations:
            case 1:
                self.no_of_first_argument(num_of_column, argument1, argument2)
            case 2:
                self.implication(num_of_column, argument1, argument2)
            case 3:
                self.disjunction(num_of_column, argument1, argument2)
            case 4:
                self.pierce_operation(num_of_column, argument1, argument2)

    def negative_of_argument(self, argument):
        argument = np.where(argument == "1", "2", argument)
        argument = np.where(argument == "0", 1, argument)
        argument = np.where(argument == "2", 0, argument)
        return argument

    @staticmethod
    def sum_diff_of_numbers(num1, num2):  # Сумма/разность чисел
        summ = ""
        carry = 0
        for i in reversed(range(0, len(num1))):
            if (int(num1[i]) + int(num2[i]) == 1) and (carry == 0):
                summ = "1" + summ
            elif (int(num1[i]) + int(num2[i]) == 1) and (carry > 0):
                summ = "0" + summ
            elif (int(num1[i]) + int(num2[i]) == 2) and (carry > 0):
                summ = "1" + summ
            elif (int(num1[i]) + int(num2[i]) == 0) and (carry > 0):
                summ = "1" + summ
                carry -= 1
            elif (int(num1[i]) + int(num2[i]) == 0) and (carry == 0):
                summ = "0" + summ
            elif (int(num1[i]) + int(num2[i]) == 2) and (carry == 0):
                summ = "0" + summ
                carry += 1
        summ = np.array([num for num in summ])
        return summ

    def sum_of_fields(self):
        example_data = input("Input your example data: ")[:3]
        diagonal_data = self.diagonal
        if diagonal_data is True:
            self.convert_to_straight()
        for num_of_string, string in enumerate(self.matrix):
            if np.array2string(string, separator='')[1:-1].replace(' ', '')[0:3] == example_data:
                self.matrix[num_of_string][11:16] = Associative_processor.sum_diff_of_numbers(
                    self.matrix[num_of_string][3:7], self.matrix[num_of_string][7:11])
            if diagonal_data is True:
                self.convert_to_diagonal()
        print(self.matrix.T)

    def choose_read_or_write(self):
        type_of_operation = int(input("1 -- Read word\n 2 -- Read column\n 3 -- Write word\n 4 -- Write column\n "))
        match type_of_operation:
            case 1:
                self.read_word()
            case 2:
                self.read_column()
            case 3:
                self.write_word()
            case 4:
                self.write_column()

    def read_word(self):
        num_of_word = int(input("Number of word: "))
        diagonal_info = self.diagonal
        if self.diagonal is True:
            self.convert_to_straight()
        print(self.matrix[num_of_word])
        if diagonal_info is True:
            self.convert_to_diagonal()

    def read_column(self):
        num_of_col = int(input("Number of column: "))
        print(self.matrix[num_of_col])

    def write_word(self):
        word = np.array(list(input("Word:").zfill(16)[:16]), dtype=int)
        num_of_word = int(input("Number of word: "))
        diagonal_info = self.diagonal
        if self.diagonal is True:
            self.convert_to_straight()
        self.matrix[num_of_word] = word
        if diagonal_info is True:
            self.convert_to_diagonal()
        print(self.matrix.T)

    def write_column(self):
        column = np.array(list(input("Column:").zfill(16)[:16]), dtype=int)
        num_of_col = int(input("Number of column: "))
        self.matrix[num_of_col] = column
        print(self.matrix.T)

    @staticmethod
    def reccure_algorithm_for_intervals(matrix_string, min, max, g, l):
        for num, value in enumerate(matrix_string):
            prev_g, prev_l = g, l
            g = Associative_processor.calculating_g(prev_g, prev_l, int(min[num]), int(value))
            l = Associative_processor.calculating_l(prev_g, prev_l, int(min[num]), int(value))
        if g == 0 and l == 1:
            return 0
        g, l = 0, 0
        for num, value in enumerate(matrix_string):
            prev_g, prev_l = g, l
            g = Associative_processor.calculating_g(prev_g, prev_l, int(max[num]), int(value))
            l = Associative_processor.calculating_l(prev_g, prev_l, int(max[num]), int(value))
        if g == 1 and l == 0:
            return 0
        return 1