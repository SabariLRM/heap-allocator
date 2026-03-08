#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

#define N 4096
#define Chu 32

struct Chunk {
    char* cur;
    int s;
    bool avail;
    bool chustat;
    struct Chunk *next;
};

struct Heap {
    char* start;
    size_t size;
};

struct Heap heap;
struct Chunk *head = NULL;

int meta,totchu,b,no;

void freeh(){
    munmap(heap.start,heap.size);
}

char* alloc(int s){
    int i = 0,c = 0;
    s = (s + Chu -1) & ~(Chu - 1);
    if (head == NULL){
        struct Chunk *new = (struct Chunk *)heap.start;
        new->cur = heap.start + meta;
        new->s = s;
        new->avail = false;
        new->next = NULL;
        head = new;
        return new->cur;
    }
    struct Chunk *nex = head;
    struct Chunk *cc = head;
    while (cc != NULL){
        nex = cc;
        cc = cc->next;
        i++;
        c += nex->s;
        if (nex->s >= s && nex->avail == true){
            if (nex->s >= (s+Chu)){
                struct Chunk *rem = (struct Chunk *)(nex + sizeof(struct Chunk *));
                rem->cur = nex->cur + s;
                rem->s = nex->s - s;
                rem->avail = true;
                rem->next = nex->next;
                nex->s = s;
                nex->avail = false;
                nex->next = rem;
                return nex->cur;
            }
            nex->avail = false;
            return nex->cur;
        }
    }
    if ((c + s) >= totchu){return NULL;}
    int y = (i*sizeof(struct Chunk));
    if ((y+sizeof(struct Chunk)) >= meta){return NULL;}
    struct Chunk *new = (struct Chunk *)(heap.start + y);
    new->cur = heap.start + meta + c;
    new->s = s;
    new->avail = false;
    new->next = NULL;
    nex->next = new;
    return new->cur;
}

void freec(char* p){
    if (head == NULL){return;}
    struct Chunk *freev = head;
    struct Chunk *prev = NULL;
    while (freev->cur != p){
        prev = freev;
        freev = freev->next;
        if(freev == NULL){return;}
    }
    if (prev != NULL && prev->avail == true){
        prev->s = prev->s + freev->s;
        prev->next = freev->next;
        return;
    }
    freev->avail = true;
}

char* all(size_t s){
    for (int i = 0;i<)
}

int main(){
    
    
    size_t p = (N + 4096 - 1) & ~(4096 - 1);

    char* ptr = (char*)mmap(NULL,p,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1,0);
    
    heap.start = ptr;
    heap.size = p;
    meta = (0.25 * heap.size);
    totchu = (0.75 * heap.size);
    b = sizeof(struct Chunk);
    no = meta/b;
    struct Chunk *tempchu = ptr; 
    head = tempchu;
    for (int i = 0;i<no;i++){
        *tempchu = ptr+(i*b);
        tempchu->cur = NULL;
        tempchu->s = 0;
        tempchu->avail = false;
        tempchu->chustat = false;
        tempchu->next = tempchu + b;
    }
    tempchu->next = NULL;
    char* a1 = alloc(64);
    printf("a1: %p\n",a1);
    printf("chunk: %d\n",aa);
    char* a2 = alloc(32);
    printf("a2: %p\n",a2);
    a1[0] = 'a';
    printf("a1 char: %c\n",a1[0]);
    freec(a1);
    char* a3 = alloc(32);
    printf("a3: %p\n",a3);
    a3[0] = 'b';
    printf("a3 char: %c\n",a3[0]);

    return 0;
}
