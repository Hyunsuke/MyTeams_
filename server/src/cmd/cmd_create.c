/*
** EPITECH PROJECT, 2024
** cmd_create.c
** File description:
** commande /create
*/

#include "server.h"

char **define_context(server_t *s, int client_fd)
{
    client_t **client_head = &s->clients;
    user_t **user_head = &s->users;
    client_t *current_client = *client_head;
    user_t *current_user = *user_head;
    char **context_tab;
    char *save_name;
    char uuid[37];

    while (current_client != NULL) {
        if (current_client->fd == client_fd) {
            save_name = current_client->name;
            break;
        }
        current_client = current_client->next;
    }
    while (current_user != NULL) {
        if (strcmp(current_user->name, save_name) == 0) {
            uuid_unparse(current_user->uuid, uuid);
            context_tab = my_str_to_word_array(current_user->context, '/');
            return context_tab;
        }
        current_user = current_user->next;
    }
    return NULL;
}

////////////////////GESTION ERREUR////////////////////////////

char *get_type_of_create(server_t *s, int client_fd)
{
    int pos = 0;
    char *type_create;
    char **context_parse = define_context(s, client_fd);

    for (; context_parse[pos] != NULL; pos++);
    if (pos == 1) {
        type_create = "team";
    }
    if (pos == 2) {
        type_create = "channel";
    }
    if (pos == 3) {
        type_create = "thread";
    }
    if (pos == 4) {
        type_create = "reply";
    }
    return type_create;
}

