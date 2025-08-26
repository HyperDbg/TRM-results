# Manually clean and organize the extracted text
data = [
    {"Tool": "Baremetal", "Time (TSC)": 5417299},
    {"Tool": "TRM", "Time (TSC)": 8511886},
    {"Tool": "DynamoRIO", "Time (TSC)": 9250563},
    {"Tool": "HyperDbg (EPT)", "Time (TSC)": 13129050},
    {"Tool": "HyperDbg (SYSCALL)", "Time (TSC)": 28456842},
    {"Tool": "Valgrind", "Time (TSC)": 68335624},
    {"Tool": "Intel PIN", "Time (TSC)": 2625163923},
    {"Tool": "Qiling Framework", "Time (TSC)": 8244872361}
]

# Compute the ratios using Baremetal as the reference
baremetal_time = data[0]["Time (TSC)"]
ratios = [{"Tool": entry["Tool"], "Performance Ratio": entry["Time (TSC)"] / baremetal_time} for entry in data]

ratios

'''
[{'Tool': 'Baremetal', 'Performance Ratio': 1.0},
 {'Tool': 'TRM', 'Performance Ratio': 1.5712416833554876},
 {'Tool': 'DynamoRIO', 'Performance Ratio': 1.707596903918355},
 {'Tool': 'HyperDbg (EPT)', 'Performance Ratio': 2.423541694855684},
 {'Tool': 'HyperDbg (SYSCALL)', 'Performance Ratio': 5.252957608579479},
 {'Tool': 'Valgrind', 'Performance Ratio': 12.614334929639291},
 {'Tool': 'Intel PIN', 'Performance Ratio': 484.58907713973326},
 {'Tool': 'Qiling Framework', 'Performance Ratio': 1521.9526116243537}]
'''