#ifndef UI_H
#define UI_H

// Colors
#define C_RESET  "\033[0m"
#define C_CYAN   "\033[36m"
#define C_GREEN  "\033[32m"
#define C_YELLOW "\033[33m"
#define C_RED    "\033[31m"
#define C_MAGENTA "\033[35m"
#define C_BLUE   "\033[34m"
#define C_BOLD   "\033[1m"

// Helpers
extern const char *BANNER;
void ui_init(); // Sets codepage
void ui_clear();
void ui_header(const char *title);
void ui_print_success(const char *msg);
void ui_print_error(const char *msg);
void ui_pause();

// Input
void ui_input_str(const char *prompt, char *buffer);
int ui_input_int(const char *prompt);
double ui_input_double(const char *prompt);

#endif
