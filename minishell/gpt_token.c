#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100

int main() {
    char input[1000];
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int token_count = 0;
    bool inside_quotes = false;
    char current_quote = '\0';

    printf("Enter text input: ");
    fgets(input, sizeof(input), stdin);

    char *p = strtok(input, " \n");

    while (p != NULL && token_count < MAX_TOKENS) {
        int len = strlen(p);
        if (len > 0) {
            if (!inside_quotes && (*p == '"' || *p == '\'')) {
                inside_quotes = true;
                current_quote = *p;
                strncpy(tokens[token_count], p, MAX_TOKEN_LENGTH);
                token_count++;
            } else if (inside_quotes && *p == current_quote) {
                inside_quotes = false;
                strncat(tokens[token_count - 1], " ", MAX_TOKEN_LENGTH);
                strncat(tokens[token_count - 1], p, MAX_TOKEN_LENGTH);
            } else if (inside_quotes) {
                strncat(tokens[token_count - 1], " ", MAX_TOKEN_LENGTH);
                strncat(tokens[token_count - 1], p, MAX_TOKEN_LENGTH);
            } else {
                strncpy(tokens[token_count], p, MAX_TOKEN_LENGTH);
                token_count++;
            }
        }
        p = strtok(NULL, " \n");
    }

    printf("Tokens: ");
    for (int i = 0; i < token_count; i++) {
        printf("%s$\n", tokens[i]);
    }
    printf("\n");

    return 0;
}
