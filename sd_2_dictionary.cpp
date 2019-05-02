#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<cstdio>
using namespace std;

class dictionary
{
	class dictionary_node
	{
		friend class dictionary;
		char word[100];
		char meaning[200];
		dictionary_node *rptr;
		dictionary_node *lptr;
	};
	dictionary_node *root;
	char word1[100];
	char meaning1[200];
public:
    dictionary()
    {
        root=NULL;
    }
	void insert();
    void create(char [], char []);
	void search();
	void traversal();
	void inorder(dictionary_node *);
	void modify_data(char []);
	void delete_tree(dictionary_node* );
    void file_traversal();
};

void dictionary::insert()
{
	cout<<"\n Enter a word : ";
	cin>>word1;
	cout<<"\n Enter the meaning of the word "<<word1<<" : ";
	fflush(stdin);
	cin.getline(meaning1,200);
	ofstream fout;
    fout.open("DICTIONARY.txt",ios::out|ios::app);
	fout<<word1<<endl;
	fout<<meaning1<<endl;
	fout.close();
	create(word1,meaning1);
}

void dictionary::create(char word1[], char meaning1[])
{
	dictionary_node *temp;
	temp=new dictionary_node;
	strcpy(temp->word,word1);
	strcpy(temp->meaning,meaning1);
	temp->rptr=NULL;
	temp->lptr=NULL;

	if(root == NULL)
	{
		root=temp;
	}
	else
	{
		dictionary_node *temp1=root;
		while(1)
		{
			if((strcmp(temp->word,temp1->word)<0))
			{
				if((temp1->lptr)!=NULL)
					temp1=temp1->lptr;
				else
					break;
			}

			if((strcmp(temp->word,temp1->word)>0))
			{
				if((temp1->rptr)!=NULL)
					temp1=temp1->rptr;
				else
					break;
			}
		}
		if((strcmp(temp->word,temp1->word)<0))
		{
			temp1->lptr=temp;
		}
		else if((strcmp(temp->word,temp1->word)>0))
		{
			temp1->rptr=temp;
		}
	}
}

void dictionary::search()
{
	bool flag=false;
	cout<<"\n enter the word to be searched : ";
	cin>>word1;

	if(root ==NULL)
		cout<<"\n Your dictionary is empty";
	else
	{
		dictionary_node *temp=root;
		while(temp!=NULL)
		{
			if((strcmp(word1,temp->word))==0)
			{
				cout<<"\n word found";
				cout<<"\n "<<temp->word<<" means "<<temp->meaning;
				flag=true;
				break;
			}
			else if((strcmp(word1,temp->word))<0)
			{
				temp=temp->lptr;
			}
			else if((strcmp(word1,temp->word))>0)
			{
				temp=temp->rptr;
			}
		}
		if(flag==false)
			cout<<word1<<" not found in the dictionary ";
	}
}

void dictionary::traversal()
{
    cout<<"\n";
    inorder(root);
}

void dictionary::inorder(dictionary_node *a)
{
    if(a!=NULL)
    {
        inorder(a->lptr);
        cout<<a->word<<"\t\t";
        cout<<a->meaning<<"\n\t\t";
        inorder(a->rptr);
    }
}

void dictionary::modify_data(char ch[])
{
    /*
    fstream file1("DICTIONARY.txt",ios::in|ios::out|ios::app);
    fstream file2("Temporary_file.txt",ios::out|ios::in|ios::app);
    bool found=false;
    while(!file1.eof())
    {
        file1.getline(word1,100);
        file1.getline(meaning1,200);
        if(strcmp(word1,ch)!=0)
        {
            file2<<word1<<endl;
            file2<<meaning1<<endl;
            found=true;
        }
    }
    if(found==false)
    {
		cout<<"\n"<<ch<<" not found in the file";
		file2.close();
		ofstream ofs;
        ofs.open("Temporary_file.txt", ios::out | ios::trunc);
		remove("Temporary_file.txt");
		ofs.close();
    	return;
   	}

   	file1.close();

   	ofstream ofs;
    ofs.open("DICTIONARY.txt", ios::out | ios::trunc);
    remove("DICTIONARY.txt");
    ofs.close();
    file1.close();

    file2.seekg(0,ios::beg);
    ofstream file("DICTIONARY.txt",ios::out|ios::app);
    while(!file2.eof())
    {
    	file2>>word1;
    	file<<word1<<endl;
    	file2>>meaning1;;
    	file<<meaning1<<endl;
    }
    file.close();
    // tree will be modified after deleting the word so make the tree again using tree traversal, after deleteing the entire bst
    delete_tree(root);

    // the text file will be modified now so we will have to make the bst again thus calling the file_traversal function here
    file_traversal();
    */
}

void dictionary::file_traversal()
{
    char word[100];
    char meaning[200];
    ifstream fin("DICTIONARY.txt",ios::in|ios::app);
    while(!fin.eof())
    {
        fin.getline(word,100);
        fin.getline(meaning,200);
        create(word,meaning);
    }
}


void dictionary::delete_tree(dictionary_node *node)
{
	if(node == NULL)
		return;

	delete_tree(node->lptr);
	delete_tree(node->rptr);
	delete node;
}


int main()
{
	dictionary obj;
	int choice;
	bool fileread = false;				// at the start of the program to read the contents of the filea and store it in bst, we've used the variable fileread
	label:								// if it is false that means file is not read and data is not stored in the bst
    char ch='y';
    do{
	cout<<"\n --------------------- DICTIONARY ----------------------";
	cout<<"\n 1 Add word  ";
	cout<<"\n 2 Search meaning of a word ";
	cout<<"\n 3 Traverse the entire dictionary ";
	cout<<"\n 4 Delete a word and its meaning";
	cout<<"\n 5.Exit";
	cout<<"\n\n Enter your choice : ";
	cin>>choice;
	switch(choice)
	{
		case 1:
		{
		    if(fileread == false)
            {
                obj.file_traversal();
                fileread=true;
            }
			obj.insert();
			break;
		}
		case 2:
		{
		    if(fileread == false)
            {
                obj.file_traversal();
                fileread=true;
            }
			obj.search();
			break;
		}
		case 3:
		{
		    ofstream fout("DICTIONARY.txt",ios::in|ios::app);
		    if(!fout.eof())
		    {
		        if(fileread == false)
                {
                   obj.file_traversal();
                    fileread=true;
                }
                cout<<"\n\t\tWORD\t\tMEANING ";
                obj.traversal();
            }
            else
            {
                cout<<"\n Dictionary doesn't contain any data ";
            }
            fout.close();
			break;
		}
		case 4:
		{
		    char c[20];
		    if(fileread == false)
            {
                obj.file_traversal();
                fileread=true;
            }
            cout<<"\n enter the word of which you want to modify the data : ";
            cin.getline(c,20);
			obj.modify_data(c);

			break;
		}
		case 5:
            exit(0);
		default:
		{
			cout<<"\n wrong choice entered, enter correct one";
			goto label;
		}
	}
	cout<<"\n Do you want to continue with the operations ? (y/n) : ";
	cin>>ch;
	system("cls");
    }while(ch=='y');
	return 0;
}
