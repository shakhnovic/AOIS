from processor import Associative_processor

def main():
    processor = Associative_processor()
    choosing_task(processor)


def choosing_task(processor):
    while True:
        task = int(input("Choose task: \n1 -- intervals\n2 -- convert to diagonal\n3 -- convert to straight\n"
                         "4 -- logic operations\n5 -- summ of digits\n6 -- Read or write column\n"))
        match task:
            case 1:
                processor.intervals()
            case 2:
                processor.convert_to_diagonal()
                print(processor.matrix.T)
            case 3:
                processor.convert_to_straight()
                print(processor.matrix.T)
            case 4:
                processor.logic_operations()
            case 5:
                processor.sum_of_fields()
            case 6:
                processor.choose_read_or_write()
            case _:
                break


if __name__ == '__main__':
    main()