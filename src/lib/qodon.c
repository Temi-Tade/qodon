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

    // printf("%.2f%%\n", gc_content);
    return gc_content;
}