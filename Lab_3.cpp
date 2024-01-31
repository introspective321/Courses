//B22AI007
//PCS_2 LAB_3
#include <queue>
#include <iostream>

// Process Control Block
class PCB {
    public:
        int id;
        std::string state;
        int priority;

        PCB(int id, std::string state, int priority) : id(id), state(state), priority(priority) {}

        void changeState(std::string newstate){
            state=newstate;
        }
};

// Long-Term Scheduler
class LongTermScheduler {
    private:
        std::queue<PCB> readyQueue;
    public:
        void addProcess(PCB process) {
            readyQueue.push(process);
        }

        PCB getNextProcess() {
            PCB nextp = readyQueue.front();
            readyQueue.pop();

            return nextp;
        }

        bool hasprocess(){
            return !readyQueue.empty();
        }
};

// Short-Term Scheduler
class ShortTermScheduler {
public:
    void executeProcess(LongTermScheduler& LTS) {
        if(LTS.hasprocess()){
            PCB process = LTS.getNextProcess();
            process.changeState("Running");

            std::cout << "Process with PID: "<<process.id << " is getting executed" << std::endl;
        }

    }
};

int main() {
    LongTermScheduler LTS;
    ShortTermScheduler STS;

    // Create dummy processes and add them to the ready queue
    for (int i = 0; i <15; i++) {
        PCB process(i, "Ready", i);
        LTS.addProcess(process);
    }

    // Execute processes from the ready queue
    while (LTS.hasprocess()) {
        STS.executeProcess(LTS);
        std::cout<< "Done\n";
    }

    return 0;
}
