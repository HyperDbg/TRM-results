import re

# Define a regular expression pattern to match hexadecimal values
hex_pattern = r'\\x([0-9a-fA-F]{2})'

# Function to perform XOR operation
def xor_with_password(hex_values, password):
    result = ""
    actual_string = ""
    for hex_value in hex_values:
        # Convert hexadecimal string to integer
        value = int(hex_value, 16)
        # XOR operation
        xored_value = value ^ password
        # Convert back to hexadecimal and append to result
        result = result + "\\x" + format(xored_value, '02x')
        actual_string = actual_string + "\\x" + format(value, '02x')
        
    print(result)
    return result, actual_string

# Open the input file for reading
with open('AsmCodes.h', 'r') as input_file:
    # Open the output file for writing
    with open('AsmCodes2.h', 'w') as output_file:
        # Read the input file line by line
        for line in input_file:
            # Search for hexadecimal values in the current line
            hex_values = re.findall(hex_pattern, line)
            # If hexadecimal values are found, XOR them with the password
            if hex_values:
                result, actual_string = xor_with_password(hex_values, 0x41)
                                
                # Replace the original hexadecimal values with XORed values in the line
                new_line = line
                print("original line: " + line)
                new_line = new_line.replace(actual_string, result, 1)
                
                # Write the modified line to the output file
                print("new line: " + new_line)
                output_file.write(new_line)
            else:
                # If no hexadecimal values found, write the original line to the output file
                output_file.write(line)
