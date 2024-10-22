#include <iostream>
#include <fstream>
#include <vector>
#include <string>


struct EResource {
    int id;
    std::string title;
    std::string author; 
    std::string category;
    int year;
    std::string access_link; 
    int views;
};

std::vector<EResource> resources;

void loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    EResource temp;
    while (file >> temp.id >> temp.title >> temp.author >> temp.category >> temp.year >> temp.access_link >> temp.views) {
        resources.push_back(temp);
    }
    file.close();
}

void displayData() {
    for (const auto& res : resources) {
        std::cout << "ID: " << res.id << "\nНазвание: " << res.title << "\nАвтор: " << res.author
                  << "\nКатегория: " << res.category << "\nГод: " << res.year 
                  << "\nСсылка: " << res.access_link << "\nПросмотры: " << res.views << "\n" << std::endl;
    }
}

void editResource(int id) {
    for (auto& res : resources) {
        if (res.id == id) {
            std::cout << "Введите новые данные для ресурса (название, автор, категория, год, ссылка, просмотры): ";
            std::cin >> res.title >> res.author >> res.category >> res.year >> res.access_link >> res.views;
            return;
        }
    }
    std::cout << "Ресурс с таким ID не найден." << std::endl;
}

void calculateTotalViews() {
    int totalViews = 0;
    for (const auto& res : resources) {
        totalViews += res.views;
    }
    std::cout << "Общее количество просмотров всех ресурсов: " << totalViews << std::endl;
}

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

int main() {
    std::string filename = "resources.txt";
    loadData(filename);

    int choice;
    while (true) {
        std::cout << "Меню:\n1. Просмотр ресурсов\n2. Редактировать ресурс\n3. Подсчет просмотров\n4. Добавить ресурс\n5. Сохранить данные\n6. Выйти\n";
        std::cin >> choice;

        if (choice == 1) {
            displayData();
        } else if (choice == 2) {
            int id;
            std::cout << "Введите ID ресурса для редактирования: ";
            std::cin >> id;
            editResource(id);
        } else if (choice == 3) {
            calculateTotalViews();
        } else if (choice == 4) {
            EResource newRes;
            std::cout << "Введите данные для нового ресурса (id, название, автор, категория, год, ссылка, просмотры): ";
            std::cin >> newRes.id >> newRes.title >> newRes.author >> newRes.category >> newRes.year >> newRes.access_link >> newRes.views;
            resources.push_back(newRes);
        } else if (choice == 5) {
            saveData("new_resources.txt");
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Неверный выбор." << std::endl;
        }
    }

    return 0;
}
