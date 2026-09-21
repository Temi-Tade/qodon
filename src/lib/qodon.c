#include "qodon.h"

int validate(char template[], int is_transcribing, int is_rt) {
    size_t length = strlen(template);

    for (size_t i = 0; i < length; i++) {
        if (is_transcribing && template[i] == 'U') {
            fprintf(stderr, "Transctiption Error: Invalid base '%c' found at position '%zu'\n", template[i], i + 1);
            return 1;
        }

        if (is_rt && template[i] == 'T') {
            fprintf(stderr, "Reverse Transctiption Error: Invalid base '%c' found at position '%zu'\n", template[i], i + 1);
            return 1;
        }
    }

    return 0;
}

void get_complementary_sequence(char template[], char complement[], int is_transcribing, int is_rt) {
    // helper function to return a complement from a given template
    size_t length = strlen(template);

    for (size_t i = 0; i < length; i++) {
        switch (template[i]) {
            case 'A': complement[i] = is_transcribing ? (is_rt ? 'T': 'U') : 'T'; break; // A -> U (RT)
            case 'T': complement[i] = is_transcribing ? (is_rt ? 'T' : 'A') : 'A'; break;
            case 'G': complement[i] = 'C'; break;
            case 'C': complement[i] = 'G'; break;
            case 'U': complement[i] = 'A'; break;
            default: complement[i] = template[i];
        }
    }

    complement[length] = '\0';
}

void handle_complement(char input[], int is_transcribing, int is_rt) {
    if (validate(input, is_transcribing, is_rt) == 1) return;
    size_t length = strlen(input);

    printf("%s (Template strand)\n", input);
    char template[length];
    char complement[length];

    // use input to fill template sequence
    for (size_t i = 0; i < length; i++) {
        template[i] = input[i];
        printf("|");
    }

    template[length] = '\0';
    printf("\n");

    get_complementary_sequence(template, complement, is_transcribing, is_rt);
    printf("%s (Complementary strand)\n", complement);
}

void get_base_length(char template[]) {
    printf("%lubps\n", strlen(template));
}

void reverse(char forward[]) {
    size_t length = strlen(forward);
    char reverse[length];

    printf("%s (FWD)\n", forward);

    for (size_t i = 0; i < length; i++) {
        reverse[i] = forward[length - (i + 1)];
    }

    reverse[length] = '\0';
    printf("%s (REV)\n", reverse);
}

float get_gc_content(char sequence[]) {
    size_t length = strlen(sequence);
    float gc_count = 0;

    for (size_t i = 0; i < length; i++) {
        if (sequence[i] == 'G' || sequence[i] == 'C') {
            gc_count++;
        }
    }

    float gc_content = (gc_count / (float) length) * 100;

    return gc_content;
}

void get_aa(char dna[]) {
    FILE *fptr = fopen("codons.txt", "r");
    if (fptr == NULL) return;

    int ch = 0;
    int count = 0;
    int read = 0;
    size_t length = strlen(dna);

    char query_codon[4];
    char target_codon[4];
    char rna[length];
    char buffer[1436];

    get_complementary_sequence(dna, rna, 1, 0);

    while (read < length) {
        while ((ch = fgetc(fptr)) != EOF) {
            if (count == 3) {
                target_codon[count] = '\0'; // terminate codon sequence
                query_codon[count] = '\0'; // terminate codon sequence
                // if ()
                printf("%s %s\n", target_codon, query_codon);
                if (read >= length) break;
    
                while ((ch = fgetc(fptr)) != '\n' && ch != EOF) {
                    // Do nothing, ch++;
                    // Go to next line
                }
    
                count = 0; // reset codon count
                continue; // Go to the next iteration of the main loop
            }
            
            target_codon[count] = ch;
            query_codon[count] = rna[read];
            count++;
            // read++;
            // Process normal characters here
            
        }

        read++;
    }

    // buffer[read] = '\0';

    // printf("%s\n", buffer);

    fclose(fptr);
}