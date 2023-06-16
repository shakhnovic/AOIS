from prettytable import PrettyTable


class TableElement:
    def __init__(self, key, value):
        self.key = key
        self.value = value

class Hash_table:
    def __init__(self, table_elements):
        self.table_size = 16
        self.table_elements = table_elements
        self.table_list = []

    def calculate_index(self, key):
        hash_value = 0
        for index, letter in enumerate(key):
            hash_value += (index + 1) * ord(letter)
        index = hash_value % self.table_size
        return index

    def making_table(self):
        for element in self.table_elements:
            for num in range(self.table_size):
                self.table_list.append([])
            for num in range(self.table_size):
                if num == self.calculate_index(element.key):
                    self.table_list[num].append(element)
        self.prettytable_model()

    def prettytable_model(self):
        table = PrettyTable()
        table.field_names = ["Index", "Key", "Value"]
        for num_of_string in range(self.table_size):
            if not self.table_list[num_of_string]:
                continue
            elif len(self.table_list[num_of_string]) == 1:
                entry = self.table_list[num_of_string][0]
                table.add_row([num_of_string, entry.key, entry.value])
            else:
                for entry in self.table_list[num_of_string]:
                    table.add_row([num_of_string, entry.key, entry.value])
        print(table)

    def add_element(self):
        key = input("Input key of element: ")
        value = input("Input value of element: ")
        self.table_list[self.calculate_index(key)].append(TableElement(key, value))
        self.prettytable_model()

    def deleting_element(self, key):
        element_deleted = self.finding_element(key)
        if element_deleted is not None:
            if len(element_deleted) == 1:
                index = element_deleted[0]
                self.table_list.pop(index)
            else:
                index1, index2 = element_deleted
                self.table_list[index1].pop(index2)
        self.prettytable_model()

    def finding_element(self, key):
        index_of_search_element = self.calculate_index(key)
        try:
            entries = self.table_list[index_of_search_element]
            if len(entries) == 1:
                if entries[0].key == key:
                    print(f"Value of searching element: {entries[0].value}")
                    return [index_of_search_element]
                else:
                    print("Element doesn't exist")
            else:
                for index, entry in enumerate(entries):
                    if entry.key == key:
                        print(f"Value of searching element: {entry.value}")
                        return [index_of_search_element, index]
                print("Element doesn't exist")
                return None
        except IndexError:
            print("Element doesn't exist")

    def menu(self):
        while True:
            try:
                choice = int(input("1 -- find element\n2 -- delete element\n3 -- add element\n4 -- end\n"))
            except ValueError:
                print("Wrong variant")
                choice = "_"
            match choice:
                case 1:
                    key = input("Input searching key: ")
                    self.finding_element(key)
                case 2:
                    key = input("Input key of item being deleted: ")
                    self.deleting_element(key)
                case 3:
                    self.add_element()
                case 4:
                    break
