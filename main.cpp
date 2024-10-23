#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>

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

// Константа для максимального количества ресурсов
const int MAX_RESOURCES = 100;

// Массив для хранения ресурсов
EResource resources[MAX_RESOURCES];
int resourceCount = 0;

// Функция для очистки терминала
void clearScreen() {
    std::system("clear"); 
}

// Функция для загрузки данных из файла
void loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    while (file >> resources[resourceCount].id) {
        file >> std::ws; // Игнорировать пробелы
        std::getline(file, resources[resourceCount].title);
        std::getline(file, resources[resourceCount].author);
        std::getline(file, resources[resourceCount].category);
        file >> resources[resourceCount].year;
        file >> std::ws; // Игнорировать пробелы
        std::getline(file, resources[resourceCount].access_link);
        file >> resources[resourceCount].views;

        resourceCount++;
    }
    file.close();
}

void displayData() {
    std::cout << "============================\n";
    std::cout << " ID | Название               | Автор                 | Категория         | Год | Ссылка                      | Просмотры\n";
    std::cout << "----|------------------------|-----------------------|-------------------|-----|-----------------------------|----------\n";
    for (int i = 0; i < resourceCount; i++) {
        std::cout << " " << resources[i].id << " | "
                  << resources[i].title << " | "
                  << resources[i].author << " | "
                  << resources[i].category << " | "
                  << resources[i].year << " | "
                  << resources[i].access_link << " | "
                  << resources[i].views << "\n";
    }
    std::cout << "============================\n";
}

