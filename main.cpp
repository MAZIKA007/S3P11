#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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

// Динамический массив
EResource* resources = nullptr;
int resourceCount = 0;  // Текущее количество ресурсов
int capacity = 0;       // Текущая емкость массива

// Функция для увеличения размера массива
void resizeArray() {
    int newCapacity = (capacity == 0) ? 10 : capacity * 2; // Увеличиваем размер
    EResource* newResources = new EResource[newCapacity];

    // Копируем существующие данные в новый массив
    for (int i = 0; i < resourceCount; ++i) {
        newResources[i] = resources[i];
    }

    // Удаляем старый массив и заменяем новым
    delete[] resources;
    resources = newResources;
    capacity = newCapacity;
}

void clearScreen() {
    std::system("clear");
}

void loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    // Освобождаем старые данные
    delete[] resources;
    resources = nullptr;
    resourceCount = 0;
    capacity = 0;

    while (true) {
        if (resourceCount == capacity) {
            resizeArray();
        }

        EResource temp;
        if (!(file >> temp.id >> std::quoted(temp.title) >> std::quoted(temp.author) >> temp.category
                  >> temp.year >> temp.access_link >> temp.views)) {
            break; // Выход из цикла, если данные закончились
        }
        resources[resourceCount++] = temp;
    }

    file.close();
}

void displayData() {
    clearScreen();

    if (resourceCount == 0) {
        std::cout << "Нет данных для отображения.\n";
        return;
    }

    int widthID = 5, widthTitle = 25, widthAuthor = 20, widthCategory = 15;
    int widthYear = 6, widthLink = 30, widthViews = 10;

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

void addResource() {
    clearScreen();

    if (resourceCount == capacity) {
        resizeArray();
    }

    EResource newRes;
    newRes.id = resourceCount + 1;

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

    resources[resourceCount++] = newRes;
}

void calculateTotalViews() {
    clearScreen();

    if (resourceCount == 0) {
        std::cout << "Нет ресурсов для подсчёта.\n";
        return;
    }

    int totalViews = 0;
    int maxViews = -1;
    int maxIndex = -1;

    for (int i = 0; i < resourceCount; ++i) {
        totalViews += resources[i].views;
        if (resources[i].views > maxViews) {
            maxViews = resources[i].views;
            maxIndex = i;
        }
    }

    std::cout << "Общее количество просмотров всех ресурсов: " << totalViews << std::endl;

    if (maxIndex != -1) {
        std::cout << "\nСамый популярный ресурс:\n"
                  << "ID: " << resources[maxIndex].id << "\n"
                  << "Название: " << resources[maxIndex].title << "\n"
                  << "Автор: " << resources[maxIndex].author << "\n"
                  << "Категория: " << resources[maxIndex].category << "\n"
                  << "Год: " << resources[maxIndex].year << "\n"
                  << "Ссылка: " << resources[maxIndex].access_link << "\n"
                  << "Просмотры: " << resources[maxIndex].views << std::endl;
    }
}

void deleteResource() {
    clearScreen();

    int id;
    std::cout << "Введите ID ресурса для удаления: ";
    while (!(std::cin >> id)) {
        std::cout << "Ошибка ввода! Пожалуйста, введите корректный ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for (int i = 0; i < resourceCount; ++i) {
        if (resources[i].id == id) {
            for (int j = i; j < resourceCount - 1; ++j) {
                resources[j] = resources[j + 1]; // Сдвиг элементов
            }
            resourceCount--;
            std::cout << "Ресурс с ID " << id << " был удален." << std::endl;
            return;
        }
    }

    std::cout << "Ресурс с таким ID не найден." << std::endl;
}

// Сохранение данных в файл
void saveData(const std::string& filename) {
    clearScreen();
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка сохранения в файл." << std::endl;
        return;
    }

    for (int i = 0; i < resourceCount; ++i) {
        file << resources[i].id << " " << std::quoted(resources[i].title) << " "
             << std::quoted(resources[i].author) << " " << resources[i].category << " "
             << resources[i].year << " " << resources[i].access_link << " "
             << resources[i].views << std::endl;
    }

    file.close();
    std::cout << "Данные успешно сохранены в файл: " << filename << std::endl;
}

// Очистка памяти перед завершением программы
void cleanup() {
    delete[] resources;
    resources = nullptr;
}

int main() {
    std::string filename;
    std::cout << "Введите название файла для загрузки данных: ";
    std::cin >> filename;
    std::cin.ignore();
    loadData(filename);

    int choice;
    while (true) {
        clearScreen();
        std::cout << "Меню:\n"
                  << "1. Просмотр ресурсов\n"
                  << "2. Добавить ресурс\n"
                  << "3. Подсчет просмотров\n"
                  << "4. Удалить ресурс\n"
                  << "5. Сохранить данные в новый файл\n"
                  << "6. Выйти\n"
                  << "Выберите пункт: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: displayData(); break;
            case 2: addResource(); break;
            case 3: calculateTotalViews(); break;
            case 4: deleteResource(); break;
            case 5: {
                std::string saveFilename;
                std::cout << "Введите название файла для сохранения данных: ";
                std::cin >> saveFilename;
                saveData(saveFilename);
                break;
            }
            case 6:
                cleanup();
                std::cout << "Программа завершена." << std::endl;
                return 0;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }

        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.ignore();
        std::cin.get();
    }

    cleanup(); // Очистка памяти
    return 0;
}
