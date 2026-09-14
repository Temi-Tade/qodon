#include <stdio.h>
#include <unistd.h>
#include "qodon.h"

int main(int argc, char *argv[]) {
    int opt;
    
    while ((opt = getopt(argc, argv, "c:l:t:u:r:g:")) != -1) {
        switch (opt) {
            case 'c': handle_complement(optarg, 0, 0); break;
            case 'l': get_base_length(optarg); break;
            case 't': handle_complement(optarg, 1, 0); break;
            case 'u': handle_complement(optarg, 0, 1); break;
            case 'r': reverse(optarg); break;
            case 'g': get_gc_content(optarg); break;
            default: fprintf(stderr, "Usage: %s -[c | l | t | u] [template]\n", argv[0]);
        }
    }

    return 0;
}