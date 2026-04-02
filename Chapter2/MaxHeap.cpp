/*Summary: 
The purpose of this program is to implement a max heap for tasks that hold a string description and a priority level.
*/

#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

struct Task{
    string name;
    string description;
    int priority;
};


class Heap{
public:
    void insert(Task newTask){
        taskList.push_back(newTask);
        heapifyUp();
    }
    void remove(){

        if(taskList.size() == 0){
            cout << "Heap is empty. No more tasks to remove." << endl;
            return;
        }
        
        taskList[0] = taskList[taskList.size() - 1];
        taskList.pop_back();

        heapifyDown();

    }

    void printHeap(){

        for(int i = 0; i < ceil(log2(taskList.size() + 1)); i++){
            cout << "Level " << i << ": ";
            
            for(int j = pow(2, i) - 1; j < pow(2, i + 1) - 1 && j < taskList.size(); j++){ 
                cout << "[ " << taskList[j].name << " - " << taskList[j].priority << " ]" << "  ";
            }
            cout << "\n";
        }
        cout << "----------------------" << endl;
    }
private:

    vector<Task> taskList;

    void heapifyUp(){

        //Set Indicies for readability
        int currentIndex = taskList.size() - 1;
        int parentIndex = (currentIndex - 1) / 2;

        while(currentIndex != 0 && taskList[currentIndex].priority > taskList[parentIndex].priority){
            
            //swap the tasks
            Task tempTask = taskList[currentIndex];
            taskList[currentIndex] = taskList[parentIndex];
            taskList[parentIndex] = tempTask;

            //recalculate the new parent indicies
            currentIndex = parentIndex;
            parentIndex = (currentIndex - 1) / 2;
        }
    }

    void heapifyDown(){
        
        //Set current index
        int currentIndex = 0; 
 
        //Set child indicies
        int childIndex_R = 2 * (currentIndex + 1);
        int childIndex_L = (2 * currentIndex) + 1;

        //initialize highest priority child index
        int childIndex_H;

        //Check which child has higher priority, set childIndex_H to that index
        if(childIndex_L < taskList.size() && childIndex_R < taskList.size()){
            if(taskList[childIndex_L].priority > taskList[childIndex_R].priority){
                    childIndex_H = childIndex_L;
                } else {
                    childIndex_H = childIndex_R;
                }
            } else {
                return;
            }


        //While the current index is not a leaf, and the current task has lower priority than the highest priority child, swap them
        while(taskList[currentIndex].priority < taskList[childIndex_H].priority){
                                                            
            Task tempTask = taskList[currentIndex];

            if(childIndex_L < taskList.size() && childIndex_R < taskList.size()){
                if(taskList[childIndex_L].priority > taskList[childIndex_R].priority){
                    childIndex_H = childIndex_L;
                } else {
                    childIndex_H = childIndex_R;
                }
            } else {
                break;
            }

            //the swap
            if(taskList[currentIndex].priority < taskList[childIndex_H].priority){
                taskList[currentIndex] = taskList[childIndex_H];
                taskList[childIndex_H] = tempTask;
            }

            //Update Indicies
            currentIndex = childIndex_H;
            childIndex_R = 2 * (currentIndex + 1);
            childIndex_L = (2 * currentIndex) + 1;
        }
    }

    
};

//No longer used print function
void printVector(vector<Task> taskList){
    for(int i = 0; i < taskList.size(); i++){
        cout << "Task " << i << ": "<< endl;
            cout << "TaskName: " << taskList[i].name << endl;
            cout << "TaskDescription:" << taskList[i].description << endl;
            cout << "TaskPriority: " << taskList[i].priority << endl;
        
        cout << "----------------------" << endl;

    }
}

int main(){

    Heap maxHeap;

    string input;
    string tempField;

    Task newTask;
    
    cout << "This program will ask you for tasks, and sort them in a tree based on priority.\n" 
            "Please enter the name of the task, a brief description, and the priority level, separated by commas.\n"
            "Enter a blank task if you would like to end.\n" << endl;
    

    while(true){
        //take in the user input
        getline(cin, input);

        //edgeCase
        if(input.empty()){
            cout << "Input was empty. No more tree entries" << endl;
            break;
        }

        //stringstream set to the user input
        stringstream ss(input);

        //use getline to set newTask.name to the first entry, ended by the delimiter
        getline(ss, newTask.name, ',');
        // cout << "Task Name: " << newTask.name << endl;

        //set newTask.description to the second entry, ended by the delimiter 
        getline(ss, newTask.description, ',');
        // cout << "Task Description:" << newTask.description << endl;

        //set tempField to the string in the third input, then use stoi to store new int as newTask.priority
        getline(ss, tempField, ',');
        newTask.priority = stoi(tempField);
        // cout << "Task Priority: " << newTask.priority << endl;

        //push it to the vector
        maxHeap.insert(newTask);
        // cout << "New Task: " << newTask.name << " inserted into the heap.\n";

        //clear ss
        ss.clear();
        // cout << "StringStream Cleared.\n" << endl;

        maxHeap.printHeap();
    }
}