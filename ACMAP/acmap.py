def longest_acmap(input_1, input_2):
    m = len(input_1)
    n = len(input_2)

    # Initialize a 2D table for dynamic programming
    dp_table = [[0] * (n + 1) for _ in range(m + 1)]

    # Variables to keep track of the maximum length and its ending position
    max_length = 0
    end_position = 0

    # Fill the table based on the recurrence relation
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if input_1[i - 1] == input_2[j - 1]:
                dp_table[i][j] = dp_table[i - 1][j - 1] + 1
                if dp_table[i][j] > max_length:
                    max_length = dp_table[i][j]
                    end_position = i
            else:
                dp_table[i][j] = 0

    # Retrieve the maximum common interval
    acmap = input_1[end_position - max_length:end_position]

    return acmap, max_length

# Example usage with arrays of integers:
input_arr1 = [65, 66, 67, 68, 97, 98, 99, 49, 50, 51]
input_arr2 = [120, 121, 122, 65, 66, 67, 68, 49, 50, 51]

result_acmap, result_length = longest_acmap(input_arr1, input_arr2)

print("Longest ACMAP:", result_acmap)
print("Length of ACMAP:", result_length)
