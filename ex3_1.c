#include <stdio.h>

int main(int argc, char **argv){

    if (argc != 3){
        // stderr dla standardowego wyjścia błędów
        fprintf(stderr, "usage: %s SRC DST\n", argv[0]);
        return 1;
    }

    // rb - odczyt plików w trybie binarnym
    // FILE *src: Deklaracja wskaźnika na FILE. Wskaźnik src będzie używany do odniesienia się do otwartego pliku i operowania na nim.
    FILE *src = fopen(argv[1], "rb");
    if (!src){
        fprintf(stderr, "%s: error: can't open '%s'\n", argv[0], argv[1]);
        return 1;
    }
    
    // wb - zapis plików w trybie binarnym
    FILE *dst = fopen(argv[2], "wb");
    if(!dst){
        fprintf(stderr, "%s: error: can't open '%s'\n", argv[0], argv[2]);
        fclose(src);
        return 1;
    }

    // Odczyt danych z pliku źródłowego (src)
    while (1){

        char buffer[128];

        size_t count = fread(buffer, 1, sizeof(buffer), src);
        if (count == 0){
            break;
        }

        fwrite(buffer, 1, count, dst);

    }

    fclose(dst);
    fclose(src);
    return 0;
}