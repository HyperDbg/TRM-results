import re
import matplotlib.pyplot as plt
from matplotlib.cm import get_cmap

# List of file paths
file_paths = [
    "IntelCompiler_x64",
    "IntelCompiler_x86",
    "MSVC_x64",
    "MSVC_x86"
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

markers=['v','^','o', '+']
lines=['dashed','dashed','dashed', 'dashed']

lw = 10
overlapping = 1

# Create a separate plot for each file with unique colors
for i in range(len(file_paths)):
    color = cmap(i % 10)  # Use modulo to ensure colors repeat if more than 10 files
    overlapping = overlapping - 0.1
    lw = lw - 2
    plt.plot(all_hex_numbers[i], color=color, marker=markers[i], label=file_names[i], alpha=overlapping, linestyle=lines[i], linewidth=lw)


# Add labels and legend
plt.title('Linear chart based on relative memory offset')
plt.xlabel('Time')
plt.ylabel('Relative memory offset')
plt.grid(True)
plt.legend()
plt.show()
