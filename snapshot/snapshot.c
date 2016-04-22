#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "snapshot.h"

Entry* entry_head = NULL;
Entry* entry_tail = NULL;
Snapshot* snapshot_head = NULL;
Snapshot* snapshot_tail = NULL;
int snapshotId = 1;


//new value
Value* new_value(int value)
{
	Value* newValue = (Value*) malloc(sizeof(Value));
	newValue -> prev = NULL;
	newValue -> next = NULL;
	newValue -> value = value;
	return newValue;
}

//new entry and put values inside
Entry* new_entry(char* key, int values[], int count)
{
	//include values in entry
	Value *values_head = NULL;
	int i=0;
	for (i = 0; i < count; i++)
	{	
		//add from the back
		Value *newValue = new_value(values[i]);
		add_back_value (&values_head, newValue);
	}
	
	//value copy
	Entry *entry = (Entry*) malloc(sizeof(Entry));
	entry -> prev = NULL;
	entry -> next = NULL;
	entry -> values = values_head;
	strcpy(entry -> key, key);
	
	return entry;
}

Snapshot* new_snapshot(int id, Entry* entries)
{
    Snapshot *newSnapshot = (Snapshot *)malloc(sizeof(Snapshot));
    newSnapshot->prev = NULL;
    newSnapshot->next = NULL;
    newSnapshot->id = id;
    newSnapshot->entries = entries;
    return newSnapshot;
}

void add_back_snapshot(Snapshot* newSnapshot)
{
    Snapshot *target = snapshot_head;
    if (snapshot_head == NULL)
    {
        snapshot_head = newSnapshot;
        snapshot_tail = newSnapshot;
        return;
    }
    
    while (target->next != NULL)
        target = target->next;
    
    target->next = newSnapshot;
    newSnapshot->prev = target;
    snapshot_tail = newSnapshot;
}

//value adding from back
void add_back_value(Value** head, Value *newValue)
{
	Value* target = *head;
	
	//if there is no value, head = newValue
	if (*head == NULL)
	{
		*head = newValue;
		return;
	}
	
	//go to last one
	while (target -> next != NULL)
	{
		target = target -> next;
	}
	
	//put it at the last
	target -> next = newValue;
	newValue -> prev = target;
}

int main(int argc, char* argv[])
{
	char input[INPUT_BUFFER_LENGTH] = { 0x00 };
	char cmd[CMD_BUFFER_LENGTH] = { 0x00 };
	char params[PARAMS_MAX_COUNT][PARAMS_BUFFER_LENGTH] = { { 0x00 }, };
	int params_count = 0;
	int retval = 0;

	do {
		memset(input, 0x00, INPUT_BUFFER_LENGTH);
		memset(cmd, 0x00, CMD_BUFFER_LENGTH);
		memset(params, 0x00, PARAMS_MAX_COUNT * PARAMS_BUFFER_LENGTH);
		printf("> ");
		fgets(input, INPUT_BUFFER_LENGTH, stdin);
		input[strlen(input) - 1] = 0x00; // remove trailing newline char
		
		params_count = parseCmd(input, cmd, params);
		if (params_count != -1)
		{
			retval = runCmd(cmd, params, params_count);
			printf("\n");
		}
	} while (retval == 0);

	return 0;
}

//parse command
int parseCmd(char* source, char* cmd, char(*params)[PARAMS_BUFFER_LENGTH])
{
	int params_count = 0;

	//devide the command with space
	char *token = strtok(source, " ");
	if (token == NULL)
		return -1;

	strcpy(cmd, token);
	
	// parse parameters
	token = strtok(NULL, " ");
	
	while (token != NULL)
	{
		strcpy(params[params_count], token);
		params_count++;
		token = strtok(NULL, " ");
	}
	
	return params_count;
}

