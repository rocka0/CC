#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/rocka0/CC

    Usage:  DoublyLinkedList<int> ll;
*/

template <typename T>
class DoublyLinkedList {
public:
    // Constructor
    DoublyLinkedList() {
        head = tail = nullptr;
        cnt = 0;
    }

    // Destructor
    ~DoublyLinkedList() {
        while (head != tail) {
            Node *old = head;
            head = head->next;
            delete old;
        }
    }

    // Returns data stored in first element
    T front() const {
        assert(cnt > 0);    // List should not be empty
        return head->data;
    }

    // Returns data stored in last element
    T back() const {
        assert(cnt > 0);    // List should not be empty
        return tail->data;
    }

    // Returns data stored at index
    T get(int index) const {
        assert(cnt > 0);                       // List should not be empty
        assert(0 <= index and index < cnt);    // index should be in [0,cnt)
        Node *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Changes value of data stored at index
    void set(int index, T val) {
        assert(cnt > 0);                       // List should not be empty
        assert(0 <= index and index < cnt);    // index should be in [0,cnt)
        Node *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        temp->data = val;
    }

    // Insert node with value val before index
    void insert(int index, T val) {
        assert(cnt > 0);                       // List should not be empty
        assert(0 <= index and index < cnt);    // index should be in [0,cnt)
        if (!index) {
            push_front(val);
            return;
        }
        Node *temp = head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }
        Node *ins = new Node(val);
        ins->next = temp->next;
        temp->next->prev = ins;
        temp->next = ins;
        ins->prev = temp;
        ++cnt;
    }

    // Erase node with index
    T erase(int index) {
        assert(cnt > 0);                       // List should not be empty
        assert(0 <= index and index < cnt);    // index should be in [0,cnt)
        if (!index) {
            return pop_front();
        } else if (index + 1 == cnt) {
            return pop_back();
        } else {
            --cnt;
            Node *temp = head;
            for (int i = 0; i < index; ++i) {
                temp = temp->next;
            }
            Node *left = temp->prev;
            Node *right = temp->next;
            left->next = right;
            right->prev = left;
            T ret = temp->data;
            delete temp;
            return ret;
        }
    }

    // Add node with value val to end of list
    void push_back(T val) {
        Node *temp = new Node(val);
        if (!cnt) {
            head = tail = temp;
        } else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        ++cnt;
    }

    // Remove last value and return
    T pop_back() {
        assert(cnt > 0);    // List should not be empty
        --cnt;
        if (!cnt) {
            Node *old = head;
            head = tail = nullptr;
            T ret = old->data;
            delete old;
            return ret;
        } else {
            Node *old = tail;
            tail = tail->prev;
            tail->next = nullptr;
            T ret = old->data;
            delete old;
            return ret;
        }
    }

    // Add node with value val to start of list
    void push_front(T val) {
        Node *temp = new Node(val);
        if (!cnt) {
            head = tail = temp;
        } else {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        ++cnt;
    }

    // Remove first value and return
    T pop_front() {
        assert(cnt > 0);    // List should not be empty
        --cnt;
        if (!cnt) {
            Node *old = head;
            head = tail = nullptr;
            T ret = old->data;
            delete old;
            return ret;
        } else {
            Node *old = head;
            head = head->next;
            head->prev = nullptr;
            T ret = old->data;
            delete old;
            return ret;
        }
    }

    // Returns number of elements in the list
    int size() const {
        return cnt;
    }

    // Returns true if list is empty
    bool empty() const {
        return !cnt;
    }

    // Removes all elements from the list
    void clear() {
        while (cnt > 0) {
            pop_front();
        }
    }

    // Prints the list
    void output() const {
        assert(cnt > 0);    // List should not be empty
        Node *temp = head;
        for (int i = 0; i < cnt; ++i) {
            if (i) {
                cout << ' ';
            }
            cout << temp->data;
            temp = temp->next;
        }
    }

private:
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node() {
            next = prev = nullptr;
        }

        Node(T val) {
            data = val;
            next = prev = nullptr;
        }
    };

    Node *head;
    Node *tail;
    int cnt;
};
