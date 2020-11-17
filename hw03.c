#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
#include<string.h>

using namespace std;

#define BUF_LEN 1024
typedef struct Node{
	char *data;
	struct Node *left;
	struct Node *right;

	int dis;
}node;

struct str{
	char arr[BUF_LEN];
};

node *startSymbol;

void precedence_TreeTool(char tokens[BUF_LEN][BUF_LEN], int cnt);
char fname[BUF_LEN];
void FileLoad();
void DefunFileLoad();
void Interactive_Mode();
void makeTokens(char buf[BUF_LEN], char tokens[BUF_LEN][BUF_LEN]);
//void treeTool(char tokens[BUF_LEN][BUF_LEN], int cnt);
void printn(node *start);
void initTree(char data[BUF_LEN]);
void insertNode(node *par, char data[BUF_LEN]);
void postorder(node *startSymbol);
void printnode(node *a);

node *copy(node *root);

node* makePrecedenceTree(node *head[BUF_LEN], node * newN);
int findInd(char arr[BUF_LEN]);

node* makeBasicTree(struct str *temp);
node* makeNode(char data[BUF_LEN]);

int main(){
	char menuNum[5];

	printf("\n=======================================\n");
	printf("1.Define DEFUN\n2.Load DEFUN\n3.Interpreter\n4.Exit");
	printf("\n=======================================\n");

	printf("메뉴를 선택하세요 >>");
	fgets(menuNum, 5, stdin);
	
	if(menuNum[0] == '1'){
	       DefunFileLoad();
	}

	else if(menuNum[0] == '2')
		Interactive_Mode();
	
	else if(menuNum[0] == '3'){
		printf("실행 파일명을 입력하세요 >>.");
		return 1;
	}

	else 
		printf("없는 메뉴입니다\n");
}


void DefunFileLoad(){
	FILE *fp;
	char buf[BUF_LEN];
	char fname[BUF_LEN] = {"defun.txt"};
	char tokens[BUF_LEN][BUF_LEN];
	
	printf("DEFUN ");
	
	//fgets는 개행까지 먹어버림	
	fgets(buf, BUF_LEN, stdin);

	if((fp = fopen(fname, "w+"))==NULL){
		fprintf(stderr, "파일 읽기 오류\n");
		return;
	}
	
	//fwrite(buf, BUF_LEN, 1, fp); 
	fputs(buf, fp);
	
	makeTokens(buf, tokens);
}


void FileLoad(){
	FILE *fp;
	char buf[BUF_LEN];
	char tokens[BUF_LEN][BUF_LEN];
	
	printf("파일명을 입력하세요 >>");
	
	//fgets는 개행까지 먹어버림	
	scanf("%s", fname);

	if((fp = fopen(fname, "r"))==NULL){
		fprintf(stderr, "파일 읽기 오류\n");
		return;
	}
	
	fread(buf, BUF_LEN, 1, fp); 
	
	printf("파일 내용은\n");
	printf("---------------------------------\n");
	printf("%s", buf);
	printf("입니다\n");
	
	makeTokens(buf, tokens);
}


void Interactive_Mode(){
}

void makeTokens(char buf[BUF_LEN], char tokens[BUF_LEN][BUF_LEN]){
	//여는 괄호를 만나면 토큰에 저장한다	

	int len = strlen(buf);
	int arrFlag = 0; 
	int p=0;
	int n=0;
	
	for(int i=0; i<len-1; i++){
		if(buf[i] == '(' || buf[i] == ')'){
			arrFlag = 0; 
			if(i==0){
				tokens[0][0] = buf[i];
				++p;
			}
			else{

				tokens[++p][0] = buf[i];
				n=0;
				++p;
			}
		}
		else if(buf[i] == ' '){
			if(arrFlag){
				p++;
				n=0;
			}
		} 
		else{
			tokens[p][n++] = buf[i];
			arrFlag = 1;
		}
			
	}

	for(int i=0; i<p; i++){
		printf("%s\n", tokens[i]);
	}
	
	precedence_TreeTool(tokens, p);

	return;
}
void stackSt(stack<string> b){
	stack<string>a;
	a = b; 

	while(!a.empty()){
		cout<<"State:"<<a.top()<<endl;
		a.pop();
	}
}
void precedence_TreeTool(char tokens[BUF_LEN][BUF_LEN], int cnt){
	
	printf("precedencd 에 들옴\n");
	
	//스택에 괄호를 넣어가며 우선순위 트리를 만든다 
	stack<string>A;

	node * AA;
	
	struct str temp[3];
	
	//char imsi[BUF_LEN] = {"node"};
	string imsi = "NODE/";
	
	char ItoC[BUF_LEN];

	char check[BUF_LEN];

	node *expr[BUF_LEN];
//	node **expr;
	int expr_cnt = 0; 
	int open = 0; 
	
	printf("%d\n", cnt);

	for(int i=0; i<cnt; i++){
		//string c(tokens[i]);
	
		imsi = "NODE/";

		cout<<endl;
		cout<<i<<endl;	
		//stackSt(A);
		cout<<endl;	
		
		if(!strcmp(tokens[i], " "))
			continue;

		if(!strcmp(tokens[i], ""))
			continue;
		if(!strcmp(tokens[i], "(")){
			++open;
		}
		else if(!strcmp(tokens[i], ")")){
			if(!A.empty()){
				--open;
				//노드만들고, 계산 해줘야
				for(int p=0; p<3; p++){
					
					strcpy(temp[p].arr, A.top().c_str()); 

					A.pop();
					
				}
				
				for(int p=0; p<3; p++)
					printf("==> %s\n", temp[p].arr);
				

				
				
				
				printf("++++++++++++++++++++++%d++++++++++++++++++++++\n", expr_cnt);	
				expr[expr_cnt] = makeBasicTree(temp);
			
				printf("1) \n\n****************=== 000000000000inside print ===\n\n"); 
				if(expr_cnt >1){
				printf("1) \n\n****************=== 000000000000inside print ===\n\n"); 
					printnode(expr[0]);	
					printnode(expr[1]);	
				}
				//AA = makeBasicTree(temp);


				printf("!!!    %d\n", expr_cnt);

				printf("&& %s\n", expr[expr_cnt]->data);	
				printf("&& %s\n", expr[expr_cnt]->left->data);	
				printf("&& %s\n", expr[expr_cnt]->right->data);	
			

				/**
				 *  node/x  가 있을 경우에 
				 *  		노드를 연결한다 
				 */
			
				
				printf("\n\n=== 000000000000inside print ===\n\n"); 
				printnode(expr[0]);	
			
				makePrecedenceTree(expr, expr[expr_cnt]);
				
				
				printf("\n\n=== inside print ===\n\n"); 
				printnode(expr[expr_cnt]);

				sprintf(ItoC, "%d", expr_cnt);

				//strcat(imsi,ItoC );
				
				printf("111111, %d\n", ItoC);
				
				imsi = imsi + ItoC;//노드의 인덱스

				A.push(imsi);

				++expr_cnt;
			}
			else
			{
				return;
			}
		}
		else{
			//printf("%s를 넣는다!!\n", tokens[i]);
			A.push(tokens[i]);
		}
	}	

}

