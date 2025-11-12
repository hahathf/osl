#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PIPE1 "/tmp/pipe1"
#define PIPE2 "/tmp/pipe2"

// Function to count words
int countWords(const char *str) {
    int count = 0, inWord = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
            inWord = 0;
        else if (inWord == 0) {
            inWord = 1;
            count++;
        }
    }
    return count;
}

// Function to count lines
int countLines(const char *str) {
    int count = 1; // start with 1 line by default
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n')
            count++;
    }
    return count;
}

int main() {
    int fd1, fd2;
    char input[1000], output[1000];
    int charCount, wordCount, lineCount;
    FILE *file;

    // Create named pipes if not already existing
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    // Open PIPE1 for reading
    fd1 = open(PIPE1, O_RDONLY);
    read(fd1, input, sizeof(input));
    close(fd1);

    // Count characters, words, and lines
    charCount = strlen(input);
    wordCount = countWords(input);
    lineCount = countLines(input);

    // Write results to a file
    file = fopen("output.txt", "w");
    fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n",
            charCount, wordCount, lineCount);
    fclose(file);

    // Read file content into output buffer
    file = fopen("output.txt", "r");
    fread(output, sizeof(char), sizeof(output), file);
    fclose(file);

    // Open PIPE2 for writing and send data
    fd2 = open(PIPE2, O_WRONLY);
    write(fd2, output, strlen(output) + 1);
    close(fd2);

    return 0;
}
