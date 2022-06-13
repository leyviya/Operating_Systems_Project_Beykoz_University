#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct process{
	int no;
	int burst;
	int wait;
	int arrival;
	int turn_around;
};

void SJF(process*,int);
void print_gantt_chart(vector<process>, int);
void print_table(vector<process>,int);

int main(){
	int n;
	cout<<"Enter total number of processes: ";
	cin>>n;
	process p[n],temp[n];
	for (int i=0;i<n;i++){
		p[i].no=i+1;
		temp[i].no=i+1;
		cout<<i+1<<" process details: \n";
		cout<<"Enter arrival time and burst time: ";
		cin>>p[i].arrival;
		temp[i].arrival=p[i].arrival;
		cin>>p[i].burst;
		temp[i].burst=p[i].burst;
		p[i].wait=0;
		p[i].turn_around=0;
		temp[i].wait=0;
		temp[i].turn_around=0;
	}
	SJF(p,n);
}


bool cmp(process p1,process p2){
	if (p1.arrival==p2.arrival){
		if (p1.burst==p2.burst){
			return p1.no<p2.no;
		}
		return p1.burst<p2.burst;
	}
	return p1.arrival<p2.arrival;
}

bool cmp1(process p1,process p2){
	return p1.no<p2.no;
}



void SJF(process p[],int n){
	process temp[n];
	cout<<"\n\t\tShortest Job First\n\t\t******************";
	for(int i=0;i<n;i++){
		temp[i].no=p[i].no;
		temp[i].arrival=p[i].arrival;
		temp[i].wait=p[i].wait;
		temp[i].burst=p[i].burst;
		temp[i].turn_around=p[i].turn_around;
	}
	sort(temp,temp+n,cmp);
	vector<process> op;
	for (int i=0;i<n;i++){
		op.push_back(temp[i]);
		for (int j=i+1;j<n;j++){
			temp[j].arrival-=temp[i].burst;
			if (temp[j].arrival<0){
				temp[j].arrival=0;
			}
		}
		sort(temp+i+1,temp+n,cmp);
	}
	for(int i=0;i<n;i++){
		op[i].arrival=p[op[i].no-1].arrival;
		if (i!=0){
			op[i].wait=op[i-1].turn_around-op[i].arrival+op[i-1].arrival;
			op[i].turn_around=op[i].wait+op[i].burst;
		}
		else{
			op[i].turn_around=op[i].burst;
		}
	}
	int sum_waiting_time = 0, sum_turnaround_time=0;
	for(int i=0; i<n; i++) {
            sum_waiting_time += op[i].wait;
            sum_turnaround_time += op[i].turn_around;
    }
    cout<<endl;
    print_table(op,n);
    printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
    printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double) n);
    printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
    printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double) n);
	print_gantt_chart(op,n);
}

void print_table(vector<process> p, int n){
	sort(p.begin(),p.end(),cmp1);
    int i;
    cout<<"+-----+--------------+------------+--------------+-----------------+\n";
    cout<<"| PID | Arrival Time | Burst Time | Waiting Time | Turnaround Time |\n";
    cout<<"+-----+--------------+------------+--------------+-----------------+\n";

    for(i=0; i<n; i++) {
        printf("| %2d  |     %2d       |     %2d     |      %2d      |        %2d       |\n", p[i].no, p[i].arrival,p[i].burst, p[i].wait, p[i].turn_around);
        cout<<"+-----+--------------+------------+--------------+-----------------+\n";
    }
    cout<<"\n\n";
}

void print_gantt_chart(vector<process> p, int n){
	cout<<"\n          GANTT CHART          \n          ***********          \n";
    int i, j;
    printf("+");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst; j++) printf("--");
        printf("+");
    }
    printf("\n|");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst - 1; j++) printf(" ");
        printf("P%d", p[i].no);
        for(j=0; j<p[i].burst - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n+");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst; j++) printf("--");
        printf("+");
    }
    printf("\n0");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst; j++) printf("  ");
        if(p[i].turn_around+p[i].arrival > 9) printf("\b");
        printf("%d", p[i].turn_around+p[i].arrival);
    }
    printf("\n");
} 