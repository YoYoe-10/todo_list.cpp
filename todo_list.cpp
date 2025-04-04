#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
struct Task {
    int id;
    string description;
    bool isDone;
};

vector<Task> tasks;
int taskCounter = 1;

void addTask() {
    Task newTask;
    newTask.id = taskCounter++;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, newTask.description);
    newTask.isDone = false;
    tasks.push_back(newTask);
    cout << "Task added" << endl;
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No Tasks available.\n";
        return;
    }
    for (const auto& task : tasks) {
        cout << "[" << task.id << "] "
              << (task.isDone ? "[DONE]" : "[NOT DONE]")
              << task.description << endl;
    }
}

void markTaskDone() {
    int id;
    cout << "Enter task ID to mark as done: ";
    cin >> id;
    for (auto& task : tasks) {
        if (task.id == id) {
            task.isDone = true;
            cout << "Task marked as done.";
            return;
        }
    }
    cout << "Task not found.\n";
}

void deleteTask() {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;
    for (auto it = tasks.begin(); it != tasks.end(); it++) {
        if (it->id == id) {
            tasks.erase(it);
            cout << "Task deleted.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void saveTasksToFile() {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task.id << "|" << task.description << "|" << task.isDone << "\n";
    }
    file.close();
    cout << "Tasks saved to file.\n";
}

void loadTasksFromFile() {
    ifstream file("tasks.txt");
    if (!file.is_open()) return;

    tasks.clear();
    Task task;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find_first_of("|");
        size_t pos2 = line.find_first_of("|", pos1 + 1);

        task.id = stoi(line.substr(0, pos1));
        task.description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        task.isDone = stoi(line.substr(pos2 + 1));

        tasks.push_back(task);

        if (task.id >= taskCounter) {
            taskCounter = task.id + 1;
        }
    }
    file.close();
}
int main() {
    loadTasksFromFile();
    int choice;
    while (true) {
        cout << "\n--- TO-DO LIST ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Done\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markTaskDone(); break;
            case 4: deleteTask(); break;
            case 5: saveTasksToFile(); return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}