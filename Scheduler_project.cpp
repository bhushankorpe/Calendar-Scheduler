
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define YEAR 2016
#define NEW(x,n) (x*) malloc(n*sizeof(x))
#define FLUSH_STDIN(x) {if(x[strlen(x)-1]!='\n'){do fgets(Junk,20,stdin);while(Junk[strlen(Junk)-1]!='\n');}else x[strlen(x)-1]='\0';}
char Junk[20];

//Structure to store the date of an event
typedef struct EVENT_DATE{
    int day;
    int month;
    int hour;
    int min;
}EVENT_DATE;

//Structure to store the an event
typedef struct EVENT{
    char event_name[17];
    EVENT_DATE start_date;
    EVENT_DATE end_date;
    char event_desc[258];
}EVENT;

//Structure for a calendar
typedef struct calendar {
    EVENT event;
    struct calendar *next_event;
}CALENDAR;

//Structure for a linkedList ro store the Calendar
typedef struct Calendar_Node{
    CALENDAR *HEAD;
    CALENDAR *CURRENT;
    int count;
}CALENDAR_NODE;

CALENDAR_NODE NODE ={.HEAD=NULL,.CURRENT=NULL,.count=0};

//Function that validates a user entered date and time
bool isValidDate(EVENT_DATE *temp)
{
    bool flag=false;
    int numberOfDaysInMonths[12]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (temp->month<13 && temp->month>0)
    {
        if(temp->day <= numberOfDaysInMonths[temp->month-1])
        {
            if (temp->hour>=0 && temp->hour<=23)
            {
                if (temp->min>=0 && temp->min<=59)
                    flag=true;
            }
        }
    }
    return flag;
}


//Function that searches all events based on the input text
//If a match is found, returns the linkedList node of the matching event else returns NULL
CALENDAR* SearchEvent(char* text)
{
    CALENDAR* temp=NODE.HEAD;
    if (NODE.HEAD==NULL)
        return NODE.HEAD;
    else {
        while (temp != NULL) {
            if (strcmp(temp->event.event_name, text) == 0)
                return temp;
            else
                temp = temp->next_event;

        }
        return NULL;
    }
}

//Function to check if the entered start time and end time of an event are valid
bool isValidEventTime(EVENT_DATE start, EVENT_DATE end)
{
    bool flag=false;
    if (!(start.month>end.month)){
        if (start.month==end.month)
        {
            if (!(start.day>end.day)){
                if (start.day==end.day)
                { if(!(start.hour>end.hour))
                    { if (!(start.min>=end.min))
                            flag=true;}
                    else
                        flag=true;
                }
            }
            else
                flag=true;


        }
    }
    else flag=true;
return flag;
}

void PrintEvent(CALENDAR* temp){
    printf("\n %s",temp->event.event_name);
    printf("\n %d/%d %d:%d",temp->event.start_date.month,temp->event.start_date.day,temp->event.start_date.hour,temp->event.start_date.min);
    printf("\n %d/%d %d:%d",temp->event.end_date.month,temp->event.end_date.day,temp->event.end_date.hour,temp->event.end_date.min);
    printf("\n %s \n\n",temp->event.event_desc);
}

// Function to accept valid date and time for an event from the user
EVENT_DATE InputDate(int type)
{
    char event_datetime[13];
    FLUSH_STDIN(event_datetime);
    while (true) {
        switch(type) {
            case 1:
                printf("\n Enter new event start time (mm/dd hh:mm):");
                break;
            case 2:
                printf("\n Enter new event end time (mm/dd hh:mm):");
                break;
            case 3:
                printf("\n Enter a start time (mm/dd hh:mm):");
                break;
            case 4:
                printf("\n Enter an end time (mm/dd hh:mm):");
                break;
        }

        fgets(event_datetime, sizeof(event_datetime), stdin);

        if (event_datetime[2]=='/' && event_datetime[5]==' ' && event_datetime[8]==':')
        {
            EVENT_DATE *temp=NEW(EVENT_DATE,1);
            temp->day=10*(event_datetime[3]-48)+(event_datetime[4]-48);
            temp->month=10*(event_datetime[0]-48)+(event_datetime[1]-48);
            temp->min=10*(event_datetime[9]-48)+(event_datetime[10]-48);
            temp->hour=10*(event_datetime[6]-48)+(event_datetime[7]-48);

            if (isValidDate(temp))
            {
                printf("%s",event_datetime);
                return *temp;}

            else{
                printf("Incorrect Date and time Format");
                FLUSH_STDIN(event_datetime);
            }


        }
        else{
            printf("Incorrect Date and time Format");
            FLUSH_STDIN(event_datetime);
        }

    }

}

