#include<stdio.h> 
#include<string.h>
#include<stdlib.h> 

typedef enum{FALSE,TRUE}status_code;

typedef struct Time
{
    int hours;
    int min;
}time;

typedef struct Preferences
{
    char type[20];
    char name[20];
    struct Preferences *next;
} preferences;


typedef struct AUDIO_BOOK_TREE
{
    int audiobook_id;
    char title[20];
    char author[20];
    char narrator[20];
    time* duration;
    char genre[20];
    float sum_rating;
    int count_rating;
    int bal_factor;
    struct AUDIO_BOOK_TREE* left;
    struct AUDIO_BOOK_TREE* right;
}audio_book;

typedef struct USER_AUDIO_BOOK
{
    audio_book* aptr;
    time* timestamp;
    int user_rating;
    int bal_factor;
    struct USER_AUDIO_BOOK* left;
    struct USER_AUDIO_BOOK* right;
}user_audio_book;


typedef struct USER_TREE
{ 
	int user_id; 
	char name[20];
    char email[20];
    preferences* pref;
    user_audio_book* uaptr;
	int bal_factor;
	struct USER_TREE* left;
    struct USER_TREE* right;
}user; 

void  inOrder_user(user *root);
void  inOrder_uab(user_audio_book *root) ;
void  inOrder_ab(audio_book *root);
void print_particular_ab(audio_book* root);
void print_particular_user(user* root);
void print_particular_uab(user_audio_book* root);


int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 


int update_bal_fact_user(user* root)
{
    if(root == NULL)
	{
        return -1;
    }
    
    int left = update_bal_fact_user(root->left);
    int right = update_bal_fact_user(root->right);
    root->bal_factor = left - right;
    int ret_val=max(left,right);

    return 1 + ret_val;
}

user* search_user(user* uptr,int id)
{
   user* ptr=uptr;
    if(uptr!=NULL)
    {
      if(uptr->user_id>id)
      {
        ptr=search_user(uptr->left,id);
      }

      else if(uptr->user_id<id)
      {
        ptr=search_user(uptr->right,id);
      }
    }
    return ptr;
}

void search_audiobook(audio_book* uaptr,int id,audio_book** lptr)
{
    audio_book* ptr=uaptr;
    if(uaptr!=NULL)
    {

        search_audiobook(uaptr->left,id,lptr);
        if(uaptr->audiobook_id==id)
    {
        *lptr=uaptr;
    }
        search_audiobook(uaptr->right,id,lptr);
      
    }
    
}

status_code search_email(user*uptr,char* email)
{   status_code sc=FALSE;
    if(uptr!=NULL)
    {
        sc=search_email(uptr->left,email);
        if(sc!=TRUE)
        {
        if(strcmp(uptr->email,email)==0)
        {
            sc=TRUE;
        }
        else
        {      
             sc=search_email(uptr->right,email);
        }
        }
    } 
    return sc;   
}  
 user* create_user(int id,char* name,char* email,preferences* pref)
{
    user* lptr;
    lptr=(user*)(malloc(sizeof(user)));
    lptr->user_id=id;
      preferences *pptr, *nptr;
      pptr=NULL;
    strcpy(lptr->name,name);
    strcpy(lptr->email,email);
    while (pref != NULL)
    {
        nptr = (preferences *)(malloc(sizeof(preferences)));
        strcpy(nptr->name, pref->name);
        strcpy(nptr->type, pref->type);
        nptr->next = pptr;
        pptr = nptr;
        pref = pref->next;
    }
    lptr->pref = pptr;
    lptr->uaptr=NULL;
    lptr->left=NULL;
    lptr->right=NULL;
    lptr->bal_factor=0;
    return lptr;
}

user_audio_book* newuser_audio_book(audio_book* lptr,int id1) 
{ 
	user_audio_book* nptr = (user_audio_book*) malloc(sizeof(user_audio_book)); 
	audio_book* ptr;
	search_audiobook(lptr,id1,&ptr);
	nptr->aptr = ptr; 
	nptr->left = NULL; 
	nptr->right = NULL; 
	nptr->bal_factor = 0; 
	nptr->timestamp=(time*)(malloc(sizeof(time)));
    nptr->timestamp->hours=0;
    nptr->timestamp->min=0;
	nptr->left=0;
	nptr->right=0;
	nptr->user_rating=0;
	return(nptr); 
} 



user *rightRotate(user *y) 
{ 
	user *x = y->left; 
	user *T2 = x->right; 


	x->right = y; 
	y->left = T2; 

	
	update_bal_fact_user(x);

	return x; 
} 

 
user *leftRotate(user *x) 
{ 
	user *y = x->right; 
	user *t2 = y->left; 


	y->left = x; 
	x->right = t2; 

	update_bal_fact_user(y);

	return y; 
} 

user* insert_user(user* node, int id,char* name,char* email,preferences* pref) 
{ 

	if (node == NULL) 
	{
		return(create_user(id,name,email,pref)); 
	}

	if (id < node->user_id) 
	{
		node->left = insert_user(node->left, id,name,email,pref); 
	}
	else if (id > node->user_id) 
	{
		node->right = insert_user(node->right, id,name,email,pref); 
	}
	else 
	{
		return node; 
	}

	 update_bal_fact_user(node);

     int balance=node->bal_factor; 

	if (balance > 1 && id < node->left->user_id) 
	{
		return rightRotate(node); 
	}

	if (balance < -1 && id > node->right->user_id) 
	{
		return leftRotate(node); 
	}

	if (balance > 1 && id > node->left->user_id) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	if (balance < -1 && id < node->right->user_id) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	return node; 
} 

