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
    if (fptr == NULL) {
        printf("Error opening codons.txt\n");
        return;
    }

    size_t length = strlen(dna);
    char rna[length];
    char aa[(int) ((length / 3) + 1)];
    get_complementary_sequence(dna, rna, 1, 0);

    // Process RNA in chunks of 3 (codons)
    for (size_t i = 0; i + 2 < length; i += 3) {
        char query_codon[4];
        query_codon[0] = rna[i];
        query_codon[1] = rna[i + 1];
        query_codon[2] = rna[i + 2];
        query_codon[3] = '\0';

        if (strcmp(query_codon, "UGA") == 0 || strcmp(query_codon, "UAA") == 0 || strcmp(query_codon, "UAG") == 0) {
            break; // stop codon detected
        }

        // Rewind file pointer to the beginning for each codon search
        rewind(fptr);

        char line[100];
        int found = 0;

        // Read the file line by line
        while (fgets(line, sizeof(line), fptr) != NULL) {
            char target_codon[4];
            // Assuming the line starts with the codon (e.g., "UUU:Phenylalanine:Phe:F")
            sscanf(line, "%3s", target_codon);

            if (strcmp(query_codon, target_codon) == 0) {
                // printf("Match found! Query: %s -> Line: %s", query_codon, line);
                line[strcspn(line, "\n")] = 0; // remove \n, \n is the last char of the line
                aa[(int) i/3] = line[strlen(line) - 1]; // move one back to get last char, which is the symbol
                found = 1;
                break;
            }
        }
       
        if (!found) {
            printf("Codon %s not found in file.\n", query_codon);
        }
    }
    
    aa[(int) ((length / 3) + 1)] = '\0'; // terminate amino acid buffer
    printf("%s\n", aa);

    fclose(fptr);
}

void print_codon_list() {
    FILE *fptr;

    fptr = fopen("codons.txt", "r");

    if (fptr == NULL) {
        printf("An error occured. Could not open codons.txt.");
        return;
    }

    int c;
    char buffer[1250];
    buffer[1245] = '\0';

    while((c = fgetc(fptr)) != EOF) {
        printf("%c", c);
    }

    fclose(fptr);
    // printf("\n %ld %ld", strlen(buffer), sizeof(buffer));
}