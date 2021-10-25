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

int category_fits(struct my_category* category, struct song_node* song)
{
    return song && category && category->letter == toupper(song->artist[0]);
}

int category_has_song(struct my_category* category, struct song_node* song)
{
    struct song_node* song_list;

    if(category_fits(category, song))
    {
        song_list = category->list;

        while(song_list && song_cmp(song_list, song))
        { song_list = song_list->next_song; }

        return song_list != NULL;
    } 

    return 0;
}

int category_is_empty(struct my_category* category)
{
    return category->list == NULL;
}

int category_add(struct my_category* category, struct song_node* song)
{
    if(!category_has_song(category, song))
    {
        category->list = song_insert_sorted(category->list, song);
        return 1;
    } 
    
    return 0;
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

struct my_category* library_get_category(struct my_library* library, struct song_node* song)
{
    int i;

    for(i = 0; i < CATEGORY_LENGTH; ++i)
    {
        if (category_fits(&library->category[i], song))
        { return &library->category[i]; }
    }

    return NULL;
}

struct my_category* library_get_rand_category(struct my_library* library)
{
    int i = rand() % CATEGORY_LENGTH;
    return &library->category[i];
}

int library_add(struct my_library* library, struct song_node* song)
{
    struct my_category* category = library_get_category(library, song);

    if (category)
    { return category_add(category, song); }

    return 0;
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