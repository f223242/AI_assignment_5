class SudokuCSP:
    def __init__(self, board):
        self.board = board
        self.size = 9
        self.backtrack_calls = 0
        self.failures = 0

    def is_valid(self, row, col, num):
        # Row check
        if num in self.board[row]:
            return False

        # Column check
        for i in range(9):
            if self.board[i][col] == num:
                return False

        # Box check
        start_row = row - row % 3
        start_col = col - col % 3

        for i in range(3):
            for j in range(3):
                if self.board[start_row + i][start_col + j] == num:
                    return False

        return True

    def find_empty(self):
        for i in range(9):
            for j in range(9):
                if self.board[i][j] == 0:
                    return i, j
        return None

    def backtrack(self):
        self.backtrack_calls += 1  # Count calls

        empty = self.find_empty()
        if not empty:
            return True

        row, col = empty

        for num in range(1, 10):
            if self.is_valid(row, col, num):
                self.board[row][col] = num

                if self.backtrack():
                    return True

                # Undo assignment
                self.board[row][col] = 0

        self.failures += 1  # Count failures
        return False

    def solve(self):
        self.backtrack()
        return self.board

    def print_board(self):
        for row in self.board:
            print(" ".join(map(str, row)))


# ✅ File Reading Function
def read_board(filename):
    board = []
    with open(filename, 'r') as f:
        for line in f:
            board.append(list(map(int, line.strip())))
    return board


# ✅ MAIN RUN
if __name__ == "__main__":
    filename = "numbers.txt"   # 👈 apni file ka naam yahan likho

    board = read_board(filename)

    solver = SudokuCSP(board)
    solver.solve()

    print("\n✅ Solved Sudoku:\n")
    solver.print_board()

    print("\n📊 Statistics:")
    print("Backtrack Calls:", solver.backtrack_calls)
    print("Failures:", solver.failures)