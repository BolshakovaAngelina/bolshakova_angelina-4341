#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count_vowels(const char *word);
char* my_strdup(const char* str);
int calculate_vowel_sum(const char *sentence);
int is_uppercase_word(const char *word);
int cmp(const void *a, const void *b);
void def1(char **text, size_t *len_text);
void def2(char **text, size_t *len_text);
void def3(char **text, size_t *len_text);
void def4(char **sentences, size_t len_text);
void def5();
void read_sentences(char ***text, size_t *len_text, int *a);
int my_strcasecmp(const char *s1, const char *s2);
void remove_text(char **text, size_t *len_text);

int main() {
    printf("Course work for option 4.1, created by Bolshakova Angelina.\n");
    char **text = NULL;
    size_t len_text = 0;
    int a;
    read_sentences(&text, &len_text, &a);
    remove_text(text, &len_text);
    switch(a){
        case 0:
            break;
        case 1:
            def1(text, &len_text);
            break;
        case 2:
            def2(text, &len_text);
            break;
        case 3:
            def3(text, &len_text);
            break;
        case 4:
            def4(text, len_text);
            break;
        case 5:
            def5();
            break;
        default:
            printf("Error: Некорректный номер функции\n");
    }
    for (size_t i = 0; i < len_text; i++) {
        printf("%s\n", text[i]);
        free(text[i]);
    }
    free(text);
    return 0;
}

int count_vowels(const char *word) {
    int count = 0;
    while (*word) {
        char s = tolower(*word);
        if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u' || s == 'y') {
            count++;
        }
        word++;
    }
    return count;
}
char* my_strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    strcpy(copy, str);
    return copy;
}

int calculate_vowel_sum(const char *sentence) {
    int sum = 0;
    char *copy_sentence = my_strdup(sentence);
    if (copy_sentence == NULL) {
        return -1;
    }

    char *token = strtok(copy_sentence, " ");
    int index = 0;
    while (token != NULL) {
        if (index % 2 == 0) {
            sum += count_vowels(token);
        }
        token = strtok(NULL, " ");
        index++;
    }
    free(copy_sentence);
    return sum;
}

int is_uppercase_word(const char *word) {
    if (word[0] == '\0') return 0;
    while (*word) {
        if (!isupper((unsigned char)*word)) {
            return 0;
        }
        word++;
    }
    return 1;
}

int cmp(const void *a, const void *b) {
    const char *sentence_a = *(const char **)a;
    const char *sentence_b = *(const char **)b;
    int sum_a = calculate_vowel_sum(sentence_a);
    int sum_b = calculate_vowel_sum(sentence_b);
    return sum_b - sum_a;
}

void def1(char **text, size_t *len_text){
    for (int x = 0; x < *len_text; x++){
        for (int y = 0; text[x][y] != '\0'; y++){
            text[x][y] = tolower((unsigned char)text[x][y]);
        }
        text[x][0] = toupper((unsigned char)text[x][0]);
    }
}

void def2(char **text, size_t *len_text) {
    for (size_t x = 0; x < *len_text; x++) {
        int word_count = 0;
        for (int y = 0; text[x][y] != '\0'; y++) {
            if (y == 0 || (isspace(text[x][y - 1]) && !isspace(text[x][y]))) {
                word_count++;
            }
        }
        if (word_count % 2 == 0) {
            free(text[x]);
            for (size_t k = x; k < *len_text - 1; k++) {
                text[k] = text[k + 1];
            }
            (*len_text)--;
            x--;
        }
    }
}

void def3(char **text, size_t *len_text) {
    qsort(text, *len_text, sizeof(char *), cmp);
}

