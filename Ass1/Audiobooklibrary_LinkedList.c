#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Author
{
    char author_name[30];
    struct Author *next;
} Author;

typedef struct time
{
    int hours;
    int min;
} time;

typedef struct Preferences
{
    char type[20];
    char name[20];
    struct Preferences *next;
} preferences;

typedef struct Audio_Book
{
    int audio_id;
    char title[40];
    Author *author;
    char narrator[30];
    time *duration;
    char genre[20];
    float rating;
    int rating_count;
    struct Audio_Book *next;

} audio_book;

typedef struct USER_AUDIO_BOOK
{
    audio_book *audio_ptr;
    time *timestamp;
    float user_rating;
    struct USER_AUDIO_BOOK *next;
} user_audio_book;

typedef struct USER
{
    int user_id;
    char name[30];
    char email[30];
    preferences *pref_ptr;
    user_audio_book *user_audio_ptr;
    struct USER *next;
} user;

audio_book *divide_audio(audio_book *lptr)
{
    audio_book *slow, *fast, *ptr;
    slow = lptr;
    fast = lptr->next->next;
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
        if (fast != NULL)
        {
            fast = fast->next;
        }
    }

    ptr = slow->next;
    slow->next = NULL;
    return ptr;
}

audio_book *merge_audio(audio_book *lptr1, audio_book *lptr2)
{
    audio_book *ptr1, *ptr2, *result, *tail;
    if (lptr1 == NULL)
    {
        result = lptr2;
    }

    else if (lptr2 == NULL)
    {
        result = lptr1;
    }

    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;
        if ((lptr1->audio_id) < (lptr2->audio_id))
        {
            result = lptr1;
            ptr1 = ptr1->next;
        }

        else
        {
            result = lptr2;
            ptr2 = ptr2->next;
        }

        tail = result;
        while ((ptr1 != NULL) && (ptr2 != NULL))
        {
            if ((ptr1->audio_id) < (ptr2->audio_id))
            {
                tail->next = ptr1;
                tail = tail->next;
                ptr1 = ptr1->next;
            }

            else
            {
                tail->next = ptr2;
                tail = tail->next;
                ptr2 = ptr2->next;
            }
        }

        if (ptr1 != NULL)
        {
            tail->next = ptr1;
        }

        else
        {
            tail->next = ptr2;
        }
    }

    return result;
}

audio_book *create(int id, char *name, Author *ptr, char *nar, int hrs, int min, char *genre)
{
    Author *nptr, *lptr;
    lptr = NULL;
    audio_book *result = (audio_book *)(malloc(sizeof(audio_book)));
    result->audio_id = id;
    strcpy(result->title, name);
    while (ptr != NULL)
    {
        nptr = (Author *)(malloc(sizeof(Author)));
        strcpy(nptr->author_name, ptr->author_name);
        nptr->next = lptr;
        lptr = nptr;
        ptr = ptr->next;
    }
    result->author = lptr;
    strcpy(result->narrator, nar);
    result->duration = (time *)(malloc(sizeof(time)));
    result->duration->hours = hrs;
    result->duration->min = min;
    result->rating = 0.0;
    result->rating_count = 0;
    strcpy(result->genre, genre);
    result->next = NULL;
    return result;
}

audio_book *mergesort_audio(audio_book *lptr)
{
    audio_book *ptr, *head;
    head = lptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        ptr = divide_audio(lptr);
        lptr = mergesort_audio(lptr);
        ptr = mergesort_audio(ptr);
        head = merge_audio(lptr, ptr);
    }
    return head;
}

user *divide_user(user *lptr)
{
    user *slow, *fast, *ptr;
    slow = lptr;
    fast = lptr->next->next;
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
        if (fast != NULL)
        {
            fast = fast->next;
        }
    }

    ptr = slow->next;
    slow->next = NULL;
    return ptr;
}

user *merge_user(user *lptr1, user *lptr2)
{
    user *ptr1, *ptr2, *result, *tail;
    if (lptr1 == NULL)
    {
        result = lptr2;
    }

    else if (lptr2 == NULL)
    {
        result = lptr1;
    }

    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;
        if ((lptr1->user_id) < (lptr2->user_id))
        {
            result = lptr1;
            ptr1 = ptr1->next;
        }

        else
        {
            result = lptr2;
            ptr2 = ptr2->next;
        }

        tail = result;
        while ((ptr1 != NULL) && (ptr2 != NULL))
        {
            if ((ptr1->user_id) < (ptr2->user_id))
            {
                tail->next = ptr1;
                tail = tail->next;
                ptr1 = ptr1->next;
            }

            else
            {
                tail->next = ptr2;
                tail = tail->next;
                ptr2 = ptr2->next;
            }
        }

        if (ptr1 != NULL)
        {
            tail->next = ptr1;
        }

        else
        {
            tail->next = ptr2;
        }
    }

    return result;
}

user *mergesort_user(user *lptr)
{
    user *ptr, *head;
    head = lptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        ptr = divide_user(lptr);
        lptr = mergesort_user(lptr);
        ptr = mergesort_user(ptr);
        head = merge_user(lptr, ptr);
    }
    return head;
}