void inputTextToDate(EVENT_DATE *temp, char* event_datetime){

    temp->day=10*(event_datetime[3]-48)+(event_datetime[4]-48);
    temp->month=10*(event_datetime[0]-48)+(event_datetime[1]-48);
    temp->min=10*(event_datetime[9]-48)+(event_datetime[10]-48);
    temp->hour=10*(event_datetime[6]-48)+(event_datetime[7]-48);

}



void PrintTimeBlock()
{
    EVENT_DATE start_time=InputDate(3);
    EVENT_DATE end_time=InputDate(4);
        CALENDAR* temp=NODE.HEAD;
        //printf("The Events in the Calendar are as follows");
        while(temp!=NULL)
        {
            if((!isValidEventTime(end_time,temp->event.start_date) && !isValidEventTime(start_time,temp->event.end_date)) || (!isValidEventTime(start_time,temp->event.start_date) && !isValidEventTime(end_time,temp->event.end_date)))
                PrintEvent(temp);
            temp=temp->next_event;
        }


}


// Function to accept valid event description from the user
char* InputDescription() {
    char *event_description=NEW(char,257);
    //FLUSH_STDIN(event_description);
    while (true) {
        printf("Enter new event description (no more than 256 characters and ends with #):");
        fgets(event_description, 1000, stdin);
        if (event_description[strlen(event_description) - 2]!='#' || strlen(event_description) > 256) {
            printf("Incorrect format of Event Description");
            FLUSH_STDIN(event_description);
            continue;
        }
        else
        {
            return event_description;
        }
    }

}

// Function to accept valid event name from the user
char* InputName() {

    char *event_title = NEW(char,17);
    //printf("%s",event_title);
   FLUSH_STDIN(event_title);
    while (true) {
        //printf("%zu",sizeof(event_title));
        printf("Enter new event name (no more than 16 characters and ends with #):");
        fgets(event_title, 1000, stdin);
        //printf("%s",event_title);
        if (event_title[strlen(event_title) - 2] != '#' || strlen(event_title) > 16) {
            printf("Incorrect format of Event Name");
            FLUSH_STDIN(event_title);
            continue;
        }

      //  else if (SearchEvent(event_title)!=NULL)
        //    printf("The Event Name already exists. Please input a unique event name");

        else
        {
           // printf("%s",event_title);

            return event_title;
            }


    }

}



// Function to print all the Events stored in the Calendar Linked List
void PrintAll()
{
    if (NODE.HEAD==NULL)
        printf("\n The Calendar is Empty with no events added");
    else
    {
        CALENDAR* temp=NODE.HEAD;
        printf("The number of events are %d",NODE.count);
        printf("The Events in the Calendar are as follows");
        while(temp!=NULL)
        {
            printf("\n %s",temp->event.event_name);
            printf("\n %d/%d %d:%d",temp->event.start_date.month,temp->event.start_date.day,temp->event.start_date.hour,temp->event.start_date.min);
            printf("\n %d/%d %d:%d",temp->event.end_date.month,temp->event.end_date.day,temp->event.end_date.hour,temp->event.end_date.min);
            printf("\n %s \n\n",temp->event.event_desc);
            temp=temp->next_event;
        }
       // free(temp);
    }
}

