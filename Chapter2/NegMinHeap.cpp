/*Summary: 
The purpose of this program is to implement a negated max heap for tasks that hold a string description and a priority level.
*/

#include <iostream> 
#include <string>
#include <vector>
#include <sstream>

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

        int childIndex_H;

        if(taskList[childIndex_L].priority > taskList[childIndex_R].priority){
            childIndex_H = childIndex_L;
        } else {
            childIndex_H = childIndex_R;
        }

        while(currentIndex != taskList.size() - 1 && taskList[currentIndex].priority < taskList[childIndex_H].priority){
                                                            
            Task tempTask = taskList[currentIndex];

            if(taskList[childIndex_L].priority > taskList[childIndex_R].priority){
                childIndex_H = childIndex_L;
            } else {
                childIndex_H = childIndex_R;
            }


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
        cout << "Task Name: " << newTask.name << endl;

        //set newTask.description to the second entry, ended by the delimiter 
        getline(ss, newTask.description, ',');
        cout << "Task Description:" << newTask.description << endl;

        //set tempField to the string in the third input, then use stoi to store new int as newTask.priority
        getline(ss, tempField, ',');
        newTask.priority = stoi(tempField);
        cout << "Task Priority: " << newTask.priority << endl;

        //push it to the vector
        maxHeap.insert(newTask);
        cout << "New Task: " << newTask.name << " inserted into the heap.\n";

        //clear ss
        ss.clear();
        cout << "StringStream Cleared.\n" << endl;
    }
}