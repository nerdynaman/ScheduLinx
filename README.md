# ScheduLinx

### Thread scheduling
Here we create three threads which run parallelly and call three different functions but which do same work but with scheduling policy of FIFO and RR and OTHER and also different priorities. At last we find time taken by each function to complete and compare them on basis of different scheduling policies and priorities. it is observed that SCHED_FIFO takes least time to complete and SCHED_RR takes more time than SCHED_FIFO and SCHED_OTHER takes more time than SCHED_RR on single core

### Process Scheduling
In this we create three forked process simulataneously and which further call three different bash scripts, which have instructions to compile unziped linux kernel source code. All three processes run with different scheduling policy and priorities and nice values in every iteration of program run. At last we find time taken by each process to complete and compare them on basis of different scheduling policies and priorities. the way by which we find time taken by each process is by using non blocking wait pid commands.
## Installation

1) Download the code by cloning the repo.
2) there is a makefile already provided with which can be run by typing `make` by being in the `main directory`.
3) Generated files for process scheduling and thread scheduling are in their respesctive folders.

## Usage
1) To run the process scheduling program, type
```bash
cd processScheduling
./processScheduling
```
2) To run the thread scheduling program, type
```bash
cd threadScheduling
./threadScheduling
```
Above commands have to be run from main directory of the project.

## Output
After the program is run, it will generate a file named `output.txt` in the respective folder. This file contains the time taken by each process/thread to complete the task.

There is also a `graph.py` file in the main directory which can be used to generate graphs from the output file. To run this file, type
```bash
python3 graph.py
```
Before running this file, make sure that the `output.txt` file is present in the main directory.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Appendix
If there is any issue in proper execution of the parts using semaphore then please give suffecient permissions to the files using `chmod` command.