audio_book *Add_audiobook(audio_book *ptr, int id, char *name, Author *aptr, char *nar, int hrs, int min, char *genre)
{
    audio_book *nptr, *result;
    Author *ptr1, *ptr2, *ptr3;
    char minimum[50];
    ptr1 = aptr;
    while (ptr1 != NULL)
    {
        strcpy(minimum, ptr1->author_name);
        ptr2 = ptr1->next;
        ptr3 = NULL;
        while (ptr2 != NULL)
        {
            if (strcmp(minimum, ptr2->author_name) <= 0)
            {
                strcpy(minimum, ptr2->author_name);
                ptr3 = ptr2;
            }
            ptr2 = ptr2->next;
        }
        if (ptr3 != NULL)
        {
            strcpy(ptr3->author_name, ptr1->author_name);
        }
        strcpy(ptr1->author_name, minimum);
        ptr1 = ptr1->next;
    }
    nptr = create(id, name, aptr, nar, hrs, min, genre);
    if (ptr == NULL)
    {
        ptr = nptr;
        nptr->next = NULL;
        result = ptr;
    }
    else
    {
        nptr->next = ptr;
        ptr = nptr;
        result = mergesort_audio(ptr);
    }

    if (result != NULL)
    {
        printf("\n inserted succesfully \n");
    }

    else
    {
        printf("\n failed \n");
    }
    return result;
}

void print(audio_book *ptr)
{
    Author *nptr;
    while (ptr != NULL)
    {
        printf("\nAUDIO BOOK ID : %d\n", ptr->audio_id);
        printf("TITLE : %s\n", ptr->title);
        nptr = ptr->author;
        printf("AUTHOURS  : \n");
        while (nptr != NULL)
        {
            printf("%s\n", nptr->author_name);
            nptr = nptr->next;
        }
        printf("NARRATOR : %s\n", ptr->narrator);
        printf("HOURS  : %d\n", ptr->duration->hours);
        printf("MIN : %d\n", ptr->duration->min);
        printf("GENRE : %s\n", ptr->genre);
        printf("RATING : %f\n\n", ptr->rating);
        ptr = ptr->next;
    }
}

void print_particular(audio_book *ptr)
{
    Author *nptr;

    {
        printf("\nAUDIO ID  : %d\n", ptr->audio_id);
        printf("TITLE : %s\n", ptr->title);
        nptr = ptr->author;
        printf("AUTHOURS : \n");
        while (nptr != NULL)
        {
            printf("%s\n", nptr->author_name);
            nptr = nptr->next;
        }
        printf("NARRATOR : %s\n", ptr->narrator);
        printf("HOURS : %d\n", ptr->duration->hours);
        printf("MIN : %d\n", ptr->duration->min);
        printf("GENRE : %s\n", ptr->genre);
        printf("RATING  : %f\n\n", ptr->rating);
        ptr = ptr->next;
    }
}

void search(audio_book *a_ptr, char *pref_type, char *pref)
{
    audio_book *lptr;
    lptr = a_ptr;
    int count = 0;

    if (strcmp("title", pref_type) == 0)
    {
        while (lptr != NULL)
        {
            if (strcmp(lptr->title, pref) == 0)
            {
                print_particular(lptr);
                count = 1;
            }
            lptr = lptr->next;
        }
    }
    else if (strcmp("genre", pref_type) == 0)
    {
        while (lptr != NULL)
        {
            if (strcmp(lptr->genre, pref) == 0)
            {
                print_particular(lptr);
                count = 1;
            }
            lptr = lptr->next;
        }
    }
    else if (strcmp("author", pref_type) == 0)
    {
        while (lptr != NULL)
        {
            Author *nptr = lptr->author;
            while (nptr != NULL)
            {
                if (strcmp(nptr->author_name, pref) == 0)
                {
                    print_particular(lptr);
                    count = 1;
                }
                nptr = nptr->next;
            }
            lptr = lptr->next;
        }
    }

    if (count == 0)
    {
        printf("no such audio_book\n");
    }
}

user *create_user(int id, char *name, char *email, preferences *pref)
{
    user *lptr;
    preferences *pptr, *nptr;
    pptr = NULL;
    lptr = (user *)(malloc(sizeof(user)));
    lptr->user_id = id;
    strcpy(lptr->name, name);
    strcpy(lptr->email, email);
    while (pref != NULL)
    {
        nptr = (preferences *)(malloc(sizeof(preferences)));
        strcpy(nptr->name, pref->name);
        strcpy(nptr->type, pref->type);
        nptr->next = pptr;
        pptr = nptr;
        pref = pref->next;
    }
    lptr->pref_ptr = pptr;
    lptr->user_audio_ptr = NULL;
    lptr->next = NULL;
    return lptr;
}

user *Add_user_profile(user *u_ptr, int id, char *name, char *email, preferences *pref)
{
    user *result, *nptr, *p_ptr;
    int flag = 0;
    p_ptr = u_ptr;
    while (p_ptr != NULL && flag == 0)
    {
        if ((strcmp(p_ptr->email, email) == 0))
        {
            printf("email exits \n");
            flag = 1;
            result = u_ptr;
        }
        else
        {
            p_ptr = p_ptr->next;
        }
    }
    if (flag == 0)
    {
        if (u_ptr == NULL)
        {
            nptr = create_user(id, name, email, pref);
            nptr->next = NULL;
            result = nptr;
        }

        else
        {
            nptr = create_user(id, name, email, pref);
            nptr->next = u_ptr;
            u_ptr = nptr;
            result = mergesort_user(u_ptr);
        }
    }

    return result;
}

