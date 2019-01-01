#include <bits/stdc++.h>
#include <stdint.h>

using namespace std;
struct process {
    int arrTi;
    int procTi;
    int burTi;
    int waTi;
    int tuArTi;
    int name;
};
struct compare {
    bool operator() (const process* p1, const process* p2)
    {
        return p1->arrTi > p2->arrTi;
    }
};
int main()
{
    int totTi = 0;
    int totWaTi = 0;
    int  q8 = 0,q16 = 0,qfcfs = 0;
    int  tempTime = 0,tempTime2 = 0;
    int  procnum = 0;
    int totTuArTi = 0;
    process *temp;


    priority_queue<process*,vector<process*>, compare> queue8;
    priority_queue<process*,vector<process*>, compare> queue16;
    priority_queue<process*,vector<process*>, compare> queuefcfs;

    cout<< "Enter The Number Of Process : " <<endl;
    cin>> procnum;

    for (int i=1 ;i<=procnum;i++){

        temp = new process();
        cout << "Enter process "<< i<< " arrival-time: ";
        cin >> temp->arrTi;

        cout << "Enter process "<< i<< " burst-time: ";
         cin>> temp->procTi;

        temp->name = i ;
        temp->waTi = 0;
        temp->burTi = temp->procTi;
         temp->tuArTi = 0;
        queue8.push(temp);

    }

    while (!queue8.empty() || !queue16.empty() || !queuefcfs.empty())
    {
        while (!queue8.empty()) {

            temp = queue8.top();
            tempTime = temp->procTi;
            if (temp->arrTi > totTi)
            {
                if (queue16.empty() && queuefcfs.empty())
                    totTi = temp->arrTi;
                else break;
            }

            temp->procTi -= 8;
            tempTime2 = temp->procTi;

            queue8.pop();

            totTi += (tempTime > 8) ? 8:tempTime;
            q8 += (tempTime > 8) ? 8:tempTime;

            if (tempTime2 <= 0)
            {
                if (totTi != 0)
                    temp->waTi = totTi - temp->arrTi  - temp->burTi;
                     temp->tuArTi = temp->waTi + temp->burTi;
                cout << "Process " << temp->name << " has finished with waiting time: " << temp->waTi  <<" and turnaround time: " << temp->tuArTi << " From Queue 8 "  << endl;

                totTuArTi += temp->tuArTi;
                totWaTi += temp->waTi;

            }
            else
            {
                queue16.push(temp);
            }

        }

       // cout <<"waiting time of queue 8 "<< totalWaitTime<<endl;

        while (!queue16.empty()) {

            temp = queue16.top();
            tempTime = temp->procTi;
            temp->procTi -= 16;
            tempTime2 = temp->procTi;
            queue16.pop();
            totTi += (tempTime > 16) ? 16:tempTime;
            q16 += (tempTime > 16) ? 16:tempTime;
            if (tempTime2 <= 0)
            {
                if (totTi != 0) temp->waTi = totTi - temp->arrTi - temp->burTi;
                temp->tuArTi = temp->waTi + temp->burTi;
                cout << "Process " << temp->name << " finished with waiting time: " << temp->waTi << " and turnaround time: " << temp->tuArTi << " From Queue 16 "  <<  endl;
                totTuArTi += temp->tuArTi;
                totWaTi += temp->waTi;

            }
            else
            {
                queuefcfs.push(temp);
            }

        }
       // cout <<"waiting time of queue 16 "<< totalWaitTime<< endl;

        while (!queuefcfs.empty()) {


            temp = queuefcfs.top();
            totTi += temp->procTi;
            qfcfs += temp->procTi;
            temp->waTi = totTi - temp->arrTi - temp->burTi;
            queuefcfs.pop();
            temp->tuArTi = temp->waTi + temp->burTi;
            cout << "Process " << temp->name << "  finished with waiting time: " << temp->waTi<< " and turnaround time: " << temp->tuArTi << " From Queue FCFS " <<  endl;
            totTuArTi += temp->tuArTi;
            totWaTi += temp->waTi;

        }
    }
    cout <<"the total waiting time "<< totWaTi<< endl
    << "Total turnaround time: " << totTuArTi << endl;
    cout << "The average waiting time is: " << (double)totWaTi/procnum<<
    endl << "The average turnaround time is: " << (double)totTuArTi/procnum;;
    return 0;
}
