/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-jeffrey.winkler
** File description:
** path
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "strace.h"

static char *make_binary_path(char *path, char *name)
{
    int path_len = strlen(path);
    int name_len = strlen(name);
    char *binary_path;

    if (!(binary_path = malloc(path_len + name_len
    + path[path_len - 1] != '/')))
        return NULL;
    strcpy(binary_path, path);
    if (path[path_len - 1] != '/')
        strcat(binary_path, "/");
    strcat(binary_path, name);
    return binary_path;
}

static char *search_binary_path(char *name, char **env)
{
    char *pathlist = get_env(env, "PATH");
    char *path;
    char *binary_path;
    char *ret = NULL;

    if (!pathlist)
        pathlist = strdup("/usr/sbin:/usr/bin:/sbin:/bin");
    else
        pathlist = strdup(pathlist);
    path = strtok(pathlist, ":");
    while (path) {
        if (!(binary_path = make_binary_path(path, name)))
            ret = NULL;
        else if (!access(binary_path, F_OK))
            ret = binary_path;
        else {
            free(binary_path);
            path = strtok(NULL, ":");
            continue;
        }
        break;
    }
    free(pathlist);
    return ret;
}

static char *get_frome_home(char *name, char **env)
{
    char *home = get_env(env, "HOME");
    int home_len;
    char *path;
    char last_c;

    if (!home)
        return NULL;
    home_len = strlen(home);
    if (!(path = malloc(home_len + strlen(name) - 1)))
        return NULL;
    last_c = home[home_len - 1];
    strcpy(path, home);
    strcat(path, name + 1 + (last_c == '/' ? 1 : 0));
    return path;
}

char *get_binary_path(char *name, char **env)
{
    if (!strncmp(name, "/", 1)
    || !strncmp(name, "./", 2) || !strncmp(name, "../", 3))
        return strdup(name);
    else if (!strncmp(name, "~/", 2))
        return get_frome_home(name, env);
    else
        return search_binary_path(name, env);
}