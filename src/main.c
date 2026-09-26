
#include <unistd.h>
#include "lib/qodon.h"
#include "lib/shell.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        if (argc == 2 && argv[1] == "-h") {
            print_cli_help();
            return 0;
        }

        print_cli_help();
        return 1;
    }

    int opt;
    
    while ((opt = getopt(argc, argv, "c:l:t:u:r:g:i:a:s:")) != -1) {
        switch (opt) {
            case 'c': handle_complement(optarg, 0, 0); break;
            case 'l': get_base_length(optarg); break;
            case 't': handle_complement(optarg, 1, 0); break;
            case 'u': handle_complement(optarg, 0, 1); break;
            case 'r': reverse(optarg); break;
            case 'g': printf("%.2f%%\n", get_gc_content(optarg)); break;
            case 'i': launch_shell(optarg); break;
            case 'a': get_aa(optarg); break;
            case 's': run_dogma(optarg); break;
            default: print_cli_help();
        }
    }

    return 0;
}