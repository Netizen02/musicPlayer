#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <MMsystem.h>
#include <sys/types.h>
//#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct node
{
    struct node *prev;
    struct node *next;
    char filename[1000];
};
struct node *head;

void fileManagement(char *path);
void scheduleAudio(char *path);
void playMusic();

int main()
{
    char path[100];
    // Input path from user
    printf("Enter the path: ");
    printf("\n*********.wav Player*********\n");
    printf("\nThis is a .wav player. It is similar to an .mp3 player in the sense that they both play audio files.\n");
    printf("However this programwas designed to play only .wav files, due to timing constraints. The program works");
    printf("\nin the following way:\n");
    printf("\n1. \tThe user must create a folder of songs and audio files[in .wav format(otherwise the program won't");
    printf("\n   \tplay the audio)] of their choosing. Make sure that the name of the folder does not have any space");
    printf("\n   \tin it(e.g. '.wavMusic').");
    printf("\n2. \tThen note the file address of the files in the folder (e.g. 'C:/Users/gujar/Downloads/.wavMusic') ");
    printf("\n3. \tEnter the file address when asked.");
    printf("\n4. \tListen to your audio/music.");
    printf("\n===============================================\n");
    printf("\nThank you so much for your time.\n");
    printf("\nEnter the path: ");
    scanf("%s", path);

    fileManagement(path);
    playMusic();
    return 0;
}

//Lists all files and sub-directories recursively considering path as base path.
void fileManagement(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir){
        printf("UNABLE!");
        return;
    }
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s\n", dp->d_name);
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "\\");
            strcat(path, dp->d_name);
            scheduleAudio(path);
        }
    }
    closedir(dir);
}

void scheduleAudio(char *path)
{
   struct node *ptr,*temp;
   ptr = (struct node *) malloc(sizeof(struct node));
   if(ptr == NULL)
   {
       printf("\nOVERFLOW");
   }
   else
   {
       strcpy(ptr->filename,path);
       if(head == NULL)
       {
           ptr->next = NULL;
           ptr->prev = NULL;
           head = ptr;
       }
       else
       {
          temp = head;
          while(temp->next!=NULL)
          {
              temp = temp->next;
          }
          temp->next = ptr;
          ptr ->prev=temp;
          ptr->next = NULL;
          }
       }
}

void playMusic()
{
    char pAth[1000];
    struct node *ptr;
    printf("\n playing sound...\n");
    ptr = head;
    strcpy(pAth,ptr->filename);
    PlaySound(pAth,NULL,SND_ASYNC);
    int choice =0;
    while(choice != 5)
    {
        printf("\n*********Main Menu*********\n");
        printf("\nChoose one option from the following list ...\n");
        printf("\n===============================================\n");
        printf("\n1.Play Previous\n2.Play Next\n3.Pause\n4.Play\n5.End\n");
        printf("\nEnter your choice?\n");
        scanf("\n%d",&choice);
        switch(choice)
        {
        case 1:
            //playPrevious();
            PlaySound(NULL,NULL,SND_ASYNC);
            if(ptr == head){
                printf("Can't go to previous. This song is first in the playlist.");
                PlaySound(ptr->filename,NULL,SND_ASYNC);
            }
            else{
                ptr = ptr->prev;
                PlaySound(ptr->filename,NULL,SND_ASYNC);
            }
            break;
        case 2:
            //playNext();
            PlaySound(NULL,NULL,SND_ASYNC);
            ptr=ptr->next;
            if(ptr != NULL){
                PlaySound(ptr->filename,NULL,SND_ASYNC);
            }
            else if(ptr == NULL){
                printf("Can't go to next. This song is last in the playlist. Going to the start of the playlist.");
                ptr = head;
                PlaySound(ptr->filename,NULL,SND_ASYNC);
            }
            break;
        case 3:
            //pause();
            PlaySound(NULL,NULL,SND_ASYNC);
            break;
        case 4:
            PlaySound(ptr->filename,NULL,SND_ASYNC);
            break;
        case 5:
            exit(0);
            break;
        default:
                printf("Please enter valid choice..");
        }
    }
    printf("\n*********Thank You for your time!*********\n");
}
