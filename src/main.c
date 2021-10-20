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
    library_add(library, song_create("Rick Astly", "Never Gonna Give You Up"));
    library_add(library, song_create("Eminem", "Rap God"));

    library_print(library);
}