void print_user(user *ptr)
{
    preferences *nptr;
    user_audio_book *lptr;
    audio_book *aptr;
    while (ptr != NULL)
    {
        printf("\nUSER ID  :  %d\n", ptr->user_id);
        printf("USER NAME : %s\n", ptr->name);
        printf("EMAIL : %s\n", ptr->email);
        nptr = ptr->pref_ptr;
        lptr = ptr->user_audio_ptr;
        printf("PREFERENCES: \n");
        while (nptr != NULL)
        {
            printf("TYPE  : %s\n", nptr->type);
            printf("NAME  : %s\n", nptr->name);
            nptr = nptr->next;
        }
        if (lptr != NULL)
        {
            printf("AUDIO BOOKS \n");
            aptr = lptr->audio_ptr;
        }
        else
        {
            aptr = NULL;
        }
        while (aptr != NULL)
        {
            print_particular(aptr);
            printf("HOURS LISTENED : %d\n", lptr->timestamp->hours);
            printf("MIN LISTENED : %d\n", lptr->timestamp->min);
            printf("RATING OF BOOK : %f\n", lptr->user_rating);
            lptr = lptr->next;
            if (lptr != NULL)
            {
                aptr = lptr->audio_ptr;
            }
            else
            {
                aptr = NULL;
            }
        }
        ptr = ptr->next;
    }
}
void print_particular_user(user *ptr)
{
    preferences *nptr;
    user_audio_book *lptr;
    audio_book *aptr;
    if (ptr != NULL)
    {
        printf("%d\n", ptr->user_id);
        printf("%s\n", ptr->name);
        printf("%s\n", ptr->email);
        nptr = ptr->pref_ptr;
        lptr = ptr->user_audio_ptr;
        while (nptr != NULL)
        {
            printf("%s\n", nptr->type);
            printf("%s\n", nptr->name);
            nptr = nptr->next;
        }
        if (lptr != NULL)
        {
            aptr = lptr->audio_ptr;
        }
        else
        {
            aptr = NULL;
        }
        while (aptr != NULL)
        {
            print_particular(aptr);
            printf("%d\n", lptr->timestamp->hours);
            printf("%d\n", lptr->timestamp->min);
            printf("%f\n", lptr->user_rating);
            lptr = lptr->next;
            if (lptr != NULL)
            {
                aptr = lptr->audio_ptr;
            }
            else
            {
                aptr = NULL;
            }
        }
    }
}
void Add_user_audio_book(user *uptr, audio_book *aptr, int id, char *type, int a_id)
{
    user_audio_book *lptr, *bptr, *cptr;
    audio_book *nptr = aptr;
    audio_book *pptr;
    user *uptr1 = uptr;
    int flag1 = 0;
    while (uptr1 != NULL && flag1 == 0)
    {
        if (uptr1->user_id == id)
        {
            flag1 = 1;
        }
        else
        {
            uptr1 = uptr1->next;
        }
    }
    if (flag1 == 0)
    {
        printf("\nno such user id exists\n");
    }
    else
    {
        if ((strcmp("add", type)) == 0)
        {
            while (nptr != NULL && nptr->audio_id != a_id)
            {
                nptr = nptr->next;
            }

            if (nptr != NULL)
            {

                lptr = uptr1->user_audio_ptr;

                if (lptr == NULL)
                {
                    user_audio_book *ptr = (user_audio_book *)(malloc(sizeof(user_audio_book)));
                    ptr->audio_ptr = nptr;
                    ptr->timestamp = (time *)(malloc(sizeof(time)));
                    ptr->timestamp->hours = 0;
                    ptr->timestamp->min = 0;
                    ptr->user_rating = 0.0;
                    ptr->next = NULL;
                    uptr1->user_audio_ptr = ptr;
                }
                else
                {
                    int flag = 0;
                    user_audio_book *ptr = (user_audio_book *)(malloc(sizeof(user_audio_book)));
                    ptr->audio_ptr = nptr;
                    ptr->timestamp = (time *)(malloc(sizeof(time)));
                    ptr->timestamp->hours = 0;
                    ptr->timestamp->min = 0;
                    ptr->user_rating = 0.0;
                    ptr->next = NULL;
                    lptr = uptr1->user_audio_ptr;
                    bptr = lptr;
                    pptr = bptr->audio_ptr;
                    if (a_id < pptr->audio_id)
                    {
                        ptr->next = lptr;
                        lptr = ptr;
                        uptr1->user_audio_ptr = ptr;
                        flag = 1;
                    }

                    if (flag == 0)
                    {
                        while (bptr->next != NULL && flag == 0)
                        {
                            pptr = bptr->audio_ptr;
                            if (pptr->audio_id < a_id && bptr->next != NULL && a_id < bptr->next->audio_ptr->audio_id)
                            {
                                ptr->next = bptr->next;
                                bptr->next = ptr;
                                flag = 1;
                            }
                            bptr = bptr->next;
                        }
                    }

                    if (flag == 0)
                    {
                        if (bptr->audio_ptr->audio_id != a_id && bptr->audio_ptr->audio_id < a_id)
                        {
                            bptr->next = ptr;
                        }
                    }
                    else if (flag == 0)
                    {
                        printf("audio book id exists before\n");
                    }
                }
            }
        }
        else
        {
            lptr = uptr1->user_audio_ptr;
            bptr = lptr;
            user_audio_book *prev;
            if (lptr != NULL)
            {
                pptr = bptr->audio_ptr;
                while (pptr != NULL && pptr->audio_id != a_id)
                {
                    prev = bptr;
                    bptr = bptr->next;
                    if (bptr != NULL)
                    {
                        pptr = bptr->audio_ptr;
                    }
                    else
                    {
                        pptr = NULL;
                    }
                }
                if (pptr == lptr->audio_ptr)
                {
                    lptr = lptr->next;
                    uptr1->user_audio_ptr = lptr;
                    free(bptr);
                }
                else
                {
                    if (bptr != NULL)
                    {
                        prev->next = bptr->next;
                        free(bptr);
                    }
                }
            }
        }
    }
}
void rate_audio_book(user *uptr, audio_book *aptr, int u_id, int a_id, float rating)
{
    user *uptr1 = uptr;
    int flag1 = 0;
    while (uptr1 != NULL && uptr1->user_id != u_id)
    {
        uptr1 = uptr1->next;
    }

    user_audio_book *nptr = uptr1->user_audio_ptr;

    while (nptr != NULL && nptr->audio_ptr->audio_id != a_id)
    {
        nptr = nptr->next;
    }

    if (nptr != NULL&&nptr->user_rating==0.00)
    {
        nptr->audio_ptr->rating_count = nptr->audio_ptr->rating_count + 1;
        nptr->audio_ptr->rating = ((nptr->audio_ptr->rating)*(nptr->audio_ptr->rating_count-1) + rating) / (nptr->audio_ptr->rating_count);
        nptr->user_rating = rating;
    }
    else if(nptr!=NULL)
    {
    nptr->audio_ptr->rating = ((nptr->audio_ptr->rating)*(nptr->audio_ptr->rating_count) -(nptr->user_rating)+ rating) / (nptr->audio_ptr->rating_count);
    nptr->user_rating = rating;
    }
    print_particular_user(uptr1);
}
audio_book *delete_audiobook(audio_book *aptr, char *type, char *name)
{
    audio_book *lptr = aptr;
    audio_book *prev = aptr;
    int flag = 0;
    if ((strcmp("title", type)) == 0)
    {
        while (lptr != NULL && flag == 0)
        {
            if (strcmp(lptr->title, name) == 0)
            {
                flag = 1;
            }
            else
            {
                prev = lptr;
                lptr = lptr->next;
            }
        }

        if (flag == 0)
        {
            printf("\n no such audio_book exits \n");
        }
        else
        {
            if (lptr == aptr)
            {
                aptr = aptr->next;
            }
            else
            {
                prev->next = lptr->next;
            }
        }
    }

    else
    {
        Author *pptr;

        while (lptr != NULL)
        {
            pptr = lptr->author;
            while (pptr != NULL && flag == 0)
            {
                if (strcmp(pptr->author_name, name) == 0)
                {
                    flag = 1;
                }
                else
                {
                    pptr = pptr->next;
                }
            }
            prev = lptr;
            if (flag == 1)
            {
                if (lptr == aptr)
                {
                    aptr = aptr->next;
                }
                else
                {
                    prev->next = lptr->next;
                }
            }

            lptr = lptr->next;
        }
    }
    return aptr;
}

