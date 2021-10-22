#include <stdio.h>

#include "my_library.h"

int main(void)
{
    struct my_library* library = library_create();

    library_add(library, song_create("Juice Wrld", "Lucid Dreams"));
    library_add(library, song_create("Juice Wrld", "Out Of My Way"));
    library_add(library, song_create("Juice Wrld", "Candles"));
    library_add(library, song_create("Juice Wrld", "Robbery"));
    library_add(library, song_create("Juice Wrld", "All Girls Are The Same"));
    library_add(library, song_create("Rick Ashley", "Never Gonna Give You Up"));
    library_add(library, song_create("Post Malone", "Candles"));
    library_add(library, song_create("Post Malone", "Rockstar"));

    library_print(library);
    library_remove(library, NULL, "Candles");
    library_print(library);
    library_remove(library, "Juice Wrld", NULL);
    library_print(library);

    library_free(library);
}