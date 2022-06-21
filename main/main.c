#include <stdio.h>
#include "stdlib.h"
#include <time.h>

typedef struct node{
    int val;
    struct node* next;
    struct node* down;
}NODE;


NODE * seviyeDuzenle(NODE * head,int length,int *seviye){
	srand(time(NULL));
    NODE *head1,*prev,*current,*newNode,*tmp,*tmp2=head;
    int i,m=0;
    if (length<=3){
        head1=(NODE*) malloc(1*sizeof (NODE));
        head1->down=head;
        newNode=(NODE*) malloc(sizeof (NODE));
        head1->next=newNode;
        newNode->next=NULL;
        tmp=head->next;
        newNode->val= tmp->val;
        newNode->down= tmp;
        prev=(NODE*) malloc(sizeof (NODE));
        prev->down=head1;
        prev->next=NULL;
        (*seviye)++;
        return prev;
    } else{
        head1=(NODE*) malloc(sizeof (NODE));
        head1->down=head;
        current=head1;
        tmp=head;
        for (i=0;i<length;i++){
        	tmp=tmp->next;
            newNode=(NODE*) malloc(sizeof (NODE));
            current->next=newNode;
            if(random()){
            	newNode->val=tmp->val;
            	newNode->down=tmp;
            	newNode->next=NULL;
            	current=newNode;
            	newNode=NULL;
            	m++;
			}
        }
        current->next=NULL;
        head= seviyeDuzenle(head1,m,seviye);
        (*seviye)++;
        return head;
    }
}

int random(){
	return rand()%2;
}

void yazdir(NODE * head,int seviye){
	NODE *tmp;
	while(head->down!=NULL){
		printf("%d. seviye-> ",seviye);
		head=head->down;
		tmp=head->next;
		while(tmp!=NULL){
			printf("%d--",tmp->val);
			tmp=tmp->next;
		}
		printf("\n");
		seviye--;
	}
}

int araBul(NODE *head,int x,int seviye){
	NODE *tmp=head->down;
	if(x==tmp->val)
		return seviye;
	while(tmp!=NULL){
		while((tmp->next != NULL) && (x >= tmp->next->val)){
			if((tmp->val==x) || (tmp->next->val==x)){
				return seviye;
			}
			tmp=tmp->next;
		}
		tmp=tmp->down;
		seviye--;
	}
	return -1;
}

void degerEkle(NODE **head,int x){
	NODE *tmp=(*head)->next;
	int flag=0;
	if(x<=(tmp->val)){
			NODE *yeni=(NODE*)malloc(sizeof(NODE));
			yeni->val=x;
			*head=yeni;
			yeni->next=tmp;
			yeni->down=NULL;
	}
	else{
		while(tmp->next!=NULL && flag==0){
			if(x>=(tmp->val) && x<=(tmp->next->val)){
				NODE *yeni=(NODE*)malloc(sizeof(NODE));
				yeni->val=x;
				yeni->next=tmp->next;
				tmp->next=yeni;
				yeni->down=NULL;
				flag=1;
			}
			tmp=tmp->next;
		}
		if(flag==0){
			NODE *yeni=(NODE*)malloc(sizeof(NODE));
			yeni->val=x;
			yeni->next=NULL;
			tmp->next=yeni;
			yeni->down=NULL;
		}
	}
}

void degerSil(NODE **head,int x){
	NODE *tmp=(*head)->next;
	NODE *tmp2;
	int flag=0;
	while(tmp->next!=NULL && x!=tmp->val){
		tmp2=tmp;
		tmp=tmp->next;
		flag=1;
	}
	if(x==tmp->val){
		if(flag==1){
			tmp2->next=tmp->next;
		}
		else{
			(*head)->next=tmp->next;
		}
	}
}

int main(){
	NODE * head,*curr, * tmp, *sakla;
	int x,n,i,secim,seviyeSayisi=1;
	head=(NODE*)malloc(sizeof(NODE));
	head->down=NULL;
	head->next=NULL;
	printf("Eleman sayisi: ");
	scanf("%d",&n);	
	curr=head;
	printf("Lutfen degerleri sirali bicimde giriniz\n");
	for(i=0;i<n;i++){
		printf("%d. eleman: ",i+1);
		scanf("%d",&x);
		tmp=(NODE*)malloc(sizeof(NODE));
		tmp->val=x;
		tmp->down=NULL;
		curr->next=tmp;
		curr=curr->next;
		tmp=NULL;
	}
	curr->next=NULL;
	sakla=head;
	head=seviyeDuzenle(head,n,&seviyeSayisi);
	yazdir(head,seviyeSayisi);
	printf("\nSeviye: %d",seviyeSayisi);
	
	do{
		printf("\n\nYapmak istediginiz islemi secin\n1-Deger Ekleme\n2-Deger Silme\n3-Arama Yapma\n");
		scanf("%d",&secim);
		if(secim==1){
			printf("Eklenecek deger: ");
			scanf("%d",&x);
			seviyeSayisi=1;
			degerEkle(&sakla,x); n++;
			head=seviyeDuzenle(sakla,n,&seviyeSayisi);
			yazdir(head,seviyeSayisi);
		}
		else if(secim==3){
			printf("\nAradiginiz deger: ");
			scanf("%d",&x);
			int aranan=araBul(head,x,seviyeSayisi);
			if(aranan== -1){
				printf("\nBu eleman dizide yok :(");
			}
			else{
				printf("\nEleman %d. seviyede bulundu",aranan);
			}
		}
		else if(secim=2){
			printf("Silinecek deger: ");
			scanf("%d",&x);
			seviyeSayisi=1;
			degerSil(&sakla,x); n--;
			head=seviyeDuzenle(sakla,n,&seviyeSayisi);
			yazdir(head,seviyeSayisi);
		}
	}while(secim<4);
	
	return 0;
}