//run command
int runCmd(char* cmd, char params[][PARAMS_BUFFER_LENGTH], int params_count)
{	
 	if (strcasecmp(cmd, "BYE") == 0)
	{
		//delete database
		command_bye();
		printf("bye\n");
		return 0;
	}
	///
	else if (strcasecmp(cmd, "HELP") == 0)
	{
		printf("%s",HELP);
	}
	///ìœ„ì¹˜ë§Œë°”ê¿ˆ ã… ã… 
	else if (strcmp(cmd, "LIST") == 0)
	{
		if(strcasecmp(params[0],"KEYS")==0)
			print_keys();
		if(strcasecmp(params[0],"ENTRIES")==0)
			print_entries();
		if(strcasecmp(params[0],"SNAPSHOTS")==0)
			print_snapshots();
	}
	else if (strcasecmp(cmd, "GET") == 0)
	{
		command_get(params[0]);
	}
	else if (strcasecmp(cmd, "DEL") == 0)
	{
		command_del(params[0]);
	}
	///ì•ˆë¨
	if (strcasecmp(cmd, "PURGE") == 0)
	{
		command_purge(params[0]);
	}	
	else if (strcasecmp(cmd, "SET") == 0)
	{
		command_set(params, params_count);
	}
	else if (strcasecmp(cmd, "PUSH") == 0)
	{
		command_push(params, params_count);
	}
	else if (strcasecmp(cmd, "APPEND") == 0)
	{
		command_append(params, params_count);
	}
	///
	else if (strcasecmp(cmd, "PICK") == 0)
	{
		command_pick(params[0], atoi(params[1]));
	}
	///
	else if (strcasecmp(cmd, "PLUCK") == 0)
	{
		command_pluck(params[0], atoi(params[1]));
	}
	///
	else if (strcasecmp(cmd, "POP") == 0)
	{
		command_pop(params[0]);
	}
	///
	else if (strcasecmp(cmd, "DROP") == 0)
	{
		command_drop(atoi(params[0]));
	}
	///
	else if (strcasecmp(cmd, "ROLLBACK") == 0)
	{
		command_rollback(atoi(params[0]));
	}
	else if (strcasecmp(cmd, "CHECKOUT") == 0)
	{
		command_checkout(atoi(params[0]));
	}
	else if (strcasecmp(cmd, "SNAPSHOT") == 0)
	{
		command_snaps();
	}
	///
	else if (strcasecmp(cmd, "MIN") == 0)
	{
		command_min_value(params[0]);
	}
	///
	else if (strcasecmp(cmd, "MAX") == 0)
	{
		command_max_value(params[0]);
	}
	///
	else if (strcasecmp(cmd, "SUM") == 0)
	{
		command_sum_value(params[0]);
	}
	///
	else if (strcasecmp(cmd, "LEN") == 0)
	{
		command_len(params[0]);
	}
	
	else if (strcasecmp(cmd, "REV") == 0)
	{
		command_rev(params[0]);
	}
	//
	else if (strcasecmp(cmd, "SORT") == 0)
	{
		command_sort(params[0]);
	}
	//
	else if (strcasecmp(cmd, "UNIQ") == 0)
  {
    command_uniq(params[0]);
  }

  else if (strcasecmp(cmd, "DIFF") == 0)
  {
    command_diff(params,params_count);
  }
  else if (strcasecmp(cmd, "UNION") == 0)
  {
    command_union(params,params_count);
  }
  else if (strcasecmp(cmd, "INTER") == 0)
  {
    command_inter(params,params_count);
  
  }
	return 0;
}
int valid_set(char params[][PARAMS_BUFFER_LENGTH],int params_count)
{
  int i=0, cnt=0;
  if(entry_head==NULL)
  {
    printf("no such entry\n");
    return -1;
  }
  if(params_count<=1)
  {
   printf("not enough entry\n");
    return -1;
  }
  for(i=0;i<params_count;i++)
    if(get_entry(params[i])!=NULL)
       cnt++;
    
  if(cnt<params_count)
  {
    printf("no such entry\n");
    return -1;
  }
  else return cnt;
  
}