// Function to compare the start and end date and time of a given event, with the events in the Calendar linkedList
int compareEvent(CALENDAR* temp,CALENDAR* temp1)
{
int isStartMonthSame= (temp->event.start_date.month == temp1->event.start_date.month);
    int isStartDaySame= (temp->event.start_date.day == temp1->event.start_date.day);
    int isStartHrSame= (temp->event.start_date.hour == temp1->event.start_date.hour);
    int isStartMinSame= (temp->event.start_date.min == temp1->event.start_date.min);

    int isEndMonthSame= (temp->event.end_date.month == temp1->event.end_date.month);
    int isEndDaySame= (temp->event.end_date.day == temp1->event.end_date.day);
    int isEndHrSame= (temp->event.end_date.hour == temp1->event.end_date.hour);
    int isEndMinSame= (temp->event.end_date.min == temp1->event.end_date.min);

    if(temp->event.start_date.month>temp1->event.start_date.month)
        return 1;
    else if (isStartMonthSame && (temp->event.start_date.day>temp1->event.start_date.day))
        return 1;
    else if (isStartMonthSame && isStartDaySame && (temp->event.start_date.hour>temp1->event.start_date.hour))
        return 1;
    else if (isStartMonthSame && isStartDaySame && isStartHrSame && (temp->event.start_date.min>temp1->event.start_date.min))
        return 1;
    else if (isStartMonthSame && isStartDaySame && isStartHrSame && isStartMinSame)
    {
        printf("WARNING: %s and %s have the same start event date and time",temp->event.event_name,temp1->event.event_name);
        if(temp->event.end_date.month>temp1->event.end_date.month)
            return 1;
        else if (isEndMonthSame && (temp->event.end_date.day>temp1->event.end_date.day))
            return 1;
        else if (isEndMonthSame && isEndDaySame && (temp->event.end_date.hour>temp1->event.end_date.hour))
            return 1;
        else if (isEndMonthSame && isEndDaySame && isEndHrSame && (temp->event.end_date.min>temp1->event.end_date.min))
            return 1;
        else if (isEndMonthSame && isEndDaySame && isEndHrSame && isEndMinSame){
            if(strcmp(temp->event.event_name,temp1->event.event_name)>0)
                return 0;
        }

    }
    return 0;
}


//Function to add a valid event to the Calendar LinkedList
void AddEventNode(CALENDAR* temp)
{
    CALENDAR* previous=NULL;
    CALENDAR* current=NODE.HEAD;
    while (current!=NULL) {

            if (compareEvent(current,temp)) {
                    if (current==NODE.HEAD)
                    {
                        temp->next_event=NODE.HEAD;
                        NODE.HEAD=temp;

            }
                else{
                        previous->next_event=temp;
                        temp->next_event=current;

                    }

            previous=current;
            current=current->next_event;

        }
    }
    if (current==NODE.HEAD)
    {
        temp->next_event=NODE.HEAD;
        NODE.HEAD=temp;
        NODE.CURRENT=NODE.HEAD->next_event;

    }
    else{
        previous->next_event=temp;
        temp->next_event=current;
        NODE.CURRENT=current;

    }
    NODE.count+=1;
    //PrintAll();
   // free(temp);
}

//Function to accept valid event details from the user
void InputNewEvent() {
    CALENDAR *temp = NEW(CALENDAR, 1);
    strcpy(temp->event.event_name, InputName());
   // printf("%s",temp->event.event_name);
    bool flag=true;
    while(flag)
    {
        temp->event.start_date = InputDate(1);
        temp->event.end_date = InputDate(2);
        if (isValidEventTime(temp->event.start_date,temp->event.end_date))
            flag=false;
        else
            printf("Error: The event end date and time must be greater than the start date and time");
    }

    strcpy(temp->event.event_desc, InputDescription());
    printf("\n %s", temp->event.event_desc);
    temp->next_event=NULL;
    AddEventNode(temp);
}


int DeleteEvent(char* eventname)
{


    CALENDAR* previous=NULL;
    CALENDAR* current=NODE.HEAD;

       // printf("%s",current->event.event_name);
    while(current!=NULL) {
       //printf("%s",current->event.event_name);
        if (strcmp(current->event.event_name, eventname) == 0) {
            if (current==NODE.HEAD){
             //   printf("%s",current->event.event_name);
                NODE.HEAD=current->next_event;
                NODE.CURRENT=NODE.HEAD;
                NODE.count-=1;
            }
            else
            {
                previous->next_event=current->next_event;
                NODE.CURRENT=current;
                NODE.count-=1;
            }
            //printf("\n Event %s has been successfully deleted", eventname);
           // free(previous);
            //free(current);
            //free(eventname);
            return 1;
        }
        else
        {
            previous=current;
            current=current->next_event;
        }

    }

    printf("Error! %s not found",eventname);
   // free(previous);
   // free(current);
   // free(eventname);
    return 0;
}

