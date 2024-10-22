#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
    // Считывание данных ресурса из файла
    while (file >> temp.id >> temp.title >> temp.author >> temp.category >> temp.year >> temp.access_link >> temp.views) {
        resources.push_back(temp); // Добавление ресурса в вектор
    }
    file.close();
}

// Функция для отображения данных о ресурсах
void displayData() {
    for (const auto& res : resources) {
        std::cout << "============================\n";
        std::cout << "ID: " << res.id << "\nНазвание: " << res.title 
                  << "\nАвтор: " << res.author
                  << "\nКатегория: " << res.category 
                  << "\nГод: " << res.year 
                  << "\nСсылка: " << res.access_link 
                  << "\nПросмотры: " << res.views << "\n";
    }
    std::cout << "============================\n";
}

// Функция для редактирования ресурса по его ID
void editResource(int id) {
    for (auto& res : resources) {
        if (res.id == id) {
            // Ввод новых данных для ресурса
            std::cout << "Введите новые данные для ресурса (название, автор, категория, год, ссылка, просмотры): ";
            std::cin >> res.title >> res.author >> res.category >> res.year >> res.access_link >> res.views;
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

    // Записываем данные каждого ресурса в файл
    for (const auto& res : resources) {
        file << res.id << " " << res.title << " " << res.author << " " << res.category << " "
             << res.year << " " << res.access_link << " " << res.views << std::endl;
    }
    file.close();
}

// Функция для добавления нового ресурса
void addResource() {
    EResource newRes;

    // Автоматическое присвоение нового ID
    int maxId = 0;
    for (const auto& res : resources) {
        if (res.id > maxId) {
            maxId = res.id;
        }
    }
    newRes.id = maxId + 1; // Новый ID больше максимального на 1

    // Ввод остальных данных о ресурсе
    std::cout << "Введите название ресурса: ";
    std::cin.ignore(); // Игнорируем лишний ввод
    std::getline(std::cin, newRes.title);

    std::cout << "Введите автора: ";
    std::getline(std::cin, newRes.author);

    std::cout << "Введите категорию: ";
    std::getline(std::cin, newRes.category);

    std::cout << "Введите год: ";
    while (!(std::cin >> newRes.year) || newRes.year < 0) {
        std::cout << "Пожалуйста, введите корректный год: ";
        std::cin.clear(); // Очистка потока ввода в случае ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите ссылку: ";
    std::cin.ignore(); // Сброс ввода перед использованием getline
    std::getline(std::cin, newRes.access_link);

    std::cout << "Введите количество просмотров: ";
    while (!(std::cin >> newRes.views) || newRes.views < 0) {
        std::cout << "Пожалуйста, введите корректное количество просмотров: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    resources.push_back(newRes); // Добавляем новый ресурс в вектор
    saveData("new_resources.txt"); // Автоматически сохраняем данные
}

// Функция для удаления ресурса по его ID
void deleteResource(int id) {
    bool found = false;
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->id == id) {
            resources.erase(it); // Удаление ресурса
            saveData("new_resources.txt"); // Сохранение изменений
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
    std::string filename = "resources.txt";
    loadData(filename); // Загрузка данных при старте программы

    int choice;
    while (true) {
        std::cout << "Меню:\n1. Просмотр ресурсов\n2. Редактировать ресурс\n3. Подсчет просмотров\n4. Добавить ресурс\n5. Удалить ресурс\n6. Выйти\n";
        if (!(std::cin >> choice)) {
            std::cout << "Пожалуйста, введите корректный выбор." << std::endl;
            std::cin.clear(); // Очистка в случае некорректного ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Обработка выбора пользователя
        if (choice == 1) {
            displayData(); // Показать все ресурсы
        } else if (choice == 2) {
            int id;
            std::cout << "Введите ID ресурса для редактирования: ";
            while (!(std::cin >> id)) {
                std::cout << "Ошибка ввода! Пожалуйста, введите корректный ID: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            editResource(id); // Редактировать ресурс
        } else if (choice == 3) {
            calculateTotalViews(); // Подсчитать общее количество просмотров
        } else if (choice == 4) {
            addResource(); // Добавить новый ресурс
        } else if (choice == 5) {
            int id;
            std::cout << "Введите ID ресурса для удаления: ";
            while (!(std::cin >> id)) {
                std::cout << "Ошибка ввода! Пожалуйста, введите корректный ID: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            deleteResource(id); // Удалить ресурс
        } else if (choice == 6) {
            break; // Выйти из программы
        } else {
            std::cout << "Неверный выбор." << std::endl;
        }
    }

    return 0;
}