user*add_user_profile(user*uptr,int id,char*name,char*email,preferences* pref)
{
     user*nptr;
     status_code sc;
     sc=search_email(uptr,email);
     if(sc==FALSE)
     {
        uptr=insert_user(uptr,id,name,email,pref);
     }
     else
     {
        printf("the email you provided is already exists");
     }
     return uptr;
}

int update_bal_fact_uab(user_audio_book* root)
{
    if(root == NULL)
	{
        return -1;
    }
    
    int left = update_bal_fact_uab(root->left);
    int right = update_bal_fact_uab(root->right);
    root->bal_factor = left - right;
    int ret_val=max(left,right);

    return 1 + ret_val;
}

user_audio_book *rightRotate_uab(user_audio_book *y) 
{ 
	user_audio_book *x = y->left; 
	user_audio_book *T2 = x->right; 


	x->right = y; 
	y->left = T2; 

	
	update_bal_fact_uab(x);

	return x; 
} 

 
user_audio_book *leftRotate_uab(user_audio_book *x) 
{ 
	user_audio_book *y = x->right; 
	user_audio_book*T2 = y->left; 


	y->left = x; 
	x->right = T2; 

	update_bal_fact_uab(y);

	return y; 
} 


user_audio_book* insert_uab(user_audio_book* node, int id,audio_book* aptr) 
{ 

	if (node == NULL) 
	{
		return(newuser_audio_book(aptr,id)); 
	}

	if (id < node->aptr->audiobook_id) 
	{
		node->left = insert_uab(node->left, id,aptr); 
	}
	else if (id > node->aptr->audiobook_id) 
	{
		node->right = insert_uab(node->right, id,aptr); 
	}
	else 
	{
		return node; 
	}

	 update_bal_fact_uab(node);

     int balance=node->bal_factor; 

	if (balance > 1 && id < node->left->aptr->audiobook_id) 
	{
		return rightRotate_uab(node); 
	}

	if (balance < -1 && id > node->right->aptr->audiobook_id) 
	{
		return leftRotate_uab(node); 
	}

	if (balance > 1 && id > node->left->aptr->audiobook_id) 
	{ 
		node->left = leftRotate_uab(node->left); 
		return rightRotate_uab(node); 
	} 

	if (balance < -1 && id < node->right->aptr->audiobook_id) 
	{ 
		node->right = rightRotate_uab(node->right); 
		return leftRotate_uab(node); 
	} 

	return node; 
} 


void  inOrder_user(user *root) 
{ 
	if(root != NULL) 
	{ 
		
		inOrder_user(root->left); 
        print_particular_user(root);
		inOrder_user(root->right); 
	} 
} 

void  inOrder_uab(user_audio_book *root) 
{ 
	if(root != NULL) 
	{ 
		
		inOrder_uab(root->left); 
        print_particular_uab(root);
		inOrder_uab(root->right); 
	} 
} 


user_audio_book* search_user_audio_book(user_audio_book* uaptr,int id)
{
    user_audio_book* ptr=uaptr;
    if(uaptr!=NULL)
    {
      if(uaptr->aptr->audiobook_id>id)
      {
        ptr=search_user_audio_book(uaptr->left,id);
      }
      else if(uaptr->aptr->audiobook_id<id)
      {
        ptr=search_user_audio_book(uaptr->right,id);
      }
    }
    return ptr;
}

int update_bal_fact1(audio_book* root){
    if(root == NULL)
    {
        return -1;
    }
    
    int left = update_bal_fact1(root->left);
    int right = update_bal_fact1(root->right);
    root->bal_factor = left - right;
    int ret_val=max(left,right);

    return 1 + ret_val;
}

audio_book *rightRotate_ab(audio_book*y) 
{ 
	audio_book *x = y->left; 
	audio_book *T2 = x->right; 


	x->right = y; 
	y->left = T2; 

	
	update_bal_fact1(x);

	return x; 
} 

 
audio_book *leftRotate_ab(audio_book *x) 
{ 
	audio_book *y = x->right; 
	audio_book *T2 = y->left; 


	y->left = x; 
	x->right = T2; 

	update_bal_fact1(y);

	return y; 
} 

audio_book* newaudio_book(int id,char* author,char* title,char* narr,float s_rating,int c_rating,int h,int m,char* genre) 
{ 
	audio_book* nptr = (audio_book*) malloc(sizeof(audio_book)); 
	nptr->audiobook_id = id; 
	strcpy(nptr->author,author);
	strcpy(nptr->title,title);
    strcpy(nptr->narrator,narr);
	nptr->sum_rating=s_rating;
	nptr->count_rating=c_rating;
	nptr->duration=(time*)(malloc(sizeof(time)));
    strcpy(nptr->genre,genre);
	nptr->duration->hours=h;
	nptr->duration->min=m;
	nptr->left = NULL; 
	nptr->right = NULL; 
	nptr->bal_factor = 0; 
	return(nptr); 
} 

