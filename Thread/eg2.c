#include <pthread.h>
#include <stdio.h>

/* Define a structure to pass parameters to char_print function. */
struct char_print_parms
{
    /* Define the character to print. */
    char character;
    /* Define the number of times to print the character. */
    int count;
};

/* A function that prints the specified character for a specified number of times. */
void* char_print(void* parameters)
{
    /* Cast the parameter to the correct structure type. */
    struct char_print_parms* p = (struct char_print_parms*)parameters;

    /* Print the character 'count' times. */
    for (int i = 0; i < p->count; ++i)
        fputc(p->character, stderr);

    return NULL;
}

/* Main program. */
int main()
{
    pthread_t thread1_id;
    pthread_t thread2_id;
    struct char_print_parms thread1_args;
    struct char_print_parms thread2_args;

    /* Create a new thread to print 30000 'x'. */
    thread1_args.character = 'x';
    thread1_args.count = 30000;
    pthread_create(&thread1_id, NULL, char_print, &thread1_args);

    /* Create a new thread to print 20000 'o'. */
    thread2_args.character = 'o';
    thread2_args.count = 20000;
    pthread_create(&thread2_id, NULL, char_print, &thread2_args);

    /* Ensure the first thread has finished. */
    pthread_join(thread1_id, NULL);

    /* Ensure the second thread has finished. */
    pthread_join(thread2_id, NULL);

    /* Now it's safe to return. */
    return 0;
}

