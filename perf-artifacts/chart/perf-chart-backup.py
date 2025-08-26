import matplotlib.pyplot as plt
import numpy as np

# Data from LaTeX table
tools = [
    "Baremetal", "TRM", "DynamoRIO", "HyperDbg (EPT)", "HyperDbg (SYSCALL)",
    "Valgrind", "Intel PIN", "Qiling Framework (QEMU)" #, "QEMU"
]
methods = [
    "Hardware", "Hardware (Virt)", "Instrumentation", "Hardware (Virt)", "Hardware (Virt)",
    "Instrumentation", "Instrumentation", "Emulation" #, "Emulation"
]
times = [
    5417299, 8511886, 9250563, 13129050, 28456842,
    68335624, 2625163923, 8244872361 #, 8244872361
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

# Create a bar chart with a logarithmic scale on the x-axis
plt.figure(figsize=(10, 6))
bars = plt.barh(tools, times, color=bar_colors)

# Set logarithmic scale for the x-axis
plt.xscale('log')

# Add labels and title
plt.xlabel('Time (TSC, Log Scale)')
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
plt.legend(handles, labels, title="Method", loc='upper center', bbox_to_anchor=(0.5, 0.135), ncol=4)

# Bold the text for "TRM" in the plot
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

# Highlight the "TRM" text by bolding it
plt.gca().get_yaxis().get_ticklabels()[tools.index("TRM")].set_fontweight('bold')

# Adjust layout to ensure everything fits within the chart area
plt.tight_layout()

# Display the chart
plt.savefig("perf-comp.pdf", format="pdf", bbox_inches="tight") 
plt.show()