audio_book* insert_ab(audio_book* node, int id,char* author,char* title,char* narr,float s_r,int c_r,int h,int m,char* genre) 
{ 

	if (node == NULL) 
		return(newaudio_book(id,author,title,narr,s_r,c_r,h,m,genre)); 

	if (strcmp(title,node->title)<0  || (strcmp(title,node->title)==0 && (strcmp(author,node->author)<0)) )
	{
		node->left = insert_ab(node->left, id,author,title,narr,s_r,c_r,h,m,genre); 
	}
	else if (strcmp(title,node->title)>0  || (strcmp(title,node->title)==0 && (strcmp(author,node->author)>0)))
	{
		node->right = insert_ab(node->right, id,author,title,narr,s_r,c_r,h,m,genre); 
	}
	else 
		return node; 

	 update_bal_fact1(node);
     int balance=node->bal_factor; 
	 
	if(strcmp(title,node->title)==0)
	{
		if (balance > 1 && strcmp(author,node->left->author)<0) 
		return rightRotate_ab(node); 
	

	if (balance < -1 && strcmp(author,node->right->author)>0) 
		return leftRotate_ab(node); 

	if (balance > 1 && strcmp(author,node->left->author)>0) 
	{ 
		node->left = leftRotate_ab(node->left); 
		return rightRotate_ab(node); 
	} 

	if (balance < -1 && strcmp(author,node->right->author)<0) 
	{ 
		node->right = rightRotate_ab(node->right); 
		return leftRotate_ab(node); 
	} 
	}

	if (balance > 1 && strcmp(title,node->left->title)<0) 
    {
		return rightRotate_ab(node); 
    }
	

	if (balance < -1 && strcmp(title,node->right->title)>0) 
    {
		return leftRotate_ab(node); 
    }

	if (balance > 1 && strcmp(title,node->left->title)>0) 
	{ 
		node->left = leftRotate_ab(node->left); 
		return rightRotate_ab(node); 
	} 

	if (balance < -1 && strcmp(title,node->right->title)<0) 
	{ 
		node->right = rightRotate_ab(node->right); 
		return leftRotate_ab(node); 
	}


	return node; 
} 

void print_particular_ab(audio_book* root)
{
    printf("AUDIO BOOK ID : %d \n",root->audiobook_id);
    printf("TITLE : %s\n",root->title);
    printf("AUTHOR : %s\n",root->author);
     printf("NARRATOR : %s\n",root->narrator);
    printf("GENRE : %s\n",root->genre);
    printf("HOURS   : %d ",root->duration->hours);
    printf("MIN : %d \n",root->duration->min);
    float rating=((root->sum_rating)/(root->count_rating));
    printf("Rating : %f \n\n",rating);
    
}

void print_particular_uab(user_audio_book* root)
{
 print_particular_ab(root->aptr);
 printf("HOURS   : %d ",root->timestamp->hours);
    printf("MIN : %d \n",root->timestamp->min);
    printf("Rating : %d \n\n",root->user_rating);
    
    
}

void print_particular_user(user* root)
{
    printf("\nUSER ID : %d \n",root->user_id);
    printf("NAME : %s\n",root->name);
    printf("EMAIL : %s\n",root->email);
    preferences *nptr;
     nptr = root->pref;
      printf("PREFERENCES: \n");
    while (nptr != NULL)
        {
            printf("TYPE  : %s\n", nptr->type);
            printf("NAME  : %s\n", nptr->name);
            nptr = nptr->next;
        }
    inOrder_uab(root->uaptr);
}

void  inOrder_ab( audio_book* root) 
{ 
	if(root != NULL) 
	{ 
		
		inOrder_ab(root->left); 
        print_particular_ab(root);
		inOrder_ab(root->right); 
	} 
} 

void edit_audio_book(audio_book *aptr, int id, char *type, char *name, time *tptr)
{
    audio_book *aptr1;
    search_audiobook(aptr,id,&aptr1);

  
    if (strcmp(type, "title") == 0)
    {
        strcpy(aptr1->title, name);
    }
    else if (strcmp(type, "author") == 0)
    {
        strcpy(aptr1->author,name);
    }
    else if (strcmp(type, "duration") == 0)
    {
        aptr1->duration->hours = tptr->hours;
        aptr1->duration->min = tptr->min;
    }
}

//5

void search_author(audio_book*aptr,char*name)
{
    audio_book* root=aptr;
    if(root!=NULL)
    {
        search_author(root->left,name);
        if(strcmp(root->author,name)==0)
        {
          print_particular_ab(root);
        }
        search_author(root->right,name);

    }
}

void search_title(audio_book*aptr,char*name)
{
    audio_book* root=aptr;
    if(root!=NULL)
    {
        search_title(root->left,name);
        if(strcmp(root->title,name)==0)
        {
            print_particular_ab(root);
        }
        search_title(root->right,name);

    }
}

void search_genre(audio_book*aptr,char*name)
{
    audio_book* root=aptr;
    if(root!=NULL)
    {
        search_genre(root->left,name);
        if(strcmp(root->genre,name)==0)
        {
           print_particular_ab(root);
        }
        search_genre(root->right,name);

    }
}


void search_audio_book(audio_book* aptr,char* type,char* name)
{
    
    if(strcmp("author",type)==0)
    {
       search_author(aptr,name);
    }
    else if(strcmp("title",type)==0)
    {
        search_title(aptr,name);
    }
    else if(strcmp("genre",type)==0)
    {
        search_genre(aptr,name);
    }
}


//6

