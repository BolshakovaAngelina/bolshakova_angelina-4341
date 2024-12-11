int word_counter(const char *sentence){
    int word_count = 0;
    for (int j = 0; sentence[j] != '\0'; j++){
        if (j == 0 || ((isspace(sentence[j-1])) && (!isspace(sentence[j])))){
            word_count++;
        }
    }
    return word_count;
}
int simbol_counter(const char *sentence){
    int simbol_count = strlen(sentence);
    return simbol_count;
}

int cmp2(const void *a, const void *b) {
    const char *first = *(const char **)a;
    const char *second = *(const char **)b;
    int word_diff = word_counter(first) - word_counter(second);
    if (word_diff != 0) {
        return word_diff;
    }
    return simbol_counter(first) - simbol_counter(second);
}
void def7(char **text, size_t *len_text){
    qsort(text, *len_text, sizeof(char *), cmp2);
}

void def8(char ***text, size_t *len_text, int *num) {
    for (int i = 0; i < *len_text; i++) {
        size_t original_length = strlen((*text)[i]);
        size_t new_length = original_length * (*num) + 1; 
        char *new_sentence = (char *)malloc(new_length * sizeof(char));
        strcpy(new_sentence, (*text)[i]);
        for (int count = 1; count < *num; count++) {
            strcat(new_sentence, (*text)[i]);
        }
        free((*text)[i]);
        (*text)[i] = new_sentence;
        for (int j = 0; j < (new_length-2); j++){
            if ((*text)[i][j] == '.'){
                (*text)[i][j] = ' ';
            }
        }
    }
}


int count_upper(char* text){
    int count = 0;
    for (int i = 0; i < strlen(text); i++){
        if (isupper(text[i])){
            count++;
        }
    }
    return count;
}
void def8(char ***text, size_t *len_text){
    int max_count = count_upper(*(text)[0]);
    for (size_t i = 1; i < *len_text; i++){
        int this_count = count_upper((*text)[i]);
        if (this_count > max_count){
            free((*text)[i]);
            for (size_t k = i; k < ((*len_text)-1); k++){
                (*text)[k] = (*text)[k+1];
            }
            (*len_text)--;
            i--;
        }
    }
}


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
