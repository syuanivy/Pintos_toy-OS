/*
 * shell.c
 *
 *  Created on: May 10, 2015
 *      Author: rreeves
 */
 
 #include <stdio.h>
 #include <string.h>
 #include "thread.h"
 #include "interrupt.h"
 
 static char* get_thread_status(enum thread_status status) {
     
    switch (status) {
        case THREAD_RUNNING:
            return "Running";
        case THREAD_READY:
            return "Ready";
        case THREAD_BLOCKED:
            return "Blocked";
        case THREAD_DYING:
            return "Dying";
    }
 }
 
 static uint32_t get_total_runtime(struct thread *t) {
     if (t->status == THREAD_RUNNING) {
         return t->total_runtime + (timer_get_timestamp() - t->time_at_status);
     }
     else {
         return t->total_runtime;
     }
 }
 
 static uint32_t get_percent_runtime(struct thread *t) {
     //return t->start_time;
//     return get_total_runtime(t) / (timer_get_timestamp() - t->start_time) * 100;
        return 0;
 }
 
 static void print_thread_status(struct thread *t, void *param UNUSED) {
   
    printf("\n%d, %s, %s, %u, %u", 
        t->tid, 
        strlen(t->name) > 0 ? t->name : "[No Name]",
        get_thread_status(t->status),
        get_total_runtime(t),
        get_percent_runtime(t)
    );
}

static void print_threads_status() {
    interrupts_disable();

    printf("\nThread ID, Name, Status, Total run time, % total run time since thread start");
    thread_foreach(&print_thread_status, NULL);

    interrupts_enable();
}

void run_shell() {
    printf("\nStarting the osOS shell...\n");

    char input[100];
    while (true) {

        memset(input, 0, 100);
        int index = 0;

        uart_puts("\nosO$ "); 
        char inputc = uart_getc();

        while (inputc != 13) {
            uart_putc(inputc);
            input[index++] = inputc;

            inputc = uart_getc();
        }

        input[index] = '\0';

    if (!strcmp(input, "help")) {
        printf("\nts - thread status - show running threads and their run times");
        printf("\nrun <func> - launch a thread function and wait for its completion");
        printf("\nbg <func> - launch a command in the background");
        printf("\nshutdown - shutdown the operating system");
    }
    else if (!strcmp(input, "ts")) {
        print_threads_status();
    }
    else if (
        input[0] == 'r'
        && input[1] == 'u'
        && input[2] == 'n'
        && input[3] == ' '
    ) {
        printf("\nTODO - run command");
    }
    else if (
        input[0] == 'b'
        && input[1] == 'g'
        && input[2] == ' '
    ) {
        printf("\nTODO - bg command");
    }
    else if (strcmp(input, "shutdown") == 0) {
        break;
    }
    else {
        printf("\nUnknown command. Enter 'help' for list of commands.");
    }
}

    printf("\nGoodbye from the osOS shell");
}