#include <algorithm>
#include <iostream>
#include <vector>

struct Process {
    size_t pid;
    float arrTime;
    float burstTime;
    float turnaroundTime;
    float waitingTime;
    Process(size_t pid_, float arrTime_, float burstTime_) : pid(pid_), arrTime(arrTime_), burstTime(burstTime_),
            waitingTime(0), turnaroundTime(0) {}
};

class FirstComeFirstServed {
    private:
        std::vector<Process> processes;
    public:
        FirstComeFirstServed() {}
        void addProcess(int pid, float arrivalTime, float burstTime) {
            processes.push_back(Process(pid, arrivalTime, burstTime));
        }
        void schedule() {
        if (processes.empty()) {
            std::cout << "There are no processes." << std::endl;
            return;
        }
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.arrTime < b.arrTime;
        });
        
        float currentTime = 0.0;
        for (int i = 0; i < processes.size(); ++i) {
            if (currentTime < processes[i].arrTime) {
                currentTime = processes[i].arrTime;
            }
            processes[i].waitingTime = currentTime - processes[i].arrTime;
            currentTime += processes[i].burstTime;
            processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
            processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

            std::cout << "Process Id " << processes[i].pid << std::endl;
            std::cout << "Process arrival time " << processes[i].arrTime << std::endl;
            std::cout << "Process burst time " << processes[i].burstTime << std::endl;
            std::cout << "Process turn around time " << processes[i].turnaroundTime << std::endl;
            std::cout << "Process waiting time " << processes[i].waitingTime << std::endl;
        }
    }
};

int main() {
    FirstComeFirstServed fcfs;
    fcfs.addProcess(1, 0, 6);
    fcfs.addProcess(2, 3, 4);
    fcfs.addProcess(3, 4, 8);
    fcfs.addProcess(4, 7, 5);
    fcfs.schedule();
}