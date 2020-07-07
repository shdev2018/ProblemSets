from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    matrix = []
    Alen = len(a) + 1
    Blen = len(b) + 1

    # Create empty matrix
    for i in range(Alen):
        matrix.append([])
        for j in range(Blen):
            matrix[i].append((0, None))

    # Base Conditions
    # Cost of matching A string to empty
    for i in range(1, Alen):
        matrix[i][0] = (i, Operation.DELETED)

    # Cost of matching empty to B string
    for i in range(1, Blen):
        matrix[0][i] = (i, Operation.INSERTED)

    # Calculate rest of matrix
    for i in range(1, Alen):
        for j in range(1, Blen):
            delete = matrix[i - 1][j][0]
            insert = matrix[i][j - 1][0]
            substitute = matrix[i - 1][j - 1][0]

            # If match
            if a[i - 1] is b[j - 1]:
                matrix[i][j] = (substitute, Operation.SUBSTITUTED)

            # If above smaller, delete
            elif delete < insert and delete < substitute:
                matrix[i][j] = (delete + 1, Operation.DELETED)

            # If left smaller, insert
            elif insert < delete and insert < substitute:
                matrix[i][j] = (insert + 1, Operation.INSERTED)

            else:
                matrix[i][j] = (substitute + 1, Operation.SUBSTITUTED)

    return matrix