void sort_by_rating(audio_book *aptr)
{
    audio_book *lptr, *min;
    int count = 0;
    int loc;
    audio_book *audio[100];
    float rat_m;
    lptr = aptr;
    while (lptr != NULL)
    {
        audio[count] = lptr;
        lptr = lptr->next;
        count++;
    }

    for (int i = 0; i < count - 1; i++)
    {
        min = audio[i];
        loc = i;
        for (int j = i + 1; j < count; j++)
        {
            if (audio[j]->rating < min->rating)
            {
                min = audio[j];
                loc = j;
            }
        }
        audio[loc] = audio[i];
        audio[i] = min;
    }

    int i = count - 1;
    while (i >= 0)
    {
        print_particular(audio[i]);
        i = i - 1;
    }
}
user_audio_book *merge_user_audio(user_audio_book *lptr1, user_audio_book *lptr2)
{
    user_audio_book *ptr1, *ptr2, *result, *tail;
    user_audio_book *ptr3, *ptr4;
    if (lptr1 == NULL)
    {
        result = lptr2;
    }

    else if (lptr2 == NULL)
    {
        result = lptr1;
    }

    else
    {
        int flag3 = 0;
        ptr1 = lptr1;
        ptr2 = lptr2;
        if (strcmp(lptr1->audio_ptr->title, lptr2->audio_ptr->title) < 0)
        {
            result = lptr1;
            ptr1 = ptr1->next;
        }

        else if (strcmp(lptr1->audio_ptr->title, lptr2->audio_ptr->title) == 0)
        {
            ptr3 = lptr1;
            ptr4 = lptr2;
            while (ptr3->audio_ptr->author != NULL && ptr4->audio_ptr->author != NULL && flag3 == 0)
            {
                if (strcmp(ptr3->audio_ptr->author->author_name, ptr4->audio_ptr->author->author_name) < 0)
                {
                    result = lptr1;
                    flag3 = 1;
                    ptr1 = ptr1->next;
                }
                else if (strcmp(ptr3->audio_ptr->author->author_name, ptr4->audio_ptr->author->author_name) > 0)
                {
                    result = lptr2;
                    flag3 = 1;
                    ptr2 = ptr2->next;
                }
                else
                {
                    ptr3->audio_ptr->author = ptr3->audio_ptr->author->next;
                    ptr4->audio_ptr->author = ptr4->audio_ptr->author->next;
                }
            }
        }
        else
        {
            result = lptr2;
            ptr2 = ptr2->next;
        }

        tail = result;
        while ((ptr1 != NULL) && (ptr2 != NULL))
        {
            if (strcmp(ptr1->audio_ptr->title, ptr2->audio_ptr->title) < 0)
            {
                tail->next = ptr1;
                tail = tail->next;
                ptr1 = ptr1->next;
            }
            else if (strcmp(ptr1->audio_ptr->title, ptr2->audio_ptr->title) == 0)
            {
                ptr3 = ptr1;
                ptr4 = ptr2;
                while (ptr3->audio_ptr->author != NULL && ptr4->audio_ptr->author != NULL && flag3 == 0)
                {
                    if (strcmp(ptr3->audio_ptr->author->author_name, ptr4->audio_ptr->author->author_name) < 0)
                    {
                        tail->next = ptr1;
                        tail = tail->next;
                        ptr1 = ptr1->next;
                        flag3 = 1;
                    }
                    else if (strcmp(ptr3->audio_ptr->author->author_name, ptr4->audio_ptr->author->author_name) > 0)
                    {

                        tail->next = ptr2;
                        tail = tail->next;
                        ptr2 = ptr2->next;
                        flag3 = 1;
                    }
                    else
                    {
                        ptr3->audio_ptr->author = ptr3->audio_ptr->author->next;
                        ptr4->audio_ptr->author = ptr4->audio_ptr->author->next;
                    }
                }
            }
            else
            {
                tail->next = ptr2;
                tail = tail->next;
                ptr2 = ptr2->next;
            }
        }

        if (ptr1 != NULL)
        {
            tail->next = ptr1;
        }

        else
        {
            tail->next = ptr2;
        }
    }

    return result;
}
user_audio_book *divide_user_audio(user_audio_book *lptr)
{
    user_audio_book *slow, *fast, *ptr;
    slow = lptr;
    fast = lptr->next->next;
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
        if (fast != NULL)
        {
            fast = fast->next;
        }
    }

    ptr = slow->next;
    slow->next = NULL;
    return ptr;
}

