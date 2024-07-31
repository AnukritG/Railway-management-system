#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

void viewInfo();
void bookTicket();
void cancelTicket();
void admin();
void verifyPassword();
void viewPassenger();
void addTrain();
void deleteTrain();
void writeAdminData();
void readAdminData();
void writeBookingData();
void readBookingData();

struct Train
{
    char serial[10];
    char trainNumber[10];
    char trainName[20];
    char start[10];
    char destination[10];
    char price[10];
    int seat;
    char time[10];
} trains[1000];

struct Ticket
{
    char trainNumber[20];
    char passengerName[20];
    char phone[20];
    char date[20];
    int seat;
} tickets[1000];

int trainCount = 0, ticketCount = 0;
char tempTrainNumber[100], tempName[100], tempPhone[100];

int main()
{
    readAdminData();
    readBookingData();
    system("COLOR 0f");
    int choice;
    time_t currentTime;
    time(&currentTime);
    printf("\n\t\t\t     %s\n",ctime(&currentTime));

    printf("\n\t\t\t=================================\n");
    printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
    printf("\t\t\t=================================\n\n\n");
    printf("\n\t\t\t[1] VIEW INFORMATION\n");
    printf("\n\t\t\t[2] BOOK TICKET\n");
    printf("\n\t\t\t[3] CANCEL TICKET\n");
    printf("\n\t\t\t[4] ADMIN");
    printf("\n\n\t\t\t[5] EXIT\n");
    printf("\n\t\t\t********************************");
    printf("\n\t\t\t********************************");
    printf("\n\t\t\tENTER YOUR CHOICE: ");

    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            viewInfo();
            break;
        case 2:
            bookTicket();
            break;
        case 3:
            cancelTicket();
            break;
        case 4:
            verifyPassword();
            break;
        case 5:
            system("cls");
            printf("\n\t\t\t=================================\n");
            printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
            printf("\t\t\t=================================");
            getch();
            exit(0);
            break;
        default:
            system("cls");
            printf("\n\t\t\t=================================\n");
            printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
            printf("\t\t\t=================================\n");
            printf("\n\n\t\t\t<<<<<<<<YOU ENTERED WRONG CHOICE>>>>>>>>\n");
            printf("\t\t\t<<<<<<<<PLEASE ENTER RIGHT THING>>>>>>>>\n");
            getch();
            system("cls");
            main();
    }
    return 0;
}

void bookTicket()
{
    int count, found = -1;
    char trainNumber[10];
    system("cls");
    readAdminData();
    printf("\n\t\t\t=================================\n");
    printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
    printf("\t\t\t=================================\n");
    printf("\n\n\t\t\tHow many tickets do you want to buy: ");
    scanf("%d", &count);
    for(int i = ticketCount; i < ticketCount + count; i++)
    {
        printf("\n\n\t\t\tEnter train number: ");
        scanf("%s", tickets[i].trainNumber);
        for(int j = 0; j < trainCount; j++)
        {
            if(strcmp(tickets[i].trainNumber, trains[j].trainNumber) == 0)
            {
                if(trains[j].seat == 0)
                {
                    printf("\n\n\t\t\tNo available seat");
                    getch();
                    system("cls");
                    main();
                }
                else
                {
                    found = 1;
                    printf("\n\t\t\tEnter booking details for ticket %d: ", i + 1);
                    printf("\n\t\t\tEnter date: ");
                    scanf("%s", tickets[i].date);
                    printf("\n\t\t\tEnter your name: ");
                    scanf("%s", tickets[i].passengerName);
                    printf("\n\t\t\tEnter your phone number: ");
                    scanf("%s", tickets[i].phone);
                    printf("\n\t\t\tSeat number: %d", trains[j].seat);
                    tickets[i].seat = trains[j].seat;
                    writeBookingData();
                    trains[j].seat--;
                    writeAdminData();
                }
            }
        }
        if(found == -1)
        {
            printf("\n\n\t\t\tTrain not found!!!");
            getch();
            system("cls");
            main();
        }
    }
    ticketCount += count;
    writeBookingData();
    printf("\n\n\t\t\tEnter '1' for main menu & press any key to exit: ");
    int ch;
    scanf("%d", &ch);
    if(ch == 1)
    {
        system("cls");
        main();
    }
    else
    {
        exit(0);
    }
}

