#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<dirent.h>
#include"linklist.h"

#define FILENAME "DAQ- Crosshead; … - (Timed).txt"
#define INFO_CSV "info.csv"
#define DATA_CSV "data.csv"
#define FIELDSIZE 30


typedef struct files {
    size_t filesize;
    char* filename;
    char clientname[FIELDSIZE];
    char testrun[FIELDSIZE];
    char date[FIELDSIZE];
    char time[FIELDSIZE];
    Node *crosshead;
    Node *load;
    Node *times;
    Node *video;
    Node *axial;
    Node *traverse;
}fileinfo;

void searchfile(const char *name, Node** files_found, char* find_file_name) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            //printf("[%s]\n", entry->d_name);
            searchfile(path, files_found, find_file_name);
        }
        else {
            //printf("%s %s\n", entry->d_name, name);
            if(strcmp(entry->d_name, find_file_name) == 0) {
                char full_path[1024];
                snprintf(full_path, sizeof(full_path), "%s/%s", name, entry->d_name);
                //printf("Found %s %s %s\n", entry->d_name, name, full_path);
                add_list(files_found, full_path);
            }
        }
    }
    closedir(dir);
}



long int getfilesize(const char* filename) {
    FILE* fileptr;
    int ret_val;
    long int size;

    fileptr = fopen(filename,"r");
    if(fileptr == NULL) {
        printf("Cannot open %s file\n", filename);
        return -1;
    }

    ret_val = fseek(fileptr,0, SEEK_END);
    if(ret_val != 0) {
        printf("Calculating fseel failed for %s file\n", filename);
        return -1;
    }

    size = ftell(fileptr);
    if(size == -1) {
        printf("Calculating ftell failed for %s file\n", filename);
        return -1;
    }
    printf("Size of file %s: %ld bytes\n", filename, size);

    ret_val = fclose(fileptr);
    if(ret_val == -1) {
        printf("Cannot close %s file\n", filename);
        return -1;
    }

    return size;
}


fileinfo * parse_files(const char *dirname, int* number_of_files) {
    Node* file_list = NULL;
    Node* mover = NULL;
    searchfile(dirname, &file_list, FILENAME);
    print_list(file_list);
    mover = file_list;

    *number_of_files = length_list(file_list);
    fileinfo *f = NULL ;
    f = (fileinfo *) malloc(sizeof(fileinfo)*(*number_of_files)); 
    int i = 0;
    while(mover != NULL && i < *number_of_files) {
        FILE* fileptr;
        long int filesize;
        char crosshead[25], load[25], time[25], video[25], axial[25], traverse[25];
        int ret_val;
        size_t len = 0;
        char* line = NULL;
        size_t bytes_read;

        f[i].filename = (char *) malloc(sizeof(char)*strlen(mover->string));
        strcpy(f[i].filename, mover->string);
        f[i].crosshead = NULL;
        f[i].load = NULL;
        f[i].times = NULL;
        f[i].video = NULL;
        f[i].axial = NULL;
        f[i].traverse = NULL;

        filesize = getfilesize(mover->string);
        if(filesize == -1) {
            printf("Getting filesize failed for %s file\n", mover->string);
            return NULL;
        }
        f[i].filesize = filesize;
        fileptr = fopen(mover->string,"r");
        if(fileptr == NULL) {
            printf("Cannot open %s file\n", mover->string);
            return NULL;
        }

        int linenumber = 1;
        while ((bytes_read = getline(&line, &len, fileptr)) != -1) {
            if(linenumber == 1) {
                //printf("Retrieved line of length %zu\n", bytes_read);
                sscanf(line,"%*s %s", f[i].clientname);
                //printf("%s\n",f.clientname);
            }
            else if(linenumber == 2) {
                sscanf(line, " %*[a-zA-Z :] %[0-9_ ]", f[i].testrun);
                //printf("%s\n", f.testrun);
            }
            else if(linenumber == 3){
                sscanf(line, "%*[a-zA-Z:] %s %s",f[i].date, f[i].time);
                //printf("%s %s\n",f.date, f.time);
                //printf("%s",line);
            }
            
            else if(linenumber >= 8) {
                sscanf(line, "%s\t%s\t%s\t%s\t%s\t%s", crosshead, load, time, video, axial, traverse);
                add_list(&(f[i].crosshead), crosshead);
                add_list(&(f[i].load), load);
                add_list(&(f[i].times), time);
                add_list(&(f[i].video), video);
                add_list(&(f[i].axial), axial);
                add_list(&(f[i].traverse), traverse);

                //printf("%s\t%s\t%s\t%s\t%s\t%s\n", crosshead, load, time, video, axial, traverse);
            }
            linenumber++;
        }

        printf("crosshead values parsed: %d\n",length_list(f[i].crosshead));
        printf("load values parsed: %d\n",length_list(f[i].load));
        printf("times values parsed: %d\n",length_list(f[i].times));
        printf("video values parsed: %d\n",length_list(f[i].video));
        printf("axial values parsed: %d\n",length_list(f[i].axial));
        printf("traverse values parsed: %d\n",length_list(f[i].traverse));
        printf("\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");

        ret_val = fclose(fileptr);
        if(ret_val == -1) {
            printf("Cannot close %s file\n", mover->string);
            return NULL;
        }
        mover = mover->next;
        i++;
    }

return f;
}