// 차집합
void command_diff(char params[][PARAMS_BUFFER_LENGTH], int params_count) {

  if (params_count < 2)
    return;

  Entry* entry = NULL;
  Value* val=NULL;
  int size_all = 0, i = 0, j = 0, curr = 0;
 
  // Get array size
  entry = get_entry(params[i]);
  size_all = get_length_of_values(entry);

  // Allocation tmp array
  int* tmp = (int*) malloc(sizeof(int) * size_all);
  int* pass_bitmap = (int*) malloc(sizeof(int) * size_all);
  memset(tmp, '\0', size_all);
  memset(pass_bitmap, '\0', size_all);

  // Get first Entry
  entry = get_entry(params[0]);
  if(entry == NULL)
    return;

  // Copy to Array
  curr = 0;
  for (val = entry -> values; val != NULL; val = val -> next)
    tmp[curr++] = val->value;

  // Loop all entry 
  for (i = 1; i < params_count; i++) {

    // Pick KEY
    entry = get_entry(params[i]);
    if (entry == NULL)
      break;

    // Pick value
    for (val = entry -> values; val != NULL; val = val -> next) {
      for (j = 0; j < size_all && tmp[j] != val->value; j++);

      if (j < size_all) {
        pass_bitmap[j] = 1;
      }
    }
  }
 // Print Olny diff
  printf("[");
  for (i = 0; i < size_all; i++) {
    if (pass_bitmap[i] != 1)
      printf("%d ", tmp[i]);
  }
  if(i!=0)printf("\b");
  printf("]\n"); 
  // Free
  free(tmp);
  free(pass_bitmap); 
}

// 합집합
void command_union(char params[][PARAMS_BUFFER_LENGTH], int params_count) {

  if (params_count < 2)
    return;

  Entry* entry = NULL;
  Value* val;
  int size_all = 0, i = 0, j = 0, curr = 0;
 
  // Sum array size
  for (i = 0; i < params_count; i++) {
    entry = get_entry(params[i]);
    size_all += get_length_of_values(entry);
  }

  // Allocation tmp array
  int* tmp = (int*) malloc(sizeof(int) * size_all);
  memset(tmp, '\0', size_all);

  printf("[");
  for (i = 0; i < params_count; i++) {

    // Pick KEY
    entry = get_entry(params[i]);
    if(entry == NULL)
      return;

    // Pick value
    for (val = entry -> values; val != NULL; val = val -> next) 
    {
      for (j = 0; j < size_all && tmp[j] != val->value; j++);
      if (j >= size_all) 
      {
        printf("%d ", val->value);
        tmp[curr++] = val->value;
      }
    }
  }
  if(i!=0)printf("\b");
  printf("]");
  free(tmp);
}

int dupcheck(Entry* result,int val)
{
  Value* r = result->values;
  int false =0;
  while(r!=NULL)
  {
    if(r->value==val)
      false =1;
    r=r->next;
  }
  return false;
}
Entry* inter(Entry* a, Entry* b)
{
  Entry* result =(Entry*)malloc(sizeof(Entry));
  result->values = (Value*)malloc(sizeof(Value));
  strcpy(result->key,"INTER");
  Value *av = a->values;
  Value *bv = b->values;
  Value *rv = result->values;
  rv->prev=NULL;rv->next=NULL;

  while(av!=NULL)
  {
    bv = b->values;
    while(bv!=NULL)
    {
      if(av->value==bv->value)
      {
        if(dupcheck(result,av->value)==0)
        {
            rv->value = av->value;
            Value* tmp=(Value*)malloc(sizeof(Value));
            tmp->value=0;tmp->next=NULL;tmp->prev=NULL;
            tmp->prev=rv;
            rv->next=tmp;
            rv=rv->next;
        }
      }
      bv=bv->next;
    }
    av=av->next;
  }
  rv->value=-1; 
  return result;
}
void command_inter(char params[][PARAMS_BUFFER_LENGTH],int params_count)
{
  Entry** selected=NULL;
  Entry* entry = NULL;
  Entry* result=NULL;
  Value* rv=NULL;
  int i=0;
  int valid = valid_set(params,params_count);
  int tmp=0;
  if(valid==-1)return;
  selected = (Entry**)malloc(sizeof(Entry*)*valid);
  
  for(i=0;i<valid;i++)
  {  
    selected[i]=(Entry*)malloc(sizeof(Entry));
    if((entry=get_entry(params[i]))!=NULL)
    { 
      selected[i]=entry;tmp++; 
    }
  }
  valid=tmp;
  result=inter(selected[0],selected[1]);

  for(i=2;i<valid;i++)
     result=inter(result,selected[i]);
  
  rv= result->values;
  printf("[");
  while(rv->value!=-1)
  {
    printf("%d ",rv->value);
    rv=rv->next;
  }
  if(result->values->value!=-1)printf("\b");
  printf("]");
}
///
//find the entry with key
Entry* get_entry(char* key)
{
	Entry *head = entry_head;
	
	//until find the key, keep searching
	while(head != NULL)
	{	
		if (strcmp(head -> key, key) == 0){
			return head;
		}
	head = head->next;
	}
	return NULL;
}

