"""
    Мои задания: поиск по соответсвию и сортировка по возрастанию/убыванию
"""
import random

BIT_SIZE = 16


class Processor:
    def __init__(self):
        self.matrix = [[random.randint(0, 1) for _ in range(16)] for _ in range(random.randint(4, 16))]
        self.address = [random.randint(0, 1) for _ in range(16)]
        self.g, self.l = 0, 0
        self.printing_of_matrix()

    def printing_of_matrix(self):
        for row in self.matrix:
            for element in row:
                print(element, end=" ")
            print()

    def searching_by_accordance(self):
        self.g, self.l = 0, 0
        tick_of_matching = {}
        example_data = input("Input your example data: ")
        for char in str(example_data):
            if char != '0' and char != '1':
                print("Wrong example data!\n")
                return 0
        if len(example_data) > BIT_SIZE:
            example_data = example_data[0:BIT_SIZE]
        elif len(example_data) < BIT_SIZE:
            example_data = example_data.zfill(BIT_SIZE)
        print(f"Our data for matching: {example_data}")
        for num in range(len(self.matrix)):
            tick_of_matching.update({f"{self.matrix[num]}": self.reccure_algorithm_for_accordance(self.matrix[num], example_data)})
        print(f"Strings with the highest matching digits: \n{sorted(tick_of_matching.items(), key=lambda item: item[1])[-3:]}\n")


    def sorting(self, mid):
        self.g, self.l = 0, 0
        begin_mid = mid
        while mid != 0:
            self.quick_sort(mid)
            mid = len(self.matrix[:mid])//2
        if len(self.matrix[begin_mid:]) > 1:
            self.sorting(len(self.matrix[begin_mid:])//2 + begin_mid)
        else:
            print("From smaller to larger:\n")
            self.printing_of_matrix()
            print("From larger to smaller:\n")
            self.matrix = self.matrix[::-1]
            self.printing_of_matrix()


    def quick_sort(self, mid):
        smaller, larger = [], []
        quicksort_element = self.matrix[mid]
        for word in (self.matrix[:mid] + self.matrix[mid + 1:]):
            if self.reccure_algorithm_for_sorting(self.matrix[mid], word) == 1:
                larger.append(word)
            else:
                smaller.append(word)
        self.matrix = smaller + [quicksort_element] + larger


    @staticmethod
    def reccure_algorithm_for_accordance(matrix_string, data):
        tick = 0
        for digit, value_of_digit in enumerate(data):
            if value_of_digit == str(matrix_string[digit]):
                tick += 1
            else:
                pass
        return tick

    def reccure_algorithm_for_sorting(self, ref_word, matrix_word):
        self.g, self.l = 0, 0
        for num, value in enumerate(matrix_word):
            prev_g, prev_l = self.g, self.l
            self.g = calculating_g(prev_g, prev_l, int(ref_word[num]), int(value))
            self.l = calculating_l(prev_g, prev_l, int(ref_word[num]), int(value))
        if self.g == 1 and self.l == 0:
            return 1
        else:
            return 0

def calculating_l(prev_g, prev_l, digit_a, digit_S):
    l = int(prev_l or (digit_a and not digit_S and not prev_g))
    return l

def calculating_g(prev_g, prev_l, digit_a, digit_S):
    g = int(prev_g or (not digit_a and digit_S and not prev_l))
    return g
