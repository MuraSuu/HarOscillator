import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import subprocess

"""
The code here is modified so I doesnt print the phase space, but
a x-t 'space', where t is time.
"""

dataset = []
set_cord = [[], []]
cmd = './error.o'
process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
i = 0

for line in process.stdout:
    temp = (line.decode("ASCII"))[:-1]
    if temp == 'End':
        i+=1
        dataset.append(set_cord)
        set_cord = [[], []]
        continue
    temp = temp.split()
    set_cord[0].append(float(temp[0])) #time
    set_cord[1].append(float(temp[1])) #x

fig, main_ax = plt.subplots()
N = len(dataset)
for i in range(0, N):
    main_ax.plot(dataset[i][0], dataset[i][1])
main_ax.set_xlabel('t')
main_ax.set_ylabel('x')
main_ax.set_title("phase space")
plt.show()
