target:
	gcc processScheduling/processScheduling.c -o processScheduling/processScheduling
	gcc threadScheduling/threadScheduling.c -o threadScheduling/threadScheduling
	processScheduling/./processScheduling
	threadScheduling/./threadScheduling