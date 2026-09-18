#include <unistd.h>
#include "lib/qodon.h"
#include "lib/shell.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: qdn [flag] <FASTA sequence>\n");
        return 1;
    }

    int opt;
    
    while ((opt = getopt(argc, argv, "c:l:t:u:r:g:i:")) != -1) {
        switch (opt) {
            case 'c': handle_complement(optarg, 0, 0); break;
            case 'l': get_base_length(optarg); break;
            case 't': handle_complement(optarg, 1, 0); break;
            case 'u': handle_complement(optarg, 0, 1); break;
            case 'r': reverse(optarg); break;
            case 'g': printf("%.2f%%\n", get_gc_content(optarg)); break;
            case 'i': launch_shell(optarg); break;
            default: fprintf(stderr, "Usage: %s -[c | l | t | u | r | g | i] [template]\n", argv[0]);
        }
    }

    return 0;
}