#include <stdio.h>

#include "my_library.h"
#include "song_library.h"

int main(void)
{
    struct my_library* library = library_create();
    int i;

    for(i = 0; i < MUSIC_LIBRARY_SIZE; ++i)
    {
        const char* artist = MUSIC_LIBRARY[i].artist;
        const char* title = MUSIC_LIBRARY[i].title;

        library_add(library, song_create(artist, title));
    }

    library_print(library);

    library_free(library);
}