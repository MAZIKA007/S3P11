#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Для использования std::setw()
#include <limits>  // Для обработки ошибок ввода
#include <cstdlib> // Для очистки экрана

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

// Максимальное количество ресурсов
const int MAX_RESOURCES = 1000;
EResource resources[MAX_RESOURCES];
int resourceCount = 0;

// Функция для очистки экрана
void clearScreen() {
    std::system("clear"); // Для Linux и macOS
}

// Функция для загрузки данных из файла
void loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    resourceCount = 0; // Обнуляем количество ресурсов
    while (file >> resources[resourceCount].id >> std::quoted(resources[resourceCount].title)
                >> std::quoted(resources[resourceCount].author) >> resources[resourceCount].category
                >> resources[resourceCount].year >> resources[resourceCount].access_link
                >> resources[resourceCount].views) {
        resourceCount++;
        if (resourceCount >= MAX_RESOURCES) break;
    }

    file.close();
}

void displayData() {
    // Определение ширины колонок
    int widthID = 5, widthTitle = 25, widthAuthor = 20, widthCategory = 15;
    int widthYear = 6, widthLink = 30, widthViews = 10;

    // Заголовок таблицы с точной шириной столбцов
    std::cout << std::left;
    std::cout << "=====================================================================================================================================\n";
    std::cout << "| " << std::setw(widthID) << "ID"
              << " | " << std::setw(widthTitle) << "Title"
              << " | " << std::setw(widthAuthor) << "Author"
              << " | " << std::setw(widthCategory) << "Category"
              << " | " << std::setw(widthYear) << "Year"
              << " | " << std::setw(widthLink) << "Link"
              << " | " << std::setw(widthViews) << "Views"
              << " |\n";
    std::cout << "=====================================================================================================================================\n";

    // Вывод каждого ресурса из массива
    for (int i = 0; i < resourceCount; ++i) {
        std::cout << "| " << std::setw(widthID) << resources[i].id
                  << " | " << std::setw(widthTitle) << resources[i].title.substr(0, widthTitle)
                  << " | " << std::setw(widthAuthor) << resources[i].author.substr(0, widthAuthor)
                  << " | " << std::setw(widthCategory) << resources[i].category.substr(0, widthCategory)
                  << " | " << std::setw(widthYear) << resources[i].year
                  << " | " << std::setw(widthLink) << resources[i].access_link.substr(0, widthLink)
                  << " | " << std::setw(widthViews) << resources[i].views
                  << " |\n";
        std::cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    std::cout << "=====================================================================================================================================\n";
}
// Функция для подсчета общего количества просмотров всех ресурсов
void calculateTotalViews() {
    clearScreen();
    int totalViews = 0;
    for (int i = 0; i < resourceCount; ++i) {
        totalViews += resources[i].views;
    }
    std::cout << "Общее количество просмотров всех ресурсов: " << totalViews << std::endl;
}

// Функция для добавления нового ресурса
void addResource() {
    clearScreen();
    if (resourceCount >= MAX_RESOURCES) {
        std::cerr << "Превышено максимальное количество ресурсов." << std::endl;
        return;
    }

    EResource newRes;

    // Присвоение нового ID
    newRes.id = resourceCount + 1;

    // Ввод остальных данных с проверкой на пустоту
    std::cout << "Введите название ресурса: ";
    std::getline(std::cin, newRes.title);
    if (newRes.title.empty()) {
        std::cerr << "Ошибка: Название не может быть пустым." << std::endl;
        return;
    }

    std::cout << "Введите автора: ";
    std::getline(std::cin, newRes.author);
    if (newRes.author.empty()) {
        std::cerr << "Ошибка: Автор не может быть пустым." << std::endl;
        return;
    }

    std::cout << "Введите категорию: ";
    std::getline(std::cin, newRes.category);
    if (newRes.category.empty()) {
        std::cerr << "Ошибка: Категория не может быть пустой." << std::endl;
        return;
    }

    std::cout << "Введите год: ";
    while (!(std::cin >> newRes.year) || newRes.year < 0) {
        std::cout << "Пожалуйста, введите корректный год: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(); // Для сброса буфера

    std::cout << "Введите ссылку: ";
    std::getline(std::cin, newRes.access_link);
    if (newRes.access_link.empty()) {
        std::cerr << "Ошибка: Ссылка не может быть пустой." << std::endl;
        return;
    }

    std::cout << "Введите количество просмотров: ";
    while (!(std::cin >> newRes.views) || newRes.views < 0) {
        std::cout << "Пожалуйста, введите корректное количество просмотров: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    resources[resourceCount] = newRes;
    resourceCount++;
}

// Функция для сохранения данных в новый файл
void saveData(const std::string& filename) {
    clearScreen();
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка сохранения в файл." << std::endl;
        return;
    }

    // Запись данных каждого ресурса в файл
    for (int i = 0; i < resourceCount; ++i) {
        file << resources[i].id << " " << std::quoted(resources[i].title) << " "
             << std::quoted(resources[i].author) << " " << resources[i].category << " "
             << resources[i].year << " " << resources[i].access_link << " "
             << resources[i].views << std::endl;
    }

    file.close();
    std::cout << "Данные успешно сохранены в файл: " << filename << std::endl;
}

// Функция для удаления ресурса по его ID
void deleteResource() {
    clearScreen();
    int id;
    std::cout << "Введите ID ресурса для удаления: ";
    while (!(std::cin >> id)) {
        std::cout << "Ошибка ввода! Пожалуйста, введите корректный ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool found = false;
    for (int i = 0; i < resourceCount; ++i) {
        if (resources[i].id == id) {
            for (int j = i; j < resourceCount - 1; ++j) {
                resources[j] = resources[j + 1]; // Сдвиг массива
            }
            resourceCount--; // Уменьшаем количество ресурсов
            found = true;
            std::cout << "Ресурс с ID " << id << " был удален." << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "Ресурс с таким ID не найден." << std::endl;
    }
}

int main() {
    std::string filename;
    std::cout << "Введите название файла для загрузки данных: ";
    std::cin >> filename;
    std::cin.ignore(); // Для сброса символа новой строки

    loadData(filename);

    int choice;
    while (true) {
        std::cout << "\nМеню:\n1. Просмотр ресурсов\n2. Добавить ресурс\n3. Подсчет просмотров\n4. Удалить ресурс\n5. Сохранить данные в новый файл\n6. Выйти\n";
        std::cout << "Выберите пункт: ";
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода! Пожалуйста, введите корректное число." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(); // Сбросить буфер

        if (choice == 1) {
            displayData();
        } else if (choice == 2) {
            addResource();
        } else if (choice == 3) {
            calculateTotalViews();
        } else if (choice == 4) {
            deleteResource();
        } else if (choice == 5) {
            std::string saveFilename;
            std::cout << "Введите название файла для сохранения данных: ";
            std::cin >> saveFilename;
            saveData(saveFilename);
        } else if (choice == 6) {
            break; // Выход
        } else {
            std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
        }

        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.get(); // Ожидание нажатия Enter
    }

    return 0;
}
