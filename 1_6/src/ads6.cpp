#include <stdio.h>
#include <string.h>

bool GenerateChild(char *source_alphabet, size_t alphabet_size, char *source_stack, char *source_result, bool to_stack, char *target) {
    char *alphabet = new char[alphabet_size];
    char *stack = new char[alphabet_size];
    char *result = new char[alphabet_size];

    memcpy(alphabet, source_alphabet, alphabet_size *  sizeof(char));
    memcpy(stack, source_stack, alphabet_size *  sizeof(char));
    memcpy(result, source_result, alphabet_size *  sizeof(char));

    size_t alphabet_front_index = 0;
    while (!alphabet[alphabet_front_index] && alphabet_front_index < alphabet_size) alphabet_front_index++;

    size_t stack_top_index = 0;
    while (stack[stack_top_index]) stack_top_index++;

    size_t result_back_index = 0;
    while (result[result_back_index]) result_back_index++;

    if (to_stack) {
        stack[stack_top_index] = alphabet[alphabet_front_index];
        alphabet[alphabet_front_index] = 0;
    } else {
        result[result_back_index] = stack[--stack_top_index];
        stack[stack_top_index--] = 0;
    }

    if (alphabet_front_index < alphabet_size && GenerateChild(alphabet, alphabet_size, stack, result, true, target)) {
        return true;
    } else if (stack[stack_top_index] && GenerateChild(alphabet, alphabet_size, stack, result, false, target)) {
        return true;
    }

    bool correct = true;

    for (size_t i = 0; i < alphabet_size; i++) {
        if (result[i] != target[i]) {
            correct = false;
            break;
        }
    }

    return correct;
}

int main() {
    char *source = new char[64];
    char *target = new char[64];

    scanf("%s %s", source, target);

    size_t length = strlen(source);

    char *stack = new char[length];
    char *result = new char[length];

    stack[0] = 0;

    if (GenerateChild(source, length, stack, result, true, target)) {
        puts("YES");
    } else {
        puts("NO");
    }

	return 0;
}
