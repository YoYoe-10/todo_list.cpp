#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
struct Task {
    int id;
    string description;
    bool isDone;
    string dueDate;
};

vector<Task> tasks;
int taskCounter = 1;

bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < date.length(); i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

void addTask() {
    Task newTask;
    newTask.id = taskCounter++;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, newTask.description);
    string inputDate;
    while (true) {
        cout << "Enter due date (YYYY-MM-DD): ";
        getline(cin, inputDate);

        if (isValidDate(inputDate)) {
            newTask.dueDate = inputDate;
            break;
        } else {
            cout << "Invalid format. Please use YYYY-MM-DD.\n";
        }
    }
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
              << task.description << "(Due: " << task.dueDate << ")" << endl;
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

void editTask() {
    int id;
    cout << "Enter task ID to edit: ";
    cin >> id;
    cin.ignore();

    for (auto& task : tasks) {
        if (task.id == id) {
            cout << "Current description: " << task.description << endl;
            cout << "Enter new description: ";
            getline(cin, task.description);
            cout << "Task updated.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void filterTasksByStatus() {
    int choice;
    cout << "View which tasks?\n";
    cout << "1. Completed tasks\n";
    cout << "2. Incomplete tasks\n";
    cout << "Choice option: ";
    cin >> choice;

    bool found = false;

    for (const auto& task : tasks) {
        if ((choice == 1 & task.isDone) || (choice == 2 & !task.isDone)) {
            cout << "[" << task.id << "]"
                 << (task.isDone ? "[DONE]" : "[NOT DONE]")
                 << task.description << " (Due: " << task.dueDate << ")" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Not matching tasks found.\n";
    }
}

bool compareByDueDate(const Task& a, const Task& b) {
    return a.dueDate < b.dueDate;
}

void sortTasksByDueDate() {
    if (tasks.empty()) {
        cout << "No tasks to sort.\n";
        return;
    }
    sort(tasks.begin(), tasks.end(), compareByDueDate);
    cout << "Tasks sorted by due date:\n";
    for (const auto& task : tasks) {
        cout << "[" << task.id << "] "
             << (task.isDone ? "[DONE]" : "[NOT DONE]")
             << task.description << " (Due: " << task.dueDate << ")" << endl;
    }
}

void saveTasksToFile() {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task.id << "|" << task.description << "|" << task.isDone << "|" << task.dueDate << "\n";
    }
    file.close();
    cout << "Tasks saved to file.\n";
}

void loadTasksFromFile() {
    ifstream file("tasks.txt");
    if (!file.is_open()) return;

    tasks.clear();
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;

        Task task;
        task.id = stoi(line.substr(0, pos1));
        task.description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        task.isDone = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        task.dueDate = line.substr(pos3 + 1);

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
        cout << "5. Edit Task\n";
        cout << "6. View Done/Not Done Tasks\n";
        cout << "7. Sort Tasks by Due Date\n";
        cout << "8. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markTaskDone(); break;
            case 4: deleteTask(); break;
            case 5: editTask(); break;
            case 6: filterTasksByStatus(); break;
            case 7: sortTasksByDueDate(); break;
            case 8: saveTasksToFile(); return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}