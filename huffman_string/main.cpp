#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define MAX_SZ 256

//The Huffman tree node definition
typedef struct _htNode {
    char symbol;
    struct _htNode *left, *right;
} htNode;


typedef struct _htTree {
    htNode *root;
    //int size;
} htTree;

//The Huffman table nodes (linked list implementation)
typedef struct _hlNode {
    char symbol;
    char *code;
    struct _hlNode *next;
} hlNode;

// Huffman table
typedef struct _hlTable {
    hlNode *first;
    hlNode *last;
} hlTable;

htTree * buildTree(char *inputString);
hlTable * buildTable(htTree *huffmanTree);
void encode(hlTable *table, char *stringToEncode);
void decode(htTree *tree, char *stringToDecode);

// -----------pQueue----------------
typedef struct _pQueueNode {
    htNode * val;
    unsigned int priority;
    struct _pQueueNode *next;
} pQueueNode;

typedef struct _pQueue {
    unsigned int size;
    pQueueNode *first;
} pQueue;

void initPQueue(pQueue **queue);
void addPQueue(pQueue **queue, htNode * val, unsigned int priority);
htNode * getPQueue(pQueue **queue);



// --------------Huffman Methods---------------
void traverseTree(htNode *treeNode, hlTable **table, int k, char code[256])
{
    //If we reach the end we introduce the code in the table
    if(treeNode->left == NULL && treeNode->right == NULL)
    {
        code[k] = '\0';
        hlNode *aux = (hlNode *)malloc(sizeof(hlNode));
        aux->code = (char *)malloc(sizeof(char)*strlen(code));
        strcpy(aux->code,code);
        aux->symbol = treeNode->symbol;
        aux->next = NULL;
        if((*table)->first == NULL)
        {
            (*table)->first = aux;
            (*table)->last = aux;
        }
        else
        {
            (*table)->last->next = aux;
            (*table)->last = aux;
        }

    }

    //We concatenate a 0 for each step to the left
    if(treeNode->left!=NULL)
    {
        code[k]='0';
        traverseTree(treeNode->left,table,k+1,code);

    }
    //We concatenate a 1 for each step to the right
    if(treeNode->right!=NULL)
    {
        code[k]='1';
        traverseTree(treeNode->right,table,k+1,code);

    }
}

hlTable * buildTable(htTree * huffmanTree)
{
    //We initialize the table
    hlTable *table = (hlTable *)malloc(sizeof(hlTable));
    table->first = NULL;
    table->last = NULL;

    //Auxiliary variables
    char code[256];
    //k will memories the level on which the traversal is
    int k=0;

    //We traverse the tree and calculate the codes
    traverseTree(huffmanTree->root,&table,k,code);
    return table;
}

htTree * buildTree(char *inputString)
{
    //The array in which we calculate the frequency of the symbols
    //Knowing that there are only 256 posibilities of combining 8 bits
    //(256 ASCII characters)
    int * probability = (int *)malloc(sizeof(int)*256);

    //We initialize the array
    for(int i=0; i<256; i++)
        probability[i]=0;

    //We consider the symbol as an array index and we calculate how many times each symbol appears
    for(int i=0; inputString[i]!='\0'; i++)
        probability[(unsigned char) inputString[i]]++;

    //The queue which will hold the tree nodes
    pQueue * huffmanQueue;
    initPQueue(&huffmanQueue);

    //We create nodes for each symbol in the string
    for(int i=0; i<256; i++)
        if(probability[i]!=0)
        {
            htNode *aux = (htNode *)malloc(sizeof(htNode));
            aux->left = NULL;
            aux->right = NULL;
            aux->symbol = (char) i;

            addPQueue(&huffmanQueue,aux,probability[i]);
        }

    //We free the array because we don't need it anymore
    free(probability);

    //We apply the steps described in the article to build the tree
    while(huffmanQueue->size!=1)
    {
        int priority = huffmanQueue->first->priority;
        priority+=huffmanQueue->first->next->priority;

        htNode *left = getPQueue(&huffmanQueue);
        htNode *right = getPQueue(&huffmanQueue);

        htNode *newNode = (htNode *)malloc(sizeof(htNode));
        newNode->left = left;
        newNode->right = right;

        addPQueue(&huffmanQueue,newNode,priority);
    }

    //We create the tree
    htTree *tree = (htTree *) malloc(sizeof(htTree));

    tree->root = getPQueue(&huffmanQueue);

    return tree;
}

