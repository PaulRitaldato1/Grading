#include <iostream>
#include <sstream>
#include <cstdio>

char* strcpy(char *dest, const char* src){
	int i;
    for(i=0;src[i]!='\0';i++)
		dest[i] = src[i];
    dest[i]='\0';
	return dest;
}

bool strmatch(const char *s1, const char *s2){
	int i;
	for(i=0;s1[i]!='\0';i++){
		if(s2[i]=='\0'||s1[i]!=s2[i])
			return false;
	}
	return s1[i]==s2[i];
}

bool strfind(const char *search, const char *source){
    int i;
	for(int j=0;source[j]!='\0';j++){
		for(i=0;source[i+j]!='\0';i++){
			if(search[i]=='\0')
				return true;
			else if(source[i+j]!=search[i])
                break;
		}
        if(search[i]=='\0')
				return true;
	}
	return false;
}

struct node{
	node():next(NULL),line(new char[80]){}
	~node(){delete[] line;}
    node* next;
    char* line;
};

enum TextOperation {
	insertEnd,
	insert,
	erase,
	edit,
	search,
	invalid=-1
};

class list{
    public:
    void insertEnd(const char* str);
	void insertStart(const char* str);
    void insert(int pos, const char* str);
    void erase(int pos);
    void edit(int pos, const char* str);
	void print();
	void search(const char* str);
	private:
		node* listHead = NULL;
};

void list::insertEnd(const char* str){
	node **temp = &listHead;
	for(;*temp;temp=&(*temp)->next){}
	*temp = new node();
	strcpy((*temp)->line,str);
}

void list::insertStart(const char* str){
	node * insert = new node();
	strcpy(insert->line,str);
	insert->next = listHead;
	listHead = insert;
}


void list::insert(int pos, const char* str){
	int i;
	if(!listHead)
		return insertEnd(str);
	if(pos<1)
		return insertStart(str);
	node *temp = listHead;
	for(i=0;temp->next&&i<pos-1;temp=temp->next)i++;
	if(i+1!=pos){
		//std::cout<<"Error: Invalid Insert Postion"<<std::endl;
		return;
	}
	node * insert = new node();
	strcpy(insert->line,str);
	insert->next = temp->next;
	temp->next = insert; 
}


void list::erase(int pos){
	int i;
	if(listHead){
		if(pos < 0)
			return;
		else if(pos == 0){
			node *temp = listHead;
			listHead = temp->next;
			delete temp;
		}else{
			node *temp = listHead;
			for(i=0;temp->next&&i<pos-1;temp=temp->next)i++;
			if(i+1!=pos || !temp->next){
				//std::cout<<"Error: Invalid Delete Postion"<<std::endl;
				return;
			}
			node* deleteMe = temp->next;
			if(deleteMe&&deleteMe->next)
				temp->next = deleteMe->next;
			else
				temp->next = NULL;
			delete deleteMe;
		}
	}else{
		//std::cout<<"Error: Empty Document"<<std::endl;
	}
}

void list::edit(int pos, const char* str){
	if(listHead){
		node *temp = listHead;
		int i;
		for(i=0;temp->next&&i<pos;temp=temp->next)i++;
		if(i==pos)
			strcpy(temp->line,str);
		else{
			//std::cout<<"Error: Invalid Edit Position"<<std::endl;
			return;
		}
	}else{
		//std::cout<<"Error: Empty Document"<<std::endl;
	}
}

void list::print(){
	node *temp = listHead;
	for(int i=0;temp;temp=temp->next)
        std::fprintf(stdout,"%d %s\n",++i,temp->line);
}

void list::search(const char* str){
	node *temp = listHead;
    bool notFound = true;
	for(int i=1;temp;temp=temp->next){
		if(strfind(str,temp->line)){
            std::fprintf(stdout,"%d %s\n",i,temp->line);
            notFound = false;
			//return;
		}i++;
	}if(notFound)
        std::fprintf(stdout,"not found\n");
}

class DocEditor{
	public:
		DocEditor():document(new list),close(false){}
		~DocEditor(){delete document;}
		void parse();
		void quit(){close = true;}
		bool stayOpen(){return !close;}
	private:
		bool close;
		list* document = NULL;
};

#include <string>
void DocEditor::parse(){
	std::string buffer;
	std::string bufferArg;
	std::string bufferLine;
	char arg[10];
    int pos=-1;
    char line[81];
	
	std::getline(std::cin,buffer);
	std::istringstream stream(buffer);
	stream>>bufferArg;
	if(bufferArg.length() < 10)
		strcpy(arg, bufferArg.c_str());
	else{
		//std::cout<<"Error: Invalid Command"<<std::endl;
		return;
	}
	TextOperation oper=invalid;
	if(strmatch(arg, "insertEnd"))
		oper=insertEnd;
	else if(strmatch(arg, "insert"))
		oper=insert;
	else if(strmatch(arg, "delete"))
		oper=erase;
	else if(strmatch(arg, "edit"))
		oper=edit;
	else if(strmatch(arg, "print"))
		return document->print();
	else if(strmatch(arg, "search"))
		oper=search;
	else if(strmatch(arg, "quit"))
		return quit();
	if(oper==invalid){
		//std::cout<<"Error: Invalid Command"<<std::endl;
		return;
	}
	if(oper==insert||oper==erase||oper==edit){
		stream>>pos;
		if(stream.fail()){
			//std::cout<<"Error: Invalid/No Position Provided"<<std::endl;
			return;
		}
		if(pos < 1){
			//std::cout<<"Error: Invalid/No Position"<<std::endl;
			return;
		}
		if(oper==erase)
			return document->erase(pos-1);
	}
	std::getline(stream,bufferLine);
	if(!bufferLine.empty()){
		if(bufferLine.length() > 82){
			//std::cout<<"Error: Line Input too long"<<std::endl;
			return;
		}else if(bufferLine.length() < 3){
			//std::cout<<"Error: Line Input too short"<<std::endl;
			return;
		}else{
			bufferLine = bufferLine.substr(2,bufferLine.length()-3);
			strcpy(line, bufferLine.c_str());
		}
	}else{
		//std::cout<<"No Line Input Provided"<<std::endl;
        return;
	}
	switch(oper){
		case insertEnd:
			document->insertEnd(line);
            break;
		case insert:
            document->insert(pos-1,line);
			break;
		case edit:
            document->edit(pos-1,line);
			break;
		case search:
            document->search(line);
			break;
		default:
            //std::fprintf(stdout,"Error: Invalid Input");
			break;
	}
}


int main(){
    DocEditor *editor = new DocEditor();
	while(editor->stayOpen())
        editor->parse();
    return 0;
}