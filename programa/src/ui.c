#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ui.h"

#ifdef _WIN32
#include <windows.h>
#endif

// ASCII Banner
const char *BANNER = 
    C_BLUE
    "  ____   ___  ____    ______   ______  _______ _______ __  __ \n"
    " |  _ \\ / _ \\/ ___|  / ___\\ \\ / / ___||_   _| ____|  \\/  |\n"
    " | |_) | | | \\___ \\  \\___ \\\\ V /\\___ \\  | | |  _| | |\\/| |\n"
    " |  __/| |_| |___) |  ___) || |  ___) | | | | |___| |  | |\n"
    " |_|    \\___/|____/  |____/ |_| |____/  |_| |_____|_|  |_|\n"
    C_RESET;

void ui_init() {
    #ifdef _WIN32
    system("chcp 65001 > nul"); // UTF-8
    #endif
}

void ui_clear() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void ui_header(const char *title) {
    ui_clear();
    printf("%s\n", BANNER);
    printf(C_CYAN "  ========================================================\n" C_RESET);
    // Center title roughly
    int pad = (56 - strlen(title)) / 2;
    if (pad < 0) pad = 0;
    
    printf(C_CYAN "  ||" C_RESET);
    for(int i=0; i<pad; i++) printf(" ");
    printf(C_BOLD "%s" C_RESET, title);
    for(int i=0; i<pad; i++) printf(" ");
    if (strlen(title)%2 != 0) printf(" "); // Adjust for odd length
    printf(C_CYAN "||\n" C_RESET);
    
    printf(C_CYAN "  ========================================================\n" C_RESET);
    printf("\n");
}

void ui_print_success(const char *msg) {
    printf(C_GREEN "  [OK] %s" C_RESET "\n", msg);
}

void ui_print_error(const char *msg) {
    printf(C_RED "  [ERROR] %s" C_RESET "\n", msg);
}

void ui_pause() {
    printf(C_YELLOW "\n  Presione ENTER para continuar..." C_RESET);
    getchar(); getchar(); 
}

void ui_input_str(const char *prompt, char *buffer) {
    printf(C_MAGENTA "  > %s" C_RESET, prompt);
    scanf(" %[^\n]", buffer);
}

int ui_input_int(const char *prompt) {
    int v;
    printf(C_MAGENTA "  > %s" C_RESET, prompt);
    scanf("%d", &v);
    return v;
}

double ui_input_double(const char *prompt) {
    double v;
    printf(C_MAGENTA "  > %s" C_RESET, prompt);
    scanf("%lf", &v);
    return v;
}
