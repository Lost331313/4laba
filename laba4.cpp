#include <iostream>
#include <windows.h>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

unsigned my_str_len(const char* S) {
    unsigned L = 0;
    while (S[L]) ++L;
    return L;
}

void keyboard_input(char* text, int N) {
    cin.ignore();
    cout << "Введите текст, завершите точкой." << endl;
    cin.getline(text, N);
    int len_of_sequence = my_str_len(text);
    if (text[len_of_sequence - 1] == '.') {
        text[len_of_sequence - 1] = '\0'; // Убираем точку в конце
    }
}

void input_from_file(char* text, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return;
    }
    file.read(text, 600); // Чтение текста из файла
    file.close();
}

void print_result(const char* text) {
    cout << text << endl;
}

// Удаление лишних пробелов
void delete_extra_spaces(char* text) {
    int i = 0, j = 0;
    bool space_found = false;
    while (text[i]) {
        if (isspace(text[i])) {
            if (!space_found) {
                text[j++] = ' ';
                space_found = true;
            }
        }
        else {
            text[j++] = text[i];
            space_found = false;
        }
        i++;
    }
    if (j > 0 && text[j - 1] == ' ') j--; // Убираем пробел в конце
    text[j] = '\0';
}

// Удаление лишних знаков препинания
void delete_extra_punctuation(char* text) {
    int i = 0, j = 0;
    while (text[i]) {
        if (ispunct(text[i]) && ispunct(text[i + 1])) {
            if (text[i] == '.' && text[i + 1] == '.' && text[i + 2] == '.' && !ispunct(text[i + 3])) {
                text[j++] = text[i++];
                text[j++] = text[i++];
                text[j++] = text[i++];
            }
            else {
                while (ispunct(text[i + 1])) i++;
            }
        }
        text[j++] = text[i++];
    }
    text[j] = '\0';
}

void make_lower(char* text) {
    for (int i = 0; text[i]; i++) {
        text[i] = tolower(text[i]);
    }
}

void correctLetterCase(char* text) {
    bool capitalize_next = true;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            if (capitalize_next) {
                text[i] = toupper(text[i]);
                capitalize_next = false;
            }
            else {
                text[i] = tolower(text[i]);
            }
        }
        if (isspace(text[i])) {
            capitalize_next = true;
        }
    }
}

void how_many_symbols_in_word(const char* text) {
    int counter = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] != ' ' && text[i] != '\0') {
            cout << text[i];
            counter++;
        }
        else if (counter > 0) {
            cout << " - " << counter << endl;
            counter = 0;
        }
    }
    if (counter > 0) {
        cout << " - " << counter << endl; // Для последнего слова
    }
}

int linear_search(const char* text, const char* pattern) {
    int text_len = my_str_len(text);
    int pattern_len = my_str_len(pattern);
    for (int i = 0; i <= text_len - pattern_len; ++i) {
        int j = 0;
        while (j < pattern_len && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == pattern_len) {
            return i; // Нашли подстроку
        }
    }
    return -1; // Подстрока не найдена
}

void organize_words(const char* text, char words[50][10], int& count) {
    int word_len = 0;
    count = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] == ' ' || text[i] == '\0') {
            if (word_len > 0) {
                words[count][word_len] = '\0';
                count++;
                word_len = 0;
            }
        }
        else {
            words[count][word_len++] = text[i];
        }
    }
    if (word_len > 0) {
        words[count][word_len] = '\0';
        count++;
    }
}

void swap_words(char words[50][10], int i, int j) {
    char temp[10];
    strcpy_s(temp, sizeof(temp), words[i]);
    strcpy_s(words[i], sizeof(words[i]), words[j]);
    strcpy_s(words[j], sizeof(words[j]), temp);
}

void sort_alphabetically(char words[50][10], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                swap_words(words, i, j);
            }
        }
    }
}

void display_menu() {
    cout << "Выберите действие:" << endl;
    cout << "1. Выберите откуда брать последовательность." << endl;
    cout << "2. Необходимо отредактировать входной текст." << endl;
    cout << "3. Вывести на экран слова последовательности в алфавитном порядке." << endl;
    cout << "4. Вывести на экран количество символов в каждом слове исходной последовательности." << endl;
    cout << "5. Необходимо найти все подстроки, которую введёт пользователь в имеющейся строке." << endl;
    
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int identificator, num1, count, result = -1; // Инициализация переменной result
    const int N = 600;
    char sequence[N] = { 0 }, pattern[30], words[50][10];

    while (true) {
        display_menu();
        cout << "ВВЕДИТЕ НОМЕР ЗАДАНИЯ: ";
        cin >> identificator;
        switch (identificator) {
        case 1:
            cout << "Выберите ввод:" << endl;
            cout << "1. С клавиатуры." << endl;
            cout << "2. Из файла." << endl;
            cin >> num1;
            if (num1 == 1) {
                keyboard_input(sequence, N);
            }
            else if (num1 == 2) {
                input_from_file(sequence, "text.txt");
            }
            print_result(sequence);
            break;
        case 2:
            delete_extra_spaces(sequence);
            delete_extra_punctuation(sequence);
            make_lower(sequence);
            print_result(sequence);
            break;
        case 3:
            organize_words(sequence, words, count);
            sort_alphabetically(words, count);
            for (int i = 0; i < count; i++) {
                cout << words[i] << " ";
            }
            cout << endl;
            break;
        case 4:
            how_many_symbols_in_word(sequence);
            break;
        case 5:
            cout << "Введите подстроку для поиска: ";
            cin.ignore();
            cin.getline(pattern, 30);
            result = linear_search(sequence, pattern);
            if (result == -1) {
                cout << "Подстрока не найдена." << endl;
            }
            else {
                cout << "Подстрока найдена на индексе: " << result << endl;
            }
            break;
       
        case 6:
            cout << "Выход!" << endl;
            return 0;
        default:
            cout << "Некорректный номер задания." << endl;
            break;
        }
        cout << "Задание выполнено. Нажмите Enter, чтобы продолжить." << endl;
        cin.ignore();
        cin.get();
    }

    return 0;
}
