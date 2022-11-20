import numpy as np
import matplotlib.pyplot as plt
# read from a file and store the data in string
with open('data.txt', 'r') as f:
    data = f.readlines()
priority = [10, 20, 30, 40, 50, 60] # comment out maybe
niceValues = [2,4,6,8,10,12]        # comment out maybe
SCHEDOTHER = []
SCHEDFIFO = []
SCHEDRR = []
for i in range(len(data)):
    # priority.append(int(data[i].split()[-2]))
    # niceValues.append(int(data[i].split()[-1]))
    if data[i].split()[0][0] == 'A':
        SCHEDOTHER.append(float((data[i].split()[0])[1:]))
    elif data[i].split()[0][0] == 'B':
        SCHEDFIFO.append(float((data[i].split()[0])[1:]))
    elif data[i].split()[0][0] == 'C':
        SCHEDRR.append(float((data[i].split()[0])[1:]))

    if data[i].split()[1][0] == 'A':
        SCHEDOTHER.append(float((data[i].split()[1])[1:]))
    elif data[i].split()[1][0] == 'B':
        SCHEDFIFO.append(float((data[i].split()[1])[1:]))
    elif data[i].split()[1][0] == 'C':
        SCHEDRR.append(float((data[i].split()[1])[1:]))

    if data[i].split()[2][0] == 'A':
        SCHEDOTHER.append(float((data[i].split()[2])[1:]))
    elif data[i].split()[2][0] == 'B':
        SCHEDFIFO.append(float((data[i].split()[2])[1:]))
    elif data[i].split()[2][0] == 'C':
        SCHEDRR.append(float((data[i].split()[2])[1:]))
print(SCHEDOTHER)
print(SCHEDFIFO)
print(SCHEDRR)
print(priority)
print(niceValues)
figure = plt.subplots(figsize =(12, 8))
width = 0.25
fp1 = np.arange(len(SCHEDOTHER))
fp2 = [x + width for x in fp1]
fp3 = [x + width for x in fp2]
plt.bar(fp1, SCHEDOTHER, color ='b', width = width, label ='SCHED_OTHER')
plt.bar(fp2, SCHEDFIFO, color ='g', width = width, label ='SCHED_FIFO')
plt.bar(fp3, SCHEDRR, color ='r', width = width, label ='SCHED_RR')
plt.ylabel('Time')
plt.xlabel('priorities and nice value')
ar = [num for num in range(len(SCHEDOTHER))]+[num + 2*width for num in range(len(SCHEDOTHER))]
plt.xticks(ar , [f'nice: {niceValues[0]}', f'nice: {niceValues[1]}',f'nice: {niceValues[2]}',f'nice: {niceValues[3]}',f'nice: {niceValues[4]}',f'nice: {niceValues[5]}', f'priority: {priority[0]}',f'priority: {priority[1]}',f'priority: {priority[2]}',f'priority: {priority[3]}',f'priority: {priority[4]}',f'priority: {priority[5]}'])
plt.legend()
plt.show()