int write_file_to_csv( fileinfo* data_parsed, int number_of_files) {
    FILE* datafileptr;
    FILE* infofileptr;
    int i;

    datafileptr = fopen(DATA_CSV,"w+");
    infofileptr = fopen(INFO_CSV,"w+");

    fprintf(datafileptr, "\tCrosshead,\tLoad,\tTime,\tVideo,\tAxial,\tTraverse\n");
    fprintf(infofileptr, "\tTest client,\tTest Run,\tFile name,\tDate,\tTime,\tFile size(Bytes)\n");
    for(i = 0 ; i < number_of_files; i++) {
        fileinfo current = data_parsed[i];
        fprintf(infofileptr,"\t%s,\t%s,\t%s,\t%s,\t%s,\t%ld\n", current.clientname,
                current.testrun, current.filename, current.date,current.time,current.filesize);
        printf("file name: %s\t fize size: %ld\n", current.filename, current.filesize);
        free(current.filename);
        Node* temp_crosshead;
        Node* temp_load;
        Node* temp_time;
        Node* temp_video;
        Node* temp_axial;
        Node* temp_traverse;

        temp_crosshead = current.crosshead;
        temp_load = current.load;
        temp_time = current.times;
        temp_video = current.video;
        temp_axial = current.axial;
        temp_traverse = current.traverse;
        while(temp_crosshead !=NULL) {
            fprintf(datafileptr, "\t%s,\t%s,\t%s,\t%s,\t%s,\t%s\n", temp_crosshead->string, temp_load->string,
                     temp_time->string, temp_video->string, temp_axial->string, temp_traverse->string);
            free(temp_crosshead->string);
            free(temp_load->string);
            free(temp_time->string);
            free(temp_axial->string);
            free(temp_video->string);
            free(temp_traverse->string);

            temp_crosshead = temp_crosshead->next;
            temp_load = temp_load->next;
            temp_time = temp_time->next;
            temp_video = temp_video->next;
            temp_axial = temp_axial->next;
            temp_traverse = temp_traverse->next;
        }
        delete_list(temp_crosshead);
        delete_list(temp_load);
        delete_list(temp_time);
        delete_list(temp_video);
        delete_list(temp_axial);
        delete_list(temp_traverse);
    }
    fclose(datafileptr);
    fclose(infofileptr);
    return 0;
}

int main(int argc, char* argv[]) {
    fileinfo* data_parsed;
    int number_of_files;
    int ret_val;
    data_parsed = parse_files(argv[1],&number_of_files);
    ret_val =write_file_to_csv(data_parsed, number_of_files);
    free(data_parsed);
    return ret_val;
}