user_audio_book *mergesort_user_audio(user_audio_book *lptr)
{
    user_audio_book *ptr, *head;
    head = lptr;
    if (lptr != NULL && lptr->next != NULL)
    {
        ptr = divide_user_audio(lptr);
        lptr = mergesort_user_audio(lptr);
        ptr = mergesort_user_audio(ptr);
        head = merge_user_audio(lptr, ptr);
    }
    return head;
}
user_audio_book *insert(user_audio_book *uptr, user_audio_book *lptr)
{
    user_audio_book *ptr = (user_audio_book *)(malloc(sizeof(user_audio_book)));
    ptr->audio_ptr = lptr->audio_ptr;
    ptr->timestamp = (time *)malloc(sizeof(time));
    ptr->timestamp->hours = lptr->timestamp->hours;
    ptr->timestamp->min = lptr->timestamp->min;
    ptr->user_rating = lptr->user_rating;
    ptr->next = uptr;
    uptr = ptr;
    return uptr;
}
void merge_user_lib(user *uptr, int id1, int id2)
{
    user *uptr1 = uptr;
    user *uptr2 = uptr;
    int flag1 = 0;
    while (uptr1 != NULL && flag1 == 0)
    {
        if (uptr1->user_id == id1)
        {
            flag1 = 1;
        }
        else
        {
            uptr1 = uptr1->next;
        }
    }

    flag1 = 0;
    while (uptr2 != NULL && flag1 == 0)
    {
        if (uptr2->user_id == id2)
        {
            flag1 = 1;
        }
        else
        {
            uptr2 = uptr2->next;
        }
    }

    user_audio_book *lptr1 = uptr1->user_audio_ptr;
    user_audio_book *lptr2 = uptr2->user_audio_ptr;
    flag1 = 0;
    while (lptr2 != NULL)
    {
        flag1 = 0;
        lptr1 = uptr1->user_audio_ptr;
        while (lptr1 != NULL && flag1 == 0)
        {
            if (lptr1->audio_ptr->audio_id == lptr2->audio_ptr->audio_id)
            {
                flag1 = 1;
            }
            lptr1 = lptr1->next;
        }
        if (flag1 == 0)
        {
            uptr1->user_audio_ptr = insert(uptr1->user_audio_ptr, lptr2);
        }
        lptr2 = lptr2->next;
    }
    uptr1->user_audio_ptr = mergesort_user_audio(uptr1->user_audio_ptr);
    print_particular_user(uptr1);
    int flag2 = 0;
    lptr1 = uptr1->user_audio_ptr;
    while (lptr1 != NULL)
    {
        flag2 = 0;
        lptr2 = uptr2->user_audio_ptr;
        while (lptr2 != NULL && flag2 == 0)
        {
            if (lptr2->audio_ptr->audio_id == lptr1->audio_ptr->audio_id)
            {
                flag2 = 1;
            }
            lptr2 = lptr2->next;
        }
        if (flag2 == 0)
        {
            uptr2->user_audio_ptr = insert(uptr2->user_audio_ptr, lptr1);
        }
        lptr1 = lptr1->next;
    }
    uptr2->user_audio_ptr = mergesort_user_audio(uptr2->user_audio_ptr);
    print_particular_user(uptr2);
}