void printnode(node *a){
	if(a->data !=NULL){
		printf("data : %s\n", a->data);
	}
	if(a->left != NULL){
		printf("left : %s\n", a->left->data);
	       	printnode(a->left);
	}

	if(a->right != NULL){
		printf("right : %s\n", a->right->data);
		printnode(a->right);
	}
}


int findInd(char arr[BUF_LEN]){

	char *ptr;
	if((ptr = strrchr(arr, '/'))==NULL)
		return -1;

	ptr+=1;

	return atoi(ptr);


}

node *copy(node *root){
	node *newR;
	if(root!=NULL){
		newR = new node;
		newR->data = root->data;
		newR->left = copy(root->left);
		newR->right = copy(root->right);
	}
	else return NULL;

	return newR;
}

node* makePrecedenceTree(node *head[BUF_LEN], node * newN){
	
	

	printf("============\n");
	printnode(head[0]);


	int ch[3];
	
	node * copynode;
	//copynode = copy(newN);

	printf("%s, %s, %s\n", newN->data, newN->left->data, newN->right->data);	

	ch[0] = findInd(newN->data);
	if(ch[0] > 0){
		printf("============\n");
	}

	ch[1] = findInd(newN->left->data);
	if(ch[1] > 0){
		printf("~~~%d\n", ch[1]);

		copynode = copy(head[ch[1]]);
		
		printf("head->data: %s\n", head[ch[1]]->data);
		printf("head->data: %s\n", head[ch[1]]->left->data);

		printf("copynode->left: %s\n", copynode->data);
		printf("copynode->left: %s\n", copynode->left->data);
		printf("copynode->right: %s\n", copynode->right->data);
		
		newN->left = copynode;
		//printf("head->ch[1]->data , %s\n", head[ch[1]]->data);
		printf("head->ch[1]->data , %s\n", newN->left->left->data);
		//newN->left->data = head[ch[1]]->data;
		//printf("head->ch[1]->data , %s\n", newN->left->data);
	}

	ch[2] = findInd(newN->right->data);
	if(ch[2] > 0){
		printf("2)~~~%d\n", ch[2]);
		newN->right = head[ch[2]];
		printf("head->ch[1]->data , %s\n", newN->right->data);
		//newN->right->data = head[ch[2]]->data;
	}

	//printf("makePreTree: %d, %d, %d\n", a,b,c);
	
	return newN;
		


}

node* makeBasicTree(struct str *temp){
	//1,2 ==> 피연산자 3==>연산자  
	printf("==makeBasicTree\n");
	node *head;
	node *basic[3];

	for(int i=0; i<3; i++){
		printf("^^ %s\n", temp[i].arr);	
		basic[i] = makeNode(temp[i].arr);
		printf("%s\n", basic[i]->data);
	}

	basic[2]->left = basic[1];
	basic[2]->right = basic[0];

	head = basic[2];

	return head;
				
}

node* makeNode(char data[BUF_LEN]){
	printf("====\n");
	node *newNode = (node*)malloc(sizeof(node));
	newNode->left = NULL;
	newNode->right = NULL;

	//strcpy(newNode->data, data);
	newNode->data = data;
	printf("##%s\n", newNode->data);
	return newNode;
}
void postorder(node *startSymbol){//전위순회 
		
}
//스택을 사용하여
void minusGrammer(node *start){

}

void ifGrammer(node *start){

}

void printn(node *start){
	printf("%s\n", start->data);
	printf("%s\n", start->left->data);
	printf("%s\n", start->right->data);
}


//루트 노드 
void initTree(char data[BUF_LEN]){
	node *New;
	New = (node*)(malloc(sizeof(node)));
	
	startSymbol = New;
	startSymbol->data = data;
	
	New->left=NULL;
	New->right=NULL;

	printf("대빵 %s\n", startSymbol->data);
}

void insertNode(node *par, char data[BUF_LEN]){
	node *New;
	New = (node*)(malloc(sizeof(node)));
	New->data = data;

	printf("1 == %s\n", New->data);

	if(par->left == NULL){
		par->left = New;
		printf("=== %s\n", par->left->data);
		return;
	}
	
	if(par->right == NULL){
		par->right = New;
		return;
	}	

}
