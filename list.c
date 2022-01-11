#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define INITIAL_SIZE 2

typedef struct entry
{
	char *name, *lastname;
	float height;
	int age;
} Entry;

//you might want to write some functions to manipulate entries, such as initializing, copying, etc.

Entry *initializeEntry(char *name,char *lastname, float height, int age)
{
  Entry *newEntry = malloc(sizeof(Entry));

  newEntry->name = malloc(sizeof(char)*(strlen(name)+1));
  strcpy(newEntry->name,name);

  newEntry->lastname = malloc(sizeof(char)*(strlen(lastname)+1));
  strcpy(newEntry->lastname,lastname);

  newEntry->height = height;
  newEntry->age = age;

  return newEntry;
}

typedef struct arrayList 
{
	int capacity;     //max possible
	int size;         //number of entries
	Entry **data;
} List;

List *initializeList()
{
  List *newList = malloc(sizeof(List));
  newList->size = 0;
  newList->capacity = INITIAL_SIZE;
  newList->data = malloc(sizeof(Entry *)*newList->capacity);

  return newList;
}

void shiftPosition(List *myList, int position)
{
  int cur=myList->size;
      if (position==0)
      {
        while (cur>position)
        {
          myList->data[cur]=myList->data[cur-1];
          cur--;
        }
      }
      else if (position > 0)
      {
        while ((myList->data[cur-1] != NULL)||(cur<position))
        {
          myList->data[cur]=myList->data[cur-1];
          cur--;
        }
      }
}

void doubleCapacity(List *myList)
{
  int newCap = (myList->capacity)*2;
  myList->capacity = newCap;
  myList->data = realloc(myList->data,sizeof(Entry *)*newCap); 
}

void halveCapacity(List *myList)
{
  int newCap = (myList->capacity)/2;
  myList->capacity = newCap;
  myList->data = realloc(myList->data,sizeof(Entry *)*newCap);
}

void insertToHead(List *myList, char *name,char *lastname, float height, int age)
{
  if (myList->size==0)
  {
    Entry *newEntry = initializeEntry(name,lastname,height,age);
    myList->data[myList->size] = newEntry;
    myList->size+=1;
  }
  
  else
  {
    if (((myList->size)+1)<=(myList->capacity))
    {
      shiftPosition(myList, 0);
      Entry *newEntry = initializeEntry(name,lastname,height,age);
      myList->data[0] = newEntry;
      myList->size+=1;
    }

    else if (((myList->size)+1)>(myList->capacity))
    {
      doubleCapacity(myList);
      shiftPosition(myList, 0);

      Entry *newEntry = initializeEntry(name,lastname,height,age);
      myList->data[0] = newEntry;
      myList->size+=1;
    }
  }
}

void insertToTail(List *myList, char *name,char *lastname, float height, int age)
{
  if (((myList->size)+1)<=(myList->capacity))
  {
    Entry *newEntry = initializeEntry(name,lastname,height,age);
    myList->data[myList->size] = newEntry;
    myList->size+=1;
  }
  else if (((myList->size)+1)>(myList->capacity))
  {
    doubleCapacity(myList);
    
    Entry *newEntry = initializeEntry(name,lastname,height,age);
    myList->data[myList->size] = newEntry;
    myList->size+=1;
  }
  else printf("Invalid Insert!\n");
}

void printList(List *myList)
{
  int i=0;
  if (myList->data[0] != NULL)
  {
    while (myList->data[i] != NULL)
    {
      printf("[%d]    %-10s %-10s, ", i,myList->data[i]->name,myList->data[i]->lastname);
      printf("%.2f,    %d\n", myList->data[i]->height,myList->data[i]->age);
      i++;
    }
  }
  else printf("List is empty!!\n");
}

void printListInfo(List *myList)
{
  printf("size:%d capacity:%d\n",myList->size, myList->capacity);
}

int findPosition(List *myList,char *name)
{
  int i=0;
  if (myList->data[0] != NULL)
  {
    while (myList->data[i] != NULL)
    {
      if (!strcmp(myList->data[i]->name,name))
      {
        return i;
      }
      else i++;
    }
    return -1;
  }
}

void insertToPosition(List *myList, int position, char *name,char *lastname, float height, int age)
{
  if (((myList->size)+1)<=(myList->capacity))
  {
    if (myList->size==position)
    {
      Entry *newEntry = initializeEntry(name,lastname,height,age);
      myList->data[position] = newEntry;
      myList->size+=1;
    }
    else 
    {
      shiftPosition(myList, position);

      Entry *newEntry = initializeEntry(name,lastname,height,age);
      myList->data[position] = newEntry;
      myList->size+=1;
    }
  }
  else if (((myList->size)+1)>(myList->capacity))
    {
      doubleCapacity(myList);
      shiftPosition(myList, 0);

      Entry *newEntry = initializeEntry(name,lastname,height,age);
      myList->data[position] = newEntry;
      myList->size+=1;
    }
  else printf("Invalid Insert!\n");
}

