#include <stdio.h>

#include "my_library.h"
#include "song_library.h"

#define print_section(section) do{printf("\n\n\t==== " section " ====\n");}while(0)

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

    print_section("Kendrick Lamar is kinda cool...");

    printf("\nPrinting Kendrick Lamar:\n");
    library_print_match(library, "Kendrick Lamar", NULL);

    printf("\nRemoving Songs With Title \"Alright\"...\n");
    library_remove(library, NULL, "Alright");

    printf("\nPrinting Kendrick Lamar:\n");
    library_print_match(library, "Kendrick Lamar", NULL);

    print_section("We are done here");

    printf("Clearing Library...\n\n");
    library_clear(library);

    printf("Print Out Entire Library:\n");
    library_print(library);

    printf("\nFreeing Library...\n");
    library_free(library);
}