void listening_progress(user* uptr,int u_id,int id2,time *tpr, int *pptr)
{
    user* uptr1=uptr;
    user_audio_book* nptr,*ptr;
    uptr1=search_user(uptr1,u_id);
    ptr=uptr1->uaptr;
    nptr=search_user_audio_book(ptr,id2);
    int rem;
    if (tpr == NULL)
    {
        rem = ((nptr->aptr->duration->hours * 60) + nptr->aptr->duration->min) * (*pptr) / 100;
        nptr->timestamp->hours += rem / 60;
        nptr->timestamp->min += rem % 60;
        if (nptr->timestamp->min > 60)
        {
            nptr->timestamp->hours += 1;
            nptr->timestamp->min = nptr->timestamp->min % 60;
        }
       
    }
    else
    {

        rem = (nptr->timestamp->min + tpr->min);
        if (rem > 60)
        {
            nptr->timestamp->hours += tpr->hours + 1;
            nptr->timestamp->min = rem % 60;
        }
        else
        {
            nptr->timestamp->hours += tpr->hours;
            nptr->timestamp->min = rem;
        }
    }
    print_particular_uab(nptr);
}

//7
void merge_self_lib(user_audio_book** lptr,int l,int m,int n,user_audio_book** ptr1)
{
    int i,j,k;
    i=l;
    j=m+1;
    k=l;
    while((i<=m)&&(j<=n))
    {
        if(lptr[i]->timestamp->hours<(lptr[j]->timestamp->hours))
        {
            ptr1[k]=lptr[i];
            k++;
            i++;
        }
        else if(lptr[i]->timestamp->hours==(lptr[j]->timestamp->hours)&&lptr[i]->timestamp->min<lptr[j]->timestamp->min)
        {
            ptr1[k]=lptr[i];
            k++;
            i++;
        }

       else
       {
        ptr1[k]=lptr[j];
        k++;
        j++;
       }
    }

    if(i<=m)
    {
         while(i<=m)
         {
            ptr1[k]=lptr[i];
            k++;
            i++;
         }
    }
    else if(j<=n)
    {
        while(j<=n)
        {
            ptr1[k]=lptr[j];
            k++;
            j++;
        }
    }

    i=l;
    while(i<=n)
    {
        lptr[i]=ptr1[i];
        i++;
    }
}


void mergesort_user_lib(user_audio_book** aptr,int l,int h,user_audio_book** ptr1)
{
    int mid;
    if(l<h)
    {
        mid=((l+h)/2);
        mergesort_user_lib(aptr,l,mid,ptr1);
        mergesort_user_lib(aptr,mid+1,h,ptr1);
        merge_self_lib(aptr,l,mid,h,ptr1);
    }
}

void copy_userlib(user_audio_book* aptr1,user_audio_book** lptr,int* index,char* type)
{
    if(aptr1!=NULL)
    {
        copy_userlib(aptr1->left,lptr,index,type);
        if(strcmp(aptr1->aptr->genre,type)==0)
        {
        lptr[(*index)]=aptr1;
        ++(*index);
        }
        copy_userlib(aptr1->right,lptr,index,type);
    }
}

void display_user_libraries(user* uptr,int id,char* type)
{
    user* uptr1=search_user(uptr,id);
    user_audio_book* lptr[30];
    user_audio_book* ptr1[30];
    int index=0;
    copy_userlib(uptr1->uaptr,lptr,&index,type);
    if(index!=0)
    {
         mergesort_user_lib(lptr,0,index-1,ptr1);
         int x=index-1;
         while(x>=0)
         {
            print_particular_uab(lptr[x]);
            x--;
         }
    }
}

//8

void rate_audio_book(user* uptr,audio_book* aptr,int id,int a_id,int rating)
{
    user* ptr1;
    user_audio_book* ptr2,*ptr4;
    audio_book* ptr3;
    ptr1=search_user(uptr,id);
    ptr2=ptr1->uaptr;
    ptr4=search_user_audio_book(ptr2,a_id);
    ptr3=ptr4->aptr;
    if(ptr4->user_rating==0)
    {
        ptr4->user_rating=rating;
        ptr3->sum_rating+=rating;
        ++ptr3->count_rating;
    }
    else
    {
        ptr3->sum_rating=ptr3->sum_rating-ptr4->user_rating+rating;
        ptr4->user_rating=rating;
    }

    print_particular_uab(ptr4);
    
}

//9

void merge_self(audio_book** lptr,int l,int m,int n,audio_book** ptr1)
{
    int i,j,k;
    i=l;
    j=m+1;
    k=l;
    while((i<=m)&&(j<=n))
    {
        if((lptr[i]->sum_rating/lptr[i]->count_rating)<(lptr[j]->sum_rating/lptr[j]->count_rating))
        {
            ptr1[k]=lptr[i];
            k++;
            i++;
        }

       else
       {
        ptr1[k]=lptr[j];
        k++;
        j++;
       }
    }

    if(i<=m)
    {
         while(i<=m)
         {
            ptr1[k]=lptr[i];
            k++;
            i++;
         }
    }
    else if(j<=n)
    {
        while(j<=n)
        {
            ptr1[k]=lptr[j];
            k++;
            j++;
        }
    }

    i=l;
    while(i<=n)
    {
        lptr[i]=ptr1[i];
        i++;
    }
}

