#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#define MAX_KEY_LENGTH 16
#define MAX_LINE_LENGTH 1024

#define INPUT_BUFFER_LENGTH 255
#define CMD_BUFFER_LENGTH 50
#define PARAMS_MAX_COUNT 50
#define PARAMS_BUFFER_LENGTH 50

typedef struct Value Value;
typedef struct Entry Entry;
typedef struct Snapshot Snapshot;

struct Value {
	Value* prev;
	Value* next;
	int value;
};

struct Entry {
	Entry* prev;
	Entry* next;
	Value* values;
	char key[MAX_KEY_LENGTH];
};

struct Snapshot {
	Snapshot* prev;
	Snapshot* next;
	Entry* entries;
	int id;
};

Value* new_value(int value);
Entry* new_entry(char* key, int values[], int count);
Snapshot* new_snapshot(int id, Entry* entries);

void add_front_entry(Entry* newEntry);
void add_back_value(Value** head, Value* newValue);
void add_back_snapshot(Snapshot* newSnapshot);

Entry* get_entry(char* key);
Value* get_value(Entry* entry, int index);
Snapshot* get_snapshot(int id);
void set_values(Entry* entry, int values[], int count);
void push_values(char* key, int values[], int count);
void append_values(char* key, int values[], int count);
void insert_entry(Entry* newEntry, int index);
void delete_values(Value* values);
void delete_entry(Entry* entry);
void delete_entry_value(Entry *entry, int index);
void delete_all_entry(Entry* e);
void delete_snapshot(Snapshot* remove);
Entry *copy_entry(Entry *entry);
void int_swap(int *a, int *b);
void value_swap(Value **_prev, Value **_next);
int get_length_of_values(Entry* entry);
void revers_values(Entry* entry);
void sort_values(Entry* entry);
void print_keys();
void print_entries();
void print_snapshots();
int snapshot();
int drop_snapshot(int id);
int checkout_snapshot(int id);
int rollback_snapshot(int id);

int parseCmd(char* source, char* cmd, char(*params)[PARAMS_BUFFER_LENGTH]);
int runCmd(char* cmd, char params[][PARAMS_BUFFER_LENGTH], int params_count);

void command_get(char* key);
void command_del(char* key);
void command_purge(char* key);
void command_set(char params[][PARAMS_BUFFER_LENGTH], int params_count);
void command_push(char params[][PARAMS_BUFFER_LENGTH], int params_count);
void command_append(char params[][PARAMS_BUFFER_LENGTH], int params_count);
void command_pick(char* key, int index);
void command_pluck(char* key, int index);
void command_pop(char* key);
void command_drop(int id);
void command_rollback(int id);
void command_checkout(int id);
void command_snaps();
void command_min_value(char* key);
void command_max_value(char* key);
void command_sum_value(char* key);
void command_len(char* key);
void command_rev(char* key);
void command_uniq(char* key);
void command_sort(char* key);
void command_bye();

void command_inter(char params[][PARAMS_BUFFER_LENGTH],int params_count);
void command_diff(char params[][PARAMS_BUFFER_LENGTH],int params_count);
void command_union(char params[][PARAMS_BUFFER_LENGTH],int params_count);


#define HELP "BYE   clear database and exit\n"\
"HELP  display this help message\n\n"\
"LIST KEYS       displays all keys in current state\n"\
"LIST ENTRIES    displays all entries in current state\n"\
"LIST SNAPSHOTS  displays all snapshots in the database\n\n"\
"GET <key>    displays entry values\n"\
"DEL <key>    deletes entry from current state\n"\
"PURGE <key>  deletes entry from current state and snapshots\n\n"\
"SET <key> <value ...>     sets entry values\n"\
"PUSH <key> <value ...>    pushes values to the front\n"\
"APPEND <key> <value ...>  appends values to the back\n\n"\
"PICK <key> <index>   displays value at index\n"\
"PLUCK <key> <index>  displays and removes value at index\n"\
"POP <key>            displays and removes the front value\n\n"\
"DROP <id>      deletes snapshot\n"\
"ROLLBACK <id>  restores to snapshot and deletes newer snapshots\n"\
"CHECKOUT <id>  replaces current state with a copy of snapshot\n"\
"SNAPSHOT       saves the current state as a snapshot\n\n"\
"MIN <key>  displays minimum value\n"\
"MAX <key>  displays maximum value\n"\
"SUM <key>  displays sum of values\n"\
"LEN <key>  displays number of values\n\n"\
"REV <key>   reverses order of values\n"\
"UNIQ <key>  removes repeated adjacent values\n"\
"SORT <key>  sorts values in ascending order\n\n"\
"DIFF <key> <key ...>   displays set difference of values in keys\n"\
"INTER <key> <key ...>  displays set intersection of values in keys\n"\
"UNION <key> <key ...>  displays set union of values in keys\n"\

#endif
