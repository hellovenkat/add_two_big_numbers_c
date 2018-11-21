#include <stdio.h>
#include <stdlib.h> 
#include <limits.h> 
#include <string.h>
#include <assert.h>
#include <gmp.h>
/* ----------------------------------------------------------
   -------------Code used by both Queue and Stack----------- */
struct Node 
{ 
    int key; 
    struct Node *next; 
};
struct Node* newNode(int k) 
{ 
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node)); 
    temp->key = k; 
    temp->next = NULL; 
    return temp;  
} 
/* -------------------------------------------------------
   ---------------yourQueue implementation--------------- */ 
struct Queue 
{ 
    struct Node *front, *rear; 
}; 
struct Queue *createQueue() 
{ 
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 
void enQueue(struct Queue *q, int k) 
{ 
	if(k>9){
			printf("\n cannot be inserted in the queue \n");
			return;
	}
    struct Node *temp = newNode(k); 
    if (q->rear == NULL) 
    { 
       q->front = q->rear = temp; 
       return; 
    } 
    q->rear->next = temp; 
    q->rear = temp; 
} 
  
struct Node *deQueue(struct Queue *q) 
{ 
    // If q is empty, returns NULL. 
    if (q->front == NULL) 
       return NULL; 
    struct Node *temp = q->front; 
    q->front = q->front->next; 
    if (q->front == NULL) 
       q->rear = NULL; 
    return temp; 
}
/* -------------------------------------------------------
   ---------------yourStack implementation--------------- */
struct Stack 
{ 
    struct Node *high; 
}; 
struct Stack* createStack() 
{ 
	struct Stack *my = (struct Stack*) malloc(sizeof(struct Stack));
	my->high = NULL;
	return my;
}
void pushStack(struct Stack *s, int val)
{	
	// if stack is empty
	if(val>9){
		printf("\n cannot be inserted in the stack\n");
		return;
	}
	struct Node *temp = newNode(val); 
	if(s->high == NULL){
		s->high = temp;
	}	
	else{
		temp->next = s->high; 
		s->high = temp; 
	}
}
struct Node *popStack(struct Stack *s){
	if (s->high == NULL) 
       return NULL;    
    struct Node *temp = s->high; 
    s->high = s->high->next; 
    return temp; 
} 
/* -------------------------------------------------------
   ---------------helper function for yourAdd--------------- */
char* doAdd(int temp_res, char* result){
	char res[2];
	sprintf(res, "%d", temp_res); 
	int newSize = strlen(result)  + strlen(res) + 1;
	char * newBuffer = (char *)malloc(newSize);
	strcpy(newBuffer,result);
	strcat(newBuffer,res);
	return newBuffer;
}
/* -------------------------------------------------------
   --------------yourAdd implementation--------------- */
char* yourAdd (struct Queue *q, struct Stack* stack)
{
	char *result= "";
	while(stack->high !=NULL || q->front !=NULL){
		int popped_ele_stack = 0;
		int ele_queue = 0;
		if(stack->high !=NULL){
			struct Node *temp_stack_node = popStack(stack);
			popped_ele_stack = temp_stack_node->key;;
		}
		if(q->front !=NULL){
			struct Node *n = deQueue(q);
			ele_queue = n->key;
		}
		
		int temp_res = popped_ele_stack + ele_queue;
		result = doAdd(temp_res, result);
	}
	return result;
}
//This main function is to test your implementation.
void main(int argc, char* argv[]) 
{ 
	struct Queue *num1 = createQueue(); //should only be able to push 0-9. num1->push(10) is invalid
	struct Stack *num2 = createStack(); //should only be able to push 0-9. num2->push(10) is invalid
	mpz_t comp;
	mpz_init(comp);
    mpz_set_ui(comp,9);  // Initializing the variable 'comp' as 9, for checking if the value that is being inserted is greater than 9.
	mpz_t temp_loop1;
	mpz_init(temp_loop1);
	mpz_t num1Length;
	mpz_t num2Length;
	int flag_num1;
	int flag_num2;
	mpz_init(num1Length);
	mpz_set_ui(num1Length,0); // Initializing the variable 'num1Length' as 0.
    mpz_init(num2Length);
	mpz_set_ui(num2Length,0);  // Initializing the variable 'num2Length' as 0.
    // The input argument can be of any length, even greater than 20 digits
	flag_num1 = mpz_set_str(num1Length,argv[1], 10);    // Parsing the first input argument as a base 10 number and storing it in num1Length
	assert (flag_num1 == 0);
	flag_num2 = mpz_set_str(num2Length,argv[2], 10);    // Parsing the second input argument as a base 10 number and storing it in num1Length
	assert (flag_num2 == 0);

	for (mpz_set_ui(temp_loop1,1);  mpz_cmp(temp_loop1, num1Length) <= 0; mpz_add_ui(temp_loop1,temp_loop1,1) )
	{	
		if(mpz_cmp(temp_loop1, comp) <= 0){  //checking the number is less than 10 before pushing
			unsigned long int i = mpz_get_ui(temp_loop1);  // conversion of gmp integer to standard C type integer.
			enQueue(num1, i);    // pushing into the queue
		}
	}
	//Note: remember that the input can be greater than 20 digits.
	for (mpz_set_ui(temp_loop1,1);  mpz_cmp(temp_loop1, num2Length) <= 0; mpz_add_ui(temp_loop1,temp_loop1,1) )
	{			
		if(mpz_cmp(temp_loop1, comp) <= 0){   //checking the number is less than 10 before pushing
			unsigned long int i = mpz_get_ui(temp_loop1);
			pushStack(num2, i);   // pushing onto the stack
		}
	}
	if((mpz_cmp_d(num1Length,0) <= 0) && (mpz_cmp_d(num2Length,0) <= 0)){
        printf("invalid inputs");
    }
    else{
	    char *result = 	yourAdd(num1, num2);
	    printf("result: %s\n", result);
    }
    // cleaning up the variables
    mpz_clear(comp);
	mpz_clear(temp_loop1);
	mpz_clear(num1Length);
	mpz_clear(num2Length);
}