void def4(char **sentences, size_t len_text) {
    for (size_t i = 0; i < len_text; i++) {
        char *sentence = sentences[i];
        char *copy_sentence = my_strdup(sentence);
        char *token = strtok(copy_sentence, " ");
        int word_count = 0;
        char *words[100];

        while (token != NULL && word_count < 100) {
            words[word_count++] = token;
            token = strtok(NULL, " ");
        }

        if (word_count > 2) {
            char *formatted_words[100];

            for (int j = 0; j < word_count; j++) {
                if (j > 0 && j < word_count - 1 && is_uppercase_word(words[j])) {
                    formatted_words[j] = (char *)malloc(100 * sizeof(char));
                    snprintf(formatted_words[j], 100, "\033[34m%s\033[0m", words[j]);
                } else {
                    formatted_words[j] = my_strdup(words[j]);
                }
            }

            char modified_sentence[1000] = "";
            for (int j = 0; j < word_count; j++) {
                strcat(modified_sentence, formatted_words[j]);
                if (j < word_count - 1) {
                    strcat(modified_sentence, " ");
                }
                free(formatted_words[j]);
            }

            free(sentences[i]);
            sentences[i] = my_strdup(modified_sentence);
        }

        free(copy_sentence);
    }
}

void def5(){
    printf("Справка о функциях:\nФункция 1: Преобразовать предложения так, чтобы каждое первое слово в нем начиналось с заглавной буквы, а остальные символы были прописными.\nФункция 2: Удалить все предложения, состоящие из четного количества слов.\nФункция 3: Отсортировать предложения по сумме количеств гласных букв в каждом втором слове.\nФункция 4: Вывести на экран все предложения, в которых в середине предложения встречаются слова, состоящие из прописных букв. Данные слова нужно выделить синим цветом.\nФункция 5: Вывод справки о функциях, которые реализует программа.");
}

void read_sentences(char ***text, size_t *len_text, int *a) {
    char *sentence = NULL;
    size_t len_sentence = 0;
    int delim = 0;

    scanf("%d", a);
    if (*a != 5) {
        while (1) {
            int s = getchar();
            if (s == EOF) break;
            if (s == '\n') {
                delim++;
                if (delim == 2) {
                    break;
                }
                continue;
            } else {
                delim = 0;
            }
            char *new_sentence = realloc(sentence, (len_sentence + 1) * sizeof(char));
            if (new_sentence == NULL) {
                free(sentence); 
                perror("Error: Ошибка выделения памяти");
                exit(EXIT_FAILURE);
            }
            sentence = new_sentence;
            sentence[len_sentence++] = (char)s;
            if (s == '.') {
                sentence = realloc(sentence, (len_sentence + 1) * sizeof(char));
                if (sentence == NULL) {
                    perror("Error: Ошибка выделения памяти");
                    exit(EXIT_FAILURE);
                }
                sentence[len_sentence] = '\0';
                size_t start = 0;
                while (isspace((unsigned char)sentence[start])) {
                    start++;
                }
                if (start > 0) {
                    memmove(sentence, sentence + start, len_sentence - start + 1);
                    len_sentence -= start;
                }
                *text = realloc(*text, (*len_text + 1) * sizeof(char *));
                if (*text == NULL) {
                    perror("Error: Ошибка выделения памяти");
                    exit(EXIT_FAILURE);
                }
                (*text)[*len_text] = my_strdup(sentence);
                (*len_text)++;
                len_sentence = 0;
                free(sentence);
                sentence = NULL; 
            }
        }
    }

    free(sentence);
    if (*len_text == 0) {
        printf("Error: Введен пустой текст\n");
    }
}

int my_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower(*s1) != tolower(*s2)) {
            return 1;
        }
        s1++;
        s2++;
    }
    return (*s1 == *s2) ? 0 : 1;
}

void remove_text(char **text, size_t *len_text) {
    for (size_t i = 0; i < *len_text; i++) {
        for (size_t j = i + 1; j < *len_text; j++) {
            if (my_strcasecmp(text[i], text[j]) == 0) {
                free(text[j]);
                for (size_t k = j; k < *len_text - 1; k++) {
                    text[k] = text[k + 1];
                }
                (*len_text)--; 
                j--; 
            }
        }
    }
}
