#include "my_song.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song_node* song_create(const char* artist, const char* title)
{
    struct song_node* song = malloc(sizeof(struct song_node));

    strncmp(song->artist, artist, MAX_ARTIST_SIZE);
    strncmp(song->title, title, MAX_TITLE_SIZE);

    song->next_song = NULL;

    return song;
}


int song_cmp(struct song_node* a, struct song_node* b)
{
    int artist_cmp;
    int title_cmp;

    artist_cmp = strcmp(a->artist, b->artist);
    if(artist_cmp) return artist_cmp;

    title_cmp = strcmp(a->title, b->title);
    if(title_cmp) return title_cmp;

    return 0;
}

struct song_node* song_insert_front(struct song_node* front, struct song_node* new)
{
    new->next_song = front;
    return new;
}

struct song_node* song_insert_sorted(struct song_node* front, struct song_node* new)
{
    struct song_node* place = front;

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
}

struct song_node* song_print(struct song_node* songs)
{
    printf("Songs {\n");
    
}

struct song_node* song_free_all(struct song_node* songs)
{
    if (songs)
    {
        song_free_all(songs);
        free(songs);
    }
}