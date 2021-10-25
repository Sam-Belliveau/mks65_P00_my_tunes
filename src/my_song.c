#include "my_song.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song_node* song_create(const char* artist, const char* title)
{
    struct song_node* song = malloc(sizeof(struct song_node));

    strncpy(song->artist, artist, MAX_ARTIST_SIZE);
    strncpy(song->title, title, MAX_TITLE_SIZE);

    song->next_song = NULL;

    return song;
}

int song_match(struct song_node* song, const char* artist, const char* title)
{
    int artist_cmp;
    int title_cmp;
    
    if(!song) return 0;

    if(artist)
    {
        artist_cmp = strcmp(song->artist, artist);
        if(artist_cmp) return 0;
    }

    if(title)
    {
        title_cmp = strcmp(song->title, title);
        if(title_cmp) return 0;
    }

    return 1;
}

int song_cmp(struct song_node* a, struct song_node* b)
{
    int artist_cmp;
    int title_cmp;
    
    if(a && b)
    {
        artist_cmp = strcmp(a->artist, b->artist);
        if(artist_cmp) return artist_cmp;

        title_cmp = strcmp(a->title, b->title);
        if(title_cmp) return title_cmp;

        return 0;
    } 
    else return a == b;
}

struct song_node* song_insert_front(struct song_node* front, struct song_node* new)
{
    new->next_song = front;
    return new;
}

struct song_node* song_insert_sorted(struct song_node* front, struct song_node* new)
{
    struct song_node* place = front;

    if (front)
    {
        if (song_cmp(new, place) <= 0) return song_insert_front(front, new); 
        else 
        {
            while(place->next_song)
            {
                if (song_cmp(new, place->next_song) <= 0) 
                {
                    new->next_song = place->next_song;
                    place->next_song = new;
                    return front;
                } 
                else place = place->next_song;
            }

            place->next_song = new;
        }
    
        return front;
    } else
    {
        return new;
    }
}

struct song_node* song_get(struct song_node* list, const char* artist, const char* title)
{
    while(list && !song_match(list, artist, title)) list = list->next_song;
    return list;
}

struct song_node* song_remove(struct song_node* list, const char* artist, const char* title)
{
    struct song_node* song;
    struct song_node* next;

    while(list && song_match(list, artist, title))
    {
        song = list;
        list = list->next_song;
        free(song);
    }

    song = list;

    while(song && (next = song->next_song))
    {
        if(song_match(next, artist, title))
        {
            song->next_song = next->next_song;
            free(next);
        } else 
        { song = song->next_song; }
    }

    return list;
}

void song_print(struct song_node* song)
{
    if(song) printf("%s - %s", song->artist, song->title);
    else printf("[NULL SONG]");
}

void song_print_list(struct song_node* songs)
{
    if(songs)
    {
        printf("{[");
        song_print(songs);
        songs = songs->next_song;

        for(; songs; songs = songs->next_song)
        {
            printf("] | [");
            song_print(songs);
        }
        printf("]}");
    }

    else printf("{EMPTY}");
}

struct song_node* song_free_all(struct song_node* songs)
{
    if (songs)
    {
        song_free_all(songs->next_song);
        free(songs);
    }

    return NULL;
}