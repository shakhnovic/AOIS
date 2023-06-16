from hash_table import Hash_table
from hash_table import TableElement

KEYS = ["Ivan", "Mariya", "Vadim", "Timofey", "Dmitriy", "Artemiy", "Isabella", "Ahmed",
        "Mary", "Alex", "William", "Emila", "Olivia", "James",
        "Sophia", "Ethan", "Isabella", "Michael", "Emma", "Benjamin", "Ava"]

VALUES = ["Causality", "Covariance", "Action", "Physical field", "Symmetry", "Physical interaction", "Statistical ensemble", "Quantum", "Wave",
          "Particle", "Experiment", "Multiverse", "Nuclear physics", "Big Bang", "Black hole", "Gravitational singularity", "Electromagnetic radiation", "RPG-7", "OLHA", "URAGAN",
          "Magnetism"]


def main():
    table_elements = []
    for i in range(0, len(KEYS)):
        table_elements.append(TableElement(KEYS[i], VALUES[i]))
    table = Hash_table(table_elements)
    table.making_table()
    table.menu()


if __name__ == '__main__':
    main()