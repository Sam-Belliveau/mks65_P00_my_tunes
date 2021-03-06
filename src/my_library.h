#ifndef SAM_BELLIVEAU_MY_LIBRARY_HEADER
#define SAM_BELLIVEAU_MY_LIBRARY_HEADER 1

#include "my_song.h"

struct my_category
{
    char letter;
    struct song_node* list;
};

struct my_category category_create(const char);

int category_is_empty(struct my_category*);

void category_add(struct my_category*, struct song_node*);

struct song_node* category_get_song(struct my_category*, const char*, const char*);
struct song_node* category_get_rand(struct my_category*);

void category_remove(struct my_category*, const char*, const char*);

void category_print(struct my_category*);

struct my_category* category_clear(struct my_category*);

#define CATEGORY_LENGTH (('Z' - 'A' + 1))

struct my_library
{
    struct my_category category[CATEGORY_LENGTH];
};

struct my_library* library_create();

int library_is_empty(struct my_library*);

struct my_category* library_get_category(struct my_library*, const char);
struct my_category* library_get_category_song(struct my_library*, struct song_node*);
struct my_category* library_get_category_rand(struct my_library*);

int library_add(struct my_library*, struct song_node*);

struct song_node* library_get_song(struct my_library*, const char*, const char*);
struct song_node* library_get_song_rand(struct my_library*);
struct song_node* library_get_song_rand_match(struct my_library*, const char*, const char*);

void library_remove(struct my_library*, const char*, const char*);

void library_print(struct my_library*);
void library_print_short(struct my_library*);
void library_print_match(struct my_library*, const char*, const char*);

struct my_library* library_clear(struct my_library*);
struct my_library* library_free(struct my_library*);

#endif