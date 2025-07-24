#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

void rip(char *str, char *arr, int pos, int i, int open, int left, int right) {
    if (str[i] == '\0') {
        if (open == 0 && left == 0 && right == 0) {
            arr[pos] = '\0';
            printf("%s\n", arr);
        }
        return;
    }

    char c = str[i];

    if (c == '(') {
        // Ignorar '(' se ainda houver left para remover
        if (left > 0)
            rip(str, arr, pos, i + 1, open, left - 1, right);

        // Manter '('
        arr[pos] = c;
        rip(str, arr, pos + 1, i + 1, open + 1, left, right);
    }
    else if (c == ')') {
        // Ignorar ')' se ainda houver right para remover
        if (right > 0)
            rip(str, arr, pos, i + 1, open, left, right - 1);

        // Manter ')' se houver parêntese aberto
        if (open > 0) {
            arr[pos] = c;
            rip(str, arr, pos + 1, i + 1, open - 1, left, right);
        }
    }
    else {
        // Caracteres normais são sempre mantidos
        arr[pos] = c;
        rip(str, arr, pos + 1, i + 1, open, left, right);
    }
}

void calcularRemocoes(char *str, int *left, int *right) {
    int l = 0, r = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(') {
            l++;
        } else if (str[i] == ')') {
            if (l > 0)
                l--;
            else
                r++;
        }
    }
    *left = l;
    *right = r;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s \"expressão\"\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int left = 0, right = 0;

    calcularRemocoes(input, &left, &right);

    char *buffer = malloc(strlen(input) + 1);
    if (!buffer) {
        perror("malloc");
        return 1;
    }

    printf("Parênteses a remover: ( = %d, ) = %d\n", left, right);
    rip(input, buffer, 0, 0, 0, left, right);

    free(buffer);
    return 0;
}
