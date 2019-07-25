typedef int (*child_func_pointer_t)();

// returns -1 on error, child pid otherwise
pid_t fork_child_in_function(child_func_pointer_t child_func, const char* child_name)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        printf("Hello! I'm child %s and I've just started with pid=%d (parent_pid=%d)\n", child_name, getpid(), getppid());
        exit(child_func());
    }
    if (child_pid < 0)
        printf("Error forking %s!\n", child_name);
    return child_pid;
}

void wait_child(pid_t child_pid, const char* child_name)
{
    int child_status;
    waitpid(child_pid, &child_status, 0);
    if (WIFEXITED(child_status))
        printf("%s has exited with exit code %d\n", child_name, WEXITSTATUS(child_status));
    else
        printf("%s has terminated abnormally\n", child_name);
}

void fork_and_wait_child(child_func_pointer_t child_func, const char* child_name)
{
    pid_t child_pid = fork_child_in_function(child_func, child_name);
    if (child_pid > 0)
        wait_child(child_pid, child_name);
}


int grandchild1_func()
{
    sleep(1);
    return 5;
}

int grandchild2_func()
{
    sleep(1);
    return 6;
}

int child_func()
{
    int grandchild1_pid, grandchild2_pid;
    grandchild1_pid = fork_child_in_function(grandchild1_func, "grandchild1");
    grandchild2_pid = fork_child_in_function(grandchild2_func, "grandchild2");
    if (grandchild1_pid > 0)
        wait_child(grandchild1_pid, "grandchild1");
    if (grandchild2_pid > 0)
        wait_child(grandchild2_pid, "grandchild2");
    return 0;
}

void variation2()
{
    fork_and_wait_child(child_func, "child");
}
