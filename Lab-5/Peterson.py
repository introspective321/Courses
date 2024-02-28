import time
import threading

#Initialising the shared variables
turn = 0
flag = [False, False]
i=0
j=1

#Function to run process i
def process_i():
    global turn
    while(True):
        flag[i]=True
        turn = j
        while(flag[j] and turn == j):
            pass
        print("Process i is in critical section")
        time.sleep(2)
        flag[i]=False


#Function to run process j
def process_j():
    global turn
    while(True):
        flag[j]=True
        turn = i
        while(flag[i] and turn == i):
            pass
        print("Process j is in critical section")
        time.sleep(2)
        flag[j]=False

#Creating two threads to run both the processes concurrentlty
thread_i = threading.Thread(target=process_i)
thread_j = threading.Thread(target=process_j)

#Starting the threads
thread_i.start()
thread_j.start()
thread_i.join()
thread_j.join()