void SearchbyEventName()
{
    char* text=NEW(char,17);
    CALENDAR *temp =SearchEvent(text);
    printf("\n Enter the event name to be searched: ");
    scanf("%s",text);

    if (temp!=NULL)
        PrintEvent(temp);
    else
        printf("%s not found",text);
    free(text);
}

void SearchKeyword()
{
    char* text=NEW(char,17);int flag=1;
    FLUSH_STDIN(text);
    printf("\n Enter the keyword to be searched:");
    fgets(text,1000,stdin);
    //printf("%s",text);
    CALENDAR *temp =NODE.HEAD;
    strtok(text, "\n");
    printf("%d %d %s",strlen(text),strlen(temp->event.event_name),strstr(temp->event.event_name,text));
    while (temp!=NULL)
    {
        if (strstr(temp->event.event_name,text)!= NULL ){
            PrintEvent(temp); flag=0;
        }

        else if (strstr(temp->event.event_desc,text)!= NULL){
            PrintEvent(temp);flag=0;
        }

        temp=temp->next_event;

    }
    if (flag==1)
        printf("The keyword does not match any event name or description");
    free(text);
}

void PrintConflicts()
{
    char* text = NEW(char,17);
    printf("Enter the event name to find conflicts");

    while(*fgets(text,1000,stdin)==10)
        ;
    strtok(text, "\n");
    CALENDAR* temp = SearchEvent(text);
    if(temp == NULL)
    {
        printf("No conflicting events found.\n");
        PrintConflicts();
    }
    else
    {
        CALENDAR* current = NODE.HEAD;
        int match1,match2,numberOfconflicts=0;
        while(current!=NULL)
        {
            match1 = !isValidEventTime(temp->event.end_date,current->event.end_date) \
				&& !isValidEventTime(temp->event.end_date,current->event.start_date);
            match2 = !isValidEventTime(temp->event.start_date,current->event.end_date) \
				&& !isValidEventTime(current->event.start_date,temp->event.end_date);
            if((match1 || match2) && temp!=current)
            {
                numberOfconflicts++;
                PrintEvent(current);
            }
            current = current->next_event;
        }
        if(!numberOfconflicts)
            printf("No conflicting events found.\n");
    }
    free(temp);
}

int ModifyEvent()
{
    char *eventitle=NEW(char,17); int input;
            FLUSH_STDIN(eventitle);
    printf("\n Enter event name to modify:");
    fgets(eventitle, sizeof(eventitle),stdin);
    CALENDAR* temp=SearchEvent(eventitle);

    if (temp==NULL)
        return 0;
    else
    { CALENDAR* modified_event=NEW(CALENDAR,1);
        *modified_event=*temp;
        DeleteEvent(temp->event.event_name);
        while(1) {
            printf("Which field would you like to change ?\n"
                           "\n"
                           "1. Change event name:\n"
                           "\n"
                           "2. Change start time:\n"
                           "\n"
                           "3. Change end time:\n"
                           "\n"
                           "4. Change description");
            scanf("%d", &input);
            switch (input) {
                case 1:
                    strcpy(modified_event->event.event_name,InputName());
                    AddEventNode(modified_event);
                    return 1;
                case 2:
                        modified_event->event.start_date=InputDate(1);
                    while(!isValidEventTime(modified_event->event.start_date,modified_event->event.end_date))
                    {
                        printf("Invalid date and time. STart date must be less than end date");
                        modified_event->event.start_date=InputDate(1);
                    }
                    AddEventNode(modified_event);
                    return 1;

                case 3:modified_event->event.end_date=InputDate(2);
                    while(!isValidEventTime(modified_event->event.start_date,modified_event->event.end_date))
                    {
                        printf("Invalid date and time. STart date must be less than end date");
                        modified_event->event.end_date=InputDate(2);
                    }
                    AddEventNode(modified_event);
                    return 1;
                case 4:
                    strcpy(modified_event->event.event_desc,InputDescription());
                    AddEventNode(modified_event);
                    return 1;
                default: printf("Error! option between 1-4 expected.");break;

            }
        }
    }


}

