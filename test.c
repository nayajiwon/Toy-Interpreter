#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


#define BUF_LEN 1024

typedef struct Node{
	char *data;
	struct Node *left;
	struct Node *right;
}node;

node *startSymbol;

char fname[BUF_LEN];
void FileLoad();
void Interactive_Mode();
void makeTokens(char buf[BUF_LEN], char tokens[BUF_LEN][BUF_LEN]);

int main(){
	char menuNum[5];

	printf("\n=======================================\n");
	printf("1.File Load\n2.Interactive Mode\n3.Exit");
	printf("\n=======================================\n");

	printf("메뉴를 선택하세요 >>");
	fgets(menuNum, 5, stdin);
	
	if(menuNum[0] == '1')
	       FileLoad();

	else if(menuNum[0] == '2')
		Interactive_Mode();
	
	else if(menuNum[0] == '3'){
		printf("프로그램을 종료합니다.");
		return 1;
	}

	else 
		printf("없는 메뉴입니다\n");
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
	
	treeTool(tokens, p);

	return;
}

void minusGrammer(){
}

void ifGrammer(){
}

void treeTool(char tokens[BUF_LEN][BUF_LEN], int cnt){
	for(int i=0; i<cnt; i++){
		if((!strcmp(tokens[i], "(")) || (!strcmp(tokens[i], ")")) || (!strcmp(tokens[i], " ")))
			continue;
		else if((!strcmp(tokens[i], "minus")) || (!strcmp(tokens[i], "if"))) 
			//부모 노드 만들기 
			initTree(tokens[i]);
		else{
			printf("%s 들어옴  \n", tokens[i]);
			//자식노드 , 부모노드랑 연결할것 
			insertNode(startSymbol, tokens[i]);
		}
	}
	printn(startSymbol);
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

	if(par->left == NULL){
		paZZr->left = New;
		printf("=== %s\n", par->left->data);
		return;
	}
	
	if(par->right == NULL){
		par->right = New;
		return;
	}	

}
