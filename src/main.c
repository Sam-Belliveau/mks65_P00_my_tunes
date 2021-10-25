#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_library.h"
#include "song_library.h"

#define print_section(section) do{printf("\n\n================ " section " ================\n");}while(0)

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
    
    print_section("Library");
    
    printf("Print Out Entire Library:\n");
    library_print(library);

    print_section("J Section Manipulation");

    printf("\nPrint Out J Category:\n");
    category_print(library_get_category(library, 'J'));

    printf("\n\nRemoving Songs With Artist \"Juice WRLD\"...\n");
    library_remove(library, "Juice WRLD", NULL);

    printf("\nPrint Out J Category:\n");
    category_print(library_get_category(library, 'J'));

    print_section("Kendrick Lamar");

    printf("\nPrinting Songs with Artist \"Kendrick Lamar\":\n");
    library_print_match(library, "Kendrick Lamar", NULL);

    printf("\nRemoving Songs With Title \"Alright\"...\n");
    library_remove(library, NULL, "Alright");
    printf("Removing Songs With Title \"DNA.\"...\n");
    library_remove(library, NULL, "DNA.");
    printf("Removing Songs With Title \"King Kunta\"...\n");
    library_remove(library, NULL, "King Kunta");

    printf("\nPrinting Songs with Artist \"Kendrick Lamar\":\n");
    library_print_match(library, "Kendrick Lamar", NULL);

    print_section("Random Songs");

    srand(time(0));
    printf("Printing 10 Random Songs:\n");
    for(i = 0; i < 10; ++i)
    {
        printf("\t%d) ", i);
        song_print(library_get_song_rand(library));
        printf("\n");
    }

    print_section("We are done here");

    printf("Clearing Library...\n\n");
    library_clear(library);

    printf("Print Out Entire Library:\n");
    library_print(library);

    printf("\nFreeing Library...\n");
    library_free(library);
}