//get the value with the index
Value* get_value(Entry* entry, int index)
{
	int i = 0;
	Value* head;
	
	//when the index is find, return the value
	for (head = entry -> values; head != NULL; head = head -> next, i++)
	{
		if (i == index)
		{
			return head;
		}
	}
	return NULL;
}

void print_keys()
{
    if (entry_head == NULL)
    {
        printf("no keys\n");
        return;
    }
    
    Entry* iterator;
    for (iterator = entry_head; iterator != NULL; iterator = iterator->next)
    {
        printf("%s\n", iterator->key);
    }
}

//print entries
void print_entries()
{
	//if there is no entry print 'no entris'
	if (entry_head == NULL)
	{
		printf("no entries\n");
		return;
	}
	
	Entry *head;
	Value* val;
	
	//printing repeated until there is no next
	for (head = entry_head; head != NULL; head = head -> next)
	{
		//print entry
		printf("%s ", head -> key);
		//print values
		printf("[");
		for(val = head -> values; val != NULL; val = val -> next)
		{
			//at the last value, print with no space
			printf((val -> next != NULL ? "%d " : "%d"), val -> value);
		}
		printf("]\n");

	}
}

//print snapshots
void print_snapshots()
{
	//if there is no snapshot -> print 'no snapshots'
	if (snapshot_head == NULL)
	{
		printf("no snapshots\n");
		return;
	}
	
	Snapshot *head = snapshot_head;
	for (head = snapshot_head; head != NULL; head = head -> next)
	{
		printf("%d\n", head -> id);
	}
}

//displays entry values
void command_get(char* key)
{	
	//get entry for key
	Entry* entry = get_entry(key);
	Value* val;
	//if a <key>does not exist in the current state, print no such key
	if(entry == NULL) {printf("no such key\n"); return;}

	//print value
	printf("[");
	for (val = entry -> values; val != NULL; val = val -> next)
	{
		//at the last value, print with no space
		printf((val->next != NULL ? "%d " : "%d"), val->value);
	}
	printf("]\n");
}

//deletes entry from current state
void command_del(char* key)
{
	Entry* entry = get_entry(key);
	if (entry != NULL)
	{
		delete_entry(entry);
		printf("ok\n");
	}
	else
		printf("no such key\n");
}

