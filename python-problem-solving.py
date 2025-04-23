from collections import Counter     # Useful for mode calculation


class StatisticsCalculator:
    """Calculates basic statistics (mean, median, mode) for a list of integers."""

    def __init__(self, data):
        """
        Initializes the calculator with a list of sorted integers.
        """
        if not data:
            raise ValueError("Data list cannot be empty.")
        self.data = sorted(data)

    def calculate_mean(self):
        """Calculates the mean (average) of the data."""
        return sum(self.data) / len(self.data)

    def calculate_median(self):
        """Calculates the median (middle value) of the data."""
        n = len(self.data)
        mid = n // 2
        if n % 2:
            return self.data[mid]
        else:
            return (self.data[mid - 1] + self.data[mid]) / 2.0

    def calculate_mode(self):
        """Calculates the mode(s) (most frequent value(s)) of the data."""
        counts = Counter(self.data)
        max_count = max(counts.values(), default=0)
        mode_value = [val for val, cnt in counts.items() if cnt == max_count]
        return mode_value, max_count


if __name__ == "__main__":
    # test_data = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8]
    # test_data = [1, 2, 3, 4, 5]
    test_data = [1, 2, 2, 3, 4, 4, 4, 5]
    calculator = StatisticsCalculator(test_data)

    print(f"Data:   {test_data}")
    print(f"Mean:   {calculator.calculate_mean():.2f}")
    print(f"Median: {calculator.calculate_median():.2f}")
    modes, freq = calculator.calculate_mode()
    print(f"Mode ({freq} occurrence{'s' if freq > 1 else ''}): {modes}")
