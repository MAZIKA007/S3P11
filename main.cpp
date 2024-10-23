#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

// Структура для хранения данных об электронных ресурсах
struct EResource {
    int id;
    std::string title;
    std::string author;
    std::string category;
    int year;
    std::string access_link;
    int views;
};

// Вектор для хранения всех ресурсов
std::vector<EResource> resources;

// Функция для загрузки данных из файла
void loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    EResource temp;
    while (file >> temp.id >> temp.title >> temp.author >> temp.category >> temp.year >> temp.access_link >> temp.views) {
        resources.push_back(temp); // Добавление ресурса в вектор
    }
    file.close();
}

// Функция для отображения данных о ресурсах в виде таблицы
void displayData() {
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(20) << "Название"
              << std::setw(15) << "Автор"
              << std::setw(15) << "Категория"
              << std::setw(6) << "Год"
              << std::setw(30) << "Ссылка"
              << std::setw(10) << "Просмотры" << std::endl;

    std::cout << "======================================================================" << std::endl;

    for (const auto& res : resources) {
        std::cout << std::left << std::setw(5) << res.id
                  << std::setw(20) << res.title
                  << std::setw(15) << res.author
                  << std::setw(15) << res.category
                  << std::setw(6) << res.year
                  << std::setw(30) << res.access_link
                  << std::setw(10) << res.views << std::endl;
    }
    std::cout << "======================================================================" << std::endl;
}

// Функция для редактирования ресурса по его ID
void editResource(int id) {
    for (auto& res : resources) {
        if (res.id == id) {
            std::cout << "Введите новые данные для ресурса (название, автор, категория, год, ссылка, просмотры): ";

            std::cin.ignore();
            std::getline(std::cin, res.title);
            std::getline(std::cin, res.author);
            std::getline(std::cin, res.category);
            
            while (!(std::cin >> res.year) || res.year < 0) {
                std::cout << "Ошибка! Введите корректный год: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            std::cin.ignore();
            std::getline(std::cin, res.access_link);
            
            while (!(std::cin >> res.views) || res.views < 0) {
                std::cout << "Ошибка! Введите корректное количество просмотров: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            return;
        }
    }
    std::cout << "Ресурс с таким ID не найден." << std::endl;
}

// Функция для подсчета общего количества просмотров всех ресурсов
void calculateTotalViews() {
    int totalViews = 0;
    for (const auto& res : resources) {
        totalViews += res.views; // Суммируем количество просмотров
    }
    std::cout << "Общее количество просмотров всех ресурсов: " << totalViews << std::endl;
}

// Функция для сохранения данных в файл
void saveData(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка сохранения в файл." << std::endl;
        return;
    }

    for (const auto& res : resources) {
        file << res.id << " " << res.title << " " << res.author << " " << res.category << " "
             << res.year << " " << res.access_link << " " << res.views << std::endl;
    }
    file.close();
}

// Функция для добавления нового ресурса
void addResource() {
    EResource newRes;

    int maxId = 0;
    for (const auto& res : resources) {
        if (res.id > maxId) {
            maxId = res.id;
        }
    }
    newRes.id = maxId + 1;

    std::cout << "Введите название ресурса: ";
    std::cin.ignore();
    std::getline(std::cin, newRes.title);

    std::cout << "Введите автора: ";
    std::getline(std::cin, newRes.author);

    std::cout << "Введите категорию: ";
    std::getline(std::cin, newRes.category);

    std::cout << "Введите год: ";
    while (!(std::cin >> newRes.year) || newRes.year < 0) {
        std::cout << "Пожалуйста, введите корректный год: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите ссылку: ";
    std::cin.ignore();
    std::getline(std::cin, newRes.access_link);

    std::cout << "Введите количество просмотров: ";
    while (!(std::cin >> newRes.views) || newRes.views < 0) {
        std::cout << "Пожалуйста, введите корректное количество просмотров: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    resources.push_back(newRes);
    saveData("resources.txt");
}

// Функция для удаления ресурса по его ID
void deleteResource(int id) {
    bool found = false;
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->id == id) {
            resources.erase(it);
            saveData("resources.txt");
            std::cout << "Ресурс с ID " << id << " был удален." << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Ресурс с таким ID не найден." << std::endl;
    }
}

int main() {
    // Загрузка данных из фиксированного файла "resources.txt"
    const std::string filename = "resources.txt";
    loadData(filename);

    int choice;
    while (true) {
        std::cout << "\nМеню:\n1. Просмотр ресурсов\n2. Редактировать ресурс\n3. Подсчет просмотров\n4. Добавить ресурс\n5. Удалить ресурс\n6. Сохранить данные в новый файл\n7. Выйти\n";
        if (!(std::cin >> choice)) {
            std::cout << "Пожалуйста, введите корректный выбор." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            displayData();
        } else if (choice == 2) {
            int id;
            std::cout << "Введите ID ресурса для редактирования: ";
            while (!(std::cin >> id)) {
                std::cout << "Ошибка! Введите корректный ID: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            editResource(id);
        } else if (choice == 3) {
            calculateTotalViews();
        } else if (choice == 4) {
            addResource();
        } else if (choice == 5) {
            int id;
            std::cout << "Введите ID ресурса для удаления: ";
            while (!(std::cin >> id)) {
                std::cout << "Ошибка! Введите корректный ID: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            deleteResource(id);
        } else if (choice == 6) {
            std::string newFilename;
            std::cout << "Введите название нового файла для сохранения данных: ";
            std::cin >> newFilename;
            saveData(newFilename);
        } else if (choice == 7) {
            break;
        } else {
            std::cout << "Неверный выбор." << std::endl;
        }
    }

    return 0;
}