void encode(hlTable *table, char *stringToEncode)
{
    hlNode *traversal;

    printf("\nEncoding\nInput string : %s\nEncoded string : \n",stringToEncode);

    //For each element of the string traverse the table
    //and once we find the symbol we output the code for it
    for(int i=0; stringToEncode[i]!='\0'; i++)
    {
        traversal = table->first;
        while(traversal->symbol != stringToEncode[i])
            traversal = traversal->next;
        printf("%s",traversal->code);
    }

    printf("\n");
}

void decode(htTree *tree, char *stringToDecode)
{
    htNode *traversal = tree->root;

    printf("\nDecoding\nInput string : %s\nDecoded string : \n",stringToDecode);

    //For each "bit" of the string to decode
    //we take a step to the left for 0
    //or ont to the right for 1
    for(int i=0; stringToDecode[i]!='\0'; i++)
    {
        if(traversal->left == NULL && traversal->right == NULL)
        {
            printf("%c",traversal->symbol);
            traversal = tree->root;
        }

        if(stringToDecode[i] == '0')
            traversal = traversal->left;

        if(stringToDecode[i] == '1')
            traversal = traversal->right;

        if(stringToDecode[i]!='0'&&stringToDecode[i]!='1')
        {
            printf("The input string is not coded correctly!\n");
            return;
        }
    }

    if(traversal->left == NULL && traversal->right == NULL)
    {
        printf("%c",traversal->symbol);
        traversal = tree->root;
    }

    printf("\n");
}



//pQueue methods
void initPQueue(pQueue **queue)
{
    //We allocate memory for the priority queue type
    //and we initialize the values of the fields
    (*queue) = (pQueue *) malloc(sizeof(pQueue));
    (*queue)->first = NULL;
    (*queue)->size = 0;
    return;
}
void addPQueue(pQueue **queue, htNode * val, unsigned int priority)
{
    //If the queue is full we don't have to add the specified value.
    //We output an error message to the console and return.
    if((*queue)->size == 256)
    {
        printf("\nQueue is full.\n");
        return;
    }

    pQueueNode *aux = (pQueueNode *)malloc(sizeof(pQueueNode));
    aux->priority = priority;
    aux->val = val;

    //If the queue is empty we add the first value.
    //We validate twice in case the structure was modified abnormally at runtime (rarely happens).
    if((*queue)->size == 0 || (*queue)->first == NULL)
    {
        aux->next = NULL;
        (*queue)->first = aux;
        (*queue)->size = 1;
        return;
    }
    else
    {
        //If there are already elements in the queue and the priority of the element
        //that we want to add is greater than the priority of the first element,
        //we'll add it in front of the first element.

        //Be careful, here we need the priorities to be in descending order
        if(priority<=(*queue)->first->priority)
        {
            aux->next = (*queue)->first;
            (*queue)->first = aux;
            (*queue)->size++;
            return;
        }
        else
        {
            //We're looking for a place to fit the element depending on it's priority
            pQueueNode * iterator = (*queue)->first;
            while(iterator->next!=NULL)
            {
                //Same as before, descending, we place the element at the begining of the
                //sequence with the same priority for efficiency even if
                //it defeats the idea of a queue.
                if(priority<=iterator->next->priority)
                {
                    aux->next = iterator->next;
                    iterator->next = aux;
                    (*queue)->size++;
                    return;
                }
                iterator = iterator->next;
            }
            //If we reached the end and we haven't added the element,
            //we'll add it at the end of the queue.
            if(iterator->next == NULL)
            {
                aux->next = NULL;
                iterator->next = aux;
                (*queue)->size++;
                return;
            }
        }
    }
}

htNode * getPQueue(pQueue **queue)
{
    htNode * returnValue;
    //We get elements from the queue as long as it isn't empty
    if((*queue)->size>0)
    {
        returnValue = (*queue)->first->val;
        (*queue)->first = (*queue)->first->next;
        (*queue)->size--;
    }
    else
    {
        //If the queue is empty we show an error message.
        //The function will return whatever is in the memory at that time as returnValue.
        //Or you can define an error value depeding on what you choose to store in the queue.
        printf("\nQueue is empty.\n");
    }
    return returnValue;
}





int main(void)
{
	/*
	char text[256];
	std::cout << "Input text:" << std::endl;
	scanf ("%s", text);
	*/
	char text[256] = "Hello hi hhm";

    htTree *codeTree = buildTree(text);
    hlTable *codeTable = buildTable(codeTree);

    encode(codeTable, text);

    decode(codeTree,"01001111111111100001001100010101101");

    return 0;
}