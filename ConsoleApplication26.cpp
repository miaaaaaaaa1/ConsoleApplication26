#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int value, Node* next = nullptr, Node* prev = nullptr) : data(value), next(next), prev(prev) {}
};

class List {
    Node* head;
    Node* tail;
    int size;
    int grow;

public:
    List(int initialSize = 0, int growFactor = 1)
        : head(nullptr), tail(nullptr), size(0), grow(growFactor) {
        SetSize(initialSize);
    }

    void AddToHead(int value) {
        Node* newNode = new Node(value, head, nullptr);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void AddToTail(int value) {
        Node* newNode = new Node(value, nullptr, tail);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void DeleteFromTail() {
        if (IsEmpty()) return;
        if (head->next == nullptr) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* beforeLast = tail->prev;
            beforeLast->next = nullptr;
            delete tail;
            tail = beforeLast;
        }
        size--;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int growFactor = 1) {
        grow = growFactor;
        while (size > newSize) {
            DeleteFromTail();
        }
        while (size < newSize) {
            AddToTail(0);
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        Node* current = head;
        for (int i = 0; i < size; i++) {
            current = current->next;
        }
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void RemoveAll() {
        Clear();
    }

    int GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void SetAt(int index, int value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->data = value;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void Add(int value) {
        if (size >= grow) {
            SetSize(size + grow);
        }
        AddToTail(value);
    }

    void Append(const List& other) {
        Node* current = other.head;
        while (current != nullptr) {
            AddToTail(current->data);
            current = current->next;
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            Clear();
            Node* current = other.head;
            while (current != nullptr) {
                AddToTail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    Node* GetData() const {
        return head;
    }

    void InsertAt(int index, int value) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }
        if (index == 0) {
            AddToHead(value);
        }
        else if (index == size) {
            AddToTail(value);
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node* newNode = new Node(value, current->next, current);
            current->next->prev = newNode;
            current->next = newNode;
            size++;
        }
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            if (head) head->prev = nullptr;
            delete temp;
        }
        else if (index == size - 1) {
            DeleteFromTail();
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size--;
    }

    void Clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    void Show() const {
        for (Node* i = head; i != nullptr; i = i->next) {
            cout << i->data << " ";
        }
        cout << "\n";
    }

    ~List() {
        Clear();
    }
};

int main() {
    List list;
    list.AddToHead(10);
    list.AddToTail(20);
    list.AddToTail(30);
    list.Add(40);

    cout << "List: ";
    list.Show();

    cout << "Size: " << list.GetSize() << "\n";
    cout << "Superscript: " << list.GetUpperBound() << "\n";

    list.SetAt(1, 50);
    cout << "Element at index 1: " << list.GetAt(1) << "\n";

    list.RemoveAt(2);
    cout << "After removal: ";
    list.Show();
}
