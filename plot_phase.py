import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import subprocess

dataset = []
set_cord = [[], []]
cmd = './phase.o'
process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
i = 0

for line in process.stdout:
    temp = (line.decode("ASCII"))[:-1]
    if temp == "End":
        dataset.append(set_cord)
        set_cord = [[], []]
        i+=1
        continue 
    temp = temp.split()
    set_cord[0].append(float(temp[0])) #theta
    set_cord[1].append(float(temp[1])) #theta dot


N = len(dataset)
fig, ax = plt.subplots()
for i in range(0, N):
    ax.plot(dataset[i][0], dataset[i][1])
plt.show()
