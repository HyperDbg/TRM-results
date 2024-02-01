import re
import matplotlib.pyplot as plt
from matplotlib.cm import get_cmap

# List of file paths
file_paths = [
    "IntelCompiler_x64",
    "IntelCompiler_x86",
    # "MSVC_x64",
    # "MSVC_x86",
    "MSVC_Themida",
    "MSVC_VMProtect"
]

# Lists to store the extracted hex numbers and corresponding file names
all_hex_numbers = []
file_names = []

# Regular expression pattern to match hex numbers
hex_pattern = re.compile(r';\s*\+0x([0-9a-fA-F]+)')

# Process each file
for file_path in file_paths:
    hex_numbers = []
    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            match = hex_pattern.search(line)
            if match:
                hex_numbers.append(int(match.group(1), 16))
    
    # Add hex numbers and file name to the lists
    all_hex_numbers.append(hex_numbers)
    file_names.append(file_path)

# Use a colormap for the lines
cmap = get_cmap('tab10')

markers=['o', 'o', 'o', 'o']
lines=['solid','solid','solid', 'solid']

lw = 5
overlapping = 1

# Create a separate plot for each file with unique colors
for i in range(len(file_paths)):
    color = cmap(i % 10)  # Use modulo to ensure colors repeat if more than 10 files
    overlapping = overlapping - 0.1
    lw = lw - 1
    plt.plot(all_hex_numbers[i], color=color, label=file_names[i], alpha=overlapping, linestyle=lines[i], linewidth=lw)
    
    # Fill the area under the line
    plt.fill_between(range(len(all_hex_numbers[i])), all_hex_numbers[i], color=color, alpha=0.2)

# Add labels and legend
plt.xlabel('Time', fontsize=20)
plt.ylabel('Relative memory offset', fontsize=20)

# Add grid with borders
plt.grid(True, which='both', linestyle='-', linewidth=0, color='black')

# Set legend font size and position
plt.legend(loc='upper right', bbox_to_anchor=(0.95, 0.93), prop={'size': 20})  # Adjust the font size here

plt.show()