void listening_progress(user *uptr, int u_id, int a_id, time *tpr, int *pptr)
{
    user *uptr1 = uptr;
    int flag1 = 0;
    user_audio_book *nptr;
    int rem;
    while (uptr1 != NULL && flag1 == 0)
    {
        if (uptr1->user_id == u_id)
        {
            flag1 = 1;
        }
        else
        {
            uptr1 = uptr1->next;
        }
    }
    nptr = uptr1->user_audio_ptr;

    while (nptr != NULL && nptr->audio_ptr != NULL && nptr->audio_ptr->audio_id != a_id)
    {
        nptr = nptr->next;
    }

    if (tpr == NULL)
    {
        rem = ((nptr->audio_ptr->duration->hours * 60) + nptr->audio_ptr->duration->min) * (*pptr) / 100;
        nptr->timestamp->hours += rem / 60;
        nptr->timestamp->min += rem % 60;
        if (nptr->timestamp->min > 60)
        {
            nptr->timestamp->hours += 1;
            nptr->timestamp->min = nptr->timestamp->min % 60;
        }
        print_particular_user(uptr1);
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
}

void listening_history_report_user(user *uptr, int id)
{
    user *uptr1 = uptr;
    int flag1 = 0;
    user_audio_book *nptr;
    Author *aptr;
    int total_min = 0;
    int total_hours = 0;
    while (uptr1 != NULL && flag1 == 0)
    {
        if (uptr1->user_id == id)
        {
            flag1 = 1;
        }
        else
        {
            uptr1 = uptr1->next;
        }
    }
    nptr = uptr1->user_audio_ptr;
    while (nptr != NULL)
    {
        printf("\nUSER ID : %d", nptr->audio_ptr->audio_id);
        printf("TITLE : %s\n", nptr->audio_ptr->title);
        aptr = nptr->audio_ptr->author;
        printf("AUTHOURS : \n");
        while (aptr != NULL)
        {
            printf(" %s ", aptr->author_name);
            aptr = aptr->next;
        }
        printf("\n HOURS : %d", nptr->timestamp->hours);
        printf("  MIN : %d\n", nptr->timestamp->min);
        total_min += nptr->timestamp->min;
        total_hours += nptr->timestamp->hours;
        nptr = nptr->next;
    }
    printf("\n THE TOTAL LISTENING TIME IS : \n");
    total_hours = total_hours + (total_min) / 60;
    total_min = total_min % 60;
    printf("TOTAL HOURS = %d\n", total_hours);
    printf("TOTAL MINUTES =%d\n", total_min);
}

void display_user_libraries(user *uptr, int id, char *type)
{
    int flag1 = 0;
    user *uptr1 = uptr;
    user_audio_book *ptr[100];
    user_audio_book *minimum;
    user_audio_book *nptr;
    int count = 0;
    int loc;
    while (uptr1 != NULL && flag1 == 0)
    {
        if (uptr1->user_id == id)
        {
            flag1 = 1;
        }
        else
        {
            uptr1 = uptr1->next;
        }
    }
    nptr = uptr1->user_audio_ptr;
    while (nptr != NULL)
    {
        if (strcmp((nptr->audio_ptr->genre), type) == 0)
        {
            ptr[count] = nptr;
            count++;
        }
        nptr = nptr->next;
    }
    for (int i = 0; i < count - 1; i++)
    {
        minimum = ptr[i];
        loc = i;
        for (int j = i + 1; j < count; j++)
        {
            if ((ptr[j]->timestamp->hours < minimum->timestamp->hours))
            {
                minimum = ptr[j];
                loc = j;
            }
            else
            {
                if (ptr[j]->timestamp->hours == minimum->timestamp->hours)
                {
                    if (ptr[j]->timestamp->min < minimum->timestamp->min)
                    {
                        minimum = ptr[j];
                        loc = j;
                    }
                }
            }
        }
        ptr[loc] = ptr[i];
        ptr[i] = minimum;
    }
    int i = count - 1;
    while (i >= 0)
    {
        print_particular(ptr[i]->audio_ptr);
        printf("hours : %d  ", ptr[i]->timestamp->hours);
        printf("min : %d/n", ptr[i]->timestamp->min);
        i--;
    }
}

void listening_history_report_audio_book(audio_book *aptr, int id, user *uptr)
{
    user *uptr1 = uptr;
    audio_book *aptr1 = aptr;
    user_audio_book *uaptr;
    int flag = 0;
    int total_min = 0, total_hours = 0;
    while (aptr1 != NULL && flag == 0)
    {
        if (aptr1->audio_id == id)
        {
            flag = 1;
        }
        else
        {
            aptr1 = aptr1->next;
        }
    }
    print_particular(aptr1);
    if (flag == 1)
    {
        while (uptr1 != NULL)
        {
            uaptr = uptr1->user_audio_ptr;
            while (uaptr != NULL)
            {
                if (uaptr->audio_ptr->audio_id == aptr1->audio_id)
                {
                    total_min += uaptr->timestamp->min;
                    total_hours += uaptr->timestamp->hours;
                }

                uaptr = uaptr->next;
            }
            uptr1 = uptr1->next;
        }
        printf("\nTHE TOTAL LISTENING TIME OF AUDIO_BOOK IS : \n");
        total_hours = total_hours + (total_min) / 60;
        total_min = total_min % 60;
        printf("TOTAL HOURS = %d\n", total_hours);
        printf("TOTAL MINUTES =%d\n", total_min);
    }
    else
    {
        printf("\n NOT VALID AUDIO_ID\n");
    }
}

void most_popular_audiobook(audio_book *aptr)
{
    audio_book *lptr, *max;
    int count = 0;
    int loc;
    audio_book *audio[100];
    float rat_m;
    lptr = aptr;
    while (lptr != NULL)
    {
        audio[count] = lptr;
        lptr = lptr->next;
        count++;
    }
    int i;
    max = audio[0];
    for (i = 1; i < count - 1; i++)
    {

        if (audio[i]->rating > max->rating)
        {
            max = audio[i];
        }
    }

    if (max->rating == 0.00)
    {
        printf("\n NO RATINGS ARE AVAILABLE TO DETERMINE POPULARITY \n");
    }
    else
    {
        int j = count - 1;
        printf("THE MOST POPULAR AUDIO BOOK IS/ARE : \n");
        while (j >= 0)
        {
            if (max->rating == audio[j]->rating)
            {
                print_particular(audio[j]);
            }
            j--;
        }
    }
}
FILE *audiobookappend_(FILE *fptr, audio_book *ptr)
{
    Author *aptr;
    if (ptr == NULL)
    {
        return fptr;
    }
    else
    {
        fputs("AUDIO ID : ", fptr);
        fprintf(fptr, "%d", ptr->audio_id);
        fputs("\nTITLE  : ", fptr);
        fputs(ptr->title, fptr);
        fputs("\nAUTHORS : ", fptr);
        aptr = ptr->author;
        while (aptr != NULL)
        {
            fputs(aptr->author_name, fptr);
            fputs("  ", fptr);
            aptr = aptr->next;
        }
        fputs("\nNARRATOR : ", fptr);
        fputs(ptr->narrator, fptr);
        fputs("\nDURATION  ", fptr);
        fputs("\nHOURS : ", fptr);
        fprintf(fptr, "%d", ptr->duration->hours);
        fputs("  MIN : ", fptr);
        fprintf(fptr, "%d", ptr->duration->min);
        fputs("\n", fptr);
        fputs("RATING : ", fptr);
        fprintf(fptr, "%f", ptr->rating);
        fputs("\nGENRE : ", fptr);
        fputs(ptr->genre, fptr);
        fputs("\n", fptr);
    }
    return fptr;
}
void edit_audio_book(audio_book *aptr, int id, char *type, char *name, Author *nptr, time *tptr)
{
    audio_book *aptr1 = aptr;
    Author *a_ptr1;
    while (aptr1 != NULL && aptr1->audio_id != id)
    {
        aptr1 = aptr1->next;
    }
    if (strcmp(type, "title") == 0)
    {
        strcpy(aptr1->title, name);
    }
    else if (strcmp(type, "author") == 0)
    {
        Author *ptr1, *ptr2, *ptr3;
        char minimum[50];
        ptr1 = nptr;
        while (ptr1 != NULL)
        {
            strcpy(minimum, ptr1->author_name);
            ptr2 = ptr1->next;
            ptr3 = NULL;
            while (ptr2 != NULL)
            {
                if (strcmp(minimum, ptr2->author_name) <= 0)
                {
                    strcpy(minimum, ptr2->author_name);
                    ptr3 = ptr2;
                }
                ptr2 = ptr2->next;
            }
            if (ptr3 != NULL)
            {
                strcpy(ptr3->author_name, ptr1->author_name);
            }
            strcpy(ptr1->author_name, minimum);
            ptr1 = ptr1->next;
        }
        Author *lptr = NULL;
        Author *ptr;
        while (nptr != NULL)
        {
            ptr = (Author *)(malloc(sizeof(Author)));
            strcpy(ptr->author_name, nptr->author_name);
            ptr->next = lptr;
            lptr = ptr;
            nptr = nptr->next;
        }
        aptr1->author = lptr;
    }
    else if (strcmp(type, "duration") == 0)
    {
        aptr1->duration->hours = tptr->hours;
        aptr1->duration->min = tptr->min;
    }
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
    Author *ptr, *lptr = NULL;
    audio_book *aptr = NULL, *aptr1;
    user *uptr = NULL, *uptr1;
    user_audio_book *ptr3;
    char name_user[30];
    char email[30];
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

            while (fscanf(fptr, "%s", author) != EOF && author[0] != '$')
            {
                ptr = (Author *)(malloc(sizeof(Author)));
                strcpy(ptr->author_name, author);
                ptr->next = lptr;
                lptr = ptr;
            }

            aptr = Add_audiobook(aptr, audio_id, name, lptr, narrator, hours, min, genre);

            lptr = NULL;
            hours = min = 0.0;
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
            uptr = Add_user_profile(uptr, user_id, name_user, email, ptr1);
        }
        else if (copy[0] == 'b')

        {
            fscanf(fptr, "%d", &user_id);

            fscanf(fptr, "%d", &id);

            while (id != -1)
            {

                Add_user_audio_book(uptr, aptr, user_id, "add", id);
                fscanf(fptr, "%d", &id);
            }
        }
        else
        {
            fgets(copy, 200, fptr);
        }
    }

    fclose(fptr);
   /* printf("ENTER THE AUDIO BOOK ID :");
    scanf("%d",&audio_id);
    printf("ENTER THE new  title : ");
    scanf("%s",name1);
    printf("ENTER THE NARRATOR : ");
    scanf("%s",narrator);

     /*Author*atr,*atr1=NULL;
     int n;
     printf("ENTER THE No of AUTHOURS : ");
     scanf("%d",&n);
     while(n!=0)
     {
         atr=(Author*)(malloc(sizeof(Author)));             //1.1
         printf("ENTER THE AUTHOR name : ");
         scanf("%s",atr->author_name);
         atr->next=atr1;
         atr1=atr;
         n--;
      }

     printf("ENTER THE new  HOURS :");
     scanf("%d",&hours);
     printf("ENTER THE new  MIN  :");
     scanf("%d",&min);
     printf("ENTER THE GENRE : ");
     scanf("%s",genre);
    Add_audiobook(aptr,audio_id,name1,atr1,narrator,hours,min,genre);
    print(aptr);*/

    /*printf("ENTER THE AUDIO BOOK ID :");
    scanf("%d",&audio_id);
     printf("ENTER THE type title/authours/duration : \n");
     scanf("%s",type1);
     if(strcmp(type1,"title")==0)
     {
     printf("ENTER THE new  title : ");
     scanf("%s",name1);
     edit_audio_book(aptr,audio_id,type1,name1,NULL,NULL);
     }
     else if(strcmp(type1,"author")==0)
     {   Author*atr,*atr1=NULL;
         int n;
         printf("ENTER THE No of AUTHOURS : ");
         scanf("%d",&n);
         while(n!=0)
         {
             atr=(Author*)(malloc(sizeof(Author)));             //1.2
             printf("ENTER THE AUTHOR name : ");
             scanf("%s",atr->author_name);
             atr->next=atr1;
             atr1=atr;
             n--;
         }
          edit_audio_book(aptr,audio_id,type1,NULL,atr1,NULL);
     }
     else
     {
        time*tmr;
        tmr=(time*)(malloc(sizeof(time)));
        printf("ENTER THE new  HOURS :");
        scanf("%d",&tmr->hours);
        printf("ENTER THE new  MIN  :");
        scanf("%d",&tmr->min);
         edit_audio_book(aptr,audio_id,type1,NULL,NULL,tmr);

     }*/

    /*printf("ENTER THE type to search by title/author/genre : \n");
     scanf("%s",type1);
     printf("ENTER THE name of the type : ");
     scanf("%s",name1);
     search(aptr,type1,name1);*/
    // 3

    /* printf("ENTER THE type to delete title/author : \n");
     scanf("%s",type1);
     printf("ENTER THE name : ");
     scanf("%s",name1);
     aptr=delete_audiobook(aptr,type1,name1);                                                //2
     print(aptr);*/

    /*printf("ENTER THE NEW USER ID : ");
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

    }*/
    // 4

    /*printf("ENTER THE USER ID : ");
    scanf("%d",&user_id);
    printf("DO YOU WANT TO add/remove AUDIO BOOK : ");
    scanf("%s",add);
    printf("ENTER THE AUDIO BOOK ID :");
    scanf("%d",&audio_id);
    Add_user_audio_book(uptr,aptr,user_id,add,audio_id);*/
    // 5

    /* printf("ENTER THE USER ID : ");
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
         time* tptr=(time* )(malloc(sizeof(time)));
         printf("ENTER THE HOURS : ");
         scanf("%d",&tptr->hours);
         printf("ENTER THE MIN : ");
          scanf("%d",&tptr->min);
          listening_progress(uptr,user_id,audio_id,tptr,NULL);                                       //6
     }*/

    /*printf("ENTER THE USER ID : ");
    scanf("%d",&user_id);
    printf("ENTER THE TYPE OF THE AUDIO BOOK : ");
    scanf("%s",type1);
    display_user_libraries(uptr,user_id,type1);*/
    // 7

    float rating1;
     int count;
     printf("ENTER THE USER ID : ");
     scanf("%d",&user_id);
     printf("\nENTER THE AUDIO BOOK ID :");
     scanf("%d",&audio_id);
     printf("ENTER THE RATING OF THE AUDIO BOOK B/W 1 - 5 :\n");
     scanf("%f",&rating1);
     rate_audio_book(uptr,aptr,user_id,audio_id,rating1);
      printf("ENTER THE USER ID : ");
     scanf("%d",&user_id);
     printf("\nENTER THE AUDIO BOOK ID :");
     scanf("%d",&audio_id);
     printf("ENTER THE RATING OF THE AUDIO BOOK B/W 1 - 5 :\n");
     scanf("%f",&rating1);
     rate_audio_book(uptr,aptr,user_id,audio_id,rating1);
    
    // 8

    /*most_popular_audiobook(aptr);*/ // 9

    /*printf("ENTER THE USER ID : ");
     scanf("%d",&user_id);
     listening_history_report_user(uptr,user_id);*/
    // 10

    /*int user_id1;
    int user_id2;
    printf("ENTER THE USER ID 1  : ");
    scanf("%d",&user_id1);
    printf("ENTER THE USER ID 2 : ");
    scanf("%d",&user_id2);
    merge_user_lib(uptr,user_id1,user_id2);*/
    // 11

    /* printf("ENTER THE AUDIO BOOK ID :");
     scanf("%d",&audio_id);
     listening_history_report_audio_book(aptr,audio_id,uptr);*/
    // 12

   /* sort_by_rating(aptr);*/ // 13

    uptr1 = uptr;
    aptr1 = aptr;
    while (aptr1 != NULL)
    {
        fputs("AUDIO BOOK : \n", fptr1);
        fptr1 = audiobookappend_(fptr1, aptr1);
        fputs("\n", fptr1);
        aptr1 = aptr1->next;
    }
    while (uptr1 != NULL)
    {
        fputs("USER : ", fptr1);
        fputs("\n", fptr1);
        fputs("USER ID : ", fptr1);
        fprintf(fptr1, "%d", uptr1->user_id);
        fputs("\n", fptr1);
        fputs("USER NAME : ", fptr1);
        fputs(uptr1->name, fptr1);
        fputs("\n", fptr1);
        fputs("EMAIL : ", fptr1);
        fputs(uptr1->email, fptr1);
        fputs("\n", fptr1);
        fputs("PREFERENCES : ", fptr1);
        ptr2 = uptr1->pref_ptr;

        while (ptr2 != NULL)
        {
            fputs(ptr2->type, fptr1);
            fputs(" ", fptr1);
            fputs(ptr2->name, fptr1);
            fputs(" ", fptr1);
            ptr2 = ptr2->next;
        }
        ptr3 = uptr1->user_audio_ptr;
        fputs("\n\nAUDIO BOOKS : \n\n", fptr1);

        while (ptr3 != NULL)
        {
            fptr1 = audiobookappend_(fptr1, ptr3->audio_ptr);
            fputs("\n", fptr1);
            fputs("TIMELISTENED TO : \n", fptr1);
            fputs("HOURS : ", fptr1);
            fprintf(fptr1, "%d", ptr3->timestamp->hours);
            fputs(" ", fptr1);
            fputs("MIN : ", fptr1);
            fprintf(fptr1, "%d", ptr3->timestamp->min);
            fputs("\nUSER RATING : ", fptr1);
            fprintf(fptr1, "%f", ptr3->user_rating);
            fputs("\n\n", fptr1);
            ptr3 = ptr3->next;
        }
        fputs("\n", fptr1);

        uptr1 = uptr1->next;
    }

    return 0;
}

