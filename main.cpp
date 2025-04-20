#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

const std::string TASK_FILE = "tasks.txt";

void showMenu() {
    std::cout << "\n===== Task Manager =====\n";
    std::cout << "1. View Tasks\n";
    std::cout << "2. Add Task\n";
    std::cout << "3. Delete Task\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

std::vector<std::string> loadTasks() {
    std::ifstream file(TASK_FILE);
    std::vector<std::string> tasks;
    std::string line;
    while (getline(file, line)) {
        tasks.push_back(line);
    }
    return tasks;
}

void saveTasks(const std::vector<std::string>& tasks) {
    std::ofstream file(TASK_FILE);
    for (const auto& task : tasks) {
        file << task << "\n";
    }
}

void viewTasks() {
    std::vector<std::string> tasks = loadTasks();
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    std::cout << "\n--- Your Tasks ---\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i] << "\n";
    }
}

void addTask() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string task;
    std::cout << "Enter new task: ";
    getline(std::cin, task);
    std::ofstream file(TASK_FILE, std::ios::app);
    file << task << "\n";
    std::cout << "Task added!\n";
}

void deleteTask() {
    std::vector<std::string> tasks = loadTasks();
    viewTasks();
    if (tasks.empty()) return;
    int index;
    std::cout << "Enter task number to delete: ";
    std::cin >> index;
    if (index < 1 || index > tasks.size()) {
        std::cout << "Invalid task number.\n";
        return;
    }
    tasks.erase(tasks.begin() + index - 1);
    saveTasks(tasks);
    std::cout << "Task deleted!\n";
}

int main() {
    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: viewTasks(); break;
            case 2: addTask(); break;
            case 3: deleteTask(); break;
            case 4: std::cout << "Goodbye!\n"; return 0;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}