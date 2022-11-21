Thread scheduling:
    here we create three threads which run parallelly and call three different functions but which 
    do same work but with scheduling policy of FIFO and RR and OTHER and also different priorities.
    At last we find time taken by each function to complete and compare them on basis of different
    scheduling policies and priorities.
    it is observed that SCHED_FIFO takes least time to complete and SCHED_RR takes more time than
    SCHED_FIFO and SCHED_OTHER takes more time than SCHED_RR on single core 

Process Scheduling:
    in this we create three forked process simulataneously and which further call three different bash scripts, which have 
    instructions to compile unziped linux kernel source code. All three processes run with different scheduling policy and
    priorities and nice values in every iteration of program run. At last we find time taken by each process to complete and compare them on basis of           different scheduling policies and priorities. the way by which we find time taken by each process is by using non blocking wait pid commands.
