import matplotlib.pyplot as plt
import numpy as np

# Data from LaTeX table
tools = [
    "Bare metal", "TRM", "DynamoRIO", "HyperDbg\n  (EPT)  ", " HyperDbg  \n (SYSCALL)",
    "Valgrind", "Intel PIN", "Qiling  \n  (QEMU)" #, "QEMU"
]
methods = [
    "Hardware", "Hardware (Virt)", "Instrumentation", "Hardware (Virt)", "Hardware (Virt)",
    "Instrumentation", "Instrumentation", "Emulation" #, "Emulation"
]
times = [
    5417299/1000, 8511886/1000, 9250563/1000, 13129050/1000, 28456842/1000,
    68335624/1000, 2625163923/1000, 8244872361/1000 #, 8244872361
]

# Define a set of colors for different methods
method_colors = {
    "Hardware": '#f781bf',
    "Hardware (Virt)": '#4daf4a',
    "Instrumentation": '#ff7f00',
    "Emulation": '#377eb8'
}

# Assign colors to bars based on the method
bar_colors = [method_colors[method] for method in methods]

# Highlight "TRM" by changing its color
highlight_index = tools.index("TRM")  # Find the index for "TRM"
bar_colors[highlight_index] = 'lightgreen'  # Highlight color for "TRM"

# Create a vertical bar chart with a logarithmic scale on the y-axis
plt.figure(figsize=(10, 6))
bars = plt.bar(tools, times, color=bar_colors)

# Set logarithmic scale for the y-axis
plt.yscale('log')

# Add labels and title
plt.ylabel('Time (TSC, Log Scale) - Lower is Better')
plt.title('Performance Comparison')

# Bold the label for "TRM"
for i, tool in enumerate(tools):
    if tool == "TRM":
        bars[i].set_edgecolor('black')  # Highlight the edge of the "TRM" bar
        bars[i].set_linewidth(2)        # Make the edge more visible

# Create a legend with a color square for each method
handles = [plt.Line2D([0], [0], marker='s', color='w', markerfacecolor=color, markersize=10) for color in method_colors.values()]
labels = list(method_colors.keys())

# Adjust the legend position to be inside the chart, below the bars
plt.legend(handles, labels, title="Method", loc='upper center', bbox_to_anchor=(0.5, -0.2), ncol=4)

# Bold the text for "TRM" in the plot
plt.xticks(fontsize=10, rotation=45, ha='right')
plt.yticks(fontsize=10)

# Adjust layout to ensure everything fits within the chart area
plt.tight_layout()

# Display the chart
plt.savefig("perf-comp-switched.pdf", format="pdf", bbox_inches="tight")
plt.show()
