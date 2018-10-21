using namespace std;

// struct to store data and point to the next node
struct node {
    string line;
    node *next;
};

// class to initialize and hold methods for list
class list {
private:
    node *head, *tail;
public:
    list()
    {
        head=NULL;
        tail=NULL;
    }

    // method declarations
    node* insertEnd(string line);
    node* insert(int pos, string line);
    void deleteAtPosition(int pos);
    void edit(int pos, string line);
    void print();
    void search(string line);
};