void mergesort(audio_book** aptr,int l,int h,audio_book** ptr1)
{
    int mid;
    if(l<h)
    {
        mid=((l+h)/2);
        mergesort(aptr,l,mid,ptr1);
        mergesort(aptr,mid+1,h,ptr1);
        merge_self(aptr,l,mid,h,ptr1);
    }
}

void store_audio_ptr(audio_book* aptr,audio_book** lptr,int* index)
{
    if(aptr!=NULL)
    {
        store_audio_ptr(aptr->left,lptr,index);
        if(aptr->count_rating!=0.00)
        {
        lptr[(*index)]=aptr;
        ++(*index);
        }
        store_audio_ptr(aptr->right,lptr,index);

    }
}

void most_popular_audiobook(audio_book* aptr)
{
    audio_book* ptr=aptr;
    audio_book* lptr[40];
    audio_book* ptr1[40];
    int index=0;
    store_audio_ptr(ptr,lptr,&index);
    if(index!=0)
    {
        mergesort(lptr,0,index-1,ptr1);
        float maximum=((lptr[index-1]->sum_rating)/lptr[index-1]->count_rating);
        int x=index-1;
        while(x>=0)
        {
            if(((lptr[x]->sum_rating)/lptr[x]->count_rating)==maximum)
            {
                print_particular_ab(lptr[x]);
            }
              x--;
        }
    }
    
}

//10

void total_listening_time(user_audio_book* uptr,time** tptr)
{
    if(uptr!=NULL)
    {
        total_listening_time(uptr->left,tptr);
        (*tptr)->hours+=uptr->timestamp->hours;
        (*tptr)->min+=uptr->timestamp->min;
        total_listening_time(uptr->right,tptr);
    }
}

void listening_report_user(user* uptr,int id)
{
    user* ptr;
    time* tptr=(time*)(malloc(sizeof(time)));
    tptr->hours=0;
    tptr->min=0;
    ptr=search_user(uptr,id);
    total_listening_time(ptr->uaptr,&tptr);
    print_particular_user(ptr);
    tptr->hours+=(tptr->min)/60;
    tptr->min=(tptr->min)%60;
    printf(" THE TOTAL LISTENING TIME IS : \n");
    printf("TOTAL HOURS : %d",tptr->hours);
    printf("TOTAL MIN : %d\n",tptr->min);

}

//12
time* return_timestamp(user_audio_book* uptr,int id)
{
    user_audio_book* ptr=uptr;
    time* tptr=NULL;
    while((ptr!=NULL)&&(ptr->aptr->audiobook_id!=id))
    {
        if(id<ptr->aptr->audiobook_id)
        {
            ptr=ptr->left;
        }

        else if(id>ptr->aptr->audiobook_id)
        {
            ptr=ptr->right;
        }
    }

    if(ptr!=NULL&&(ptr->aptr->audiobook_id==id))
    {
        tptr=ptr->timestamp;
    }
    return tptr;
}

void total_user_lt(user* uptr,int id,time** tptr)
{
    if(uptr!=NULL)
    {
        total_user_lt(uptr->left,id,tptr);
        time* tptr1;
        tptr1=return_timestamp(uptr->uaptr,id);
        if(tptr1!=NULL)
        {
            (*tptr)->hours+=tptr1->hours;
            (*tptr)->min+=tptr1->min;
        }
        total_user_lt(uptr->right,id,tptr);
    }
}



void listening_history_audio_book(user* uptr,int id,audio_book* aptr)
{
    user* lptr=uptr;
    audio_book* nptr=NULL;
    search_audiobook(aptr,id,&nptr);
    if(nptr!=NULL)
    {
    time* tptr;
    tptr=(time*)(malloc(sizeof(time)));
    tptr->hours=0;
    tptr->min=0;
    total_user_lt(uptr,id,&tptr);
    print_particular_ab(nptr);
    printf(" THE TOTAL LISTENING TIME OF AUDIO BOOK IS : \n");
    printf("TOTAL HOURS : %d",tptr->hours);
    printf("TOTAL MIN : %d\n",tptr->min);
    }
}

//13

void range_search(audio_book *aptr, int id1, int id2)
{
    if (aptr == NULL)
        return;
    if (aptr->audiobook_id >= id1 && aptr->audiobook_id <= id2)
       print_particular_ab(aptr);
    range_search(aptr->left, id1, id2);
    range_search(aptr->right, id1, id2);
}

FILE *audiobookappend_(FILE *fptr, audio_book *ptr)
{
    if (ptr == NULL)
    {
        return fptr;
    }
    else
    {
         fputc('a', fptr);
        fprintf(fptr, " %d ", ptr->audiobook_id);
        fputs(ptr->title, fptr);      
        fputs(" ", fptr);
        fputs(ptr->narrator, fptr);
         fputs(" ", fptr);
        fprintf(fptr, "%d", ptr->duration->hours);
        fputs(" ", fptr);
        fprintf(fptr, "%d", ptr->duration->min);
          fputs(" ", fptr);
        fputs(ptr->genre, fptr);
         fputs(" ", fptr);
           fprintf(fptr, "%f ", ptr->sum_rating);

             fprintf(fptr, "%d ", ptr->count_rating);
              fputs(ptr->author, fptr);  
              fputs(" ", fptr);
              fputs("$", fptr);

        fputs("\n", fptr);
    }
    return fptr;
}

audio_book * min_ab(audio_book* aptr)
{
    audio_book* ptr = aptr;
    while (ptr->left != NULL)
    {
        ptr = ptr->left;
    }
 
    return ptr;
}
 
