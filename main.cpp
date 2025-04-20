#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

const std::string TASK_FILE = "tasks.txt";

// Task structure
struct Task {
    std::string description;
    std::string dueDate;
};

// Show menu options
void showMenu() {
    std::cout << "\n===== Task Manager =====\n";
    std::cout << "1. View Tasks\n";
    std::cout << "2. Add Task\n";
    std::cout << "3. Delete Task\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

// Load tasks from file
std::vector<Task> loadTasks() {
    std::ifstream file(TASK_FILE);
    std::vector<Task> tasks;
    std::string line;

    while (getline(file, line)) {
        size_t sep = line.find('|');
        if (sep != std::string::npos) {
            Task t;
            t.description = line.substr(0, sep - 1); // trim before '|'
            t.dueDate = line.substr(sep + 2);        // skip "| "
            tasks.push_back(t);
        }
    }

    return tasks;
}

// Save tasks to file
void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file(TASK_FILE);
    for (const auto& task : tasks) {
        file << task.description << " | " << task.dueDate << "\n";
    }
}

// View all tasks
void viewTasks() {
    std::vector<Task> tasks = loadTasks();
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }

    std::cout << "\n--- Your Tasks ---\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i].description
                  << " (Due: " << tasks[i].dueDate << ")\n";
    }
}

// Add a new task
void addTask() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Task newTask;

    std::cout << "Enter task description: ";
    getline(std::cin, newTask.description);

    std::cout << "Enter due date (e.g. 2025-04-22): ";
    getline(std::cin, newTask.dueDate);

    std::ofstream file(TASK_FILE, std::ios::app);
    file << newTask.description << " | " << newTask.dueDate << "\n";

    std::cout << "Task added!\n";
}

// Delete a task
void deleteTask() {
    std::vector<Task> tasks = loadTasks();
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

// Main loop
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