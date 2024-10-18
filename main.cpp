#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

const int  MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    string delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return "\n";
        }
    
        if (pos == 1) {
            pop_front();
            return " nothing inside";
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return" ";
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return " ";
        }
        string custumer = temp->data;
        if (!temp->next) {
            pop_back();
            return" ";
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        return custumer;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    string pop_front() {
        string custumer = head->data;
        if (!head) {
            cout << "List is empty." << endl;
        return "\n";
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
            return custumer;
        }
        else{
            head = tail = nullptr;
            return custumer;
        }
        delete temp;
    
    }

    string pop_back() {
        string custumer = tail->data;
        if (!tail) {
            cout << "List is empty." << endl;
            return "\n";
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
            return custumer;
        }
        else{
            head = tail = nullptr;
        return custumer;
        }
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    int getSize() {
    Node *current = head;
    int count = 0;
    while (current) {
      current = current->next;
      count++;
    }
    return count;
  }
};
   vector<string> getnames(string f) {
        vector<string> lists;
        ifstream fin(f);
        string name;
        if(!fin.good()){
            cout <<"Can't open file";
        }
        while (fin >> name) {
         lists.push_back(name);
  }
  return lists;
}
    string pickName(vector<string> v){
        int i = (rand() % (v.size())); 
        string select = v[i];
        v.erase(v.begin() + i);
        return select;

    }

int main() {
    srand(time(0));
    string custumer;
    DoublyLinkedList line;
    cout << "Store opends: \n";
    vector<string> names = getnames("names.txt");
   
    for (int i = 0; i < MIN_LS; i++) {
        
        custumer = pickName(names);
        line.push_back(custumer);
        cout << custumer << " joined the line.\n";
    }
    cout <<"Resulting line: \n";
    line.print();

    int help, join, endlea, leave, vip;
    for (int i = 0; i < MAX_LS -1; i++) {
        cout << "\nTime step #" << i + 2 << endl;
        help = rand() % 100 + 1;
        if (help <= 40) {
            custumer = line.pop_front();
            cout << "\n\t" << custumer << " is served\n";
        }
        join = rand() % 100 + 1;
        if (join <= 60) {
            custumer = pickName(names);
            line.push_back(custumer);
            vip = rand() % 100 + 1;
            if (vip <= 10) {
                line.push_front(custumer);
                cout << "\n\t" << custumer << " (VIP) joins the front of the line\n";
            } else
                cout << "\n\t" << custumer << " joins the line\n";
        }
        endlea = rand() % 100 + 1;
        if (endlea <= 20) {
            custumer = line.pop_back();
            cout << "\n\t" << custumer << " (at the rear) left the line\n";
        }
        for (int i = 0; i < line.getSize(); i++) {
            leave = rand() % 100 + 1;
            if (leave <= 10) {
                cout << "\n\t" << line.delete_pos(i) << " left the line\n";
            }
        }
    line.print();
        
  }
    
    return 0;
}