//deletes entry from current state and snapshots
void command_purge(char* key)
{
	Entry *entry = entry_head;
	Snapshot *snapshot = snapshot_head;
	
	//find the entry with the key
	while (entry != NULL)
	{
		if (strcmp(entry -> key, key) == 0)
		{
			delete_entry(entry);
			break;
		}
		entry = entry -> next;
	}
	
	while (snapshot != NULL)
	{
		entry = snapshot -> entries;
		while (entry != NULL)
		{
			if (strcmp(entry -> key, key) == 0)
			{
				//in the middle
				if (entry -> prev != NULL)
					entry = entry -> next;
				
				if (entry -> next != NULL)
					entry = entry -> prev;
				
				//entry=entry_head
				if (entry -> prev == NULL)
					snapshot -> entries = entry -> next;
				
				delete_values(entry -> values);
				
				free(entry);
				
				break;
			}
			entry = entry -> next;
		}
		snapshot = snapshot -> next;
	}
	printf("ok\n");
}
/**
void command_purge(char* key)
{	
	Entry* entry = get_entry(key);
	Snapshot* tmp = snapshot_head;
	if(entry==NULL) printf("no such key\n");
	else{
		delete_entry(entry);
		while(tmp!=NULL)
		{
			if(tmp->entries){
			delete_entry(entry);}
			tmp=tmp->next;
		}
		printf("ok\n");
	
	}

}
**/
//push values from the front
void push_values(char* key, int values[], int count)
{
	Entry* newEntry = new_entry(key, values, count);
	add_front_entry(newEntry);
}

//delete values
void delete_values(Value* values)
{
	while (values != NULL)
	{
		Value* next = values->next;
		free(values);
		values = next;
	}
}

//delete value
void delete_entry_value(Entry* entry, int index)
{
	Value *target;
	int i = 0;
	
	//find the value at the index
	for (target = entry -> values; target != NULL; target = target -> next, i++)
	{
		if (i == index)
			break;
	}
	
	if (target != NULL)
	{	
		//if the value is in the middle
		if (target -> prev != NULL)
			target -> prev -> next= target -> next;
		
		if (target -> next != NULL)
			target -> next -> prev = target -> prev;
		
		//if the target is the first value
		if (index == 0)
			entry -> values = target -> next;
		
		free(target);
	}
}
void delete_all_entry(Entry* e)
{
    Entry* remove;
    //entry is not null
    while (e != NULL)
    {
        if (e == entry_tail)
        {
            entry_head->next = entry_tail;
            entry_tail->prev = entry_head;
            return ;
        }
        
        remove = e;
        e = e->next;
        free(remove->values);
        free(remove);
        remove = NULL;
    }
}
//de

void delete_entry(Entry* entry)
{
    Entry* prev = entry->prev;
    Entry* next = entry->next;
    
    if (prev != NULL)
        prev->next = next;
    if (next != NULL)
        next->prev = prev;
    if (entry == entry_head)
        entry_head = next;
    if (entry == entry_tail)
        entry_tail = prev;
    if(entry->values !=NULL)
    delete_values(entry->values);
   // free(entry->values);
	free(entry);
}

void delete_snapshot(Snapshot* remove)
{
    Snapshot* prev = remove->prev;
    Snapshot* next = remove->next;
    
    if (prev != NULL)
        prev->next = next;
    if (next != NULL)
        next->prev = prev;
    if (remove == snapshot_head)
        snapshot_head = next;
    if (remove == snapshot_tail)
        snapshot_tail = prev;
	if(remove->entries != NULL)
	delete_all_entry(remove->entries);
    free(remove);
}

//clear database
void command_bye(){
  Entry* iterator = NULL;

  if (entry_head == NULL)
  {
    printf("no keys\n");
    return;
  }

  for (iterator = entry_head; iterator != NULL; iterator = entry_head)
  {
    printf("Free : %s \n", iterator->key);
    delete_entry(iterator);
  }

  if (snapshot_head == NULL)
    return;
  
  Snapshot *snap_iterator = NULL;
  for (snap_iterator = snapshot_head; snap_iterator->next != NULL; snap_iterator = snap_iterator->next)
  {
    drop_snapshot(snap_iterator->id);
  }	

}
//make the index 0
void add_front_entry(Entry* newEntry)
{
	insert_entry(newEntry, 0);
}

