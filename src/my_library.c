#include "my_library.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct my_category category_create(const char letter)
{
    struct my_category category;

    category.letter = toupper(letter);
    category.list = NULL;

    return category;
}

int category_is_empty(struct my_category* category)
{
    return category->list == NULL;
}

int category_add(struct my_category* category, struct song_node* song)
{
    category->list = song_insert_sorted(category->list, song);
}

struct song_node* category_get_song(struct my_category* category, const char* artist, const char* title)
{
    return category ? song_get(category->list, artist, title) : NULL;
}

struct song_node* category_get_rand(struct my_category* category)
{
    return song_get_rand(category->list);
}

void category_remove(struct my_category* category, const char* artist, const char* title)
{
    category->list = song_remove(category->list, artist, title);
}

void category_print(struct my_category* category)
{
    printf("%c: ", category->letter);
    song_print_list(category->list);
}

struct my_category* category_clear(struct my_category* category)
{
    category->list = song_free_all(category->list);
    return category;
}

int library_is_empty(struct my_library* library)
{
    int i;
    int empty = 0;

    for(i = 0; i < CATEGORY_LENGTH; ++i)
    { empty |= category_is_empty(&library->category[i]); }

    return empty;
}

struct my_library* library_create()
{
    int i;
    char category;
    struct my_library* library = malloc(sizeof(struct my_library));

    category = 'A';
    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        library->category[i] = category_create(category);
        category += 1;
    }

    return library;
}

struct my_category* library_get_category(struct my_library* library, const char letter)
{
    int i;

    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        if (toupper(library->category[i].letter) == toupper(letter))
        { return &library->category[i]; }
    }

    return NULL;
}

struct my_category* library_get_category_song(struct my_library* library, struct song_node* song)
{
    return library_get_category(library, song->artist[0]);
}

struct my_category* library_get_category_rand(struct my_library* library)
{
    int i;
    struct my_category* category;

    if(library_is_empty(library))
    { return NULL; }
    else
    {
        do 
        {
            i = rand() % CATEGORY_LENGTH;
            category = &library->category[i];
        } while(category_is_empty(category));
    }
    
    return category;
}

int library_add(struct my_library* library, struct song_node* song)
{
    struct my_category* category = library_get_category_song(library, song);

    if (category)
    { return category_add(category, song); }

    return 0;
}

struct song_node* library_get_song(struct my_library* library, const char* artist, const char* title)
{
    return category_get_song(library_get_category(library, artist[0]), artist, title);
}

struct song_node* library_get_song_rand(struct my_library* library)
{
    return category_get_rand(library_get_category_rand(library));
}

void library_remove(struct my_library* library, const char* artist, const char* title)
{
    int i;

    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        category_remove(&library->category[i], artist, title);
    }
}

void library_print(struct my_library* library)
{
    int i;
    struct my_category* category;
    struct song_node* song;

    printf("Library {");
    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        category = &library->category[i];

        if (!category_is_empty(category))
        {
            printf("\n\tCategory %c:\n", category->letter);
            song = category->list;

            while(song)
            {
                printf("\t\t");
                song_print(song);
                printf("\n");

                song = song->next_song;
            }
        }
    }
    printf("}\n");
}

void library_print_short(struct my_library* library)
{
    int i;
    struct my_category* category;

    printf("Library {");
    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        category = &library->category[i];

        if (!category_is_empty(category))
        {
            printf("\n\tCategory %c:\t", category->letter);
            category_print(category);
        }
    }
    printf("\n}\n");
}

void library_print_match(struct my_library* library, const char* artist, const char* title)
{
    int i, first;
    struct my_category* category;
    struct song_node* song;

    first = 1;

    printf("Library { (");
    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        category = &library->category[i];

        if (!category_is_empty(category))
        {
            song = category->list;

            while(song)
            {
                if(song_match(song, artist, title))
                {
                    if(!first) printf(") | (");

                    song_print(song);
                    first = 0;
                }

                song = song->next_song;
            }
        }
    }
    printf(") }\n");
}

struct my_library* library_clear(struct my_library* library)
{
    int i = 0;

    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        category_clear(&library->category[i]);
    }

    return library;
}

struct my_library* library_free(struct my_library* library)
{
    if(library)
    {
        library_clear(library);
        free(library);
    }

    return NULL;
}