void addResource() {
    if (resourceCount >= MAX_RESOURCES) {
        std::cout << "Достигнуто максимальное количество ресурсов." << std::endl;
        return;
    }

    EResource newRes;
    newRes.id = resourceCount + 1; // Новый ID больше текущего количества

    std::cout << "Введите название ресурса: ";
    std::getline(std::cin >> std::ws, newRes.title);
    if (newRes.title.empty()) {
        std::cerr << "Название не может быть пустым." << std::endl;
        return;
    }

    std::cout << "Введите автора: ";
    std::getline(std::cin >> std::ws, newRes.author);
    if (newRes.author.empty()) {
        std::cerr << "Автор не может быть пустым." << std::endl;
        return;
    }

    std::cout << "Введите категорию: ";
    std::getline(std::cin >> std::ws, newRes.category);
    if (newRes.category.empty()) {
        std::cerr << "Категория не может быть пустой." << std::endl;
        return;
    }

    std::cout << "Введите год: ";
    while (!(std::cin >> newRes.year) || newRes.year < 0) {
        std::cout << "Пожалуйста, введите корректный год: ";
        std::cin.clear(); // Очистка потока ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите ссылку: ";
    std::getline(std::cin >> std::ws, newRes.access_link);
    if (newRes.access_link.empty()) {
        std::cerr << "Ссылка не может быть пустой." << std::endl;
        return;
    }

    std::cout << "Введите количество просмотров: ";
    while (!(std::cin >> newRes.views) || newRes.views < 0) {
        std::cout << "Пожалуйста, введите корректное количество просмотров: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    resources[resourceCount++] = newRes; // Добавляем новый ресурс
}

// Функция для редактирования ресурса по его ID
void editResource(int id) {
    for (int i = 0; i < resourceCount; i++) {
        if (resources[i].id == id) {
            std::cout << "Введите новые данные для ресурса (пустое значение оставит старое):\n";
            std::string input;

            std::cout << "Название (текущее: " << resources[i].title << "): ";
            std::getline(std::cin >> std::ws, input);
            if (!input.empty()) resources[i].title = input;

            std::cout << "Автор (текущий: " << resources[i].author << "): ";
            std::getline(std::cin >> std::ws, input);
            if (!input.empty()) resources[i].author = input;

            std::cout << "Категория (текущая: " << resources[i].category << "): ";
            std::getline(std::cin >> std::ws, input);
            if (!input.empty()) resources[i].category = input;

            std::cout << "Год (текущий: " << resources[i].year << "): ";
            std::string yearInput;
            std::getline(std::cin >> std::ws, yearInput);
            if (!yearInput.empty()) resources[i].year = std::stoi(yearInput);

            std::cout << "Ссылка (текущая: " << resources[i].access_link << "): ";
            std::getline(std::cin >> std::ws, input);
            if (!input.empty()) resources[i].access_link = input;

            std::cout << "Просмотры (текущие: " << resources[i].views << "): ";
            std::string viewsInput;
            std::getline(std::cin >> std::ws, viewsInput);
            if (!viewsInput.empty()) resources[i].views = std::stoi(viewsInput);

            return;
        }
    }
    std::cout << "Ресурс с таким ID не найден." << std::endl;
}

// Функция для удаления ресурса по его ID
void deleteResource(int id) {
    for (int i = 0; i < resourceCount; i++) {
        if (resources[i].id == id) {
            // Сдвигаем все элементы после удаляемого на одну позицию влево
            for (int j = i; j < resourceCount - 1; j++) {
                resources[j] = resources[j + 1];
            }
            resourceCount--; // Уменьшаем количество ресурсов
            std::cout << "Ресурс с ID " << id << " был удален." << std::endl;
            return;
        }
    }
    std::cout << "Ресурс с таким ID не найден." << std::endl;
}

// Функция для подсчета общего количества просмотров
void calculateTotalViews() {
    int totalViews = 0;
    int maxViews = 0;
    int maxIndex = -1;

    for (int i = 0; i < resourceCount; i++) {
        totalViews += resources[i].views; // Суммируем количество просмотров
        if (resources[i].views > maxViews) {
            maxViews = resources[i].views;
            maxIndex = i; // Сохраняем индекс ресурса с максимальными просмотрами
        }
    }

    std::cout << "Общее количество просмотров всех ресурсов: " << totalViews << std::endl;
    if (maxIndex != -1) {
        std::cout << "Ресурс с наибольшим количеством просмотров:\n";
        std::cout << " ID: " << resources[maxIndex].id
                  << "\nНазвание: " << resources[maxIndex].title
                  << "\nАвтор: " << resources[maxIndex].author
                  << "\nКатегория: " << resources[maxIndex].category
                  << "\nГод: " << resources[maxIndex].year
                  << "\nСсылка: " << resources[maxIndex].access_link
                  << "\nПросмотры: " << resources[maxIndex].views << "\n";
    }
}

void saveSessionData(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла для записи: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < resourceCount; i++) {
        file << resources[i].id << " "
             << resources[i].title << " "
             << resources[i].author << " "
             << resources[i].category << " "
             << resources[i].year << " "
             << resources[i].access_link << " "
             << resources[i].views << std::endl;
    }
    file.close();
    std::cout << "Данные сохранены в файл: " << filename << std::endl;
}

void mainMenu() {
    std::string filename;
    std::cout << "Введите имя файла для загрузки данных: ";
    std::cin >> filename;

    loadData(filename); 

    int choice;
    while (true) {
        clearScreen();
        std::cout << "Меню:\n";
        std::cout << "1. Просмотр ресурсов\n";
        std::cout << "2. Добавить ресурс\n";
        std::cout << "3. Редактировать ресурс\n";
        std::cout << "4. Удалить ресурс\n";
        std::cout << "5. Подсчет просмотров\n";
        std::cout << "6. Сохранить данные в новый файл\n";
        std::cout << "0. Выйти\n";
        std::cout << "Выберите пункт меню: ";

        while (!(std::cin >> choice) || choice < 0 || choice > 6) {
            std::cout << "Ошибка ввода! Пожалуйста, введите корректный пункт меню: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice == 1) {
            displayData();
        } else if (choice == 2) {
            addResource();
        } else if (choice == 3) {
            int id;
            std::cout << "Введите ID ресурса для редактирования: ";
            while (!(std::cin >> id)) {
                std::cout << "Ошибка ввода! Пожалуйста, введите корректный ID: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            editResource(id);
        } else if (choice == 4) {
            int id;
            std::cout << "Введите ID ресурса для удаления: ";
            while (!(std::cin >> id)) {
                std::cout << "Ошибка ввода! Пожалуйста, введите корректный ID: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            deleteResource(id);
        } else if (choice == 5) {
            calculateTotalViews();
        } else if (choice == 6) {
            std::string saveFilename;
            std::cout << "Введите имя нового файла для сохранения данных: ";
            std::cin >> saveFilename;
            saveSessionData(saveFilename);
        } else if (choice == 0) {
            break;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
