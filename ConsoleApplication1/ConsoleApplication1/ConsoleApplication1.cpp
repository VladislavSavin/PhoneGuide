#include <iostream> 
#include <string> 
#include <list> 
#include <fstream> 
#include <windows.h> 

using namespace std;

struct Subscriber {
    string name;
    string number;
    string town;
    string street;
    int house;
};

list<Subscriber> lst;

ifstream& operator>>(ifstream& in, Subscriber& obj) {
    in >> obj.name;
    in >> obj.number;
    in >> obj.town;
    in >> obj.street;
    in >> obj.house;
    return in;
}

istream& operator>>(istream& in, Subscriber& obj) {
    cout << "Добавление новых контактов:\n\n";
    cout << "Имя: "; in >> obj.name;
    cout << "Номер телефона: "; in >> obj.number;
    cout << "Адрес: "; in >> obj.town; in >> obj.street >> obj.house;
    return in;
}

ostream& operator<<(ostream& out, Subscriber& obj) {
    out << obj.name << "\n";
    out << obj.number << "\n";
    out<< obj.town << obj.street << " " << obj.house << "\n";
    return out;
}

void clear() {
    ofstream in("input.txt", ios::out | ios::trunc);
    in.close();
}

void clear_new() {
    ofstream in("input_new.txt", ios::out | ios::trunc);
    in.close();
}

bool isFileEmpty() {
    ifstream in("input.txt");
    in.seekg(0, ios::end);
    if (in.tellg() == 0) {
        return true;
    }
    in.close();
    return false;
}

void SaveInFile() {
    clear();
    ofstream out("input.txt");
    for (const Subscriber& data : lst) {
        out << data.name << "\n";
        out << data.number << "\n";
        out << data.town << endl << data.street << " " << data.house << "\n";
    }
    out.close();
}

void SaveNewFile() { 
    clear_new();
    ofstream out("input_new.txt");
    for (const Subscriber& data : lst) {
        out << data.name << "\n";
        out << data.town << data.street << data.house << "\n";
    }
    cout << "\nНовый файл успешно сформирован!\n\n";
    out.close();
}

void ReadFile(Subscriber& data) {
    ifstream in("input.txt");
    while (in >> data) {
        lst.push_back(data);
    }
    in.close();
}

void OutPutFile(Subscriber& data) {
    if (!isFileEmpty()) {
        ifstream in("input.txt");
        if (in) {
            int k = 0;
            while (in >> data) {
                k++;
                cout << "-----------------------------------------------------------------------------------------------\n";
                cout << "Контакт #" << k << ":\n\n";
                cout << data.name << endl << data.number << endl;
                cout << data.town << " " << data.street << " " << data.house;
                cout << "\n";
            }
            in.close();
        }
        else {
            cout << "Файл input.txt не найден!\n";
        }
    }
    else {
        cout << "Файл пуст!\n\n";
    }
}

void OutPutNewFile(Subscriber& data) {
    ifstream in("input_new.txt");
    if (in) {
        int k = 0;
        while (in >> data.name >> data.number) {
            k++;
            cout << "-----------------------------------------------------------------------------------------------\n";
            cout << "Контакт #" << k << ":\n";
            cout << data.name << endl;
            cout << data.town << " " << data.street << " " << data.house;
            cout << endl;
        }
        in.close();
    }
    else {
        cout << "Файл input_new.txt не найден!\n";
    }
}

void Add(Subscriber& data) {
    int k;
    cout << "-----------------------------------------------------------------------------------------------\n";
    cout << "Количество добавляемых контактов: ";
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cout << "-----------------------------------------------------------------------------------------------\n";
        cout << "Контакт #" << i << ":\n";
        cin >> data;
        lst.push_back(data);
    }
    cout << "\nЗаписи обновлены!\n\n";
    SaveInFile();
}

void Delete(string const& key) {
    bool flag = false;
    for (auto it = lst.begin(); it != lst.end();) {
        if (it->name == key) {
            it = lst.erase(it);
            flag = true;
        }
        else {
            ++it;
        }
    }
    if (!flag) {
        cout << "\nКонтакта с таким именем не найдено!\n\n";
        return;
    }
    else {
        cout << "\nКонтакт удалён!\n\n";
    }
    SaveInFile();
}

void reNumber(string const& key) {
    int k = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (it->name == key) {
            k++;
            cout << "-----------------------------------------------------------------------------------------------\n";
            cout << "Контакт #" << k << ":\n";
            cout << it->number << " => ";
            cin >> it->number;
            it->number = it->number;
            cout << "\n";
        }
    }
    if (!k) {
        cout << "Контакта с таким именем не найдено!\n\n";
        return;
    }
    else {
        cout << "Контакты успешно обновлены!\n\n";
    }
    SaveInFile();
}

void OutPut() {
    ifstream in("input.txt");
    bool flag = false;
    string digits;
    cout << "Введите две первых цифры номера или две первых буквы имени: ";
    cin >> digits;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (it->name.find(digits) == 0 || it->number.find(digits) == 0) {
            cout << it->name << "\n";
            cout << it->number << "\n";
            cout << it->town << endl << it->street << " " << it->house << "\n";
            flag = true;
        }
    }
    in.close();
    if (!flag) {
        cout << "Искомых контактов не найдено!\n\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Subscriber people;
    ReadFile(people);
    int choice, isRunning;
    string name;
    do {
        cout << "-----------------------------------------------------------------------------------------------\n";
        cout << "Выберите действие:\n";
        cout << "-----------------------------------------------------------------------------------------------\n";
        cout << "0 - Выход.\n";
        cout << "1 - Добавить новую запись.\n";
        cout << "2 - Удалить запись (по имени абонента).\n";
        cout << "3 - Изменить номер телефона (по имени абонента).\n";
        cout << "4 - Поиск абонента по двум буквам имени или по двум цифрам номера.\n";
        cout << "5 - Список всех абонентов.\n";
        cout << "6 - Формирование списка без номеров.\n";
        cout << "7 - Список без номеров.\n";
        cout << "-----------------------------------------------------------------------------------------------\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice) {
        case 0:
            exit(0);
            break;
        case 1:
            Add(people);
            break;
        case 2:
            cout << "Введите имя: ";
            cin >> name;
            Delete(name);
            break;
        case 3:
            cout << "Введите имя: ";
            cin >> name;
            cout << "\n";
            reNumber(name);
            break;
        case 4:
            OutPut();
            break;
        case 5:
            OutPutFile(people);
            break;
        case 6:
            SaveNewFile();
            break;
        case 7:
            OutPutNewFile(people);
            break;
        default:
            cout << "Что-то пошло не так! Повторите запрос!\n";
        }
        cout << "-----------------------------------------------------------------------------------------------\n";
        cout << "Вы хотите вернуться в меню?\n";
        cout << "1 - Вернуться\n";
        cout << "Ваш выбор: ";
        cin >> isRunning;
        if (isRunning == 1) system("cls");
    } while (isRunning == 1);
    return 0;
}