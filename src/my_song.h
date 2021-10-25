#ifndef SAM_BELLIVEAU_MY_SONG_HEADER
#define SAM_BELLIVEAU_MY_SONG_HEADER 1

#define MAX_ARTIST_SIZE 64
#define MAX_TITLE_SIZE 64

struct song_node
{
    char artist[MAX_ARTIST_SIZE];
    char title[MAX_TITLE_SIZE];

    struct song_node* next_song;
};

struct song_node* song_create(const char*, const char*);

int song_eq_str(struct song_node*, const char*, const char*);
int song_cmp(struct song_node*, struct song_node*);

struct song_node* song_insert_front(struct song_node*, struct song_node*);
struct song_node* song_insert_sorted(struct song_node*, struct song_node*);

struct song_node* song_remove(struct song_node*, const char*, const char*);

void song_print(struct song_node*);
void song_print_list(struct song_node*);

struct song_node* song_get_index(struct song_node*, int);

struct song_node* song_get_rand(struct song_node*);

int song_list_length(struct song_node*);

struct song_node* song_free_all(struct song_node*);

#endif