//insert entry
void insert_entry(Entry* newEntry, int index)
{
	int i = 1;
	Entry* target;
	Entry* temp;
	
	//if there is no entry, new entry is the head and the tail
	if (entry_head == NULL)
	{
		entry_head = newEntry;
		entry_tail = newEntry;
		entry_head -> prev = NULL;
		entry_head -> next = NULL;
	}
	
	//put it in the front
	else if (index == 0)
	{
		newEntry -> next = entry_head;
		entry_head -> prev = newEntry;
		entry_head = newEntry;
	}
	
	else
	{
		target = entry_head;
		
		//if there is no next, put new entry next to the head(target)
		if (target -> next == NULL)
		{
			entry_head -> next = newEntry;
			newEntry->prev = entry_head;
		}
		
		else
		{
			//get the last entry
			while (target -> next != NULL && i < index)
			{
				target = target -> next;
				i++;
			}
			
			//put new entry at the last
			temp = target -> next;
			target -> next = newEntry;
			newEntry -> prev = target;
			newEntry -> next = temp;
		}
	}
}

//sets entry values

void command_set(char params[][PARAMS_BUFFER_LENGTH], int params_count)
{
	//find entry with the key
	Entry* entry = get_entry(params[0]);
	
	//if there is already,
	if(entry==NULL)
	{
		//put values inside the entry with push_value function
		int* values = (int*) malloc(sizeof(int) * (params_count - 1));
	  int i=0;
		for (i = 0; i < params_count - 1; i++)
			values[i] = atoi(params[i + 1]);
		
		//add from front
		push_values(params[0], values, params_count - 1);
		
		free(values);
		
		printf("ok\n");
	}
}

//pushes values to the front
void command_push(char params[][PARAMS_BUFFER_LENGTH], int params_count)
{
	int i;
	Value* newValue;
	
	//find entry with key
	Entry* entry = get_entry(params[0]);
	
	if (entry != NULL) {
		
		for (i = 1; i < params_count; i++) {
			newValue = new_value(atoi(params[i]));
			
			//if there is no value, put value
			if (entry -> values == NULL) {
				entry -> values = newValue;
			}
			
			else {
				//put newvalue in the front
				entry -> values -> prev = newValue;
				newValue -> next = entry -> values;
				entry -> values = newValue;
			}
		}
		printf("ok\n");
	}
	
	else {
		printf("no such key\n");
	}
}

//appends values to the back
void command_append(char params[][PARAMS_BUFFER_LENGTH], int params_count)
{
	Value *newValue, *tail;
  int i=0;	
	//find the entry with the key
	Entry* entry = get_entry(params[0]);
	
	if (entry != NULL) {
		tail = entry -> values;
		
		//get the last
		while (tail != NULL) {
			
			if(tail -> next ==NULL)
				break;
			
			tail = tail -> next;
		}
		
		//append values in command line to the back
		for (i = 1; i < params_count; i++) {
			newValue = new_value(atoi(params[i]));
			
			if (entry -> values == NULL) {
				entry -> values = newValue;
				tail = entry -> values;
			}
			
			else {
				tail -> next = newValue;
				newValue -> prev = tail;
				tail = newValue;
			}
		
		}
		printf("ok\n");
	}
	else {
		printf("invalid input\n");
	}
}

//displays value at index
void command_pick(char* key, int index)
{
	//get entry with the key
	Entry* entry = get_entry(key);
	//Value* head;
	if(entry == NULL) printf("no such key\n");
	else
	{
		int value_length = get_length_of_values(entry);
		
		//if an index does not exist in an entry, print index out of range
		if (index == 0 ||index < 0 ||index > value_length) {
			printf("index out of range\n");
			return;

		}
		//print out the value at the index
		Value* value = get_value(entry, index - 1);
		if (value != NULL) {
			printf("%d\n", value -> value);
		}
	}
}

//displays and removes value at index
//similar to pick method
void command_pluck(char* key, int index)
{
	Entry* entry = get_entry(key);

	if(entry ==NULL) {printf("no such key\n");}
	else{
		//find value length
		int value_length = get_length_of_values(entry);
		
		if (index == 0 ||index < 0 ||index > value_length) {
			printf("index out of range\n");
			return;
		}
		
		Value* value = get_value(entry, index - 1);
		if (value != NULL) {
			printf("%d\n", value -> value);
			//same as pick method but delete the value
			delete_entry_value(entry, index - 1);
		}
	}

}