audio_book* delete_ab(audio_book* root,char* title,char* author)
{
 
    if (root == NULL)
    {
        return root;
    }
 
if (strcmp(title,root->title)<0  || (strcmp(title,root->title)==0 && (strcmp(author,root->author)<0)) )
	{
        root->left = delete_ab(root->left,title,author);
	}
 
    else if (strcmp(title,root->title)>0  || (strcmp(title,root->title)==0 && (strcmp(author,root->author)>0)))
	{
        root->right = delete_ab(root->right,title,author);
	}

    else
    {
        
        if( (root->left == NULL) || (root->right == NULL) )
        {
            audio_book*temp = root->left ? root->left : root->right;
 
            
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
             {
            root->audiobook_id=temp->audiobook_id;
			 strcpy(root->author,temp->author);
			 strcpy(root->title,temp->title);
			 strcpy(root->narrator,temp->narrator);
			 root->sum_rating=temp->sum_rating;
			 root->count_rating=temp->count_rating;
			 root->duration->hours=temp->duration->hours;
			 root->duration->min=temp->duration->min;
			 strcpy(root->genre,temp->genre);
			 root->left=temp->left;
			 root->right=temp->right;
             }
        }
        else
        {

            audio_book* temp = min_ab(root->right);
             root->audiobook_id=temp->audiobook_id;
			 strcpy(root->author,temp->author);
			 strcpy(root->title,temp->title);
			 strcpy(root->narrator,temp->narrator);
			 root->sum_rating=temp->sum_rating;
			 root->count_rating=temp->count_rating;
			 root->duration->hours=temp->duration->hours;
			 root->duration->min=temp->duration->min;
			 strcpy(root->genre,temp->genre);


          
            root->right = delete_ab(root->right,temp->title,temp->author);
        }
    }
 
    if (root == NULL)
    {
      return root;
    }

    update_bal_fact1(root);

    int balance = root->bal_factor;

    if (balance > 1 && root->left->bal_factor >= 0)
    {
        return rightRotate_ab(root);
    }
 
    if (balance > 1 && root->left->bal_factor < 0)
    {
        root->left =  leftRotate_ab(root->left);
        return rightRotate_ab(root);
    }
 
    if (balance < -1 && root->right->bal_factor <= 0)
        return leftRotate_ab(root);
 
    if (balance < -1 && root->right->bal_factor > 0)
    {
        root->right = rightRotate_ab(root->right);
        return leftRotate_ab(root);
    }
 
    return root;
}

user_audio_book* min_uab(user_audio_book* uptr)
{

  user_audio_book* ptr = uptr;  
    while (ptr->left != NULL)
    {
        ptr = ptr->left;
    }
 
    return ptr;
}
 

user_audio_book* delete_uab(user_audio_book* root, int id)
{

 
    if (root == NULL)
        return root;
 
    
    if ( id < root->aptr->audiobook_id)
        root->left = delete_uab(root->left, id);
 
    
    else if( id > root->aptr->audiobook_id )
        root->right = delete_uab(root->right, id);
 
    
    else
    {
       
        if( (root->left == NULL) || (root->right == NULL) )
        {
            user_audio_book*temp = root->left ? root->left :
                                             root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
            { 
			  root->aptr=temp->aptr;
			  root->user_rating=temp->user_rating;
			  root->timestamp->hours=temp->timestamp->hours;
			  root->timestamp->min=temp->timestamp->min;
			  root->left=temp->left;
			  root->right=temp->right;
			}

            free(temp);
        }
        else
        {
            user_audio_book* temp = min_uab(root->right);         
              root->aptr=temp->aptr;
			  root->user_rating=temp->user_rating;
			  root->timestamp->hours=temp->timestamp->hours;
			  root->timestamp->min=temp->timestamp->min;
            root->right = delete_uab(root->right, temp->aptr->audiobook_id);
        }
    }
 

    if (root == NULL)
    {
      return root;
    }
 
     update_bal_fact_uab(root);
 
   
    int balance = root->bal_factor;
 
    if (balance > 1 && root->left->bal_factor >= 0)
    {
        return rightRotate_uab(root);
    }
 
    if (balance > 1 && root->left->bal_factor < 0)
    {
        root->left =  leftRotate_uab(root->left);
        return rightRotate_uab(root);
    }
 
    if (balance < -1 && root->right->bal_factor <= 0)
        return leftRotate_uab(root);

    if (balance < -1 && root->right->bal_factor > 0)
    {
        root->right = rightRotate_uab(root->right);
        return leftRotate_uab(root);
    }
 
    return root;
}


void add_to_user_lib(user* uptr,audio_book* aptr,int u_id,int a_id,char* type)
{
  

    user* uptr1;
    uptr1=search_user(uptr,u_id);
   
    user_audio_book* ptr1;
    ptr1=uptr1->uaptr;
    
    if(uptr1!=NULL)
    {
        if(strcmp(type,"add")==0)
        {
           
           uptr1->uaptr= insert_uab(uptr1->uaptr,a_id,aptr);
         
        }
        else
        {
            uptr1->uaptr=delete_uab(uptr1->uaptr,a_id);
              print_particular_user(uptr1);
        }
      
    }

}


FILE* inorder_append_ab(FILE* fptr,audio_book* root)
{
    if(root!=NULL)
    {
       inorder_append_ab(fptr,root->left);
       fptr=audiobookappend_(fptr,root);
       inorder_append_ab(fptr,root->right);
    }
    return fptr;

}

