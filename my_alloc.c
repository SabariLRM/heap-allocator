#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

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

int meta,totchu;

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
        new->chustat = false;
        new->next = NULL;
        head = new;
        return new->cur;
    }
    struct Chunk *nex = head;
    struct Chunk *cc = head;
    struct Chunk *find = head;
    while(find != NULL && find->chustat == false){
        find = find->next;
    }
    int rr = 0;
    while(nex != NULL){
        rr++;
        nex = nex->next;
    }
    nex = head;
    while (cc != NULL){
        if(cc->chustat){
            cc = cc->next;
            continue;
        }
        nex = cc;
        cc = cc->next;
        c += nex->s;
        if (nex->s >= s && nex->avail == true){
            if (nex->s >= (s+Chu)){
                struct Chunk *rem;
                if (find == NULL){
                    int al = rr * sizeof(struct Chunk);
                    if (al + sizeof(struct Chunk) > meta){return NULL;}
                    rem = (struct Chunk *)(heap.start + al);
                }else{
                    rem = find;
                    rem->chustat = false;
                }
                rem->cur = nex->cur + s;
                rem->s = nex->s - s;
                rem->avail = true;
                rem->chustat = false;
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
    if ((c + s) > totchu){return NULL;}
    int y = (rr*sizeof(struct Chunk));
    if ((y+sizeof(struct Chunk)) > meta){return NULL;}
    find = head;
    while(find != NULL && find->chustat == false){
        find = find->next;
    }
    struct Chunk *new;
    if (find == NULL){
        new = (struct Chunk *)(heap.start + y);
    }else{
        new = find;
    }
    new->cur = heap.start + meta + c;
    new->s = s;
    new->avail = false;
    new->chustat = false;
    new->next = NULL;
    nex->next = new;
    return new->cur;
}

void freec(char* p){
    if (p == NULL) return;
    if (head == NULL){return;}
    struct Chunk *freev = head;
    struct Chunk *prev = NULL;
    while (freev->cur != p){
        if (!freev->chustat && freev->cur == p) break;
        if (!freev->chustat) prev = freev;
        freev = freev->next;
        if (freev == NULL) return;
    }
    if (prev != NULL && prev->avail == true){
        prev->s = prev->s + freev->s;
        freev->chustat = true;     
        freev->cur = NULL;
        freev->s = 0;
        freev->avail = false;
        return;
    }
    freev->avail = true;
}


void heap_init(size_t N){
    
    size_t p = (N + 4096 - 1) & ~(4096 - 1);

    char* ptr = (char*)mmap(NULL,p,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1,0);
    
    heap.start = ptr;
    heap.size = p;
    meta = (0.25 * heap.size);
    totchu = (0.75 * heap.size);
}
