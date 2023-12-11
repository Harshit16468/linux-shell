#include "headers.h"
void decodeHtmlEntities(char *input, int l)
{
    char *search[] = {"&lt;", "&gt;", "&amp;", "&quot;", "&apos;"};
    char *replace[] = {"<", ">", "&", "\"", "'"};
    for (int i = 0; i < sizeof(search) / sizeof(search[0]); i++)
    {
        char *pos = input;
        while ((pos = strstr(pos, search[i])) != NULL)
        {
            memmove(pos + strlen(replace[i]), pos + strlen(search[i]), strlen(pos) - strlen(search[i]) + 1);
            memcpy(pos, replace[i], strlen(replace[i]));
            pos += strlen(replace[i]);
        }
    }
    char a = '\0';
    char t[l + 1];
    int y = 0;
    int flag = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '#')
        {
            flag = 1;
        }
        if (input[i] == '<')
        {

            if (flag == 1)
            {
                t[y++] = input[i];
                continue;
            }
            a = ' ';
        }
        else if (input[i] == '>')
        {
            if (flag == 1)
            {
                t[y++] = input[i];
            }
            flag = 0;
            a = '\0';
        }
        else if (a == ' ')
        {
        }
        else
        {
            t[y++] = input[i];
        }
    }
    t[y] = '\0';
    printf("%s\n", t);

    return;
}

void iman(char *input)
{

    struct addrinfo maninfo;
    struct addrinfo *a;
    struct addrinfo *b;

    char *token = strtok(input, " \n");
    token = strtok(NULL, " \n");

    char *weburl = (char *)malloc(4096);
    snprintf(weburl, 4096, "/?topic=%s&section=all", token);

    memset(&maninfo, 0, sizeof(struct addrinfo));
    maninfo.ai_family = AF_INET;
    maninfo.ai_socktype = SOCK_STREAM;

    if (getaddrinfo("man.he.net", "http", &maninfo, &a) != 0)
    {
        perror("Getaddrinfo failed");
    }

    int filedescripter = -1;
    b = a;
    while (b != NULL)
    {
        filedescripter = socket(b->ai_family, b->ai_socktype, b->ai_protocol);
        if (filedescripter == -1)
        {
            continue;
        }

        if (connect(filedescripter, b->ai_addr, b->ai_addrlen) != -1)
        {
            break;
        }

        close(filedescripter);
        b = b->ai_next;
    }

    if (b == NULL)
    {
        fprintf(stderr, "Failed to connect to the server\n");
        freeaddrinfo(a);
        return;
    }

    freeaddrinfo(a);
    char apicall[4096];
    snprintf(apicall, 4096, "GET %s HTTP/1.1\r\nHost: man.he.net\r\n\r\n", weburl);
    if (write(filedescripter, apicall, strlen(apicall)) < 0)
    {
        perror("Failed to send GET request");
        close(filedescripter);
        return;
    }

    char result[100000];
    result[0] = '\0';

    int first = 0;
    ssize_t n;
    while (n = recv(filedescripter, result, sizeof(result), 0) > 0)
    {
        char *noresponse = strstr(result, "No matches for");

        if (noresponse != NULL)
        {

            printf("Error: No such command\n");
            return;
        }
        char *start = strstr(result, "NAME\n");
        char *end = strstr(result, "</PRE>");
        if (start == NULL && end == NULL && first != 0)
        {

            decodeHtmlEntities(result, strlen(result));
        }
        else if (start == NULL && end != NULL && first != 0)
        {

            ssize_t l = (end - result);
            char *data = (char *)malloc(l + 1);

            if (data == NULL)
            {
                perror("Memory allocation failed");
                return;
            }
            strncpy(data, result, l);
            data[l] = '\0';
            decodeHtmlEntities(data, l);

            free(data);
            free(weburl);
            close(filedescripter);
            return;
        }
        else if (start != NULL && end == NULL)
        {

            first = 1;
            size_t l = (start - result);
            l = strlen(result) - l;

            char *data = (char *)malloc(l + 1);

            if (data == NULL)
            {
                perror("Memory allocation failed");
                return;
            }

            strncpy(data, start, l);
            data[l] = '\0';
            decodeHtmlEntities(data, l);

            free(data);
        }
        else if (start != NULL && end != NULL)
        {

            first = 1;
            size_t l = end - start;
            char *data = (char *)malloc(l + 1);

            if (data == NULL)
            {
                return;
            }
            strncpy(data, start, l);
            data[l] = '\0';
            decodeHtmlEntities(data, l);

            free(data);
            free(weburl);
            close(filedescripter);
            return;
        }
        else
        {
            free(weburl);
            close(filedescripter);
            return;
        }
    }

    free(weburl);
    close(filedescripter);
}
