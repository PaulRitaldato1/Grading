#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>

/*
Preetham Pamulapati
*/
using namespace std;
/*
 * Class Declaration
 */
class single_llist
{
public:

	/*
	* Node Declaration
	*/
	struct node
	{
		node(const string & info, node * next = NULL);

		string info;
		struct node *next;
	};

    void insert_pos( const string & message, int index );
    void insert_end(const string & message);
    void delete_pos( int index );
    void search(const string & message);
    void edit(int index, const string & message);
    void print();
/*
* Constructor for the linked list
*/

    single_llist()
    {
        start = NULL;
        sizeList = 0;
    }
/*
* Deconstructor for the linked list
*/
    ~single_llist(){
        while(sizeList > 0){
            node * temp = start;
            start = start->next;
            delete temp;
            sizeList--;
        }
    }


private:
	node * start;
	int sizeList;
};

/*
* Extracts the message from the user input line and uses it to pass message to functions requiring string message
to be a parameter
*/
bool extractMessage(const string & input, string & message)
{
    int position = input.find_first_of("\"");
    if (position == string::npos)
    {
        cout << "Invalid Input" << endl;
        return false;
    }
    int position2 = input.find_first_of("\"",++position);
    if (position2 == string::npos)
    {
        cout << "Invalid Input" << endl;
        return false;
    }
    message = input.substr(position,position2-position);
    return true;

}
/*
* Extracts the index from the user input line and uses it to pass index to functions requiring index to be a parameter
*/
bool extractIndex(const string & input, int & index){
    int position = input.find_first_of(" ");
    if (position == string::npos)
    {
        cout << "Invalid Input" << endl;
        return false;
    }
    int position2 = input.find_first_of(" ",++position);
	index = atoi( input.substr(position,position2-position).c_str());
    return true;
}

/*
 * Main :contains menu for user input and start LineEditor
 */
int main()
{
    int position, index;
    string message;
    single_llist sl;

    do{
        string input;
		getline(cin, input);
        position = input.find_first_of(" \t");
        if (position == string::npos){
			for (int i = 0; i < position; i++) {
				input[i] = tolower(input[i]);
			}
			if (input == "quit")
				break;
            else if(input == "print")
                sl.print();
			else
				cout << "Invalid Input" << endl;
        }
        else {
            string choice = input.substr(0, position);
            for (int i = 0; i < position; i++){
                choice[i] = tolower(choice[i]);
            }
            if(choice == "insertend" && extractMessage(input,message) ){
                    sl.insert_end(message);
            }
            else if(choice == "search" && extractMessage(input, message) ){
                    sl.search(message);
            }
            else if (choice == "delete" && extractIndex(input,index))
                sl.delete_pos(index);
            else if (choice == "edit" && extractIndex(input,index) && extractMessage(input,message))
                sl.edit(index, message);
            else if (choice == "insert" && extractIndex(input,index) && extractMessage(input,message))
                sl.insert_pos(message,index);
            else if(choice == "print")
                sl.print();
            else if(choice == "quit"){
                break;
            }
			else
				cout << "Invalid Input" << endl;
        }
    } while (true);

	return 0;
}

single_llist::node::node(const string & _info, node * _next){
    info =_info;
    next = _next;
}

/*
 * Inserting message at last index
 */
void single_llist::insert_end(const string & message)
{
   insert_pos(message,sizeList+1);

}

/*
 * Insertion of a specific message at a specific index
 */
void single_llist::insert_pos(const string & message, int index)
{
    int counter = 1;
    struct node *temp, *s = start, *ptr = NULL;
    while (s != NULL && counter < index)
    {
        ptr = s;
        s = s->next;
        counter++;
    }
    if (counter == index)
    {
        temp = new single_llist::node(message,s);
        sizeList++;

        if (ptr == NULL)
            start = temp;
        else
            ptr->next = temp;
    }
}

/*
 * Delete message based at that certain index
 */
void single_llist::delete_pos(int index)
{
    int counter = 1;
    if(index > sizeList || index <= 0){
        return;
    }
    struct node *s, *ptr = NULL;
    s = start;
    while (counter < index)
    {
        ptr = s;
        s = s->next;
        counter++;
    }

    ptr->next = s->next;
    delete s;
	--sizeList;
}

/*
 * Edit a string at a certain index with a different message
 */
void single_llist::edit(int index, const string & message)
{
    int counter = 1;
    if(index > sizeList || index <= 0){
        return;
    }
    struct node *s = start;
    while (counter < index)
    {
        s = s->next;
        counter++;
    }

    s->info = message;
}

/*
 * Searching an substring in the traversed list
 */
void single_llist::search(const string & message)
{
    bool flag = false;
    int indexSearch = 1;
    struct node *s;
    s = start;
    while (s != NULL)
    {
        if (s->info.find(message) != string::npos)
        {
            flag = true;
            cout << indexSearch << " " << s->info << endl;
        }
        s = s->next;
        indexSearch++;
    }
    if (!flag)
        cout << "not found" << endl;
}

/*
 * Print Elements of a link list
 */
void single_llist::print()
{
    int counter = 1;
    struct node *temp = start;

    while (temp != NULL)
    {
        cout<< counter << " " << temp->info << endl;
        temp = temp->next;
        counter++;
    }
}
