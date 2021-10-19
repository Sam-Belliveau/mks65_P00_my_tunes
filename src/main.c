#include <stdio.h>

#include "my_song.h"

int main(void)
{
    struct song_node* songs = song_create("Juice Wrld", "All Girls Are The Same");

    songs = song_insert_sorted(songs, song_create("Juice Wrld", "Lucid Dreams"));
    songs = song_insert_sorted(songs, song_create("Juice Wrld", "Out Of My Way"));
    songs = song_insert_sorted(songs, song_create("Juice Wrld", "Candles"));
    songs = song_insert_sorted(songs, song_create("Juice Wrld", "Robbery"));

    song_print_list(songs);
}