void cancelTicket()
{
    readBookingData();
    char phoneNumber[100];
    int location = -1;
    printf("\n\n\t\t\tEnter phone number: ");
    scanf("%s", phoneNumber);
    for(int i = 0; i < ticketCount; i++)
    {
        if(strcmp(phoneNumber, tickets[i].phone) == 0)
        {
            location = i;
            break;
        }
    }
    if(location == -1)
    {
        printf("\n\n\t\t\t<<<<<<<<<<<<<<Data Not Found>>>>>>>>>>>>>>>>> \n");
        getch();
        system("cls");
        main();
    }
    else
    {
        for(int i = location; i < ticketCount - 1; i++)
        {
            tickets[i] = tickets[i + 1];
        }
        ticketCount--;
        writeBookingData();
        printf("\n\n\t\t\t<<<<<<<<<<<<<<<Ticket cancelled successfully>>>>>>>>>>>>");
        getch();
        system("cls");
        main();
    }
}

void admin()
{
    int choice;
    system("cls");
    printf("\n\t\t\t=================================\n");
    printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
    printf("\t\t\t=================================\n");
    printf("\n\n");
    printf("\n\n");
    printf("              ************************************\n");
    printf("              ||      CHOOSE YOUR LIST     ||\n");
    printf("              ||--------------------------------||\n");
    printf("              ||      [1] VIEW PASSENGERS       ||\n");
    printf("              ||      [2] ADD TRAIN             ||\n");
    printf("              ||      [3] DELETE TRAIN          ||\n");
    printf("              ||      [4] BACK                  ||\n");
    printf("              ||                                ||\n");
    printf("              ************************************\n\n");
    printf("     **********************************************************\n");
    printf("\n\t\tENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            viewPassenger();
            break;
        case 2:
            addTrain();
            break;
        case 3:
            deleteTrain();
            break;
        case 4:
            system("cls");
            getch();
            main();
            break;
        default:
            getch();
            printf("\n\t\t\tYou entered wrong key!!!!");
            getch();
            system("cls");
            main();
    }
    getch();
}

void verifyPassword()
{
    int defaultPassword = 1234567;
    int inputPassword;
    printf("\n\t\t\tEnter password: ");
    scanf("%d", &inputPassword);
    if(inputPassword == defaultPassword)
    {
        printf("\n\n\t\t\t<<<<<Login successfully>>>>>");
        getch();
        system("cls");
        admin();
    }
    else
    {
        printf("\n\n\t\t\t\t   ERROR!!!!!");
        printf("\n\n\t\t\t<<<<<<<<Wrong password>>>>>>>>");
        getch();
        system("cls");
        main();
    }
}

void deleteTrain()
{
    readAdminData();
    char trainNumber[100];
    int location = -1;
    printf("\n\n\tEnter train number: ");
    scanf("%s", trainNumber);
    for(int i = 0; i < trainCount; i++)
    {
        if(strcmp(trainNumber, trains[i].trainNumber) == 0)
        {
            location = i;
            break;
        }
    }
    if(location == -1)
    {
        printf("\n\n\t<<<<<<<<<<<<<<Data Not Found>>>>>>>>>>>>>>>>> \n");
        getch();
        system("cls");
        admin();
    }
    else
    {
        for(int i = location; i < trainCount - 1; i++)
        {
            trains[i] = trains[i + 1];
        }
        trainCount--;
        writeAdminData();
        printf("\n\n\t<<<<<<<<<<<<<Train deleted successfully>>>>>>>>>>>>>");
        getch();
        system("cls");
        admin();
    }
}

