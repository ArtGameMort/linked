#include <iostream>

template<typename T>
struct node {
    // Конструктор узла от параметра value
    explicit node(T value) : data(value), next(nullptr), prev(nullptr) {}

    node* next;  // Указатель на предыдущий узел
    node* prev;  // Указатель на следующий узел
    T data;      // Значение узла
};

template<typename T>
class list {
public:
    list();  // Конструктор по умолчанию

    ~list();  // Деструктор

    list(const list<T>& other);  // Конструктор копирования

    list<T>& operator=(const list<T>& other);  // Оператор присваивания

    void push_back(T value);  // Метод добавления элемента в конец

    void push_front(T value);  // Метод добавления элемента в начало

    void erase(size_t index);  // Метод удаление элемента по индексу

    T& operator[](size_t index);  // Перегрузка оператора [] для не константных объектов

    const T& operator[](size_t index) const;  // Перегрузка оператора [] для константных объектов

    template<typename C>
    friend std::ostream& operator<<(std::ostream& out, const list<C>& other); // Перегрузка оператора вывода

private:
    void deallocate_memory();  // Метод очистки памяти

    node<T>* head_;  // Указатель на голову
    node<T>* tail_;  // Указатель на хвост
    size_t size_;    // Размер
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const list<T>& other) {
    node<T>* curr = other.head_;
    while (curr != nullptr) {
        out << curr->data << ' ';
        curr = curr->next;
    }
    return out;
}

template<typename T>
void list<T>::deallocate_memory() {
    while (head_ != nullptr) {
        node<T>* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
    tail_ = nullptr;
    size_ = 0;
}

template<typename T>
list<T>& list<T>::operator=(const list<T>& other) {
    if (this == &other) {
        return *this;
    }
    deallocate_memory();
    node<T>* curr_node = other.head_;
    while (curr_node != other.tail_) {
        push_back(curr_node->data);
        curr_node = curr_node->next;
    }
    size_ = other.size_;
}

template<typename T>
list<T>::list(const list<T>& other) : size_(0) {
    if (other.size_ == 0) {
        tail_ = nullptr;
        head_ = nullptr;
    }
    else {
        node<T>* curr_node = other.head_;
        while (curr_node != other.tail_) {
            push_back(curr_node->data);
            curr_node = curr_node->next;
        }
        size_ = other.size_;
    }
}

template<typename T>
const T& list<T>::operator[](size_t index) const {
    auto tmp = head_;
    size_t current_index = 0;
    while (current_index < index) {
        tmp = tmp->next;
        ++current_index;
    }
    return tmp->data;
}

template<typename T>
T& list<T>::operator[](size_t index) {
    auto tmp = head_;
    size_t current_index = 0;
    while (current_index < index) {
        tmp = tmp->next;
        ++current_index;
    }
    return tmp->data;
}

template<typename T>
void list<T>::erase(size_t index) {
    if (index == 0) {
        auto tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
        return;
    }
    auto tmp = head_;
    size_t current_index = 0;
    while (current_index + 1 < index) {
        tmp = tmp->next;
        ++current_index;
    }
    auto to_delete = tmp->next;
    tmp->next = tmp->next->next;
    delete to_delete;
    --size_;
}

template<typename T>
void list<T>::push_back(T value) {
    if (size_ == 0) {
        head_ = new node(value);
        tail_ = head_;
        ++size_;
        return;
    }
    node<T>* new_node = new node(value);
    node<T>* tmp = tail_;
    tail_ = new_node;
    tail_->prev = tmp;
    tmp->next = tail_;
    ++size_;
}

template<typename T>
void list<T>::push_front(T value) {
    if (size_ == 0) {
        head_ = new node(value);
        tail_ = head_;
        ++size_;
        return;
    }
    node<T>* new_node = new node(value);
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
    ++size_;
}

template<typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
list<T>::~list() {
    deallocate_memory();
}

int menu() {
    int command;
    std::cout << "\n";
    std::cout << "1 - Введите содержимое массива" << std::endl;
    std::cout << "2 - Вывод массива" << std::endl;
    std::cout << "3 - Добавления элемента в конец" << std::endl;
    std::cout << "4 - Добавления элемента в начало" << std::endl;
    std::cout << "5 - Удаление элемента по индексу" << std::endl;
    std::cout << "6 - Выход из программы" << std::endl;
    std::cin >> command;
    return command;
}

int main() {
    /*list<int> l;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        l.push_back(value);
    }*/
    setlocale(LC_ALL, "rus");
    list<int> data;
    int n;
    while (true) {
        n = menu();
        switch (n) {
        case 1:
        {
            int n;
            std::cin >> n;
            for (int i = 0; i < n; ++i) {
                int value;
                std::cin >> value;
                data.push_back(value);
            }
            break;
        }
        case 2:
        {
            std::cout << data;
            break;
        }
        case 3:
        {
            int value;
            std::cin >> value;
            data.push_back(value);
            break;
        }
        case 4:
        {
            int value;
            std::cin >> value;
            data.push_front(value);
            break;
        }
        case 5:
        {
            int value;
            std::cin >> value;
            data.erase(value);
            break;
        }
        case 6:
            std::cout << "Хорошего дня!!! " << std::endl;
            std::cout << "Спасибо, что пользовались нашей программой! " << std::endl;
            std::cout << "До свидания! " << std::endl;
            return 0;
        }
    }
    return 0;
}