FILE *userappend_(FILE *fptr, user *ptr)
{
    if (ptr == NULL)
    {
        return fptr;
    }
    else
    {
        preferences* ptr2;
         fputc('u', fptr);
        fprintf(fptr, " %d ", ptr->user_id);
        fputs(ptr->name, fptr);      
        fputs(" ", fptr);
        fputs(ptr->email, fptr);
         fputs(" ", fptr);
           ptr2 = ptr->pref;

        while (ptr2 != NULL)
        {
            fputs(ptr2->type, fptr);
            fputs(" ", fptr);
            fputs(ptr2->name, fptr);
            fputs(" ", fptr);
            ptr2 = ptr2->next;
        } 
              fputs("$", fptr);

        fputs("\n", fptr);
    }
    return fptr;
}


FILE* inorder_append_user(FILE* fptr,user* root)
{
    if(root!=NULL)
    {
       inorder_append_user(fptr,root->left);
       fptr=userappend_(fptr,root);
       inorder_append_user(fptr,root->right);
    }
    return fptr;

}


FILE* userappend_id(FILE* fptr,user_audio_book* root)
{

     fprintf(fptr, " %d ",root->aptr->audiobook_id);
     return fptr;
}
FILE* inorder_append_user_ab(FILE* fptr,user_audio_book* root)
{
    if(root!=NULL)
    {
       inorder_append_user_ab(fptr,root->left);
       fptr=userappend_id(fptr,root);
       inorder_append_user_ab(fptr,root->right);
    }
    return fptr;

}

FILE* inorder_append_user1(FILE* fptr,user* root)
{
    if(root!=NULL)
    {
       inorder_append_user1(fptr,root->left);
       fputc('b',fptr);
       fprintf(fptr, " %d ", root->user_id);
       fptr=inorder_append_user_ab(fptr,root->uaptr);
       fputs("-1",fptr);
        fputs("\n", fptr);
       inorder_append_user1(fptr,root->right);
    }
    return fptr;

}

