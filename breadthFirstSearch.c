//Richard Herodes
//Breadth First Search
//May 2020

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

//Set global variables
//For different sized lists the list length will need to be changed here
int listLength = 6;
int numberChildren;
char wordList[6][4];

//Each node has a 2 dimensional array which had a certain number of words with a certain number of letters
struct node {
    char words[6][4];           //Manually change if list is changed
    int numWords;
};

//Create and return a list of successor nodes
struct node* successors(struct node getSucc){
    
    //Allocate memory for children list
    struct node *children = malloc(0*sizeof(struct node));

    int numChildren = 0;
    int i;
    int used = 0;

    //For every word in the wordlist check if it has been used and if not create a new node with that word as the next word
    for(i=0; i<listLength; i++){
        used = 0;
        int c;
        
        //Check if the word has been used so far
        for(c=0; c < getSucc.numWords; c++){
            
            //If word has been used set used variable to 1
            if(strcmp(getSucc.words[c],wordList[i]) == 0){
                used = 1;
            }
        }

        //If the word has not been used, append it to the current word list and give that list to a new child
        if(used == 0){

            //Create new child node
            struct node newChild;
            int v;
            
            //Copy old word list to new word list
            for(v = 0; v < getSucc.numWords; v++){
                strcpy(newChild.words[v],getSucc.words[v]);
            }
            
            //Add new word to new word list
            strcpy(newChild.words[getSucc.numWords],wordList[i]);
            newChild.numWords = getSucc.numWords + 1;

            //Allocate more memory for the children array
            children = realloc(children, (numChildren+1) * sizeof(struct node));
            
            //Add new child to children array
            int b;
            
            //Copy all words from new child word list into member of children array
            for(b = 0; b < newChild.numWords; b++){
                strcpy(children[numChildren].words[b],newChild.words[b]);
            }
            
            //Set number of words from member of children equal to the number of words in the new child
            children[numChildren].numWords = newChild.numWords;
            
            //Increment number of children
            numChildren++;
        }
    }

    //Set global variable numberChildren to new number of children
    numberChildren = numChildren;
    return children;
}

//Check if given node 
int goalCheck(struct node checkNode){
    
    //Check if the last character of the prior word matches the first character of the present word
    int correct = 0;
    int i;
    for(i = 0; i < listLength-1; i++){
        if(checkNode.words[i][2] != checkNode.words[i+1][0]){
            correct = 1;
        }
    }
    return correct;
}

//Breadth first search
struct node bfs(struct node bfsNode){
    
    //Allocate memory for the fringe
    struct node* fringe = malloc(sizeof(struct node));
    int fringeSize = 1;
    
    //Set first node in the fringe equal to the given start node
    fringe[0] = bfsNode;
    
    //Run search while nodes are still being created
    while(fringeSize>0){
        
        //Check goal state only if number of words is equal to the length of provided list
        if(fringe[0].numWords == listLength){
            if(goalCheck(fringe[0]) == 0){
                return fringe[0];
            }
        }


        //Use temporary node for fringe[0] to hold for later use
        struct node temp = fringe[0];
        
        int i=fringeSize;
        
        //Move all nodes in the fringe up in the order by one to kick out the first node
        for(i = 0; i < fringeSize; i++){
            fringe[i] = fringe[i+1];
        }

        //Reallocate fringe memory slot to 1 less than previous size to account for removal of first node
        fringeSize--;
        fringe = realloc(fringe,fringeSize*sizeof(struct node));

        //Call successors function on previous first node in fringe
        struct node* succList = successors(temp);

        //Add all children to fringe
        int x;
        for(x = 0; x < numberChildren; x++){

            //Allocate enough space for another node in the fringe
            fringe = realloc(fringe,(fringeSize+1)*sizeof(struct node));
            
            //Add new node to the end of the fringe
            int fringeWords;
            //Copy each word into the word list of the end node of the fringe
            for(fringeWords = 0; fringeWords < succList[x].numWords; fringeWords++){
                strcpy(fringe[fringeSize].words[fringeWords],succList[x].words[fringeWords]);
            }
            //Set the number of words of the node at the end of the fringe equal to the new node
            fringe[fringeSize].numWords = succList[x].numWords;

            //Increment fringe size
            fringeSize++;
        }
    }

    //Free the allocated memory used for the fringe
    free(fringe);
    struct node fail;
    
    //Set number of words to negative 1 to trigger 'no solution'
    fail.numWords=-1;
    return fail;
}


int main(){
    //Create list of words which will be fed into breadth first search algorithm
    strcpy(wordList[0],"ABC");
    strcpy(wordList[1],"CDE");
    strcpy(wordList[2],"CFG");
    strcpy(wordList[3],"EHI");
    strcpy(wordList[4],"GJC");
    strcpy(wordList[5],"GKG");

    //Create base node
    //First word of provided list used as first word of nodes
    //Set number of words to 1
    struct node startNode;
    strcpy(startNode.words[0], wordList[0]);
    startNode.numWords = 1;

    //Run breadth first search algorithm on starting node
    struct node result = bfs(startNode);

    //Print no solution if negative 1 returned
    if(result.numWords == -1){
        printf("No solution found\n");
    
    //Else number of words not negative 1
    }else{
        printf("Order of words: \n");
        int wordCount;
        
        //Print each word in list
        for(wordCount=0; wordCount<listLength; wordCount++){
            printf("%s\n",result.words[wordCount]);
        }
    }

    return 0;
}