int error_create(server_t *s, char *type, int client_fd)
{
    int nb_args = 0;

    for (; s->input_tab[nb_args] != NULL; nb_args++);
    if (strcmp(type, "team") == 0 || strcmp(type, "channel") == 0 || strcmp(type, "thread") == 0) {
        if (nb_args != 3) {
            write(client_fd, "Invalid number of args.\n", 24);
            return 84;
        }
        if (check_quotes(s->input_tab[1]) == false || check_quotes(s->input_tab[2]) == false) {
            write(client_fd, "Bad Synthax of arguments.\n", 27);
            return 84;
        }
    } else if (strcmp(type, "reply") == 0) {
        if (nb_args != 2) {
            write(client_fd, "Invalid number of args.\n", 24);
            return 84;
        }
        if (check_quotes(s->input_tab[1]) == false) {
            write(client_fd, "Bad Synthax of arguments.\n", 27);
            return 84;
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////

///////////////////////////GESTION TEAM//////////////////////////////////

team_t *create_team(server_t *s, int client_fd, char *name, char *description)
{
    (void)client_fd;
    team_t *new_team = malloc(sizeof(team_t));

    if (new_team != NULL) {
        uuid_generate(new_team->uuid);
        uuid_unparse(new_team->uuid, s->uuid_elem);
        //send team uuid ici à tout les clients 
        new_team->name = name;
        //send name ici à tout les clients
        new_team->description = description;
        //send description ici à tout les clients
        new_team->channel = NULL;
        new_team->next = NULL;
    }
    return new_team;
}

int check_team(server_t *s, char *name)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;

    while (current_team != NULL) {
        if (strcmp(current_team->name, name) == 0) {
            return 84;
        }
        current_team = current_team->next;
    }
    return 0;
}

void add_team(server_t *s, int client_fd)
{
    char *name = remove_quotes(s->input_tab[1]);
    char *description = remove_quotes(s->input_tab[2]);
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;
    user_t **user_head = &s->users;
    user_t *current_user = *user_head;
    team_t **team_head = &s->team;
    team_t *new_team = create_team(s, client_fd, name, description);
    team_t *current_team = *team_head;
    char *name_user;
    char uuid_str[37];

    if (check_team(s, name) == 84) {
        write(client_fd, "Team already exist\n", 20);
        //  send au client 
        //  int client_error_already_exist(void);
        return;
    }
    if (new_team == NULL) {
        printf("Error in team creation\n");
        return;
    }
    if (current_team == NULL) {
        *team_head = new_team;
    } else {
        while (current_team->next != NULL) {
            current_team = current_team->next;
        }
        current_team->next = new_team;
    }

    while (current_client != NULL) {
        if (current_client->fd == client_fd) {
            name_user = current_client->name;
            break;
        }
        current_client = current_client->next;
    }
    while (current_user != NULL) {
        if (strcmp(current_user->name, name_user) == 0) {
            //send user uuid ici à tout les clients
            uuid_unparse(current_user->uuid, uuid_str);
        }
        current_user = current_user->next;
    }
    //print pour server
    server_event_team_created(s->uuid_elem, name, uuid_str);
    //send cmd create à tous les clients
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////GESTION CHANNEL/////////////////////////////////

channel_t *create_channel(server_t *s, int client_fd, char *name, char *description)
{
    (void)client_fd;
    channel_t *new_channel = malloc(sizeof(channel_t));

    if (new_channel != NULL) {
        uuid_generate(new_channel->uuid);
        uuid_unparse(new_channel->uuid, s->uuid_elem);
        //send channel uuid ici à tous les clients subscribed
        new_channel->name = name;
        //send name ici à tous les clients subscribed
        new_channel->description = description;
        //send description ici à tous les clients subscribed
        new_channel->thread = NULL;
        new_channel->next = NULL;
    }
    return new_channel;
}

int check_channel(server_t *s, char *name, char **parse_context)
{
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    channel_t **channel_head;
    channel_t *current_channel;
    char uuid[37];

    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, uuid);
        if (strcmp(uuid, parse_context[1]) == 0) {
            channel_head = &current_team->channel;
            current_channel = *channel_head;
            while (current_channel != NULL) {
                if (strcmp(current_channel->name, name) == 0) {
                    return 84;
                }
            }
        }
    }
    return 0;
}

void add_channel(server_t *s, int client_fd)
{
    char *name = remove_quotes(s->input_tab[1]);
    char *description = remove_quotes(s->input_tab[2]);
    team_t **team_head = &s->team;
    team_t *current_team = *team_head;
    channel_t **channel_head;
    channel_t *current_channel;
    channel_t *new_channel = create_channel(s, client_fd, name, description);
    char **parse_context = define_context(s, client_fd);
    char uuid[37];

    if (check_channel(s, name, parse_context) == 84) {
        write(client_fd, "Channel already exist\n", 23);
        //  send au client 
        //  int client_error_already_exist(void);
        return;
    }

    //NE PAS OUBLIER DE CHECK SI LE USER EST SUBSCRIBE A LA TEAM

    if (new_channel == NULL) {
        printf("Error in channel creation\n");
        return;
    }
    while (current_team != NULL) {
        uuid_unparse(current_team->uuid, uuid);
        if (strcmp(uuid, parse_context[1]) == 0) {
            channel_head = &current_team->channel;
            current_channel = *channel_head;
            if (current_channel == NULL) {
                *channel_head = new_channel;
            } else {
                while (current_channel->next != NULL) {
                    current_channel = current_channel->next;
                }
                current_channel->next = new_channel;
            }
            //print server
            server_event_channel_created(uuid, s->uuid_elem, name);
            //send infos client à tous les clients subscribed
            return;
        }
    }
    //send erreur client//
    // client_error_unknown_team(parse_context[1]);
    /////////////////:////
}

/////////////////////////////////////////////////////////////////////////

//////////////////////////GESTION THREAD/////////////////////////////////

// void add_thread(server_t *s, )

/////////////////////////////////////////////////////////////////////////

void create_element(server_t *s, int client_fd, char *type)
{
    if (strcmp("team", type) == 0) {
        add_team(s, client_fd);
    }
    if (strcmp("channel", type) == 0) {
        add_channel(s, client_fd);
    }
    // if (strcmp("thread", type) == 0) {
    //     add_thread(s, client_fd);
    // }
    // if (strcmp("reply", type) == 0) {
    //     add_reply(s, client_fd);
    // }
}

void create_cmd(server_t *s, int client_fd)
{
    char *type;
    client_t **client_head = &s->clients;
    client_t *current_client = *client_head;

    if (check_connection_client(current_client, client_fd) == 84) {
        send_unauthorized_to_client(client_fd);
        usleep(1000);
        return;
    }
    type = get_type_of_create(s, client_fd);
    if (error_create(s, type, client_fd) == 84) {
        return;
    }
    create_element(s, client_fd, type);
}
