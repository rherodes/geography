#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>


int listLength = 6;
int numberChildren;
//assume first word in list is start word
char wordList[6][4];

struct node {
    char words[6][4];           //manually change
    int numWords;
};


struct node* successors(struct node getSucc){
    struct node *children = malloc(0*sizeof(struct node));

    int numChildren = 0;
    int i;
    int used = 0;

    for(i=0; i<listLength; i++){
        used = 0;
        int c;
        for(c=0; c < getSucc.numWords; c++){
            if(strcmp(getSucc.words[c],wordList[i]) == 0){
                used = 1;
            }
        }

        //if not used
        if(used == 0){

            //add to children array
            struct node newChild;
            int v;
            for(v = 0; v < getSucc.numWords; v++){
                strcpy(newChild.words[v],getSucc.words[v]);
            }
            strcpy(newChild.words[getSucc.numWords],wordList[i]);
            newChild.numWords = getSucc.numWords + 1;

            children = realloc(children, (numChildren+1) * sizeof(struct node));
            int b;
            for(b = 0; b < newChild.numWords; b++){
                strcpy(children[numChildren].words[b],newChild.words[b]);
            }
            children[numChildren].numWords = newChild.numWords;
            numChildren++;
        }
    }

    numberChildren = numChildren;
    return children;
}

int goalCheck(struct node checkNode){
    //check matching chars
    int correct = 0;
    int i;
    for(i = 0; i < listLength-1; i++){
        if(checkNode.words[i][2] != checkNode.words[i+1][0]){
            correct = 1;
        }
    }
    return correct;
}

//breadth first search
struct node bfs(struct node bfsNode){
    struct node* fringe = malloc(sizeof(struct node));
    int fringeSize = 1;
    fringe[0] = bfsNode;
    while(fringeSize>0){
        //only need to check goal state if numwords is length of list
        if(fringe[0].numWords == listLength){
            if(goalCheck(fringe[0]) == 0){
                return fringe[0];
            }
        }


        //set temp node for fringe[0]
        struct node temp = fringe[0];

        //remove first item from fringe

        int i=fringeSize;
        for(i = 0; i < fringeSize; i++){
            fringe[i] = fringe[i+1];
        }

        fringeSize--;
        fringe = realloc(fringe,fringeSize*sizeof(struct node));

        //get successors and add to fringe
        struct node* succList = successors(temp);

        int x;
        for(x = 0; x < numberChildren; x++){

            fringe = realloc(fringe,(fringeSize+1)*sizeof(struct node));

            int z;

            //set end of fringe to node
            int fringeWords;
            for(fringeWords = 0; fringeWords < succList[x].numWords; fringeWords++){
                strcpy(fringe[fringeSize].words[fringeWords],succList[x].words[fringeWords]);
            }
            fringe[fringeSize].numWords = succList[x].numWords;

            fringeSize++;
        }
    }

    free(fringe);
    struct node fail;
    fail.numWords=-1;
    return fail;
}


int main(){
    strcpy(wordList[0],"ABC");
    strcpy(wordList[1],"CDE");
    strcpy(wordList[2],"CFG");
    strcpy(wordList[3],"EHI");
    strcpy(wordList[4],"GJC");
    strcpy(wordList[5],"GKG");

    struct node startNode;
    strcpy(startNode.words[0], wordList[0]);
    startNode.numWords = 1;

    struct node result = bfs(startNode);

    //print result
    if(result.numWords == -1){
        printf("No solution found\n");
    }else{
        printf("Order of words: \n");
        int wordCount;
        for(wordCount=0; wordCount<listLength; wordCount++){
            printf("%s\n",result.words[wordCount]);
        }
    }

    return 0;
}
