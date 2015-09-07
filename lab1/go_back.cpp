#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;
pthread_t sender,receiver;
const int LIMIT=1000;
const int total_packets_on_receiver_side=15;
int sender_packet[LIMIT];
int receiver_packet[LIMIT];
int sender_count=0,receiver_count=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int timeout=0;
const int PROBABILITY_COUNT_MAX=10;
int PROBABILITY_COUNT;
int probability[PROBABILITY_COUNT_MAX];
int total_packet_sent=0;
time_t start,end;
int arg=0;
int packet_loss=0;
void initialize()
{
    srand(time(NULL));
    PROBABILITY_COUNT = rand()%10;
    for(int i=0;i<PROBABILITY_COUNT;++i)
    {
        probability[i]=rand()%(total_packets_on_receiver_side);
        cout<<probability[i]<<" ";
    }
    cout<<"\n\n";
    for(int i=0;i<LIMIT;++i)
    {
        sender_packet[i]=0;
        receiver_packet[i]=0;
    }
}

bool isLost(int a)
{
    for(int i=0;i<PROBABILITY_COUNT;++i)
    {
        if(a==probability[i])
        {
            probability[i]=-1;
            return true;
        }
    }
    return false;
}
void* sender_function(void* arg)
{
    cout<<"sender function\n";

    while(1)
    {
        //if(receiver_count>=total_packets_on_receiver_side)
        //pthread_exit((void*) arg);
       // sender_packet[sender_count]=1;
        pthread_mutex_lock(&mutex);
        cout<<"packet "<<sender_count<<" send-->\n";
        total_packet_sent++;
        sender_packet[sender_count]=1;
        pthread_mutex_unlock(&mutex);
        //sem_post(&scount);
        usleep(800000);
        if(!isLost(sender_count))
        sender_count++;
        else
        {
            cout<<"packet "<<sender_count+1<<" send but ";
            printf("\x1b[31mLOST\n\x1b[0m");
            sender_packet[sender_count+1]=0;
            sender_count=sender_count+2;
            packet_loss++;
        }


    }


}

void* receiver_function(void* arg)
{
    cout<<"receiver function\n";
    int previous=-1;
    int counter=0;
    while(counter++!=total_packets_on_receiver_side)
    {
        //sem_wait(&scount);
        usleep(1000000);
        if(sender_packet[receiver_count]==1)
        {
            receiver_packet[receiver_count]=1;
            cout<<"                     received "<<receiver_count<<"\n";
            receiver_count++;
        }
        else
        {
            cout<<"Waiting for packet "<<receiver_count<<"\n";
            sleep(2);
            printf("\x1b[31m\nTIMEOUT\nReturning to \x1b[0m");
            //cout<<"\n\nTIMEOUT\n Returning to ";
            cout<<receiver_count<<" packet\n\n";
            pthread_mutex_lock(&mutex);
            sender_count=receiver_count-1;
            pthread_mutex_unlock(&mutex);
        }
    }
}


int main()
{
    initialize();
	time(&start);
    pthread_create(&sender,NULL,sender_function,NULL);
    pthread_create(&receiver,NULL,receiver_function,NULL);
    //pthread_join(sender,NULL);
    pthread_join(receiver,NULL);
    time(&end);
    cout<<"Total packet sent ="<<total_packet_sent<<"\n";
    cout<<"total packet received ="<<receiver_count<<"\n";
    cout<<"total time taken = "<<end-start<<"\n";
    cout<<"average time taken for "<<receiver_count<<" packets to send "<<(end-start)<<" seconds\n";
    cout<<"packet lost by Network ="<<packet_loss<<"\n";
    cout<<"Total packet loss= "<<total_packet_sent-receiver_count<<"\n";
    cout<<"percentage of packet lost in NETWORK ="<<(100*((float)packet_loss/receiver_count))<<"\n";
    cout<<"average packet dealy "<<(float)(end-start)/receiver_count<<" seconds\n";
    return 0;
}



