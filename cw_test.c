int calculate_digit_sum(const char *word){
    int sum = 0;
    for (int i = 0; i < strlen(word); i++){
        if (isdigit(word[i])){
            sum ++;
        }
    }
    return sum;
}
int cmp1 (const void *a, const void *b){
    const char *word1 = *(const char **)a;
    const char *word2 = *(const char **)b;
    int sum1 = calculate_digit_sum(word1);
    int sum2 = calculate_digit_sum(word2);
    return sum1 - sum2;
}

void def9(char **text, size_t len_text) {
    for (size_t i = 0; i < len_text; i++) {
        char *copy = my_strdup(text[i]);
        if (copy[strlen(copy) - 1] == '.') {
            copy[strlen(copy) - 1] = '\0';
        }
        char *token = strtok(copy, " ");
        char *words[100];
        size_t word_count = 0;
        while (token != NULL) {
            words[word_count++] = token;
            token = strtok(NULL, " ");
        }
        qsort(words, word_count, sizeof(char *), cmp1);
        text[i][0] = '\0';
        for (size_t j = 0; j < word_count; j++){
            text[i] = strcat(text[i], words[j]);
            if (j < (word_count-1)){
                text[i] = strcat(text[i], " ");
            }
        }
        text[i] = strcat(text[i], ".");
        free(copy);
    }
}