void viewPassenger()
{
    system("cls");
    readBookingData();
    printf("\n\t\t\t=================================\n");
    printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
    printf("\t\t\t=================================\n");
    printf("\n\n\t\t\tPASSENGERS DETAILS\n\n");
    printf("********************************************************************************\n");
    printf("TRAIN NO\t\tNAME\t\tPHONE\t\tDATE\t\tSEAT\n");
    printf("********************************************************************************\n");
    for(int i = 0; i < ticketCount; i++)
    {
        printf("%s\t\t%s\t\t%s\t\t%s\t\t%d\n", tickets[i].trainNumber, tickets[i].passengerName, tickets[i].phone, tickets[i].date, tickets[i].seat);
    }
    getch();
    system("cls");
    admin();
}

void addTrain()
{
    readAdminData();
    printf("\n\t\t\t=================================\n");
    printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
    printf("\t\t\t=================================\n");
    printf("\n\n\n");
    printf("\n\n\t\t\tHow many trains do you want to add: ");
    int count;
    scanf("%d", &count);
    for(int i = trainCount; i < trainCount + count; i++)
    {
        printf("\n\n\t\t\tEnter train number: ");
        scanf("%s", trains[i].trainNumber);
        printf("\n\t\t\tEnter train name: ");
        scanf("%s", trains[i].trainName);
        printf("\n\t\t\tEnter start place: ");
        scanf("%s", trains[i].start);
        printf("\n\t\t\tEnter destination place: ");
        scanf("%s", trains[i].destination);
        printf("\n\t\t\tEnter seat price: ");
        scanf("%s", trains[i].price);
        printf("\n\t\t\tEnter available seats: ");
        scanf("%d", &trains[i].seat);
        printf("\n\t\t\tEnter train time: ");
        scanf("%s", trains[i].time);
        printf("\n");
    }
    trainCount += count;
    writeAdminData();
    printf("\n\n\t\t\tEnter '1' for main menu & press any key to exit: ");
    int ch;
    scanf("%d", &ch);
    if(ch == 1)
    {
        system("cls");
        main();
    }
    else
    {
        exit(0);
    }
}

void viewInfo()
{
    system("cls");
    readAdminData();
    printf("\n\t\t\t=================================\n");
    printf("\t\t\t=   RAILWAY MANAGEMENT SYSTEM   =\n");
    printf("\t\t\t=================================\n\n\n");
    printf("\n\n\n\n");
    printf("**********************************************************************************************************\n");
    printf("%-10s%-20s%-15s%-15s%-10s%-10s%-10s\n", "TRAIN NO", "TRAIN NAME", "FROM", "TO", "PRICE", "SEAT", "TIME");
    printf("**********************************************************************************************************\n");
    for(int i = 0; i < trainCount; i++)
    {
        printf("%-10s%-20s%-15s%-15s%-10s%-10d%-10s\n", 
            trains[i].trainNumber, 
            trains[i].trainName, 
            trains[i].start, 
            trains[i].destination, 
            trains[i].price, 
            trains[i].seat, 
            trains[i].time);
    }
    getch();
    system("cls");
    main();
}


void writeAdminData()
{
    FILE *file = fopen("AdminData.dat", "wb");
    fwrite(&trainCount, sizeof(trainCount), 1, file);
    fwrite(trains, sizeof(struct Train), trainCount, file);
    fclose(file);
}

void readAdminData()
{
    FILE *file = fopen("AdminData.dat", "rb");
    if(file != NULL)
    {
        fread(&trainCount, sizeof(trainCount), 1, file);
        fread(trains, sizeof(struct Train), trainCount, file);
        fclose(file);
    }
}

void writeBookingData()
{
    FILE *file = fopen("BookingData.dat", "wb");
    fwrite(&ticketCount, sizeof(ticketCount), 1, file);
    fwrite(tickets, sizeof(struct Ticket), ticketCount, file);
    fclose(file);
}

void readBookingData()
{
    FILE *file = fopen("BookingData.dat", "rb");
    if(file != NULL)
    {
        fread(&ticketCount, sizeof(ticketCount), 1, file);
        fread(tickets, sizeof(struct Ticket), ticketCount, file);
        fclose(file);
    }
}