//displays and removes the front value
void command_pop(char* key)
{
	//find the entry with key
	Entry* entry = get_entry(key);
	
	if(entry ==NULL) {printf("no such key\n");}
	//print the first value and delete it
	
	else
	{	
		int value_length = get_length_of_values(entry);
		if(value_length == 0) {printf("nil\n"); return;}
		//get the first value
		
		Value* value = get_value(entry, 0);
		if (value != NULL) {
			printf("%d\n", value -> value);
			delete_entry_value(entry, 0);
		}
	}

}

//deletes snapshot
void command_drop(int id)
{
	if (drop_snapshot(id) == 0) {
		printf("ok\n");
	}
	
	//if a snapshot does not existin the database, print no such snapshot
	else {
		printf("no such snapshot\n");
	}
}

//delete snapshot
int drop_snapshot(int id)
{
	Snapshot *snapshot_ptr = snapshot_head;
	
    while (snapshot_ptr != NULL)
    {
        if (snapshot_ptr->id == id)
            break;
        snapshot_ptr = snapshot_ptr->next;
    }
	
	if(snapshot_ptr==NULL) return -1;
	
	else
	{
		delete_snapshot(snapshot_ptr);
		return 0;
	}
}

//restores to snapshot and deletes newer snapshots
void command_rollback(int id)
{	
	Snapshot* iterator = snapshot_head;
    
	while (iterator != NULL)
    {
        if (iterator->id == id)
            break;
        iterator = iterator->next;
    }

    if (iterator == NULL)
    {
        printf("no such snapshot\n");
        return;
    }
	
    if (checkout_snapshot(id) == 0) 
	{
		int delete = id + 1;
        while (drop_snapshot(delete) == 0) {
            delete++;
        }
		
		printf("ok\n");
	}	
}

void command_checkout(int id)
{
    if (checkout_snapshot(id) == 0) {
        printf("ok\n");
    }
    else {
        printf("no such snapshot\n");
    }
}
//replaces current state with a copy of snapshot
int checkout_snapshot(int id)
{
    Entry *entry_ptr = entry_head, *target, *head, *newEntry;
    Snapshot *snapshot_ptr = snapshot_head;

	
    while (snapshot_ptr != NULL)
    {
        if (snapshot_ptr->id == id)
            break;
        snapshot_ptr = snapshot_ptr->next;
    }
   
if (snapshot_ptr != NULL)
    {
        while (entry_ptr != NULL)
        {
            target = entry_ptr;
            entry_ptr = entry_ptr->next;
            
            delete_entry(target);
        }
        
        entry_ptr = snapshot_ptr->entries;
        head = NULL;
        target = NULL;
        while (entry_ptr != NULL)
        {
            newEntry = copy_entry(entry_ptr);
            if (head == NULL)
            {
                head = newEntry;
                target = head;
            }
            else
            {
                target->next = newEntry;
                newEntry->prev = target;
                target = newEntry;
            }
            entry_ptr = entry_ptr->next;
        }
        
        entry_head = head;
        return 0;
    }
    else {
        return -1;
    }
}

Entry *copy_entry(Entry *entry)
{
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    Value *iterator = entry->values;
    Value *value_head = NULL;
    while (iterator != NULL)
    {
        Value *newValue = new_value(iterator->value);
        add_back_value(&value_head, newValue);
        iterator = iterator->next;
    }
    strcpy(newEntry->key, entry->key);
    newEntry->values = value_head;
    newEntry->prev = NULL;
    newEntry->next = NULL;
    return newEntry;
}

int rollback_snapshot(int id)
{
    int drop_id = id + 1;
    if (checkout_snapshot(id) == 0) {
        while (drop_snapshot(drop_id) == 0) {
            drop_id++;
        }
        return 0;
    }
    else {
        return -1;
    }
}