int main()
{
    FILE *fptr, *fptr1;
    fptr1 = fopen("output.txt", "a");
    fptr = fopen("input1.txt", "r");
    char copy[200];
    char name[25];
    int audio_id;
    char narrator[50];
    char genre[15];
    char author[50];
    int hours, min;
     int id1;
   int id2;
   
    audio_book *aptr = NULL, *aptr1;
    user *uptr = NULL, *uptr1;
    user_audio_book *ptr3;
    char name_user[30];
    char email[40];
    int user_id;
    preferences *ptr1, *lptr1, *ptr2;
    lptr1 = NULL;
    char preference[30];
    int id;
    char add[10];
    int no_of_pref;
    char type1[20];
    char name1[20];
    preferences *nptr, *pptr;
    int c_r;
    float s_r;
    time* tptr=(time* )(malloc(sizeof(time)));
    int rating1;

    while (fscanf(fptr, " %c", &copy) != EOF)
    {

        if (copy[0] == 'a')
        {
            fscanf(fptr, "%d", &audio_id);
            fscanf(fptr, "%s", name);
            fscanf(fptr, "%s", narrator);
            fscanf(fptr, "%d", &hours);
            fscanf(fptr, "%d", &min);
            fscanf(fptr, "%s", genre);
            fscanf(fptr, "%s",author);
            fscanf(fptr, "%f", &s_r);
            fscanf(fptr, "%d", &c_r);
            
           aptr=insert_ab(aptr,audio_id,author,name,narrator,s_r,c_r,hours,min,genre);
            

            
        }
        else if (copy[0] == 'u')
        {
            fscanf(fptr, "%d", &user_id);
            fscanf(fptr, "%s", name_user);
            fscanf(fptr, "%s", email);
            while (fscanf(fptr, "%s", preference) != EOF && preference[0] != '$')
            {
                ptr1 = (preferences *)(malloc(sizeof(preferences)));
                strcpy(ptr1->type, preference);
                fscanf(fptr, "%s", preference);
                strcpy(ptr1->name, preference);
                ptr1->next = lptr1;
                lptr1 = ptr1;
            }

            lptr1 = NULL;
            uptr = add_user_profile(uptr,user_id,name_user,email,ptr1);
        }
        else if (copy[0] == 'b')

        {
            fscanf(fptr, "%d", &user_id);

            fscanf(fptr, "%d", &id);

            while (id != -1)
            {
                
                add_to_user_lib(uptr,aptr,user_id,id,"add");
                
                fscanf(fptr, "%d", &id);
            }
        }
        else
        {
            fgets(copy, 200, fptr);
        }
    }

    fclose(fptr);
    int ch;
    printf("enter a number : ");
    scanf("%d",&ch);
   
   switch (ch)
   {
    case 1:
     printf("ENTER THE AUDIO BOOK ID :");
    scanf("%d",&audio_id);
    printf("ENTER THE new  title : ");
    scanf("%s",name1);
    printf("ENTER THE NARRATOR : ");
    scanf("%s",narrator);
    printf("ENTER THE AUTHOR : ");
    scanf("%s",author);
     printf("ENTER THE new  HOURS :");
     scanf("%d",&hours);
     printf("ENTER THE new  MIN  :");
     scanf("%d",&min);
     printf("ENTER THE GENRE : ");
     scanf("%s",genre);
    insert_ab(aptr,audio_id,author,name1,narrator,0,0,hours,min,genre);
    inOrder_ab(aptr);
    break;

    time*tmr;
        tmr=(time*)(malloc(sizeof(time)));
    case 14:
    printf("ENTER THE AUDIO BOOK ID :");
    scanf("%d",&audio_id);
     printf("ENTER THE type title/authour/duration : \n");
     scanf("%s",type1);
     if(strcmp(type1,"title")==0)
     {
     printf("ENTER THE new  title : ");
     scanf("%s",name1);
     edit_audio_book(aptr,audio_id,type1,name1,NULL);
     }
     else if(strcmp(type1,"author")==0)
     {     
             printf("ENTER THE AUTHOR name : ");
             scanf("%s",author);
         
           
         
          edit_audio_book(aptr,audio_id,type1,author,NULL);
     }
     else
     {
        
        printf("ENTER THE new  HOURS :");
        scanf("%d",&tmr->hours);
        printf("ENTER THE new  MIN  :");
        scanf("%d",&tmr->min);
         edit_audio_book(aptr,audio_id,type1,NULL,tmr);

     }
     break;

    case 5:
    printf("ENTER THE type to search by title/author/genre : \n");
     scanf("%s",type1);
     printf("ENTER THE name of the type : ");
     scanf("%s",name1);
    search_audio_book(aptr,type1,name1);
     break;                                                                     

    case 2:
     printf("ENTER THE type to delete title&author : \n");
     printf("ENTER THE title : ");
     scanf("%s",name1);
     printf("ENTER THE author : ");
     scanf("%s",author);
     aptr=delete_ab(aptr,name1,author);
                                                    
     inOrder_ab(aptr);
     break;

    case 3:
    printf("ENTER THE NEW USER ID : ");
    scanf("%d",&user_id);
    printf("ENTER THE EMAIL ID : ");
    scanf("%s",email);
    printf("ENTER THE NUMBER OF PREFERENCES : ");
    scanf("%d",&no_of_pref);
    pptr=NULL;
    for(int i=0;i<no_of_pref;i++)
    {
        printf("ENTER THE type : \n");
        scanf("%s",type1);
        printf("ENTER THE name : ");
        scanf("%s",name1);
        nptr=(preferences* )(malloc(sizeof(preferences)));
        strcpy(nptr->name,name1);
        strcpy(nptr->type,type1);
        nptr->next=pptr;
        pptr=nptr;
    }
    break;
    
    case 4:

    printf("ENTER THE USER ID : ");
    scanf("%d",&user_id);
    printf("DO YOU WANT TO add/remove AUDIO BOOK : ");
    scanf("%s",add);
    printf("ENTER THE AUDIO BOOK ID :");
    scanf("%d",&audio_id);
    add_to_user_lib(uptr,aptr,user_id,audio_id,add);
    break;   
    // 5

    case 6:

    printf("ENTER THE USER ID : ");
     scanf("%d",&user_id);
     printf("ENTER THE AUDIO BOOK ID :");
     scanf("%d",&audio_id);
     printf("DO YOU WANT TO CHANGE DURATION BY time/percentage : \n");
     scanf("%s",type1);
     int* p_ptr;
     int per;


     if(strcmp(type1,"percentage")==0)
     {
         printf("ENTER THE PERCENTAGE :");
         scanf("%d",&per);
         p_ptr=&per;
         listening_progress(uptr,user_id,audio_id,NULL,p_ptr);
     }
     else
     {
         
         printf("ENTER THE HOURS : ");
         scanf("%d",&tptr->hours);
         printf("ENTER THE MIN : ");
          scanf("%d",&tptr->min);
          listening_progress(uptr,user_id,audio_id,tptr,NULL); 
          printf("ENTER THE AUDIO BOOK ID :");
     scanf("%d",&audio_id);
     listening_history_audio_book(uptr,audio_id,aptr);
                                           //6
     }
    break;
   case 7:
    printf("ENTER THE USER ID : ");
    scanf("%d",&user_id);
    printf("ENTER THE TYPE OF THE AUDIO BOOK : ");
    scanf("%s",type1);
    display_user_libraries(uptr,user_id,type1);
    break;
    // 7

     case 8:
     
     printf("ENTER THE USER ID : ");
     scanf("%d",&user_id);
     printf("\nENTER THE AUDIO BOOK ID :");
     scanf("%d",&audio_id);
     printf("ENTER THE RATING OF THE AUDIO BOOK B/W 1 - 5 :\n");
     scanf("%d",&rating1);
     rate_audio_book(uptr,aptr,user_id,audio_id,rating1);
     break;
    
    case 9:
    most_popular_audiobook(aptr);
    break;// 9
    
    case 10:
    printf("ENTER THE USER ID : ");
     scanf("%d",&user_id);
     listening_report_user(uptr,user_id);
    break;

     case 12:
    
 
    break;

   case 13:
  
    printf("ENTER THE AUDIO BOOK ID 1 :");
     scanf("%d",&id1);
      printf("ENTER THE AUDIO BOOK ID 2 :");
     scanf("%d",&id2);
    range_search(aptr,id1,id2);
    break;
   }
    fptr1=inorder_append_ab(fptr1,aptr);
    fptr1=inorder_append_user(fptr1,uptr);
   fptr1=inorder_append_user1(fptr1,uptr);
    return 0;

    

    
}