void AddInputFileEvents(char* file_name){
    FILE *file;
    file = fopen(file_name,"r");
    if (file == NULL) {
        printf("Empty file");
        exit(EXIT_FAILURE);
    }
    char* event = NEW(char,258);
    CALENDAR* current = NODE.HEAD;

    while(fgets(event, 21, file) != NULL) {
        CALENDAR *temp = NEW(CALENDAR, 1);

        strtok(event, "\n");
        strcpy(temp->event.event_name, event);
        fgets(event, 15, file);
        strtok(event, "\n");
        inputTextToDate(&temp->event.start_date, event);

        fgets(event, 15, file);
        strtok(event, "\n");
        inputTextToDate(&temp->event.end_date, event);


        fgets(event, 259, file);
        strtok(event, "\n");
        strcpy(temp->event.event_desc, event);


        fgets(event, 10, file);
        fgets(event, 10, file);

        if (NODE.HEAD == NULL)
            NODE.HEAD = temp;
        else
            current->next_event = temp;

        temp->next_event = NULL;
        NODE.CURRENT = temp;
        current = temp;
        NODE.count += 1;
    }
    fclose(file);

}

void WriteOutputFile(int argc, char* argv[])
{
    CALENDAR* current = NODE.HEAD;
    FILE* file;
    remove(argv[argc-1]);
    file = fopen(argv[argc-1],"w");
    if (file == NULL)
        exit(EXIT_FAILURE);
    while(current!=NULL)
    {
        fprintf(file,"%s\n %02d/%02d %02d:%02d \n %02d/%02d %02d:%02d\n%s\n\n\n",\
			current->event.event_name,current->event.start_date.month,current->event.start_date.day,\
			current->event.start_date.hour,current->event.start_date.min,current->event.end_date.month,\
			current->event.end_date.month,current->event.end_date.hour,current->event.end_date.min,\
			current->event.event_desc);
        current = current->next_event;
    }
    fclose(file);
}

//Function with the main menu
int main(int argc, char *argv[])
{
    int input; bool flag=true; char* text=NEW(char,17);char *eventname=NEW(char,17);

    switch(argc)
    {
        case 3:
            AddInputFileEvents(argv[1]);

        case 2:
            break;
        default:
            printf("Invalid Input \n");
            exit(0);
    }

    while (flag) {
        system("clear");
        printf("\n *************** Welcome to your Personal Calendar *******************");
        printf("\n Enter a number from the list below to select an option, or press 9 to quit \n");
        printf("\n Edit Commands \n\t 1. Add new Event \n\t 2. Delete Event \n\t 3. Modify Event");
        printf("\n\n Print Commands \n\t 4. Print all \n\t 5. Print time block \n\t 6. Print Conflicts");
        printf("\n\n Search Commands \n\t 7. Search by Name \n\t 8. Search by keyword");
        scanf("%d",&input);


        //printf("%d",input);
        switch (input)
        {

            case 1:
                InputNewEvent();
                break;

            case 2:
            FLUSH_STDIN(eventname);
                printf("\nEnter the event name to be deleted: ");
                fgets(eventname, sizeof(eventname), stdin);
                   if(DeleteEvent(eventname))
                       printf("Event %s successfully deleted",eventname);
                    break;
            case 4:
                PrintAll();
                break;



                case 3:
                    ModifyEvent();
                    break;



                case 5:
                    PrintTimeBlock();
                    break;

            case 7:
                SearchbyEventName();
                break;
            case 8:
                SearchKeyword();
                break;

                case 6:
                    PrintConflicts();
                    break;


            case 9:
                flag=false;
                WriteOutputFile(argc, argv);
                break;

            default:
                    printf("\n Error! Option between 1-9 is expected.");

        }

    }
    exit(0);
}