void command_snaps()
{
    int id = snapshot();
    printf("saved as snapshot %d\n", id);
}
int snapshot()
{
    Entry *iterator = entry_head;
    Entry *head = NULL;
    Entry *target = NULL;
    Entry *newEntry = NULL;
    Snapshot *newSnapshot = NULL;
    while (iterator != NULL)
    {
        newEntry = copy_entry(iterator);
        if (head == NULL)
        {
            head = newEntry;
            target = head;
        }
        else
        {
            target->next = newEntry;
            newEntry->prev = target;
            target = newEntry;
        }
        iterator = iterator->next;
    }
	
    newSnapshot = new_snapshot(snapshotId, head);
    add_back_snapshot(newSnapshot);
    return snapshotId++;
}

	//min value
void command_min_value(char* key)
{
	Entry* entry = get_entry(key);
	Value* head = entry -> values;
	int min = entry -> values -> value;
	
	if(entry == NULL){
		printf("no such key\n");
        return ;
	}
	
	else
	{
		while(head !=NULL)
		{
			
			if(head->value < min)
				min = head->value;
			
			head = head->next;
			
		}
		printf("%d\n",min);
		
		
	}
}

//max value
void command_max_value(char* key)
{
	Entry* entry = get_entry(key);
	Value* head = entry -> values;
	int max = entry -> values -> value;
	
	if(entry == NULL){
		printf("no such key\n");
        return ;
	}
	
	else
	{
		while(head !=NULL)
		{
			
			if(head->value > max)
				max = head->value;
			
			head = head->next;
			
		}
		printf("%d\n",max);
		
		
	}
}

//sum
void command_sum_value(char* key)
{
	Entry* entry = get_entry(key);
	Value* head = entry -> values;
	int sum = 0;
	
	if(entry == NULL){
		printf("no such key\n");
        return ;
	}
	
	else
	{
		while(head !=NULL)
		{

			sum += head->value;
			head = head->next;
			
		}
		printf("%d\n",sum);
		
		
	}
}

//length
void command_len(char* key)
{
	Entry* entry = get_entry(key);
	
	if (entry != NULL)
		printf("%d\n", get_length_of_values(entry));
	
	else
		printf("no such key\n");
}

//reverse
//reverse
void command_rev(char* key)
{
	Entry* entry = get_entry(key);
	Value* head = entry->values;
	Value* target, *temp;
	
	if(entry == NULL){
		printf("no such key\n");
	}
	else
	{
		while(head!=NULL)
		{
		if (head -> next == NULL)
			entry -> values = head;
		
		target = head;
		head = head -> next;
	
		// swap
		temp = target -> prev;
		target -> prev = target -> next;
		target -> next = temp;
		}
	
	printf("ok\n");
	}
}

void value_swap(Value **_prev, Value **_next) {
    Value *tmp;
    tmp = *_prev;
    *_prev = *_next;
    *_next = tmp;

}


//sorts values in ascending order
void command_sort(char* key){
	
	Entry* _entry = get_entry(key);
	Value* _value = _entry->values;
	Value *compare = _value->next;

	if(_entry == NULL){
		printf("no such key\n");
	}
	
	else{
		while(_value != NULL&&compare !=NULL) {
			
			if(_value->value > compare->value) {
				// BUBBLE SORT!!!
				int_swap(&_value->value, &compare->value);
			}
			
			compare = compare->next;
			_value = _value->next;
		}
		printf("ok\n");
	}
}

void int_swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void command_uniq(char* key){
    
	Entry* entry = get_entry(key);
	int index =0;

	if(entry == NULL) printf("no such key\n");
	
    else {
            // Caching the values
            Value *_value = entry->values;
            while(_value != NULL) {

                if (_value->next != NULL && _value->value == _value->next->value) {
                    //_value = del_value(&_value->next);
                    delete_entry_value(entry, index+1);
                    continue;
                }
                index++;
                _value = _value->next;
            }
		printf("ok\n");
        }
}

///
//get length
int get_length_of_values(Entry *entry)
{

	int len=1;
	Value* head;
	head = entry ->values;
	if(head==NULL){return 0;}
	while(head->next != NULL){
		head=head->next;
		len++;
	}
	return len;
}
