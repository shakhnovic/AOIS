from associate_memory import Processor

def main():
    processor = Processor()
    choosing_task(processor)


def choosing_task(processor):
    while True:
        task = int(input("Choose task: \n1 -- searching by accordance\n2 -- sorting\n3 -- The End\n"))
        match task:
            case 1:
                processor.searching_by_accordance()
            case 2:
                processor.sorting(len(processor.matrix)//2)
            case 3:
                break


if __name__ == '__main__':
    main()