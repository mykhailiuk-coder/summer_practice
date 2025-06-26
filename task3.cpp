#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 1024
#define HASH_SIZE 1024

void clean_word(char* word) {
    int i = 0, j = 0;
    while (word[i]) {
        if (isalnum(word[i])) {
            word[j++] = tolower(word[i]);
        }
        i++;
    }
    word[j] = '\0';
}

typedef struct WordNode {
    char word[MAX_WORD];
    struct WordNode* next;
} WordNode;

WordNode* hash_table[HASH_SIZE] = { NULL };

unsigned int hash(const char* word) {
    unsigned int hash_val = 0;
    while (*word) {
        hash_val = hash_val * 31 + *word++;
    }
    return hash_val % HASH_SIZE;
}

void add_to_set(const char* word) {
    unsigned int index = hash(word);
    WordNode* current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->word, word) == 0)
            return;
        current = current->next;
    }

    WordNode* new_node = (WordNode*)malloc(sizeof(WordNode));
    strcpy_s(new_node->word, MAX_WORD, word); 
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

int in_set(const char* word) {
    unsigned int index = hash(word);
    WordNode* current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->word, word) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

void free_set() {
    for (int i = 0; i < HASH_SIZE; ++i) {
        WordNode* node = hash_table[i];
        while (node != NULL) {
            WordNode* temp = node;
            node = node->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}

int main() {
    FILE* file1, * file2, * outfile;
    char word[MAX_WORD];
    char input_path1[] = "D:\\cpp_labs\\summer_practice\\c_tasks\\task3\\text1.txt";
    char input_path2[] = "D:\\cpp_labs\\summer_practice\\c_tasks\\task3\\text2.txt";

    char** unique_words = NULL;
    int unique_count = 0;

    if (fopen_s(&file1, input_path1, "r") != 0) {
        printf("Failed to open file: %s\n", input_path1);
        return 1;
    }

    if (fopen_s(&file2, input_path2, "r") != 0) {
        printf("Failed to open file: %s\n", input_path2);
        fclose(file1);
        return 1;
    }

    while (fscanf_s(file1, "%s", word, (unsigned)_countof(word)) != EOF) {
        clean_word(word);
        if (strlen(word) > 0)
            add_to_set(word);
    }

    while (fscanf_s(file2, "%s", word, (unsigned)_countof(word)) != EOF) {
        clean_word(word);
        if (strlen(word) > 0 && !in_set(word)) {
            unique_words = (char**)realloc(unique_words, (unique_count + 1) * sizeof(char*));
            unique_words[unique_count] = _strdup(word);  
            unique_count++;
        }
    }

    fclose(file1);
    fclose(file2);  

    if (fopen_s(&outfile, input_path2, "w") != 0) {
        printf("Failed to open file for writing: %s\n", input_path2);
        for (int i = 0; i < unique_count; ++i)
            free(unique_words[i]);
        free(unique_words);
        free_set();
        return 1;
    }

    for (int i = 0; i < unique_count; ++i) {
        fprintf(outfile, "%s ", unique_words[i]);
        free(unique_words[i]);
    }

    free(unique_words);
    free_set();

    fclose(outfile);

    printf("Processing completed. Result saved to file:\n%s\n", input_path2);
    return 0;
}