void deleteList(List *myList)
{
  int i=myList->size-1;
  if (myList->data[i-1] != NULL)
  {
    while (myList->data[i-1] != NULL)
    {
      myList->data[i]=NULL;
      free(myList->data[i]);
      i--;
      myList->size-=1;
    }
    myList->data[i]=NULL;
    printf("List deleted!\n");
    
  }
  
  else printf("List is empty!!\n");
}


// below are the declarations of a list of functions that you might want to define
/*
----List *initializeList();
----void deleteList(List *myList);
-+-+void doubleCapacity(List *myList);
-+-+void halveCapacity(List *myList);
----void insertToHead(List *myList, char *name,char *lastname, float height, int age);
----void insertToTail(List *myList, char *name,char *lastname, float height, int age);
----void insertToPosition(List *myList, int position, char *name,char *lastname, float height, int age);
int findPosition(List *myList,char *name);
void deleteFromHead(List *myList);
void deleteFromTail(List *myList);
void deleteFromPosition(List *myList, int position);
----void printList(List *myList);
----void printListInfo(List *myList);
*/




//you can use the main function as below, which reads the input file, parses it for each command, and runs the necessary functions that are defined above
int main(int argc, char **argv) 
{
	FILE *fp = fopen(argv[1], "r");
	char *line = NULL;
	size_t lineBuffSize = 0;
	ssize_t lineSize;
	
	if(fp == NULL){
		fprintf(stderr, "Error opening file\n");
		return -1;
	}

	List *myList;
	myList = initializeList(); //uncomment this line when you define the function
	
	while((lineSize = getline(&line,&lineBuffSize,fp)) !=-1)
	{
		char *token;
		const char delimiter[2] = " ";
		
		//Since each line ends with a newline character, let's replace it with the null-terminator character
		//otherwise, it can cause us trouble below when we make string comparisons
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';

		//split the buffer by space character and get the first part written into variable "token"
		token = strtok(line,delimiter); 
					
		//In these nested if statements, read the command from file and execute it
		if(strcmp(token,"insertToHead")==0)
		{
			char *name, *lastname;
			float height;
			int age;
			name = strtok(NULL,delimiter);
			lastname = strtok(NULL,delimiter);
			height = atof(strtok(NULL,delimiter));
			age = atoi(strtok(NULL,delimiter));
			//change the print statement below with a call to insert to list
			//printf("insertToHead(listPointer,%s,%s,%0.2f,%d)\n",name,lastname,height,age);
			insertToHead(myList,name,lastname,height,age); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"insertToTail")==0)
		{
			char *name, *lastname;
			float height;
			int age;
			name = strtok(NULL,delimiter);
			lastname = strtok(NULL,delimiter);
			height = atof(strtok(NULL,delimiter));
			age = atoi(strtok(NULL,delimiter));
			//change the print statement below with a call to insert to list
			//printf("insertToTail(listPointer,%s,%s,%0.2f,%d)\n",name, lastname,height,age);
			insertToTail(myList,name,lastname,height,age); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"insertToPosition")==0)
		{
			char *name, *lastname;
			float height;
			int age,position;
			position = atoi(strtok(NULL,delimiter));
			name = strtok(NULL,delimiter);
			lastname = strtok(NULL,delimiter);
			height = atof(strtok(NULL,delimiter));
			age = atoi(strtok(NULL,delimiter));
			//change the print statement below with a call to insert to list
			//printf("insertToPosition(listPointer,%d,%s,%s,%0.2f,%d)\n",position,name, lastname,height,age);
			insertToPosition(myList,position,name,lastname,height,age); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"findPosition")==0)
		{
			char *name;
			name = strtok(NULL,delimiter);
			//change the print statement below with a call to search to list
			//printf("findPosition(listPointer,%s)\n",name);
			printf("%d\n",findPosition(myList,name)); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"deleteFromHead")==0)
		{
			//change the print statement below with a call to search to list
			printf("deleteFromHead(listPointer)\n");
			//deleteFromHead(myList); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"deleteFromTail")==0)
		{
			//change the print statement below with a call to search to list
			printf("deleteFromTail(listPointer)\n");
			//deleteFromTail(myList); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"deleteFromPosition")==0)
		{
			int position;
			position = atoi(strtok(NULL,delimiter));
			//change the print statement below with a call to search to list
			printf("deleteFromPosition(listPointer,%d)\n",position);
			//deleteFromPosition(myList,position); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"printList")==0)
		{
			//change the print statement below with a call to print function that prints the contents of the list
			//printf("printList(listPointer)\n");
			printList(myList); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"printListInfo")==0)
		{
			//change the print statement below with a call to print function that prints size information about the list
			//printf("printListInfo(listPointer)\n");
			printListInfo(myList); //this is an example call to the actual function, once you implement it
		}
		else if(strcmp(token,"deleteList")==0)
		{
			//change the print statement below with a call to the function that deallocates the memory for the list
			//printf("deleteList(listPointer)\n");
			deleteList(myList); //this is an example call to the actual function, once you implement it
		}
		else
		{
			printf("Invalid command: <%s>\n",token);
		}
	}
  
	fclose(fp);
	return 0;
} 
