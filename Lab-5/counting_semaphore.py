import time
import threading

#Shared resource and semaphore
res = [0, 0, 0]
S = threading.Semaphore(3)


#Wait
def P(S):
    S.acquire()

#Signal
def V(S):
    S.release()

#Thread
def thread(i):
    print(f"Thread {i} is waiting")
    P(S)
    print(f"Thread {i} is in critical section")
    res[i%3] +=1
    print(f"Resource: {res}")
    time.sleep(2)
    V(S)
    print(f"Thread {i} is out of critical section")

#Creating 10 threads and starting 
threads = [threading.Thread(target=thread, args=(i,)) for i in range(10)]
for i in threads:
    i.start()

for i in threads:
    i.join()

print("All threads are done using the shared resource.")
print(f"Final resource: {res}")